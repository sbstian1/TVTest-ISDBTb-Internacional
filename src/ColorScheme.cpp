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
#include <algorithm>
#include "TVTest.h"
#include "AppMain.h"
#include "ColorScheme.h"
#include "Settings.h"
#include "ThemeManager.h"
#include "resource.h"
#include "Common/DebugDef.h"


namespace TVTest
{

namespace
{

static const LPCTSTR GradientDirectionList[] = {
	TEXT("horizontal"),
	TEXT("vertical"),
	TEXT("horizontal-mirror"),
	TEXT("vertical-mirror"),
};

static const LPCTSTR GradientTypeNameList[] = {
	TEXT("normal"),
	TEXT("glossy"),
	TEXT("interlaced"),
};

static const LPCTSTR FillTypeNameList[] = {
	TEXT("none"),
	TEXT("solid"),
	TEXT("gradient"),
};

static const LPCTSTR BorderTypeNameList[] = {
	TEXT("none"),
	TEXT("solid"),
	TEXT("sunken"),
	TEXT("raised"),
};


constexpr COLORREF HEXRGB(DWORD hex) { return RGB(hex >> 16, (hex >> 8) & 0xFF, hex & 0xFF); }

}


const CColorScheme::ColorInfo CColorScheme::m_ColorInfoList[NUM_COLORS] = {
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("StatusBack"),                         TEXT("Barra de estado: Fondo 1")},
	{HEXRGB(0x111111), CLR_INVALID,      TEXT("StatusBack2"),                        TEXT("Barra de estado: Fondo 2")},
	{HEXRGB(0x999999), CLR_INVALID,      TEXT("StatusText"),                         TEXT("Barra de estado: Texto")},
	{HEXRGB(0x777777), CLR_INVALID,      TEXT("StatusItemBorder"),                   TEXT("Barra de estado: Borde de elemento")},
	{HEXRGB(0x111111), CLR_INVALID,      TEXT("StatusBottomItemBack"),               TEXT("Barra de estado: Fondo inferior 1")},
	{HEXRGB(0x111111), CLR_INVALID,      TEXT("StatusBottomItemBack2"),              TEXT("Barra de estado: Fondo inferior 2")},
	{HEXRGB(0x999999), CLR_INVALID,      TEXT("StatusBottomItemText"),               TEXT("Barra de estado: Texto inferior")},
	{HEXRGB(0x111111), CLR_INVALID,      TEXT("StatusBottomItemBorder"),             TEXT("Barra de estado: Borde inferior")},
	{HEXRGB(0x4486E8), CLR_INVALID,      TEXT("StatusHighlightBack"),                TEXT("Barra de estado: Fondo sel. 1")},
	{HEXRGB(0x3C76CC), CLR_INVALID,      TEXT("StatusHighlightBack2"),               TEXT("Barra de estado: Fondo sel. 2")},
	{HEXRGB(0xDDDDDD), CLR_INVALID,      TEXT("StatusHighlightText"),                TEXT("Barra de estado: Texto seleccionado")},
	{HEXRGB(0x3C76CC), CLR_INVALID,      TEXT("StatusHighlightBorder"),              TEXT("Barra de estado: Borde seleccionado")},
	{HEXRGB(0x111111), CLR_INVALID,      TEXT("StatusBorder"),                       TEXT("Barra de estado: Borde exterior")},
	{HEXRGB(0xDF3F00), CLR_INVALID,      TEXT("StatusRecordingCircle"),              TEXT("Barra de estado: Indicador grab. ●")},
	{HEXRGB(0x444444), CLR_INVALID,      TEXT("StatusEventProgressBack"),            TEXT("Barra de estado: Progreso fondo 1")},
	{HEXRGB(0x444444), CLR_INVALID,      TEXT("StatusEventProgressBack2"),           TEXT("Barra de estado: Progreso fondo 2")},
	{HEXRGB(0x444444), CLR_INVALID,      TEXT("StatusEventProgressBorder"),          TEXT("Barra de estado: Progreso borde")},
	{HEXRGB(0x3465B0), CLR_INVALID,      TEXT("StatusEventProgressElapsed"),         TEXT("Barra de estado: Progreso barra 1")},
	{HEXRGB(0x3465B0), CLR_INVALID,      TEXT("StatusEventProgressElapsed2"),        TEXT("Barra de estado: Progreso barra 2")},
	{HEXRGB(0x3465B0), CLR_INVALID,      TEXT("StatusEventProgressElapsedBorder"),   TEXT("Barra de estado: Progreso barra borde")},
	{HEXRGB(0x222222), CLR_INVALID,      TEXT("Splitter"),                           TEXT("Línea divisoria")},
	{HEXRGB(0x000000), CLR_INVALID,      TEXT("ScreenBorder"),                       TEXT("Borde exterior de pantalla")},
	{HEXRGB(0x555555), CLR_INVALID,      TEXT("WindowFrame"),                        TEXT("Marco fino de ventana")},
	{HEXRGB(0x555555), CLR_INVALID,      TEXT("WindowFrameBorder"),                  TEXT("Borde del marco fino")},
	{HEXRGB(0x666666), CLR_INVALID,      TEXT("WindowActiveFrame"),                  TEXT("Marco activo de ventana")},
	{HEXRGB(0x666666), CLR_INVALID,      TEXT("WindowActiveFrameBorder"),            TEXT("Borde del marco activo")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("PanelBack"),                          TEXT("Panel: Fondo")},
	{HEXRGB(0x999999), CLR_INVALID,      TEXT("PanelText"),                          TEXT("Panel: Texto")},
	{HEXRGB(0x000000), CLR_INVALID,      TEXT("PanelTabBack"),                       TEXT("Panel: Fondo de pestaña 1")},
	{HEXRGB(0x222222), CLR_INVALID,      TEXT("PanelTabBack2"),                      TEXT("Panel: Fondo de pestaña 2")},
	{HEXRGB(0x888888), CLR_INVALID,      TEXT("PanelTabText"),                       TEXT("Panel: Texto de pestaña")},
	{HEXRGB(0x000000), CLR_INVALID,      TEXT("PanelTabBorder"),                     TEXT("Panel: Borde de pestaña")},
	{HEXRGB(0x555555), CLR_INVALID,      TEXT("PanelCurTabBack"),                    TEXT("Panel: Pestaña sel. fondo 1")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("PanelCurTabBack2"),                   TEXT("Panel: Pestaña sel. fondo 2")},
	{HEXRGB(0xAAAAAA), CLR_INVALID,      TEXT("PanelCurTabText"),                    TEXT("Panel: Pestaña sel. texto")},
	{HEXRGB(0x444444), CLR_INVALID,      TEXT("PanelCurTabBorder"),                  TEXT("Panel: Pestaña sel. borde")},
	{HEXRGB(0x000000), CLR_INVALID,      TEXT("PanelTabMargin"),                     TEXT("Panel: Margen de pestaña 1")},
	{HEXRGB(0x222222), CLR_INVALID,      TEXT("PanelTabMargin2"),                    TEXT("Panel: Margen de pestaña 2")},
	{HEXRGB(0x888888), CLR_INVALID,      TEXT("PanelTabMarginBorder"),               TEXT("Panel: Margen de pestaña borde")},
	{HEXRGB(0x444444), CLR_INVALID,      TEXT("PanelTabLine"),                       TEXT("Panel: Línea de pestañas")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("PanelTitleBack"),                     TEXT("Panel: Título fondo 1")},
	{HEXRGB(0x111111), CLR_INVALID,      TEXT("PanelTitleBack2"),                    TEXT("Panel: Título fondo 2")},
	{HEXRGB(0xAAAAAA), CLR_INVALID,      TEXT("PanelTitleText"),                     TEXT("Panel: Título texto")},
	{HEXRGB(0x111111), CLR_INVALID,      TEXT("PanelTitleBorder"),                   TEXT("Panel: Título borde")},
	{HEXRGB(0x111111), CLR_INVALID,      TEXT("ProgramInfoBack"),                    TEXT("Panel Info: Contenido fondo")},
	{HEXRGB(0xAAAAAA), CLR_INVALID,      TEXT("ProgramInfoText"),                    TEXT("Panel Info: Contenido texto")},
	{HEXRGB(0x111111), CLR_INVALID,      TEXT("ProgramInfoBorder"),                  TEXT("Panel Info: Contenido borde")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("InformationPanelButtonBack"),         TEXT("Panel Info: Botón fondo 1")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("InformationPanelButtonBack2"),        TEXT("Panel Info: Botón fondo 2")},
	{HEXRGB(0x999999), CLR_INVALID,      TEXT("InformationPanelButtonText"),         TEXT("Panel Info: Botón texto")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("InformationPanelButtonBorder"),       TEXT("Panel Info: Botón borde")},
	{HEXRGB(0x4486E8), CLR_INVALID,      TEXT("InformationPanelHotButtonBack"),      TEXT("Panel Info: Botón resaltado 1")},
	{HEXRGB(0x3C76CC), CLR_INVALID,      TEXT("InformationPanelHotButtonBack2"),     TEXT("Panel Info: Botón resaltado 2")},
	{HEXRGB(0xDDDDDD), CLR_INVALID,      TEXT("InformationPanelHotButtonText"),      TEXT("Panel Info: Botón resaltado texto")},
	{HEXRGB(0x3C76CC), CLR_INVALID,      TEXT("InformationPanelHotButtonBorder"),    TEXT("Panel Info: Botón resaltado borde")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("ProgramListChannelBack"),             TEXT("Panel Guía: Canal fondo 1")},
	{HEXRGB(0x000000), CLR_INVALID,      TEXT("ProgramListChannelBack2"),            TEXT("Panel Guía: Canal fondo 2")},
	{HEXRGB(0xAAAAAA), CLR_INVALID,      TEXT("ProgramListChannelText"),             TEXT("Panel Guía: Canal texto")},
	{HEXRGB(0x000000), CLR_INVALID,      TEXT("ProgramListChannelBorder"),           TEXT("Panel Guía: Canal borde")},
	{HEXRGB(0x4486E8), CLR_INVALID,      TEXT("ProgramListCurChannelBack"),          TEXT("Panel Guía: Canal actual fondo 1")},
	{HEXRGB(0x3C76CC), CLR_INVALID,      TEXT("ProgramListCurChannelBack2"),         TEXT("Panel Guía: Canal actual fondo 2")},
	{HEXRGB(0xDDDDDD), CLR_INVALID,      TEXT("ProgramListCurChannelText"),          TEXT("Panel Guía: Canal actual texto")},
	{HEXRGB(0x000000), CLR_INVALID,      TEXT("ProgramListCurChannelBorder"),        TEXT("Panel Guía: Canal actual borde")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("ProgramListChannelButtonBack"),       TEXT("Panel Guía: Botón fondo 1")},
	{HEXRGB(0x000000), CLR_INVALID,      TEXT("ProgramListChannelButtonBack2"),      TEXT("Panel Guía: Botón fondo 2")},
	{HEXRGB(0xAAAAAA), CLR_INVALID,      TEXT("ProgramListChannelButtonText"),       TEXT("Panel Guía: Botón texto")},
	{HEXRGB(0x000000), CLR_INVALID,      TEXT("ProgramListChannelButtonBorder"),     TEXT("Panel Guía: Botón borde")},
	{HEXRGB(0x4486E8), CLR_INVALID,      TEXT("ProgramListChannelButtonHotBack"),    TEXT("Panel Guía: Botón sel. fondo 1")},
	{HEXRGB(0x3C76CC), CLR_INVALID,      TEXT("ProgramListChannelButtonHotBack2"),   TEXT("Panel Guía: Botón sel. fondo 2")},
	{HEXRGB(0xDDDDDD), CLR_INVALID,      TEXT("ProgramListChannelButtonHotText"),    TEXT("Panel Guía: Botón sel. texto")},
	{HEXRGB(0x3C76CC), CLR_INVALID,      TEXT("ProgramListChannelButtonHotBorder"),  TEXT("Panel Guía: Botón sel. borde")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("ProgramListBack"),                    TEXT("Panel Guía: Evento fondo 1")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("ProgramListBack2"),                   TEXT("Panel Guía: Evento fondo 2")},
	{HEXRGB(0x999999), CLR_INVALID,      TEXT("ProgramListText"),                    TEXT("Panel Guía: Evento texto")},
	{HEXRGB(0x444444), CLR_INVALID,      TEXT("ProgramListBorder"),                  TEXT("Panel Guía: Evento borde")},
	{HEXRGB(0x222222), CLR_INVALID,      TEXT("ProgramListCurBack"),                 TEXT("Panel Guía: Evento actual fondo 1")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("ProgramListCurBack2"),                TEXT("Panel Guía: Evento actual fondo 2")},
	{HEXRGB(0xAAAAAA), CLR_INVALID,      TEXT("ProgramListCurText"),                 TEXT("Panel Guía: Evento actual texto")},
	{HEXRGB(0x555555), CLR_INVALID,      TEXT("ProgramListCurBorder"),               TEXT("Panel Guía: Evento actual borde")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("ProgramListTitleBack"),               TEXT("Panel Guía: Título fondo 1")},
	{HEXRGB(0x000000), CLR_INVALID,      TEXT("ProgramListTitleBack2"),              TEXT("Panel Guía: Título fondo 2")},
	{HEXRGB(0xAAAAAA), CLR_INVALID,      TEXT("ProgramListTitleText"),               TEXT("Panel Guía: Título texto")},
	{HEXRGB(0x000000), CLR_INVALID,      TEXT("ProgramListTitleBorder"),             TEXT("Panel Guía: Título borde")},
	{HEXRGB(0x4486E8), CLR_INVALID,      TEXT("ProgramListCurTitleBack"),            TEXT("Panel Guía: Título actual fondo 1")},
	{HEXRGB(0x3C76CC), CLR_INVALID,      TEXT("ProgramListCurTitleBack2"),           TEXT("Panel Guía: Título actual fondo 2")},
	{HEXRGB(0xDDDDDD), CLR_INVALID,      TEXT("ProgramListCurTitleText"),            TEXT("Panel Guía: Título actual texto")},
	{HEXRGB(0x000000), CLR_INVALID,      TEXT("ProgramListCurTitleBorder"),          TEXT("Panel Guía: Título actual borde")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("ChannelPanelChannelNameBack"),        TEXT("Panel Canales: Canal fondo 1")},
	{HEXRGB(0x000000), CLR_INVALID,      TEXT("ChannelPanelChannelNameBack2"),       TEXT("Panel Canales: Canal fondo 2")},
	{HEXRGB(0xAAAAAA), CLR_INVALID,      TEXT("ChannelPanelChannelNameText"),        TEXT("Panel Canales: Canal texto")},
	{HEXRGB(0x000000), CLR_INVALID,      TEXT("ChannelPanelChannelNameBorder"),      TEXT("Panel Canales: Canal borde")},
	{HEXRGB(0x4486E8), CLR_INVALID,      TEXT("ChannelPanelCurChannelNameBack"),     TEXT("Panel Canales: Canal actual fondo 1")},
	{HEXRGB(0x3C76CC), CLR_INVALID,      TEXT("ChannelPanelCurChannelNameBack2"),    TEXT("Panel Canales: Canal actual fondo 2")},
	{HEXRGB(0xDDDDDD), CLR_INVALID,      TEXT("ChannelPanelCurChannelNameText"),     TEXT("Panel Canales: Canal actual texto")},
	{HEXRGB(0x000000), CLR_INVALID,      TEXT("ChannelPanelCurChannelNameBorder"),   TEXT("Panel Canales: Canal actual borde")},
	{HEXRGB(0x444444), CLR_INVALID,      TEXT("ChannelPanelEventNameBack"),          TEXT("Panel Canales: Evento 1 fondo 1")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("ChannelPanelEventNameBack2"),         TEXT("Panel Canales: Evento 1 fondo 2")},
	{HEXRGB(0x999999), CLR_INVALID,      TEXT("ChannelPanelEventNameText"),          TEXT("Panel Canales: Evento 1 texto")},
	{HEXRGB(0x444444), CLR_INVALID,      TEXT("ChannelPanelEventNameBorder"),        TEXT("Panel Canales: Evento 1 borde")},
	{HEXRGB(0x222222), CLR_INVALID,      TEXT("ChannelPanelEventName2Back"),         TEXT("Panel Canales: Evento 2 fondo 1")},
	{HEXRGB(0x222222), CLR_INVALID,      TEXT("ChannelPanelEventName2Back2"),        TEXT("Panel Canales: Evento 2 fondo 2")},
	{HEXRGB(0x999999), CLR_INVALID,      TEXT("ChannelPanelEventName2Text"),         TEXT("Panel Canales: Evento 2 texto")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("ChannelPanelEventName2Border"),       TEXT("Panel Canales: Evento 2 borde")},
	{HEXRGB(0x444444), CLR_INVALID,      TEXT("ChannelPanelCurEventNameBack"),       TEXT("Panel Canales: Evento sel. 1 fondo 1")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("ChannelPanelCurEventNameBack2"),      TEXT("Panel Canales: Evento sel. 1 fondo 2")},
	{HEXRGB(0xAAAAAA), CLR_INVALID,      TEXT("ChannelPanelCurEventNameText"),       TEXT("Panel Canales: Evento sel. 1 texto")},
	{HEXRGB(0x444444), CLR_INVALID,      TEXT("ChannelPanelCurEventNameBorder"),     TEXT("Panel Canales: Evento sel. 1 borde")},
	{HEXRGB(0x222222), CLR_INVALID,      TEXT("ChannelPanelCurEventName2Back"),      TEXT("Panel Canales: Evento sel. 2 fondo 1")},
	{HEXRGB(0x222222), CLR_INVALID,      TEXT("ChannelPanelCurEventName2Back2"),     TEXT("Panel Canales: Evento sel. 2 fondo 2")},
	{HEXRGB(0xAAAAAA), CLR_INVALID,      TEXT("ChannelPanelCurEventName2Text"),      TEXT("Panel Canales: Evento sel. 2 texto")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("ChannelPanelCurEventName2Border"),    TEXT("Panel Canales: Evento sel. 2 borde")},
	{HEXRGB(0x00FF00), CLR_INVALID,      TEXT("ChannelPanelFeaturedMark"),           TEXT("Panel Canales: Marca destacada fondo 1")},
	{HEXRGB(0x00FF00), CLR_INVALID,      TEXT("ChannelPanelFeaturedMark2"),          TEXT("Panel Canales: Marca destacada fondo 2")},
	{HEXRGB(0x00BF00), CLR_INVALID,      TEXT("ChannelPanelFeaturedMarkBorder"),     TEXT("Panel Canales: Marca destacada borde")},
	{HEXRGB(0x2D5899), CLR_INVALID,      TEXT("ChannelPanelProgress"),               TEXT("Panel Canales: Progreso barra 1")},
	{HEXRGB(0x2D5899), CLR_INVALID,      TEXT("ChannelPanelProgress2"),              TEXT("Panel Canales: Progreso barra 2")},
	{HEXRGB(0x2D5899), CLR_INVALID,      TEXT("ChannelPanelProgressBorder"),         TEXT("Panel Canales: Progreso borde")},
	{HEXRGB(0x3465B0), CLR_INVALID,      TEXT("ChannelPanelCurProgress"),            TEXT("Panel Canales: Progreso sel. barra 1")},
	{HEXRGB(0x3465B0), CLR_INVALID,      TEXT("ChannelPanelCurProgress2"),           TEXT("Panel Canales: Progreso sel. barra 2")},
	{HEXRGB(0x3465B0), CLR_INVALID,      TEXT("ChannelPanelCurProgressBorder"),      TEXT("Panel Canales: Progreso sel. borde")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("ControlPanelBack"),                   TEXT("Panel Control: Fondo 1")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("ControlPanelBack2"),                  TEXT("Panel Control: Fondo 2")},
	{HEXRGB(0x999999), CLR_INVALID,      TEXT("ControlPanelText"),                   TEXT("Panel Control: Texto")},
	{HEXRGB(0x666666), CLR_INVALID,      TEXT("ControlPanelItemBorder"),             TEXT("Panel Control: Control borde")},
	{HEXRGB(0x4486E8), CLR_INVALID,      TEXT("ControlPanelHighlightBack"),          TEXT("Panel Control: Sel. fondo 1")},
	{HEXRGB(0x3C76CC), CLR_INVALID,      TEXT("ControlPanelHighlightBack2"),         TEXT("Panel Control: Sel. fondo 2")},
	{HEXRGB(0xDDDDDD), CLR_INVALID,      TEXT("ControlPanelHighlightText"),          TEXT("Panel Control: Sel. texto")},
	{HEXRGB(0x3C76CC), CLR_INVALID,      TEXT("ControlPanelHighlightBorder"),        TEXT("Panel Control: Sel. borde")},
	{HEXRGB(0x444444), CLR_INVALID,      TEXT("ControlPanelCheckedBack"),            TEXT("Panel Control: Marcado fondo 1")},
	{HEXRGB(0x555555), CLR_INVALID,      TEXT("ControlPanelCheckedBack2"),           TEXT("Panel Control: Marcado fondo 2")},
	{HEXRGB(0xDDDDDD), CLR_INVALID,      TEXT("ControlPanelCheckedText"),            TEXT("Panel Control: Marcado texto")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("ControlPanelCheckedBorder"),          TEXT("Panel Control: Marcado borde")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("ControlPanelMargin"),                 TEXT("Panel Control: Margen general")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("CaptionPanelBack"),                   TEXT("Panel Subtítulos: Fondo")},
	{HEXRGB(0x999999), CLR_INVALID,      TEXT("CaptionPanelText"),                   TEXT("Panel Subtítulos: Texto")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("TitleBarBack"),                       TEXT("Barra de título: Fondo 1")},
	{HEXRGB(0x111111), CLR_INVALID,      TEXT("TitleBarBack2"),                      TEXT("Barra de título: Fondo 2")},
	{HEXRGB(0xAAAAAA), CLR_INVALID,      TEXT("TitleBarText"),                       TEXT("Barra de título: Texto")},
	{HEXRGB(0x777777), CLR_INVALID,      TEXT("TitleBarTextBorder"),                 TEXT("Barra de título: Texto borde")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("TitleBarIconBack"),                   TEXT("Barra de título: Icono fondo 1")},
	{HEXRGB(0x111111), CLR_INVALID,      TEXT("TitleBarIconBack2"),                  TEXT("Barra de título: Icono fondo 2")},
	{HEXRGB(0x999999), CLR_INVALID,      TEXT("TitleBarIcon"),                       TEXT("Barra de título: Iconos")},
	{HEXRGB(0x777777), CLR_INVALID,      TEXT("TitleBarIconBorder"),                 TEXT("Barra de título: Icono borde")},
	{HEXRGB(0x4486E8), CLR_INVALID,      TEXT("TitleBarHighlightBack"),              TEXT("Barra de título: Resaltado fondo 1")},
	{HEXRGB(0x3C76CC), CLR_INVALID,      TEXT("TitleBarHighlightBack2"),             TEXT("Barra de título: Resaltado fondo 2")},
	{HEXRGB(0xDDDDDD), CLR_INVALID,      TEXT("TitleBarHighlightIcon"),              TEXT("Barra de título: Icono resaltado")},
	{HEXRGB(0x3C76CC), CLR_INVALID,      TEXT("TitleBarHighlightIconBorder"),        TEXT("Barra de título: Icono res. borde")},
	{HEXRGB(0x111111), CLR_INVALID,      TEXT("TitleBarBorder"),                     TEXT("Barra de título: Borde")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("SideBarBack"),                        TEXT("Barra lateral: Fondo 1")},
	{HEXRGB(0x111111), CLR_INVALID,      TEXT("SideBarBack2"),                       TEXT("Barra lateral: Fondo 2")},
	{HEXRGB(0xAAAAAA), CLR_INVALID,      TEXT("SideBarIcon"),                        TEXT("Barra lateral: Iconos")},
	{HEXRGB(0x777777), CLR_INVALID,      TEXT("SideBarItemBorder"),                  TEXT("Barra lateral: Control borde")},
	{HEXRGB(0x4486E8), CLR_INVALID,      TEXT("SideBarHighlightBack"),               TEXT("Barra lateral: Resaltado fondo 1")},
	{HEXRGB(0x3C76CC), CLR_INVALID,      TEXT("SideBarHighlightBack2"),              TEXT("Barra lateral: Resaltado fondo 2")},
	{HEXRGB(0xDDDDDD), CLR_INVALID,      TEXT("SideBarHighlightIcon"),               TEXT("Barra lateral: Icono resaltado")},
	{HEXRGB(0x3C76CC), CLR_INVALID,      TEXT("SideBarHighlightBorder"),             TEXT("Barra lateral: Resaltado borde")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("SideBarCheckBack"),                   TEXT("Barra lateral: Marcado fondo 1")},
	{HEXRGB(0x444444), CLR_INVALID,      TEXT("SideBarCheckBack2"),                  TEXT("Barra lateral: Marcado fondo 2")},
	{HEXRGB(0xAAAAAA), CLR_INVALID,      TEXT("SideBarCheckIcon"),                   TEXT("Barra lateral: Icono marcado")},
	{HEXRGB(0x222222), CLR_INVALID,      TEXT("SideBarCheckBorder"),                 TEXT("Barra lateral: Marcado borde")},
	{HEXRGB(0x111111), CLR_INVALID,      TEXT("SideBarBorder"),                      TEXT("Barra lateral: Borde")},
	{HEXRGB(0x222222), CLR_INVALID,      TEXT("NotificationBarBack"),                TEXT("Barra notif.: Fondo 1")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("NotificationBarBack2"),               TEXT("Barra notif.: Fondo 2")},
	{HEXRGB(0xBBBBBB), CLR_INVALID,      TEXT("NotificationBarText"),                TEXT("Barra notif.: Texto")},
	{HEXRGB(0xFF9F44), CLR_INVALID,      TEXT("NotificationBarWarningText"),         TEXT("Barra notif.: Advertencia texto")},
	{HEXRGB(0xFF4444), CLR_INVALID,      TEXT("NotificationBarErrorText"),           TEXT("Barra notif.: Error texto")},
	{HEXRGB(0x111111), HEXRGB(0xFFFFFF), TEXT("EventInfoPopupBack"),                 TEXT("Popup de evento: Fondo")},
	{HEXRGB(0xBBBBBB), HEXRGB(0x333333), TEXT("EventInfoPopupText"),                 TEXT("Popup de evento: Texto")},
	{HEXRGB(0xDDDDDD), HEXRGB(0x000000), TEXT("EventInfoPopupEventTitle"),           TEXT("Popup de evento: Título del programa")},
	{HEXRGB(0x333333), HEXRGB(0xFFFFFF), TEXT("ProgramGuideBack"),                   TEXT("Guía EPG: Fondo")},
	{HEXRGB(0x222222), HEXRGB(0x000000), TEXT("ProgramGuideText"),                   TEXT("Guía EPG: Contenido del programa")},
	{HEXRGB(0x000000), CLR_INVALID,      TEXT("ProgramGuideEventTitle"),             TEXT("Guía EPG: Nombre del programa")},
	{HEXRGB(0x0000BF), CLR_INVALID,      TEXT("ProgramGuideHighlightText"),          TEXT("Guía EPG: Búsqueda contenido texto")},
	{HEXRGB(0x0000FF), CLR_INVALID,      TEXT("ProgramGuideHighlightTitle"),         TEXT("Guía EPG: Búsqueda nombre texto")},
	{HEXRGB(0x9999FF), CLR_INVALID,      TEXT("ProgramGuideHighlightBack"),          TEXT("Guía EPG: Búsqueda fondo")},
	{HEXRGB(0x6666FF), CLR_INVALID,      TEXT("ProgramGuideHighlightBorder"),        TEXT("Guía EPG: Búsqueda borde")},
	{HEXRGB(0xCCFFCC), CLR_INVALID,      TEXT("ProgramGuideFeaturedMark"),           TEXT("Guía EPG: Marca destacada fondo 1")},
	{HEXRGB(0x99FF99), CLR_INVALID,      TEXT("ProgramGuideFeaturedMark2"),          TEXT("Guía EPG: Marca destacada fondo 2")},
	{HEXRGB(0x00EF00), CLR_INVALID,      TEXT("ProgramGuideFeaturedMarkBorder"),     TEXT("Guía EPG: Marca destacada borde")},
	{HEXRGB(0x333333), CLR_INVALID,      TEXT("ProgramGuideChannelBack"),            TEXT("Guía EPG: Canal fondo 1")},
	{HEXRGB(0x111111), CLR_INVALID,      TEXT("ProgramGuideChannelBack2"),           TEXT("Guía EPG: Canal fondo 2")},
	{HEXRGB(0x999999), CLR_INVALID,      TEXT("ProgramGuideChannelText"),            TEXT("Guía EPG: Canal texto")},
	{HEXRGB(0xDDDDDD), CLR_INVALID,      TEXT("ProgramGuideChannelHighlightText"),   TEXT("Guía EPG: Canal resaltado texto")},
	{HEXRGB(0x4486E8), CLR_INVALID,      TEXT("ProgramGuideCurChannelBack"),         TEXT("Guía EPG: Canal actual fondo 1")},
	{HEXRGB(0x3C76CC), CLR_INVALID,      TEXT("ProgramGuideCurChannelBack2"),        TEXT("Guía EPG: Canal actual fondo 2")},
	{HEXRGB(0xDDDDDD), CLR_INVALID,      TEXT("ProgramGuideCurChannelText"),         TEXT("Guía EPG: Canal actual texto")},
	{HEXRGB(0x333333), HEXRGB(0xFFFFFF), TEXT("ProgramGuideTimeBack"),               TEXT("Guía EPG: Fecha/Hora fondo 1")},
	{HEXRGB(0x111111), HEXRGB(0xDDDDDD), TEXT("ProgramGuideTimeBack2"),              TEXT("Guía EPG: Fecha/Hora fondo 2")},
	{HEXRGB(0x00337F), HEXRGB(0x004CBF), TEXT("ProgramGuideTime0To2Back"),           TEXT("Guía EPG: 00~02h fondo 1")},
	{HEXRGB(0x00193F), HEXRGB(0x00337F), TEXT("ProgramGuideTime0To2Back2"),          TEXT("Guía EPG: 00~02h fondo 2")},
	{HEXRGB(0x00667F), HEXRGB(0x0099BF), TEXT("ProgramGuideTime3To5Back"),           TEXT("Guía EPG: 03~05h fondo 1")},
	{HEXRGB(0x00333F), HEXRGB(0x00667F), TEXT("ProgramGuideTime3To5Back2"),          TEXT("Guía EPG: 03~05h fondo 2")},
	{HEXRGB(0x007F66), HEXRGB(0x00BF99), TEXT("ProgramGuideTime6To8Back"),           TEXT("Guía EPG: 06~08h fondo 1")},
	{HEXRGB(0x003F33), HEXRGB(0x007F66), TEXT("ProgramGuideTime6To8Back2"),          TEXT("Guía EPG: 06~08h fondo 2")},
	{HEXRGB(0x667F00), HEXRGB(0x99BF00), TEXT("ProgramGuideTime9To11Back"),          TEXT("Guía EPG: 09~11h fondo 1")},
	{HEXRGB(0x333F00), HEXRGB(0x667F00), TEXT("ProgramGuideTime9To11Back2"),         TEXT("Guía EPG: 09~11h fondo 2")},
	{HEXRGB(0x7F6600), HEXRGB(0xBF9900), TEXT("ProgramGuideTime12To14Back"),         TEXT("Guía EPG: 12~14h fondo 1")},
	{HEXRGB(0x3F3300), HEXRGB(0x7F6600), TEXT("ProgramGuideTime12To14Back2"),        TEXT("Guía EPG: 12~14h fondo 2")},
	{HEXRGB(0x7F3300), HEXRGB(0xBF4C00), TEXT("ProgramGuideTime15To17Back"),         TEXT("Guía EPG: 15~17h fondo 1")},
	{HEXRGB(0x3F1900), HEXRGB(0x7F3300), TEXT("ProgramGuideTime15To17Back2"),        TEXT("Guía EPG: 15~17h fondo 2")},
	{HEXRGB(0x7F0066), HEXRGB(0xBF0099), TEXT("ProgramGuideTime18To20Back"),         TEXT("Guía EPG: 18~20h fondo 1")},
	{HEXRGB(0x3F0033), HEXRGB(0x7F0066), TEXT("ProgramGuideTime18To20Back2"),        TEXT("Guía EPG: 18~20h fondo 2")},
	{HEXRGB(0x66007F), HEXRGB(0x9900BF), TEXT("ProgramGuideTime21To23Back"),         TEXT("Guía EPG: 21~23h fondo 1")},
	{HEXRGB(0x33003F), HEXRGB(0x66007F), TEXT("ProgramGuideTime21To23Back2"),        TEXT("Guía EPG: 21~23h fondo 2")},
	{HEXRGB(0xBBBBBB), HEXRGB(0xFFFFFF), TEXT("ProgramGuideTimeText"),               TEXT("Guía EPG: Hora texto")},
	{HEXRGB(0x888888), CLR_INVALID,      TEXT("ProgramGuideTimeLine"),               TEXT("Guía EPG: Línea divisoria de horas")},
	{HEXRGB(0xFF6600), CLR_INVALID,      TEXT("ProgramGuideCurTimeLine"),            TEXT("Guía EPG: Línea de hora actual")},
	{HEXRGB(0xBBBBBB), HEXRGB(0x000000), TEXT("ProgramGuideDateButtonText"),         TEXT("Guía EPG: Botón fecha texto")},
	{HEXRGB(0xFF3F1F), HEXRGB(0xFF2000), TEXT("ProgramGuideDateButtonSundayText"),   TEXT("Guía EPG: Botón fecha domingo")},
	{HEXRGB(0x4F9FFF), HEXRGB(0x0020FF), TEXT("ProgramGuideDateButtonSaturdayText"), TEXT("Guía EPG: Botón fecha sábado")},
	{HEXRGB(0x333333), HEXRGB(0xFFFFFF), TEXT("ProgramGuideDateButtonBack"),         TEXT("Guía EPG: Botón fecha fondo 1")},
	{HEXRGB(0x111111), HEXRGB(0xDDDDDD), TEXT("ProgramGuideDateButtonBack2"),        TEXT("Guía EPG: Botón fecha fondo 2")},
	{HEXRGB(0x111111), HEXRGB(0xDDDDDD), TEXT("ProgramGuideDateButtonBorder"),       TEXT("Guía EPG: Botón fecha borde")},
	{HEXRGB(0xDDDDDD), HEXRGB(0x000000), TEXT("ProgramGuideDateButtonCurText"),      TEXT("Guía EPG: Botón fecha sel. texto")},
	{HEXRGB(0x111111), HEXRGB(0xDDDDDD), TEXT("ProgramGuideDateButtonCurBack"),      TEXT("Guía EPG: Botón fecha sel. fondo 1")},
	{HEXRGB(0x333333), HEXRGB(0xFFFFFF), TEXT("ProgramGuideDateButtonCurBack2"),     TEXT("Guía EPG: Botón fecha sel. fondo 2")},
	{HEXRGB(0x111111), HEXRGB(0xDDDDDD), TEXT("ProgramGuideDateButtonCurBorder"),    TEXT("Guía EPG: Botón fecha sel. borde")},
	{HEXRGB(0xBBBBBB), HEXRGB(0x000000), TEXT("ProgramGuideDateButtonHotText"),      TEXT("Guía EPG: Botón fecha res. texto")},
	{HEXRGB(0x111111), HEXRGB(0xDDDDDD), TEXT("ProgramGuideDateButtonHotBack"),      TEXT("Guía EPG: Botón fecha res. fondo 1")},
	{HEXRGB(0x333333), HEXRGB(0xFFFFFF), TEXT("ProgramGuideDateButtonHotBack2"),     TEXT("Guía EPG: Botón fecha res. fondo 2")},
	{HEXRGB(0x111111), HEXRGB(0xDDDDDD), TEXT("ProgramGuideDateButtonHotBorder"),    TEXT("Guía EPG: Botón fecha res. borde")},
	{HEXRGB(0xFFFFE0), CLR_INVALID,      TEXT("EPGContentNews"),                     TEXT("Guía EPG: Noticias / Actualidad")},
	{HEXRGB(0xE0E0FF), CLR_INVALID,      TEXT("EPGContentSports"),                   TEXT("Guía EPG: Deportes")},
	{HEXRGB(0xFFE0F0), CLR_INVALID,      TEXT("EPGContentInformation"),              TEXT("Guía EPG: Variedades / Magacín")},
	{HEXRGB(0xFFE0E0), CLR_INVALID,      TEXT("EPGContentDrama"),                    TEXT("Guía EPG: Series / Dramas")},
	{HEXRGB(0xE0FFE0), CLR_INVALID,      TEXT("EPGContentMusic"),                    TEXT("Guía EPG: Música")},
	{HEXRGB(0xE0FFFF), CLR_INVALID,      TEXT("EPGContentVariety"),                  TEXT("Guía EPG: Entretenimiento / Show")},
	{HEXRGB(0xFFF0E0), CLR_INVALID,      TEXT("EPGContentMovie"),                    TEXT("Guía EPG: Cine / Películas")},
	{HEXRGB(0xFFE0FF), CLR_INVALID,      TEXT("EPGContentAnime"),                    TEXT("Guía EPG: Animación / Efectos")},
	{HEXRGB(0xFFFFE0), CLR_INVALID,      TEXT("EPGContentDocumentary"),              TEXT("Guía EPG: Documentales / Cultura")},
	{HEXRGB(0xFFF0E0), CLR_INVALID,      TEXT("EPGContentTheater"),                  TEXT("Guía EPG: Teatro / Espectáculos")},
	{HEXRGB(0xE0F0FF), CLR_INVALID,      TEXT("EPGContentEducation"),                TEXT("Guía EPG: Aficiones / Educación")},
	{HEXRGB(0xE0F0FF), CLR_INVALID,      TEXT("EPGContentWelfare"),                  TEXT("Guía EPG: Bienestar social")},
	{HEXRGB(0xF0F0F0), CLR_INVALID,      TEXT("EPGContentOther"),                    TEXT("Guía EPG: Otros programas")},
};

const CColorScheme::GradientInfo CColorScheme::m_GradientInfoList[NUM_GRADIENTS] = {
	{TEXT("StatusBack"),                        Theme::GradientDirection::Vert, false, COLOR_STATUSBACK1,                            COLOR_STATUSBACK2},
	{TEXT("StatusBottomItemBack"),              Theme::GradientDirection::Vert, false, COLOR_STATUSBOTTOMITEMBACK1,                  COLOR_STATUSBOTTOMITEMBACK2},
	{TEXT("StatusHighlightBack"),               Theme::GradientDirection::Vert, true,  COLOR_STATUSHIGHLIGHTBACK1,                   COLOR_STATUSHIGHLIGHTBACK2},
	{TEXT("StatusEventProgressBack"),           Theme::GradientDirection::Vert, true,  COLOR_STATUSEVENTPROGRESSBACK1,               COLOR_STATUSEVENTPROGRESSBACK2},
	{TEXT("StatusEventProgressElapsed"),        Theme::GradientDirection::Vert, true,  COLOR_STATUSEVENTPROGRESSELAPSED1,            COLOR_STATUSEVENTPROGRESSELAPSED2},
	{TEXT("PanelTabBack"),                      Theme::GradientDirection::Vert, true,  COLOR_PANELTABBACK1,                          COLOR_PANELTABBACK2},
	{TEXT("PanelCurTabBack"),                   Theme::GradientDirection::Vert, true,  COLOR_PANELCURTABBACK1,                       COLOR_PANELCURTABBACK2},
	{TEXT("PanelTabMargin"),                    Theme::GradientDirection::Vert, false, COLOR_PANELTABMARGIN1,                        COLOR_PANELTABMARGIN2},
	{TEXT("PanelTitleBack"),                    Theme::GradientDirection::Vert, true,  COLOR_PANELTITLEBACK1,                        COLOR_PANELTITLEBACK2},
	{TEXT("InformationPanelButtonBack"),        Theme::GradientDirection::Vert, true,  COLOR_INFORMATIONPANEL_BUTTONBACK1,           COLOR_INFORMATIONPANEL_BUTTONBACK2},
	{TEXT("InformationPanelHotButtonBack"),     Theme::GradientDirection::Vert, true,  COLOR_INFORMATIONPANEL_HOTBUTTONBACK1,        COLOR_INFORMATIONPANEL_HOTBUTTONBACK2},
	{TEXT("ProgramListChannelBack"),            Theme::GradientDirection::Vert, true,  COLOR_PROGRAMLISTPANEL_CHANNELBACK1,          COLOR_PROGRAMLISTPANEL_CHANNELBACK2},
	{TEXT("ProgramListCurChannelBack"),         Theme::GradientDirection::Vert, true,  COLOR_PROGRAMLISTPANEL_CURCHANNELBACK1,       COLOR_PROGRAMLISTPANEL_CURCHANNELBACK2},
	{TEXT("ProgramListChannelButtonBack"),      Theme::GradientDirection::Vert, true,  COLOR_PROGRAMLISTPANEL_CHANNELBUTTONBACK1,    COLOR_PROGRAMLISTPANEL_CHANNELBUTTONBACK2},
	{TEXT("ProgramListChannelButtonHotBack"),   Theme::GradientDirection::Vert, true,  COLOR_PROGRAMLISTPANEL_CHANNELBUTTONHOTBACK1, COLOR_PROGRAMLISTPANEL_CHANNELBUTTONHOTBACK2},
	{TEXT("ProgramListBack"),                   Theme::GradientDirection::Vert, true,  COLOR_PROGRAMLISTPANEL_EVENTBACK1,            COLOR_PROGRAMLISTPANEL_EVENTBACK2},
	{TEXT("ProgramListCurBack"),                Theme::GradientDirection::Vert, true,  COLOR_PROGRAMLISTPANEL_CUREVENTBACK1,         COLOR_PROGRAMLISTPANEL_CUREVENTBACK2},
	{TEXT("ProgramListTitleBack"),              Theme::GradientDirection::Vert, true,  COLOR_PROGRAMLISTPANEL_TITLEBACK1,            COLOR_PROGRAMLISTPANEL_TITLEBACK2},
	{TEXT("ProgramListCurTitleBack"),           Theme::GradientDirection::Vert, true,  COLOR_PROGRAMLISTPANEL_CURTITLEBACK1,         COLOR_PROGRAMLISTPANEL_CURTITLEBACK2},
	{TEXT("ChannelPanelChannelNameBack"),       Theme::GradientDirection::Vert, true,  COLOR_CHANNELPANEL_CHANNELNAMEBACK1,          COLOR_CHANNELPANEL_CHANNELNAMEBACK2},
	{TEXT("ChannelPanelCurChannelNameBack"),    Theme::GradientDirection::Vert, true,  COLOR_CHANNELPANEL_CURCHANNELNAMEBACK1,       COLOR_CHANNELPANEL_CURCHANNELNAMEBACK2},
	{TEXT("ChannelPanelEventNameBack"),         Theme::GradientDirection::Vert, true,  COLOR_CHANNELPANEL_EVENTNAME1BACK1,           COLOR_CHANNELPANEL_EVENTNAME1BACK2},
	{TEXT("ChannelPanelEventName2Back"),        Theme::GradientDirection::Vert, true,  COLOR_CHANNELPANEL_EVENTNAME2BACK1,           COLOR_CHANNELPANEL_EVENTNAME2BACK2},
	{TEXT("ChannelPanelCurEventNameBack"),      Theme::GradientDirection::Vert, true,  COLOR_CHANNELPANEL_CUREVENTNAME1BACK1,        COLOR_CHANNELPANEL_CUREVENTNAME1BACK2},
	{TEXT("ChannelPanelCurEventName2Back"),     Theme::GradientDirection::Vert, true,  COLOR_CHANNELPANEL_CUREVENTNAME2BACK1,        COLOR_CHANNELPANEL_CUREVENTNAME2BACK2},
	{TEXT("ChannelPanelFeaturedMark"),          Theme::GradientDirection::Vert, true,  COLOR_CHANNELPANEL_FEATUREDMARK1,             COLOR_CHANNELPANEL_FEATUREDMARK2},
	{TEXT("ChannelPanelProgress"),              Theme::GradientDirection::Vert, true,  COLOR_CHANNELPANEL_PROGRESS1,                 COLOR_CHANNELPANEL_PROGRESS2},
	{TEXT("ChannelPanelCurProgress"),           Theme::GradientDirection::Vert, true,  COLOR_CHANNELPANEL_CURPROGRESS1,              COLOR_CHANNELPANEL_CURPROGRESS2},
	{TEXT("ControlPanelBack"),                  Theme::GradientDirection::Vert, true,  COLOR_CONTROLPANELBACK1,                      COLOR_CONTROLPANELBACK2},
	{TEXT("ControlPanelHighlightBack"),         Theme::GradientDirection::Vert, true,  COLOR_CONTROLPANELHIGHLIGHTBACK1,             COLOR_CONTROLPANELHIGHLIGHTBACK2},
	{TEXT("ControlPanelCheckedBack"),           Theme::GradientDirection::Vert, true,  COLOR_CONTROLPANELCHECKEDBACK1,               COLOR_CONTROLPANELCHECKEDBACK2},
	{TEXT("TitleBarBack"),                      Theme::GradientDirection::Vert, true,  COLOR_TITLEBARBACK1,                          COLOR_TITLEBARBACK2},
	{TEXT("TitleBarIconBack"),                  Theme::GradientDirection::Vert, true,  COLOR_TITLEBARICONBACK1,                      COLOR_TITLEBARICONBACK2},
	{TEXT("TitleBarHighlightBack"),             Theme::GradientDirection::Vert, true,  COLOR_TITLEBARHIGHLIGHTBACK1,                 COLOR_TITLEBARHIGHLIGHTBACK2},
	{TEXT("SideBarBack"),                       Theme::GradientDirection::Horz, true,  COLOR_SIDEBARBACK1,                           COLOR_SIDEBARBACK2},
	{TEXT("SideBarHighlightBack"),              Theme::GradientDirection::Horz, true,  COLOR_SIDEBARHIGHLIGHTBACK1,                  COLOR_SIDEBARHIGHLIGHTBACK2},
	{TEXT("SideBarCheckBack"),                  Theme::GradientDirection::Horz, true,  COLOR_SIDEBARCHECKBACK1,                      COLOR_SIDEBARCHECKBACK2},
	{TEXT("NotificationBarBack"),               Theme::GradientDirection::Vert, true,  COLOR_NOTIFICATIONBARBACK1,                   COLOR_NOTIFICATIONBARBACK2},
	{TEXT("ProgramGuideFeaturedMark"),          Theme::GradientDirection::Horz, true,  COLOR_PROGRAMGUIDE_FEATUREDMARK1,             COLOR_PROGRAMGUIDE_FEATUREDMARK2},
	{TEXT("ProgramGuideChannelBack"),           Theme::GradientDirection::Vert, true,  COLOR_PROGRAMGUIDE_CHANNELBACK1,              COLOR_PROGRAMGUIDE_CHANNELBACK2},
	{TEXT("ProgramGuideCurChannelBack"),        Theme::GradientDirection::Vert, true,  COLOR_PROGRAMGUIDE_CURCHANNELBACK1,           COLOR_PROGRAMGUIDE_CURCHANNELBACK2},
	{TEXT("ProgramGuideTimeBack"),              Theme::GradientDirection::Horz, true,  COLOR_PROGRAMGUIDE_TIMEBACK1,                 COLOR_PROGRAMGUIDE_TIMEBACK2},
	{TEXT("ProgramGuideTime0To2Back"),          Theme::GradientDirection::Horz, true,  COLOR_PROGRAMGUIDE_TIMEBACK_0TO2_1,           COLOR_PROGRAMGUIDE_TIMEBACK_0TO2_2},
	{TEXT("ProgramGuideTime3To5Back"),          Theme::GradientDirection::Horz, true,  COLOR_PROGRAMGUIDE_TIMEBACK_3TO5_1,           COLOR_PROGRAMGUIDE_TIMEBACK_3TO5_2},
	{TEXT("ProgramGuideTime6To8Back"),          Theme::GradientDirection::Horz, true,  COLOR_PROGRAMGUIDE_TIMEBACK_6TO8_1,           COLOR_PROGRAMGUIDE_TIMEBACK_6TO8_2},
	{TEXT("ProgramGuideTime9To11Back"),         Theme::GradientDirection::Horz, true,  COLOR_PROGRAMGUIDE_TIMEBACK_9TO11_1,          COLOR_PROGRAMGUIDE_TIMEBACK_9TO11_2},
	{TEXT("ProgramGuideTime12To14Back"),        Theme::GradientDirection::Horz, true,  COLOR_PROGRAMGUIDE_TIMEBACK_12TO14_1,         COLOR_PROGRAMGUIDE_TIMEBACK_12TO14_2},
	{TEXT("ProgramGuideTime15To17Back"),        Theme::GradientDirection::Horz, true,  COLOR_PROGRAMGUIDE_TIMEBACK_15TO17_1,         COLOR_PROGRAMGUIDE_TIMEBACK_15TO17_2},
	{TEXT("ProgramGuideTime18To20Back"),        Theme::GradientDirection::Horz, true,  COLOR_PROGRAMGUIDE_TIMEBACK_18TO20_1,         COLOR_PROGRAMGUIDE_TIMEBACK_18TO20_2},
	{TEXT("ProgramGuideTime21To23Back"),        Theme::GradientDirection::Horz, true,  COLOR_PROGRAMGUIDE_TIMEBACK_21TO23_1,         COLOR_PROGRAMGUIDE_TIMEBACK_21TO23_2},
	{TEXT("ProgramGuideDateButtonBack"),        Theme::GradientDirection::Vert, true,  COLOR_PROGRAMGUIDE_DATEBUTTON_BACK1,          COLOR_PROGRAMGUIDE_DATEBUTTON_BACK2},
	{TEXT("ProgramGuideDateButtonCurBack"),     Theme::GradientDirection::Vert, true,  COLOR_PROGRAMGUIDE_DATEBUTTON_CURBACK1,       COLOR_PROGRAMGUIDE_DATEBUTTON_CURBACK2},
	{TEXT("ProgramGuideDateButtonHotBack"),     Theme::GradientDirection::Vert, true,  COLOR_PROGRAMGUIDE_DATEBUTTON_HOTBACK1,       COLOR_PROGRAMGUIDE_DATEBUTTON_HOTBACK2},
	{TEXT("ProgramGuideFavoriteButtonBack"),    Theme::GradientDirection::Vert, true,  -1,                                           -1},
	{TEXT("ProgramGuideFavoriteButtonCurBack"), Theme::GradientDirection::Vert, true,  -1,                                           -1},
	{TEXT("ProgramGuideFavoriteButtonHotBack"), Theme::GradientDirection::Vert, true,  -1,                                           -1},
};

const CColorScheme::BorderInfo CColorScheme::m_BorderInfoList[NUM_BORDERS] = {
	{TEXT("ScreenBorder"),                           Theme::BorderType::None,   COLOR_SCREENBORDER},
	{TEXT("WindowFrameBorder"),                      Theme::BorderType::None,   COLOR_WINDOWFRAMEBORDER},
	{TEXT("WindowActiveFrameBorder"),                Theme::BorderType::None,   COLOR_WINDOWACTIVEFRAMEBORDER},
	{TEXT("StatusBorder"),                           Theme::BorderType::Raised, COLOR_STATUSBORDER},
	{TEXT("StatusItemBorder"),                       Theme::BorderType::None,   COLOR_STATUSITEMBORDER},
	{TEXT("StatusBottomItemBorder"),                 Theme::BorderType::None,   COLOR_STATUSBOTTOMITEMBORDER},
	{TEXT("StatusHighlightBorder"),                  Theme::BorderType::None,   COLOR_STATUSHIGHLIGHTBORDER},
	{TEXT("StatusEventProgressBorder"),              Theme::BorderType::None,   COLOR_STATUSEVENTPROGRESSBORDER},
	{TEXT("StatusEventProgressElapsedBorder"),       Theme::BorderType::None,   COLOR_STATUSEVENTPROGRESSELAPSEDBORDER},
	{TEXT("TitleBarBorder"),                         Theme::BorderType::Raised, COLOR_TITLEBARBORDER},
	{TEXT("TitleBarCaptionBorder"),                  Theme::BorderType::None,   COLOR_TITLEBARTEXTBORDER},
	{TEXT("TitleBarIconBorder"),                     Theme::BorderType::None,   COLOR_TITLEBARICONBORDER},
	{TEXT("TitleBarHighlightBorder"),                Theme::BorderType::None,   COLOR_TITLEBARHIGHLIGHTBORDER},
	{TEXT("SideBarBorder"),                          Theme::BorderType::Raised, COLOR_SIDEBARBORDER},
	{TEXT("SideBarItemBorder"),                      Theme::BorderType::None,   COLOR_SIDEBARITEMBORDER},
	{TEXT("SideBarHighlightBorder"),                 Theme::BorderType::None,   COLOR_SIDEBARHIGHLIGHTBORDER},
	{TEXT("SideBarCheckBorder"),                     Theme::BorderType::Sunken, COLOR_SIDEBARCHECKBORDER},
	{TEXT("ProgramGuideStatusBorder"),               Theme::BorderType::Sunken, COLOR_STATUSBORDER},
	{TEXT("PanelTabBorder"),                         Theme::BorderType::Solid,  COLOR_PANELTABBORDER},
	{TEXT("PanelCurTabBorder"),                      Theme::BorderType::Solid,  COLOR_PANELCURTABBORDER},
	{TEXT("PanelTabMarginBorder"),                   Theme::BorderType::None,   COLOR_PANELTABMARGINBORDER},
	{TEXT("PanelTitleBorder"),                       Theme::BorderType::Raised, COLOR_PANELTITLEBORDER},
	{TEXT("InformationPanelEventInfoBorder"),        Theme::BorderType::None,   COLOR_INFORMATIONPANEL_EVENTINFOBORDER},
	{TEXT("InformationPanelButtonBorder"),           Theme::BorderType::None,   COLOR_INFORMATIONPANEL_BUTTONBORDER},
	{TEXT("InformationPanelHotButtonBorder"),        Theme::BorderType::None,   COLOR_INFORMATIONPANEL_HOTBUTTONBORDER},
	{TEXT("ProgramListPanelChannelBorder"),          Theme::BorderType::None,   COLOR_PROGRAMLISTPANEL_CHANNELBORDER},
	{TEXT("ProgramListPanelCurChannelBorder"),       Theme::BorderType::None,   COLOR_PROGRAMLISTPANEL_CURCHANNELBORDER},
	{TEXT("ProgramListPanelChannelButtonBorder"),    Theme::BorderType::None,   COLOR_PROGRAMLISTPANEL_CHANNELBUTTONBORDER},
	{TEXT("ProgramListPanelChannelButtonHotBorder"), Theme::BorderType::None,   COLOR_PROGRAMLISTPANEL_CHANNELBUTTONHOTBORDER},
	{TEXT("ProgramListPanelEventBorder"),            Theme::BorderType::None,   COLOR_PROGRAMLISTPANEL_EVENTBORDER},
	{TEXT("ProgramListPanelCurEventBorder"),         Theme::BorderType::None,   COLOR_PROGRAMLISTPANEL_CUREVENTBORDER},
	{TEXT("ProgramListPanelTitleBorder"),            Theme::BorderType::None,   COLOR_PROGRAMLISTPANEL_TITLEBORDER},
	{TEXT("ProgramListPanelCurTitleBorder"),         Theme::BorderType::None,   COLOR_PROGRAMLISTPANEL_CURTITLEBORDER},
	{TEXT("ChannelPanelChannelNameBorder"),          Theme::BorderType::None,   COLOR_CHANNELPANEL_CHANNELNAMEBORDER},
	{TEXT("ChannelPanelCurChannelNameBorder"),       Theme::BorderType::None,   COLOR_CHANNELPANEL_CURCHANNELNAMEBORDER},
	{TEXT("ChannelPanelEventNameBorder"),            Theme::BorderType::None,   COLOR_CHANNELPANEL_EVENTNAME1BORDER},
	{TEXT("ChannelPanelEventName2Border"),           Theme::BorderType::None,   COLOR_CHANNELPANEL_EVENTNAME2BORDER},
	{TEXT("ChannelPanelCurEventNameBorder"),         Theme::BorderType::None,   COLOR_CHANNELPANEL_CUREVENTNAME1BORDER},
	{TEXT("ChannelPanelCurEventName2Border"),        Theme::BorderType::None,   COLOR_CHANNELPANEL_CUREVENTNAME2BORDER},
	{TEXT("ChannelPanelFeaturedMarkBorder"),         Theme::BorderType::Solid,  COLOR_CHANNELPANEL_FEATUREDMARKBORDER},
	{TEXT("ChannelPanelProgressBorder"),             Theme::BorderType::None,   COLOR_CHANNELPANEL_PROGRESSBORDER},
	{TEXT("ChannelPanelCurProgressBorder"),          Theme::BorderType::None,   COLOR_CHANNELPANEL_CURPROGRESSBORDER},
	{TEXT("ControlPanelItemBorder"),                 Theme::BorderType::None,   COLOR_CONTROLPANELITEMBORDER},
	{TEXT("ControlPanelHighlightBorder"),            Theme::BorderType::None,   COLOR_CONTROLPANELHIGHLIGHTBORDER},
	{TEXT("ControlPanelCheckedBorder"),              Theme::BorderType::None,   COLOR_CONTROLPANELCHECKEDBORDER},
	{TEXT("ProgramGuideFeaturedMarkBorder"),         Theme::BorderType::Solid,  COLOR_PROGRAMGUIDE_FEATUREDMARKBORDER},
	{TEXT("ProgramGuideDateButtonBorder"),           Theme::BorderType::Raised, COLOR_PROGRAMGUIDE_DATEBUTTON_BORDER},
	{TEXT("ProgramGuideDateButtonCurBorder"),        Theme::BorderType::Sunken, COLOR_PROGRAMGUIDE_DATEBUTTON_CURBORDER},
	{TEXT("ProgramGuideDateButtonHotBorder"),        Theme::BorderType::Raised, COLOR_PROGRAMGUIDE_DATEBUTTON_HOTBORDER},
	{TEXT("ProgramGuideTimeButtonBorder"),           Theme::BorderType::Raised, -1},
	{TEXT("ProgramGuideTimeButtonCurBorder"),        Theme::BorderType::Sunken, -1},
	{TEXT("ProgramGuideTimeButtonHotBorder"),        Theme::BorderType::Raised, -1},
	{TEXT("ProgramGuideFavoriteButtonBorder"),       Theme::BorderType::Raised, -1},
	{TEXT("ProgramGuideFavoriteButtonCurBorder"),    Theme::BorderType::Sunken, -1},
	{TEXT("ProgramGuideFavoriteButtonHotBorder"),    Theme::BorderType::Raised, -1},
};

const Theme::BorderType CColorScheme::m_CustomDefaultBorderList[NUM_BORDERS] = {
	Theme::BorderType::None,
	Theme::BorderType::None,
	Theme::BorderType::None,
	Theme::BorderType::Raised,
	Theme::BorderType::None,
	Theme::BorderType::None,
	Theme::BorderType::Sunken,
	Theme::BorderType::None,
	Theme::BorderType::None,
	Theme::BorderType::Raised,
	Theme::BorderType::None,
	Theme::BorderType::None,
	Theme::BorderType::Sunken,
	Theme::BorderType::Raised,
	Theme::BorderType::None,
	Theme::BorderType::Sunken,
	Theme::BorderType::Sunken,
	Theme::BorderType::Sunken,
	Theme::BorderType::None,
	Theme::BorderType::Solid,
	Theme::BorderType::None,
	Theme::BorderType::Raised,
	Theme::BorderType::None,
	Theme::BorderType::None,
	Theme::BorderType::Sunken,
	Theme::BorderType::Solid,
	Theme::BorderType::Solid,
	Theme::BorderType::None,
	Theme::BorderType::Sunken,
	Theme::BorderType::Solid,
	Theme::BorderType::Solid,
	Theme::BorderType::Solid,
	Theme::BorderType::Solid,
	Theme::BorderType::Solid,
	Theme::BorderType::Solid,
	Theme::BorderType::Solid,
	Theme::BorderType::Solid,
	Theme::BorderType::Solid,
	Theme::BorderType::Solid,
	Theme::BorderType::Solid,
	Theme::BorderType::None,
	Theme::BorderType::None,
	Theme::BorderType::None,
	Theme::BorderType::Sunken,
	Theme::BorderType::Sunken,
	Theme::BorderType::Solid,
	Theme::BorderType::Raised,
	Theme::BorderType::Sunken,
	Theme::BorderType::Raised,
	Theme::BorderType::Raised,
	Theme::BorderType::Sunken,
	Theme::BorderType::Raised,
	Theme::BorderType::Raised,
	Theme::BorderType::Sunken,
	Theme::BorderType::Raised,
};


CColorScheme::CColorScheme()
{
	SetDefault();
}


CColorScheme::CColorScheme(const CColorScheme &ColorScheme)
{
	*this = ColorScheme;
}


COLORREF CColorScheme::GetColor(int Type) const
{
	if (Type < 0 || Type >= NUM_COLORS)
		return CLR_INVALID;
	return m_ColorList[Type];
}


COLORREF CColorScheme::GetColor(LPCTSTR pszText) const
{
	for (int i = 0; i < NUM_COLORS; i++) {
		if (::lstrcmpi(m_ColorInfoList[i].pszText, pszText) == 0)
			return m_ColorList[i];
	}
	return CLR_INVALID;
}


bool CColorScheme::SetColor(int Type, COLORREF Color)
{
	if (Type < 0 || Type >= NUM_COLORS)
		return false;
	m_ColorList[Type] = Color;
	return true;
}


Theme::GradientType CColorScheme::GetGradientType(int Gradient) const
{
	if (Gradient < 0 || Gradient >= NUM_GRADIENTS)
		return Theme::GradientType::Normal;
	return m_FillList[Gradient].Gradient.Type;
}


Theme::GradientType CColorScheme::GetGradientType(LPCTSTR pszText) const
{
	int Length = ::lstrlen(pszText);
	if (Length > 8 && ::lstrcmpi(pszText + (Length - 8), TEXT("Gradient")) == 0) {
		Length -= 8;
		for (int i = 0; i < NUM_GRADIENTS; i++) {
			if (::StrCmpNI(m_GradientInfoList[i].pszText, pszText, Length) == 0
					&& m_GradientInfoList[i].pszText[Length] == _T('\0'))
				return m_FillList[i].Gradient.Type;
		}
	}
	return Theme::GradientType::Normal;
}


bool CColorScheme::SetGradientStyle(int Gradient, const GradientStyle &Style)
{
	if (Gradient < 0 || Gradient >= NUM_GRADIENTS)
		return false;
	m_FillList[Gradient].Gradient.Type = Style.Type;
	m_FillList[Gradient].Gradient.Direction = Style.Direction;
	return true;
}


bool CColorScheme::GetGradientStyle(int Gradient, GradientStyle *pStyle) const
{
	if (Gradient < 0 || Gradient >= NUM_GRADIENTS)
		return false;
	*pStyle = m_FillList[Gradient].Gradient;
	return true;
}


bool CColorScheme::GetGradientStyle(int Gradient, Theme::GradientStyle *pStyle) const
{
	if (Gradient < 0 || Gradient >= NUM_GRADIENTS)
		return false;
	pStyle->Type = m_FillList[Gradient].Gradient.Type;
	pStyle->Direction = m_FillList[Gradient].Gradient.Direction;
	if (m_GradientInfoList[Gradient].Color1 >= 0) {
		pStyle->Color1 = m_ColorList[m_GradientInfoList[Gradient].Color1];
		pStyle->Color2 = m_ColorList[m_GradientInfoList[Gradient].Color2];
	} else {
		pStyle->Color1 = Theme::ThemeColor();
		pStyle->Color2 = Theme::ThemeColor();
	}
	return true;
}


bool CColorScheme::GetFillStyle(int Gradient, Theme::FillStyle *pStyle) const
{
	if (Gradient < 0 || Gradient >= NUM_GRADIENTS)
		return false;
	pStyle->Type = m_FillList[Gradient].Type;
	GetGradientStyle(Gradient, &pStyle->Gradient);
	return true;
}


Theme::BorderType CColorScheme::GetBorderType(int Border) const
{
	if (Border < 0 || Border >= NUM_BORDERS)
		return Theme::BorderType::None;
	return m_BorderList[Border];
}


bool CColorScheme::SetBorderType(int Border, Theme::BorderType Type)
{
	if (Border < 0 || Border >= NUM_BORDERS
			|| Type < Theme::BorderType::None || Type > Theme::BorderType::Raised)
		return false;
	m_BorderList[Border] = Type;
	return true;
}


bool CColorScheme::GetBorderStyle(int Border, Theme::BorderStyle *pStyle) const
{
	if (Border < 0 || Border >= NUM_BORDERS)
		return false;
	pStyle->Type = m_BorderList[Border];
	if (m_BorderInfoList[Border].Color >= 0)
		pStyle->Color = m_ColorList[m_BorderInfoList[Border].Color];
	else
		pStyle->Color = Theme::ThemeColor();
	return true;
}


void CColorScheme::SetName(LPCTSTR pszName)
{
	StringUtility::Assign(m_Name, pszName);
}


bool CColorScheme::Load(CSettings &Settings)
{
	TCHAR szText[MAX_COLORSCHEME_NAME];

	if (!Settings.SetSection(TEXT("ColorScheme")))
		return false;

	if (Settings.Read(TEXT("Name"), szText, lengthof(szText)))
		SetName(szText);

	TCHAR szBase[8];
	if (Settings.Read(TEXT("Base"), szBase, lengthof(szBase))) {
		if (::lstrcmpi(szBase, TEXT("dark")) == 0)
			m_BaseScheme = BaseSchemeType::Dark;
		else if (::lstrcmpi(szBase, TEXT("light")) == 0)
			m_BaseScheme = BaseSchemeType::Light;
	}

	m_LoadedFlags.reset();
	for (int i = 0; i < NUM_COLORS; i++) {
		if (Settings.ReadColor(m_ColorInfoList[i].pszText, &m_ColorList[i]))
			SetLoadedFlag(i);
	}

	for (int i = 0; i < NUM_GRADIENTS; i++) {
		if (m_GradientInfoList[i].Color1 >= 0
				&& IsLoaded(m_GradientInfoList[i].Color1)
				&& !IsLoaded(m_GradientInfoList[i].Color2)) {
			m_ColorList[m_GradientInfoList[i].Color2] = m_ColorList[m_GradientInfoList[i].Color1];
			SetLoadedFlag(m_GradientInfoList[i].Color2);
			m_FillList[i].Gradient.Type = Theme::GradientType::Normal;
		}
	}

	static const struct {
		int To, From;
	} ColorMap[] = {
		//{COLOR_STATUSBORDER,                          COLOR_STATUSBACK1},
		{COLOR_STATUSBOTTOMITEMBACK1,                 COLOR_STATUSBACK2},
		{COLOR_STATUSBOTTOMITEMBACK2,                 COLOR_STATUSBOTTOMITEMBACK1},
		{COLOR_STATUSBOTTOMITEMTEXT,                  COLOR_STATUSTEXT},
		{COLOR_STATUSBOTTOMITEMBORDER,                COLOR_STATUSBOTTOMITEMBACK1},
		{COLOR_STATUSEVENTPROGRESSBORDER,             COLOR_STATUSEVENTPROGRESSBACK1},
		{COLOR_STATUSEVENTPROGRESSELAPSEDBORDER,      COLOR_STATUSEVENTPROGRESSELAPSED1},
		{COLOR_WINDOWFRAMEBORDER,                     COLOR_WINDOWFRAMEBACK},
		{COLOR_WINDOWACTIVEFRAMEBACK,                 COLOR_WINDOWFRAMEBACK},
		{COLOR_WINDOWACTIVEFRAMEBORDER,               COLOR_WINDOWACTIVEFRAMEBACK},
		{COLOR_INFORMATIONPANEL_EVENTINFOBORDER,      COLOR_PROGRAMINFOBACK},
		{COLOR_INFORMATIONPANEL_BUTTONBACK1,          COLOR_PANELBACK},
		{COLOR_INFORMATIONPANEL_BUTTONBACK2,          COLOR_INFORMATIONPANEL_BUTTONBACK1},
		{COLOR_INFORMATIONPANEL_BUTTONTEXT,           COLOR_PANELTEXT},
		{COLOR_INFORMATIONPANEL_HOTBUTTONBACK1,       COLOR_PANELBACK},
		{COLOR_INFORMATIONPANEL_HOTBUTTONBACK2,       COLOR_INFORMATIONPANEL_HOTBUTTONBACK1},
		{COLOR_INFORMATIONPANEL_HOTBUTTONTEXT,        COLOR_PANELTEXT},
		{COLOR_PROGRAMLISTPANEL_CUREVENTTEXT,         COLOR_PROGRAMLISTPANEL_EVENTTEXT},
		{COLOR_PROGRAMLISTPANEL_CURTITLETEXT,         COLOR_PROGRAMLISTPANEL_TITLETEXT},
		{COLOR_PANELTABLINE,                          COLOR_PANELTABBORDER},
		//{COLOR_PANELTITLEBORDER,                      COLOR_PANELTITLEBACK1},
		{COLOR_CHANNELPANEL_CURCHANNELNAMETEXT,       COLOR_CHANNELPANEL_CHANNELNAMETEXT},
		{COLOR_CHANNELPANEL_EVENTNAME2TEXT,           COLOR_CHANNELPANEL_EVENTNAME1TEXT},
		{COLOR_CHANNELPANEL_EVENTNAME2BORDER,         COLOR_CHANNELPANEL_EVENTNAME1BORDER},
		{COLOR_CHANNELPANEL_CUREVENTNAME1TEXT,        COLOR_CHANNELPANEL_EVENTNAME1TEXT},
		{COLOR_CHANNELPANEL_CUREVENTNAME1BORDER,      COLOR_CHANNELPANEL_EVENTNAME1BORDER},
		{COLOR_CHANNELPANEL_CUREVENTNAME2TEXT,        COLOR_CHANNELPANEL_CUREVENTNAME1TEXT},
		{COLOR_CHANNELPANEL_CUREVENTNAME2BORDER,      COLOR_CHANNELPANEL_CUREVENTNAME1BORDER},
		{COLOR_CHANNELPANEL_PROGRESSBORDER,           COLOR_CHANNELPANEL_PROGRESS1},
		{COLOR_CHANNELPANEL_CURPROGRESSBORDER,        COLOR_CHANNELPANEL_CURPROGRESS1},
		{COLOR_PROGRAMLISTPANEL_CHANNELTEXT,          COLOR_CHANNELPANEL_CHANNELNAMETEXT},
		{COLOR_PROGRAMLISTPANEL_CURCHANNELTEXT,       COLOR_CHANNELPANEL_CURCHANNELNAMETEXT},
		{COLOR_PROGRAMLISTPANEL_CHANNELBUTTONTEXT,    COLOR_PROGRAMLISTPANEL_CHANNELTEXT},
		{COLOR_PROGRAMLISTPANEL_CHANNELBUTTONHOTTEXT, COLOR_PROGRAMLISTPANEL_CURCHANNELTEXT},
		{COLOR_CONTROLPANELBACK1,                     COLOR_PANELBACK},
		{COLOR_CONTROLPANELBACK2,                     COLOR_PANELBACK},
		{COLOR_CONTROLPANELTEXT,                      COLOR_PANELTEXT},
		{COLOR_CONTROLPANELCHECKEDTEXT,               COLOR_CONTROLPANELHIGHLIGHTTEXT},
		{COLOR_CONTROLPANELMARGIN,                    COLOR_PANELBACK},
		{COLOR_CAPTIONPANELBACK,                      COLOR_PROGRAMINFOBACK},
		{COLOR_CAPTIONPANELTEXT,                      COLOR_PROGRAMINFOTEXT},
		{COLOR_TITLEBARTEXT,                          COLOR_STATUSTEXT},
		{COLOR_TITLEBARICON,                          COLOR_TITLEBARTEXT},
		{COLOR_TITLEBARHIGHLIGHTICON,                 COLOR_STATUSHIGHLIGHTTEXT},
		//{COLOR_TITLEBARBORDER,                        COLOR_TITLEBARBACK1},
		{COLOR_SIDEBARICON,                           COLOR_STATUSTEXT},
		{COLOR_SIDEBARHIGHLIGHTICON,                  COLOR_STATUSHIGHLIGHTTEXT},
		{COLOR_SIDEBARCHECKICON,                      COLOR_SIDEBARICON},
		//{COLOR_SIDEBARCHECKBORDER,                    COLOR_SIDEBARCHECKBACK2},
		//{COLOR_SIDEBARBORDER,                         COLOR_SIDEBARBACK1},
		{COLOR_EVENTINFOPOPUP_BACK,                   COLOR_PROGRAMINFOBACK},
		{COLOR_EVENTINFOPOPUP_TEXT,                   COLOR_PROGRAMINFOTEXT},
		{COLOR_EVENTINFOPOPUP_EVENTTITLE,             COLOR_EVENTINFOPOPUP_TEXT},
		{COLOR_PROGRAMGUIDE_CHANNELHIGHLIGHTTEXT,     COLOR_PROGRAMGUIDE_CHANNELTEXT},
		{COLOR_PROGRAMGUIDE_CURCHANNELTEXT,           COLOR_PROGRAMGUIDE_CHANNELTEXT},
		{COLOR_PROGRAMGUIDE_TIMELINE,                 COLOR_PROGRAMGUIDE_TIMETEXT},
		{COLOR_PROGRAMGUIDE_DATEBUTTON_BORDER,        COLOR_PROGRAMGUIDE_DATEBUTTON_BACK1},
		{COLOR_PROGRAMGUIDE_DATEBUTTON_CURTEXT,       COLOR_PROGRAMGUIDE_DATEBUTTON_TEXT},
		{COLOR_PROGRAMGUIDE_DATEBUTTON_CURBACK1,      COLOR_PROGRAMGUIDE_DATEBUTTON_BACK2},
		{COLOR_PROGRAMGUIDE_DATEBUTTON_CURBACK2,      COLOR_PROGRAMGUIDE_DATEBUTTON_BACK1},
		{COLOR_PROGRAMGUIDE_DATEBUTTON_CURBORDER,     COLOR_PROGRAMGUIDE_DATEBUTTON_CURBACK2},
		{COLOR_PROGRAMGUIDE_DATEBUTTON_HOTTEXT,       COLOR_PROGRAMGUIDE_DATEBUTTON_TEXT},
	};

	for (const auto Map : ColorMap) {
		if (!IsLoaded(Map.To) && IsLoaded(Map.From)) {
			m_ColorList[Map.To] = m_ColorList[Map.From];
			SetLoadedFlag(Map.To);
		}
	}

	static const struct {
		int To, From1, From2;
	} MixMap[] = {
		{COLOR_STATUSBORDER,       COLOR_STATUSBACK1,       COLOR_STATUSBACK2},
		{COLOR_PANELTITLEBORDER,   COLOR_PANELTITLEBACK1,   COLOR_PANELTITLEBACK2},
		{COLOR_TITLEBARBORDER,     COLOR_TITLEBARBACK1,     COLOR_TITLEBARBACK2},
		{COLOR_SIDEBARCHECKBORDER, COLOR_SIDEBARCHECKBACK1, COLOR_SIDEBARCHECKBACK2},
		{COLOR_SIDEBARBORDER,      COLOR_SIDEBARBACK1,      COLOR_SIDEBARBACK2},
	};

	for (const auto Map : MixMap) {
		if (!IsLoaded(Map.To) && IsLoaded(Map.From1) && IsLoaded(Map.From2)) {
			m_ColorList[Map.To] = MixColor(m_ColorList[Map.From1], m_ColorList[Map.From2]);
			SetLoadedFlag(Map.To);
		}
	}

	for (int i = 0; i < NUM_GRADIENTS; i++) {
		TCHAR szName[128];

		StringFormat(szName, TEXT("{}Style"), m_GradientInfoList[i].pszText);
		m_FillList[i].Type = Theme::FillType::Gradient;
		if (Settings.Read(szName, szText, lengthof(szText))) {
			for (int j = 0; j < lengthof(FillTypeNameList); j++) {
				if (::lstrcmpi(szText, FillTypeNameList[j]) == 0) {
					m_FillList[i].Type = static_cast<Theme::FillType>(j);
					break;
				}
			}
		}

		StringFormat(szName, TEXT("{}Gradient"), m_GradientInfoList[i].pszText);
		m_FillList[i].Gradient.Type = Theme::GradientType::Normal;
		if (Settings.Read(szName, szText, lengthof(szText))) {
			for (int j = 0; j < lengthof(GradientTypeNameList); j++) {
				if (::lstrcmpi(szText, GradientTypeNameList[j]) == 0) {
					m_FillList[i].Gradient.Type = static_cast<Theme::GradientType>(j);
					break;
				}
			}
		} else {
			switch (i) {
			case GRADIENT_TITLEBARICON:
				m_FillList[i].Gradient.Type = m_FillList[GRADIENT_TITLEBARBACK].Gradient.Type;
				break;
			case GRADIENT_SIDEBARCHECKBACK:
				m_FillList[i].Gradient.Type = m_FillList[GRADIENT_SIDEBARBACK].Gradient.Type;
				break;
			}
		}

		StringFormat(szName, TEXT("{}GradientDirection"), m_GradientInfoList[i].pszText);
		m_FillList[i].Gradient.Direction = m_GradientInfoList[i].Direction;
		if (Settings.Read(szName, szText, lengthof(szText))) {
			for (int j = 0; j < lengthof(GradientDirectionList); j++) {
				if (::lstrcmpi(szText, GradientDirectionList[j]) == 0) {
					m_FillList[i].Gradient.Direction = static_cast<Theme::GradientDirection>(j);
					break;
				}
			}
		} else {
			switch (i) {
			case GRADIENT_TITLEBARICON:
				m_FillList[i].Gradient.Direction = m_FillList[GRADIENT_TITLEBARBACK].Gradient.Direction;
				break;
			case GRADIENT_SIDEBARCHECKBACK:
				m_FillList[i].Gradient.Direction = m_FillList[GRADIENT_SIDEBARBACK].Gradient.Direction;
				break;
			}
		}
	}

	static const struct {
		int To, From;
	} GradientMap[] = {
		{GRADIENT_CHANNELPANEL_CURCHANNELNAMEBACK,       GRADIENT_CHANNELPANEL_CHANNELNAMEBACK},
		{GRADIENT_CHANNELPANEL_EVENTNAMEBACK2,           GRADIENT_CHANNELPANEL_EVENTNAMEBACK1},
		{GRADIENT_CHANNELPANEL_CUREVENTNAMEBACK1,        GRADIENT_CHANNELPANEL_EVENTNAMEBACK1},
		{GRADIENT_CHANNELPANEL_CUREVENTNAMEBACK2,        GRADIENT_CHANNELPANEL_CUREVENTNAMEBACK1},
		{GRADIENT_CHANNELPANEL_PROGRESS,                 GRADIENT_STATUSEVENTPROGRESSELAPSED},
		{GRADIENT_CHANNELPANEL_CURPROGRESS,              GRADIENT_CHANNELPANEL_PROGRESS},
		{GRADIENT_PROGRAMLISTPANEL_CHANNELBACK,          GRADIENT_CHANNELPANEL_CHANNELNAMEBACK},
		{GRADIENT_PROGRAMLISTPANEL_CURCHANNELBACK,       GRADIENT_CHANNELPANEL_CURCHANNELNAMEBACK},
		{GRADIENT_PROGRAMLISTPANEL_CHANNELBUTTONBACK,    GRADIENT_CHANNELPANEL_CHANNELNAMEBACK},
		//{GRADIENT_PROGRAMLISTPANEL_CHANNELBUTTONHOTBACK, GRADIENT_CHANNELPANEL_CURCHANNELNAMEBACK},
		{GRADIENT_PROGRAMLISTPANEL_CHANNELBUTTONHOTBACK, GRADIENT_CONTROLPANELHIGHLIGHTBACK},
		{GRADIENT_PROGRAMLISTPANEL_CUREVENTBACK,         GRADIENT_PROGRAMLISTPANEL_EVENTBACK},
		{GRADIENT_PROGRAMLISTPANEL_CURTITLEBACK,         GRADIENT_PROGRAMLISTPANEL_TITLEBACK},
		{GRADIENT_CONTROLPANELCHECKEDBACK,               GRADIENT_CONTROLPANELHIGHLIGHTBACK},
		{GRADIENT_TITLEBARBACK,                          GRADIENT_STATUSBACK},
		{GRADIENT_TITLEBARICON,                          GRADIENT_TITLEBARBACK},
		{GRADIENT_TITLEBARHIGHLIGHTBACK,                 GRADIENT_STATUSHIGHLIGHTBACK},
		{GRADIENT_SIDEBARBACK,                           GRADIENT_STATUSBACK},
		{GRADIENT_SIDEBARHIGHLIGHTBACK,                  GRADIENT_STATUSHIGHLIGHTBACK},
		{GRADIENT_SIDEBARCHECKBACK,                      GRADIENT_SIDEBARBACK},
		{GRADIENT_PROGRAMGUIDECURCHANNELBACK,            GRADIENT_PROGRAMGUIDECHANNELBACK},
		{GRADIENT_PROGRAMGUIDE_DATEBUTTON_HOTBACK,       GRADIENT_PROGRAMGUIDE_DATEBUTTON_BACK},
	};

	for (const auto Map : GradientMap) {
		if (m_GradientInfoList[Map.To].Color1 >= 0
				&& !IsLoaded(m_GradientInfoList[Map.To].Color1)
				&& IsLoaded(m_GradientInfoList[Map.From].Color1)) {
			m_ColorList[m_GradientInfoList[Map.To].Color1] = m_ColorList[m_GradientInfoList[Map.From].Color1];
			m_ColorList[m_GradientInfoList[Map.To].Color2] = m_ColorList[m_GradientInfoList[Map.From].Color2];
			SetLoadedFlag(m_GradientInfoList[Map.To].Color1);
			SetLoadedFlag(m_GradientInfoList[Map.To].Color2);
			m_FillList[Map.To] = m_FillList[Map.From];
		}
	}

	bool BorderLoaded[NUM_BORDERS];

	for (int i = 0; i < NUM_BORDERS; i++) {
		m_BorderList[i] = m_BorderInfoList[i].DefaultType;
		BorderLoaded[i] = false;
	}
	if (Settings.SetSection(TEXT("Style"))) {
		for (int i = 0; i < NUM_BORDERS; i++) {
			if (Settings.Read(m_BorderInfoList[i].pszText, szText, lengthof(szText))) {
				bool fLoaded = false;
				for (int j = 0; j < lengthof(BorderTypeNameList); j++) {
					if (::lstrcmpi(szText, BorderTypeNameList[j]) == 0) {
						m_BorderList[i] = static_cast<Theme::BorderType>(j);
						fLoaded = true;
						break;
					}
				}
				BorderLoaded[i] = fLoaded;
			}
		}
	}

	static const struct {
		int To, From;
	} BorderMap[] = {
		{BORDER_PROGRAMLISTPANEL_CHANNEL,          BORDER_CHANNELPANEL_CHANNELNAME},
		{BORDER_PROGRAMLISTPANEL_CURCHANNEL,       BORDER_CHANNELPANEL_CURCHANNELNAME},
		{BORDER_PROGRAMLISTPANEL_CHANNELBUTTONHOT, BORDER_CONTROLPANELHIGHLIGHTITEM},
		{BORDER_SIDEBARITEM,                       BORDER_STATUSITEM},
		{BORDER_SIDEBARHIGHLIGHT,                  BORDER_STATUSHIGHLIGHT},
		{BORDER_PROGRAMGUIDE_DATEBUTTON_HOT,       BORDER_PROGRAMGUIDE_DATEBUTTON},
	};

	for (const auto Map : BorderMap) {
		if (!BorderLoaded[Map.To] && BorderLoaded[Map.From]) {
			m_BorderList[Map.To] = m_BorderList[Map.From];
		}
		const int ColorTo = m_BorderInfoList[Map.To].Color;
		const int ColorFrom = m_BorderInfoList[Map.From].Color;
		if (!IsLoaded(ColorTo) && IsLoaded(ColorFrom)) {
			m_ColorList[ColorTo] = m_ColorList[ColorFrom];
			SetLoadedFlag(ColorTo);
		}
	}

	for (int i = 0; i < NUM_COLORS; i++) {
		if (!IsLoaded(i)
				&& m_ColorInfoList[i].DefaultColor != m_ColorInfoList[i].DefaultLightColor
				&& m_ColorInfoList[i].DefaultLightColor != CLR_INVALID) {
			m_ColorList[i] =
				m_BaseScheme == BaseSchemeType::Dark ?
					m_ColorInfoList[i].DefaultColor :
					m_ColorInfoList[i].DefaultLightColor;
			SetLoadedFlag(i);
		}
	}

	return true;
}


bool CColorScheme::Save(CSettings &Settings, SaveFlag Flags) const
{
	if (!Settings.SetSection(TEXT("ColorScheme")))
		return false;

	bool fSaveAllColors = true, fSaveGradients = true;

	if (!!(Flags & SaveFlag::NoDefault)) {
		/*
			SaveFlag::NoDefault が指定されている場合、デフォルトから変更されていない時のみ設定を保存する。
			Loadの処理が複雑なので、単純に変更されているもののみ保存すればいいという訳ではないため、
			デフォルトから変更されている場合は全ての設定を保存する。
		*/
		CColorScheme DefaultColorScheme;
		int i;

		for (i = 0; i < NUM_COLORS; i++) {
			if ((i < COLOR_PROGRAMGUIDE_CONTENT_FIRST || i > COLOR_PROGRAMGUIDE_CONTENT_LAST)
					&& m_ColorList[i] != DefaultColorScheme.m_ColorList[i])
				break;
		}
		if (i == NUM_COLORS)
			fSaveAllColors = false;

		for (i = 0; i < NUM_GRADIENTS; i++) {
			if (m_FillList[i] != DefaultColorScheme.m_FillList[i])
				break;
		}
		if (i == NUM_GRADIENTS)
			fSaveGradients = false;

		if (!fSaveAllColors || !fSaveGradients)
			Settings.Clear();
	}

	if (!(Flags & SaveFlag::NoName))
		Settings.Write(TEXT("Name"), m_Name);

	Settings.Write(TEXT("Base"), m_BaseScheme == BaseSchemeType::Dark ? TEXT("dark") : TEXT("light"));

	for (int i = 0; i < NUM_COLORS; i++) {
		if (fSaveAllColors || m_ColorList[i] != m_ColorInfoList[i].DefaultColor)
			Settings.WriteColor(m_ColorInfoList[i].pszText, m_ColorList[i]);
	}

	if (fSaveGradients) {
		for (int i = 0; i < NUM_GRADIENTS; i++) {
			TCHAR szName[128];

			StringFormat(szName, TEXT("{}Type"), m_GradientInfoList[i].pszText);
			Settings.Write(szName, FillTypeNameList[static_cast<int>(m_FillList[i].Type)]);
			StringFormat(szName, TEXT("{}Gradient"), m_GradientInfoList[i].pszText);
			Settings.Write(szName, GradientTypeNameList[static_cast<int>(m_FillList[i].Gradient.Type)]);
			StringFormat(szName, TEXT("{}GradientDirection"), m_GradientInfoList[i].pszText);
			Settings.Write(szName, GradientDirectionList[static_cast<int>(m_FillList[i].Gradient.Direction)]);
		}
	}

	if (Settings.SetSection(TEXT("Style"))) {
		for (int i = 0; i < NUM_BORDERS; i++)
			Settings.Write(m_BorderInfoList[i].pszText, BorderTypeNameList[static_cast<int>(m_BorderList[i])]);
	}

	return true;
}


bool CColorScheme::Load(LPCTSTR pszFileName)
{
	CSettings Settings;

	if (!Settings.Open(pszFileName, CSettings::OpenFlag::Read))
		return false;

	if (!Load(Settings))
		return false;

	SetFileName(pszFileName);

	if (m_Name.empty()) {
		TCHAR szName[MAX_COLORSCHEME_NAME];
		StringCopy(szName, ::PathFindFileName(pszFileName));
		::PathRemoveExtension(szName);
		SetName(szName);
	}

	return true;
}


bool CColorScheme::Save(LPCTSTR pszFileName, SaveFlag Flags) const
{
	CSettings Settings;

	if (!Settings.Open(pszFileName, CSettings::OpenFlag::Write))
		return false;

	return Save(Settings, Flags);
}


bool CColorScheme::SetFileName(LPCTSTR pszFileName)
{
	StringUtility::Assign(m_FileName, pszFileName);
	return true;
}


void CColorScheme::SetBaseScheme(BaseSchemeType BaseScheme)
{
	m_BaseScheme = BaseScheme;
}


void CColorScheme::SetDefault()
{
	m_BaseScheme = BaseSchemeType::Dark;

	for (int i = 0; i < NUM_COLORS; i++)
		m_ColorList[i] = m_ColorInfoList[i].DefaultColor;

	for (int i = 0; i < NUM_GRADIENTS; i++) {
		m_FillList[i].Type = Theme::FillType::Gradient;
		m_FillList[i].Gradient.Type = Theme::GradientType::Normal;
		m_FillList[i].Gradient.Direction = m_GradientInfoList[i].Direction;
	}

	for (int i = 0; i < NUM_BORDERS; i++)
		m_BorderList[i] = m_CustomDefaultBorderList[i];
}


LPCTSTR CColorScheme::GetColorName(int Type)
{
	if (Type < 0 || Type >= NUM_COLORS)
		return nullptr;
	return m_ColorInfoList[Type].pszName;
}


COLORREF CColorScheme::GetDefaultColor(BaseSchemeType BaseScheme, int Type)
{
	if (Type < 0 || Type >= NUM_COLORS)
		return CLR_INVALID;
	if (BaseScheme == BaseSchemeType::Light
			&& m_ColorInfoList[Type].DefaultLightColor != CLR_INVALID)
		return m_ColorInfoList[Type].DefaultLightColor;
	return m_ColorInfoList[Type].DefaultColor;
}


Theme::GradientType CColorScheme::GetDefaultGradientType(int Gradient)
{
	return Theme::GradientType::Normal;
}


bool CColorScheme::GetDefaultGradientStyle(int Gradient, GradientStyle *pStyle)
{
	if (Gradient < 0 || Gradient >= NUM_GRADIENTS)
		return false;
	pStyle->Type = Theme::GradientType::Normal;
	pStyle->Direction = m_GradientInfoList[Gradient].Direction;
	return true;
}


bool CColorScheme::IsGradientDirectionEnabled(int Gradient)
{
	if (Gradient < 0 || Gradient >= NUM_GRADIENTS)
		return false;
	return m_GradientInfoList[Gradient].fEnableDirection;
}


Theme::BorderType CColorScheme::GetDefaultBorderType(int Border)
{
	if (Border < 0 || Border >= NUM_BORDERS)
		return Theme::BorderType::None;
	return m_BorderInfoList[Border].DefaultType;
}


bool CColorScheme::IsLoaded(int Type) const
{
	if (Type < 0 || Type >= NUM_COLORS)
		return false;
	return m_LoadedFlags[Type];
}


void CColorScheme::SetLoaded()
{
	m_LoadedFlags.set();
}


bool CColorScheme::CompareScheme(const CColorScheme &Scheme) const
{
	for (int i = 0; i < NUM_COLORS; i++) {
		if (Scheme.IsLoaded(i) && m_ColorList[i] != Scheme.m_ColorList[i])
			return false;
	}

	for (int i = 0; i < NUM_GRADIENTS; i++) {
		if (m_FillList[i] != Scheme.m_FillList[i])
			return false;
	}

	for (int i = 0; i < NUM_BORDERS; i++) {
		if (m_BorderList[i] != Scheme.m_BorderList[i])
			return false;
	}

	return true;
}


int CColorScheme::GetColorGradient(int Type)
{
	for (int i = 0; i < NUM_GRADIENTS; i++) {
		if (m_GradientInfoList[i].Color1 == Type
				|| m_GradientInfoList[i].Color2 == Type)
			return i;
	}
	return -1;
}


int CColorScheme::GetColorBorder(int Type)
{
	for (int i = 0; i < NUM_BORDERS; i++) {
		if (m_BorderInfoList[i].Color == Type)
			return i;
	}
	return -1;
}


void CColorScheme::SetLoadedFlag(int Color)
{
	m_LoadedFlags.set(Color);
}




bool CColorSchemeList::Add(CColorScheme *pColorScheme)
{
	if (pColorScheme == nullptr)
		return false;
	m_List.emplace_back(pColorScheme);
	return true;
}


bool CColorSchemeList::Insert(int Index, CColorScheme *pColorScheme)
{
	if (Index < 0)
		return false;
	if (static_cast<size_t>(Index) >= m_List.size())
		return Add(pColorScheme);
	auto i = m_List.begin();
	std::advance(i, Index);
	m_List.emplace(i, pColorScheme);
	return true;
}


bool CColorSchemeList::Load(LPCTSTR pszDirectory)
{
	WIN32_FIND_DATA wfd;
	TCHAR szFileName[MAX_PATH];

	::PathCombine(szFileName, pszDirectory, TEXT("*.httheme"));
	const HANDLE hFind = ::FindFirstFileEx(szFileName, FindExInfoBasic, &wfd, FindExSearchNameMatch, nullptr, 0);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
				CColorScheme *pColorScheme;

				::PathCombine(szFileName, pszDirectory, wfd.cFileName);
				pColorScheme = new CColorScheme;
				if (pColorScheme->Load(szFileName))
					Add(pColorScheme);
				else
					delete pColorScheme;
			}
		} while (::FindNextFile(hFind, &wfd));
		::FindClose(hFind);
	}
	return true;
}


void CColorSchemeList::Clear()
{
	m_List.clear();
}


CColorScheme *CColorSchemeList::GetColorScheme(int Index)
{
	if (Index < 0 || static_cast<size_t>(Index) >= m_List.size())
		return nullptr;
	return m_List[Index].get();
}


bool CColorSchemeList::SetColorScheme(int Index, const CColorScheme *pColorScheme)
{
	if (Index < 0 || static_cast<size_t>(Index) >= m_List.size() || pColorScheme == nullptr)
		return false;
	*m_List[Index] = *pColorScheme;
	return true;
}


int CColorSchemeList::FindByName(LPCTSTR pszName, int FirstIndex) const
{
	if (pszName == nullptr)
		return -1;

	for (int i = std::max(FirstIndex, 0); i < static_cast<int>(m_List.size()); i++) {
		if (!IsStringEmpty(m_List[i]->GetName())
				&& ::lstrcmpi(m_List[i]->GetName(), pszName) == 0)
			return i;
	}
	return -1;
}


void CColorSchemeList::SortByName()
{
	if (m_List.size() > 1) {
		std::ranges::sort(
			m_List,
			[](const std::unique_ptr<CColorScheme> &ColorScheme1,
			   const std::unique_ptr<CColorScheme> &ColorScheme2) -> bool {
				return ::lstrcmpi(ColorScheme1->GetName(), ColorScheme2->GetName()) < 0;
			});
	}
}


} // namespace TVTest
