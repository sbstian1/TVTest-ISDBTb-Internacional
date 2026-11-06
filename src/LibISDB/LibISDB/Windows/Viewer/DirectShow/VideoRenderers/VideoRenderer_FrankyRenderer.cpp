/*
  LibISDB
  Copyright(c) 2017-2020 DBCTRADO

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

/**
 @file   VideoRenderer_FrankyRenderer.cpp
 @brief  FrankyRenderer 映像レンダラ
 @author DBCTRADO
*/


#include "../../../../LibISDBPrivate.hpp"
#include "../../../../LibISDBWindows.hpp"
#include "VideoRenderer_FrankyRenderer.hpp"
#include "../../../../Base/DebugDef.hpp"


namespace LibISDB::DirectShow
{


// {B864E92A-1BDF-4DA1-9004-CBF467DF239A}
static const CLSID CLSID_FrankyRenderer = {0xB864E92A, 0x1BDF, 0x4DA1, {0x90, 0x04, 0xCB, 0xF4, 0x67, 0xDF, 0x23, 0x9A}};

static const LPCTSTR FRANKYR_VIDEO_WINDOW_CLASS = TEXT("LibISDB FrankyRenderer Video Window");


VideoRenderer_FrankyRenderer::VideoRenderer_FrankyRenderer()
	: VideoRenderer_Basic(CLSID_FrankyRenderer, LIBISDB_STR("FrankyRenderer"), true)
{
}


bool VideoRenderer_FrankyRenderer::Initialize(
	IGraphBuilder *pGraphBuilder, IPin *pInputPin, HWND hwndRender, HWND hwndMessageDrain)
{
	static bool Registered = false;
	HINSTANCE hinst = GetWindowInstance(hwndRender);

	if (!Registered) {
		WNDCLASS wc;

		wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = VideoWndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hinst;
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = ::CreateSolidBrush(RGB(0, 0, 0));
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = FRANKYR_VIDEO_WINDOW_CLASS;
		if (::RegisterClass(&wc) == 0) {
			SetWin32Error(::GetLastError(), LIBISDB_STR("No se pudo registrar la clase de ventana de FrankyRenderer."));
			return false;
		}
		Registered = true;
	}

	m_hwndVideo = ::CreateWindowEx(
		0, FRANKYR_VIDEO_WINDOW_CLASS, nullptr,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 0, 0, 0, 0,
		hwndRender, nullptr, hinst, this);
	if (m_hwndVideo == nullptr) {
		SetWin32Error(::GetLastError(), LIBISDB_STR("No se pudo crear la ventana de FrankyRenderer."));
		return false;
	}

	if (!VideoRenderer_Basic::Initialize(pGraphBuilder, pInputPin, m_hwndVideo, m_hwndVideo)) {
		::DestroyWindow(m_hwndVideo);
		m_hwndVideo = nullptr;
		return false;
	}

	m_hwndRender = hwndRender;
	m_hwndMessageDrain = hwndMessageDrain;

	return true;
}


bool VideoRenderer_FrankyRenderer::Finalize()
{
	VideoRenderer_Basic::Finalize();

	if (m_hwndVideo != nullptr) {
		::DestroyWindow(m_hwndVideo);
		m_hwndVideo = nullptr;
	}

	return true;
}


bool VideoRenderer_FrankyRenderer::SetVideoPosition(
	int SourceWidth, int SourceHeight, const RECT &SourceRect,
	const RECT &DestRect, const RECT &WindowRect)
{
	if (m_hwndVideo == nullptr)
		return false;

	RECT rcDest = DestRect;
	::OffsetRect(&rcDest, WindowRect.left, WindowRect.top);

	::SetWindowPos(
		m_hwndVideo, HWND_BOTTOM,
		rcDest.left, rcDest.top,
		rcDest.right - rcDest.left, rcDest.bottom - rcDest.top,
		SWP_NOACTIVATE | SWP_ASYNCWINDOWPOS | SWP_NOREDRAW);

	::OffsetRect(&rcDest, -rcDest.left, -rcDest.top);

	return VideoRenderer_Basic::SetVideoPosition(SourceWidth, SourceHeight, SourceRect, rcDest, rcDest);
}


bool VideoRenderer_FrankyRenderer::GetDestPosition(ReturnArg<RECT> Rect)
{
	if (!Rect)
		return false;

	if (m_hwndVideo != nullptr) {
		if (::GetWindowRect(m_hwndVideo, &*Rect)) {
			::MapWindowRect(nullptr, m_hwndRender, &*Rect);
			return true;
		}
	}

	::SetRectEmpty(&*Rect);

	return false;
}


bool VideoRenderer_FrankyRenderer::ShowCursor(bool Show)
{
	m_ShowCursor = Show;

	return true;
}


bool VideoRenderer_FrankyRenderer::SetVisible(bool Visible)
{
	if (m_hwndVideo == nullptr)
		return false;
	return ::ShowWindow(m_hwndVideo, Visible ? SW_SHOW : SW_HIDE) != FALSE;
}


const CLSID & VideoRenderer_FrankyRenderer::GetCLSID()
{
	return CLSID_FrankyRenderer;
}


VideoRenderer_FrankyRenderer * VideoRenderer_FrankyRenderer::GetThis(HWND hwnd)
{
	return reinterpret_cast<VideoRenderer_FrankyRenderer *>(::GetWindowLongPtr(hwnd, GWLP_USERDATA));
}


LRESULT CALLBACK VideoRenderer_FrankyRenderer::VideoWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		{
			VideoRenderer_FrankyRenderer *pThis = static_cast<VideoRenderer_FrankyRenderer *>(
				reinterpret_cast<const CREATESTRUCT *>(lParam)->lpCreateParams);

			::SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
		}
		return 0;

	case WM_CHAR:
	case WM_DEADCHAR:
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSCHAR:
	case WM_SYSDEADCHAR:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_MOUSEACTIVATE:
	case WM_NCLBUTTONDBLCLK:
	case WM_NCLBUTTONDOWN:
	case WM_NCLBUTTONUP:
	case WM_NCRBUTTONDBLCLK:
	case WM_NCRBUTTONDOWN:
	case WM_NCRBUTTONUP:
	case WM_NCMBUTTONDBLCLK:
	case WM_NCMBUTTONDOWN:
	case WM_NCMBUTTONUP:
	case WM_NCMOUSEMOVE:
		{
			VideoRenderer_FrankyRenderer *pThis = GetThis(hwnd);

			if (pThis->m_hwndMessageDrain) {
				::PostMessage(pThis->m_hwndMessageDrain, uMsg, wParam, lParam);
				return 0;
			}
		}
		break;

	case WM_LBUTTONDBLCLK:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEMOVE:
		{
			VideoRenderer_FrankyRenderer *pThis = GetThis(hwnd);

			if (pThis->m_hwndMessageDrain) {
				POINT pt = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};

				::MapWindowPoints(hwnd, pThis->m_hwndMessageDrain, &pt, 1);
				::PostMessage(pThis->m_hwndMessageDrain, uMsg, wParam, MAKELPARAM(pt.x, pt.y));
				return 0;
			}
		}
		break;

	case WM_SETCURSOR:
		if (LOWORD(lParam) == HTCLIENT) {
			VideoRenderer_FrankyRenderer *pThis = GetThis(hwnd);

			::SetCursor(pThis->m_ShowCursor ? ::LoadCursor(nullptr, IDC_ARROW) : nullptr);
			return TRUE;
		}
		break;

	case WM_DESTROY:
		{
			VideoRenderer_FrankyRenderer *pThis = GetThis(hwnd);

			pThis->m_hwndVideo = nullptr;
		}
		return 0;
	}

	return ::DefWindowProc(hwnd, uMsg, wParam, lParam);
}


} // namespace LibISDB::DirectShow
