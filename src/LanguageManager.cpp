/*
  TVTest
  Copyright(c) 2008-2020 DBCTRADO

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


#include "stdafx.h"
#include "TVTest.h"
#include "AppMain.h"
#include "LanguageManager.h"
#include "PathUtil.h"
#include <algorithm>


namespace TVTest
{

	CLanguageManager::CLanguageManager()
	{
	}

	CLanguageManager::~CLanguageManager()
	{
	}

	bool CLanguageManager::Initialize(LPCTSTR pszDirectory)
	{
		if (IsStringEmpty(pszDirectory))
			return false;

		TCHAR szPath[MAX_PATH];
		::PathCombine(szPath, pszDirectory, TEXT("Languages"));
		m_LanguagesDirectory = szPath;

		if (!::PathIsDirectory(m_LanguagesDirectory.c_str())) {
			::CreateDirectory(m_LanguagesDirectory.c_str(), nullptr);
		}

		EnsureDefaultLanguageFiles();
		ScanLanguageFiles();
		return true;
	}

	void CLanguageManager::CleanString(std::wstring &str)
	{
		// Trim whitespace
		const size_t first = str.find_first_not_of(L" \t\r\n");
		if (first == std::wstring::npos) {
			str.clear();
			return;
		}
		const size_t last = str.find_last_not_of(L" \t\r\n");
		str = str.substr(first, last - first + 1);

		// Remove optional enclosing quotes
		if (str.length() >= 2 && str.front() == L'"' && str.back() == L'"') {
			str = str.substr(1, str.length() - 2);
		}

		// Process escape sequences \n and \t
		size_t pos = 0;
		while ((pos = str.find(L"\\n", pos)) != std::wstring::npos) {
			str.replace(pos, 2, L"\n");
			pos += 1;
		}
		pos = 0;
		while ((pos = str.find(L"\\t", pos)) != std::wstring::npos) {
			str.replace(pos, 2, L"\t");
			pos += 1;
		}
	}

	bool CLanguageManager::ParseLanguageFile(LPCTSTR pszFilePath, bool fLoadStrings)
	{
		HANDLE hFile = ::CreateFile(
			pszFilePath, GENERIC_READ, FILE_SHARE_READ, nullptr,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (hFile == INVALID_HANDLE_VALUE)
			return false;

		LARGE_INTEGER FileSize;
		if (!::GetFileSizeEx(hFile, &FileSize) || FileSize.QuadPart <= 0 || FileSize.QuadPart > 10 * 1024 * 1024) {
			::CloseHandle(hFile);
			return false;
		}

		std::vector<BYTE> buffer(static_cast<size_t>(FileSize.QuadPart) + 2, 0);
		DWORD dwRead = 0;
		if (!::ReadFile(hFile, buffer.data(), static_cast<DWORD>(FileSize.QuadPart), &dwRead, nullptr) || dwRead == 0) {
			::CloseHandle(hFile);
			return false;
		}
		::CloseHandle(hFile);

		std::wstring text;
		if (buffer.size() >= 2 && buffer[0] == 0xFF && buffer[1] == 0xFE) {
			// UTF-16 LE
			const wchar_t *pWide = reinterpret_cast<const wchar_t*>(buffer.data() + 2);
			size_t wideLen = (dwRead - 2) / sizeof(wchar_t);
			text.assign(pWide, wideLen);
		} else {
			// UTF-8 (check BOM)
			size_t offset = 0;
			if (buffer.size() >= 3 && buffer[0] == 0xEF && buffer[1] == 0xBB && buffer[2] == 0xBF) {
				offset = 3;
			}
			const char *pUtf8 = reinterpret_cast<const char*>(buffer.data() + offset);
			int utf8Len = static_cast<int>(dwRead - offset);
			int wideLen = ::MultiByteToWideChar(CP_UTF8, 0, pUtf8, utf8Len, nullptr, 0);
			if (wideLen > 0) {
				text.resize(wideLen);
				::MultiByteToWideChar(CP_UTF8, 0, pUtf8, utf8Len, &text[0], wideLen);
			}
		}

		if (text.empty())
			return false;

		std::wstring curSection;
		LanguageInfo info;
		info.FileName = pszFilePath;

		size_t start = 0;
		while (start < text.length()) {
			size_t end = text.find_first_of(L"\r\n", start);
			if (end == std::wstring::npos)
				end = text.length();

			std::wstring line = text.substr(start, end - start);
			start = (end < text.length() && text[end] == L'\r' && end + 1 < text.length() && text[end + 1] == L'\n')
				? end + 2 : end + 1;

			// Trim leading whitespace
			size_t first = line.find_first_not_of(L" \t");
			if (first == std::wstring::npos || line[first] == L';' || line[first] == L'#')
				continue;

			line = line.substr(first);

			if (line.front() == L'[' && line.back() == L']') {
				curSection = line.substr(1, line.length() - 2);
				continue;
			}

			size_t eqPos = line.find(L'=');
			if (eqPos == std::wstring::npos)
				continue;

			std::wstring key = line.substr(0, eqPos);
			std::wstring val = line.substr(eqPos + 1);
			CleanString(key);
			CleanString(val);

			if (key.empty())
				continue;

			if (_wcsicmp(curSection.c_str(), L"Language") == 0) {
				if (_wcsicmp(key.c_str(), L"Name") == 0)
					info.Name = val.c_str();
				else if (_wcsicmp(key.c_str(), L"Code") == 0)
					info.Code = val.c_str();
			} else if (fLoadStrings && _wcsicmp(curSection.c_str(), L"Strings") == 0) {
				m_TranslationMap[key] = val;
			}
		}

		if (!fLoadStrings && !info.Name.empty()) {
			if (info.Code.empty()) {
				// Use file name without extension as code
				TCHAR szFile[MAX_PATH];
				::lstrcpy(szFile, pszFilePath);
				::PathRemoveExtension(szFile);
				info.Code = ::PathFindFileName(szFile);
			}
			m_LanguageList.push_back(info);
		}

		return true;
	}

	void CLanguageManager::EnsureDefaultLanguageFiles()
	{
		static const struct {
			const TCHAR *Code;
			const TCHAR *Name;
		} DefaultLangs[] = {
			{ TEXT("es-ES"), TEXT("Español") },
			{ TEXT("pt-BR"), TEXT("Português") },
			{ TEXT("en-US"), TEXT("English") },
			{ TEXT("ja-JP"), TEXT("日本語") },
		};

		for (const auto &def : DefaultLangs) {
			TCHAR szFilePath[MAX_PATH];
			String FileName = def.Code;
			FileName += TEXT(".ini");
			::PathCombine(szFilePath, m_LanguagesDirectory.c_str(), FileName.c_str());

			if (!::PathFileExists(szFilePath)) {
				HANDLE hFile = ::CreateFile(
					szFilePath, GENERIC_WRITE, 0, nullptr,
					CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
				if (hFile != INVALID_HANDLE_VALUE) {
					std::string header = "; TVTest Language File\r\n[Language]\r\nName=";
					char szNameUtf8[128] = {};
					::WideCharToMultiByte(CP_UTF8, 0, def.Name, -1, szNameUtf8, sizeof(szNameUtf8), nullptr, nullptr);
					char szCodeUtf8[64] = {};
					::WideCharToMultiByte(CP_UTF8, 0, def.Code, -1, szCodeUtf8, sizeof(szCodeUtf8), nullptr, nullptr);
					header += szNameUtf8;
					header += "\r\nCode=";
					header += szCodeUtf8;
					header += "\r\n\r\n[Strings]\r\n";

					DWORD written = 0;
					::WriteFile(hFile, header.c_str(), static_cast<DWORD>(header.length()), &written, nullptr);
					::CloseHandle(hFile);
				}
			}
		}
	}

	void CLanguageManager::ScanLanguageFiles()
	{
		m_LanguageList.clear();

		if (::PathIsDirectory(m_LanguagesDirectory.c_str())) {
			TCHAR szPattern[MAX_PATH];
			::PathCombine(szPattern, m_LanguagesDirectory.c_str(), TEXT("*.ini"));

			WIN32_FIND_DATA fd;
			HANDLE hFind = ::FindFirstFile(szPattern, &fd);
			if (hFind != INVALID_HANDLE_VALUE) {
				do {
					if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
						TCHAR szFile[MAX_PATH];
						::PathCombine(szFile, m_LanguagesDirectory.c_str(), fd.cFileName);
						ParseLanguageFile(szFile, false);
					}
				} while (::FindNextFile(hFind, &fd));
				::FindClose(hFind);
			}
		}

		// Ensure the 4 primary languages are registered
		static const struct {
			const TCHAR *Code;
			const TCHAR *Name;
		} DefaultLangs[] = {
			{ TEXT("es-ES"), TEXT("Español") },
			{ TEXT("pt-BR"), TEXT("Português") },
			{ TEXT("en-US"), TEXT("English") },
			{ TEXT("ja-JP"), TEXT("日本語") },
		};

		for (const auto &def : DefaultLangs) {
			bool found = false;
			for (const auto &item : m_LanguageList) {
				if (_wcsicmp(item.Code.c_str(), def.Code) == 0) {
					found = true;
					break;
				}
			}
			if (!found) {
				LanguageInfo info;
				info.Code = def.Code;
				info.Name = def.Name;
				TCHAR szFile[MAX_PATH];
				String Format;
				Format = def.Code;
				Format += TEXT(".ini");
				::PathCombine(szFile, m_LanguagesDirectory.c_str(), Format.c_str());
				info.FileName = szFile;
				m_LanguageList.push_back(info);
			}
		}
	}

	const CLanguageManager::LanguageInfo *CLanguageManager::GetLanguageInfo(int Index) const
	{
		if (Index < 0 || Index >= static_cast<int>(m_LanguageList.size()))
			return nullptr;
		return &m_LanguageList[Index];
	}

	const CLanguageManager::LanguageInfo *CLanguageManager::GetLanguageInfoByCode(LPCTSTR pszCode) const
	{
		if (IsStringEmpty(pszCode))
			return nullptr;
		for (const auto &info : m_LanguageList) {
			if (_wcsicmp(info.Code.c_str(), pszCode) == 0)
				return &info;
		}
		return nullptr;
	}

	bool CLanguageManager::LoadLanguage(LPCTSTR pszLanguageCode)
	{
		m_TranslationMap.clear();

		if (IsStringEmpty(pszLanguageCode))
			pszLanguageCode = TEXT("es-ES");

		m_CurrentLanguage = pszLanguageCode;

		const LanguageInfo *pInfo = GetLanguageInfoByCode(pszLanguageCode);
		if (pInfo != nullptr && ::PathFileExists(pInfo->FileName.c_str())) {
			return ParseLanguageFile(pInfo->FileName.c_str(), true);
		}

		return false;
	}

	LPCTSTR CLanguageManager::Translate(LPCTSTR pszText) const
	{
		if (IsStringEmpty(pszText) || m_TranslationMap.empty())
			return pszText;

		auto it = m_TranslationMap.find(pszText);
		if (it != m_TranslationMap.end() && !it->second.empty())
			return it->second.c_str();

		return pszText;
	}

	void CLanguageManager::TranslateDialog(HWND hDlg) const
	{
		if (hDlg == nullptr || m_TranslationMap.empty())
			return;

		// Translate dialog window title
		wchar_t szTitle[512];
		if (::GetWindowText(hDlg, szTitle, 512) > 0) {
			auto it = m_TranslationMap.find(szTitle);
			if (it != m_TranslationMap.end() && !it->second.empty()) {
				::SetWindowText(hDlg, it->second.c_str());
			}
		}

		// Translate all child controls (buttons, checkboxes, labels, group boxes, tabs, listviews)
		::EnumChildWindows(
			hDlg,
			[](HWND hwndChild, LPARAM lParam) -> BOOL {
				const auto *pMap = reinterpret_cast<const std::unordered_map<std::wstring, std::wstring>*>(lParam);
				wchar_t szText[512];
				const int len = ::GetWindowText(hwndChild, szText, 512);
				if (len > 0) {
					auto it = pMap->find(szText);
					if (it != pMap->end() && !it->second.empty()) {
						::SetWindowText(hwndChild, it->second.c_str());
					}
				}

				wchar_t szClassName[64] = {};
				if (::GetClassName(hwndChild, szClassName, 64) > 0) {
					if (_wcsicmp(szClassName, WC_TABCONTROL) == 0) {
						const int tabCount = TabCtrl_GetItemCount(hwndChild);
						for (int t = 0; t < tabCount; t++) {
							wchar_t szTabText[256] = {};
							TCITEM tci = {};
							tci.mask = TCIF_TEXT;
							tci.pszText = szTabText;
							tci.cchTextMax = 255;
							if (TabCtrl_GetItem(hwndChild, t, &tci)) {
								auto itTab = pMap->find(szTabText);
								if (itTab != pMap->end() && !itTab->second.empty()) {
									tci.pszText = const_cast<wchar_t*>(itTab->second.c_str());
									TabCtrl_SetItem(hwndChild, t, &tci);
								}
							}
						}
					} else if (_wcsicmp(szClassName, WC_LISTVIEW) == 0) {
						HWND hwndHeader = ListView_GetHeader(hwndChild);
						if (hwndHeader != nullptr) {
							const int colCount = Header_GetItemCount(hwndHeader);
							for (int c = 0; c < colCount; c++) {
								wchar_t szColText[256] = {};
								HDITEM hdi = {};
								hdi.mask = HDI_TEXT;
								hdi.pszText = szColText;
								hdi.cchTextMax = 255;
								if (Header_GetItem(hwndHeader, c, &hdi)) {
									auto itCol = pMap->find(szColText);
									if (itCol != pMap->end() && !itCol->second.empty()) {
										hdi.pszText = const_cast<wchar_t*>(itCol->second.c_str());
										Header_SetItem(hwndHeader, c, &hdi);
									}
								}
							}
						}
					}
				}
				return TRUE;
			},
			reinterpret_cast<LPARAM>(&m_TranslationMap));
	}

	void CLanguageManager::TranslateMenu(HMENU hMenu) const
	{
		if (hMenu == nullptr || m_TranslationMap.empty())
			return;

		const int count = ::GetMenuItemCount(hMenu);
		for (int i = 0; i < count; i++) {
			MENUITEMINFO mii = {};
			mii.cbSize = sizeof(mii);
			mii.fMask = MIIM_STRING | MIIM_SUBMENU | MIIM_FTYPE;

			wchar_t szText[512] = {};
			mii.dwTypeData = szText;
			mii.cch = 511;

			if (::GetMenuItemInfo(hMenu, i, TRUE, &mii)) {
				if ((mii.fType & MFT_SEPARATOR) == 0 && mii.cch > 0) {
					auto it = m_TranslationMap.find(szText);
					if (it != m_TranslationMap.end() && !it->second.empty()) {
						mii.fMask = MIIM_STRING;
						mii.dwTypeData = const_cast<wchar_t*>(it->second.c_str());
						::SetMenuItemInfo(hMenu, i, TRUE, &mii);
					} else {
						wchar_t *pTab = wcschr(szText, L'\t');
						if (pTab != nullptr) {
							std::wstring textOnly(szText, pTab - szText);
							auto it2 = m_TranslationMap.find(textOnly);
							if (it2 != m_TranslationMap.end() && !it2->second.empty()) {
								std::wstring newText = it2->second + pTab;
								mii.fMask = MIIM_STRING;
								mii.dwTypeData = const_cast<wchar_t*>(newText.c_str());
								::SetMenuItemInfo(hMenu, i, TRUE, &mii);
							}
						}
					}
				}
				if (mii.hSubMenu != nullptr) {
					TranslateMenu(mii.hSubMenu);
				}
			}
		}
	}

} // namespace TVTest
