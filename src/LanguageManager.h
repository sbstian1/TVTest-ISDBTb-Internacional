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


#ifndef TVTEST_LANGUAGE_MANAGER_H
#define TVTEST_LANGUAGE_MANAGER_H


#include <vector>
#include <unordered_map>


namespace TVTest
{

	class CLanguageManager
	{
	public:
		struct LanguageInfo
		{
			String Code;
			String Name;
			String FileName;
		};

		CLanguageManager();
		~CLanguageManager();

		bool Initialize(LPCTSTR pszDirectory);
		bool LoadLanguage(LPCTSTR pszLanguageCode);
		LPCTSTR GetCurrentLanguage() const { return m_CurrentLanguage.c_str(); }
		int GetLanguageCount() const { return static_cast<int>(m_LanguageList.size()); }
		const LanguageInfo *GetLanguageInfo(int Index) const;
		const LanguageInfo *GetLanguageInfoByCode(LPCTSTR pszCode) const;

		LPCTSTR Translate(LPCTSTR pszText) const;
		void TranslateDialog(HWND hDlg) const;
		void TranslateMenu(HMENU hMenu) const;

	private:
		String m_LanguagesDirectory;
		String m_CurrentLanguage;
		std::vector<LanguageInfo> m_LanguageList;
		std::unordered_map<std::wstring, std::wstring> m_TranslationMap;

		void EnsureDefaultLanguageFiles();
		void ScanLanguageFiles();
		bool ParseLanguageFile(LPCTSTR pszFilePath, bool fLoadStrings);
		static void CleanString(std::wstring &str);
	};

} // namespace TVTest


#endif
