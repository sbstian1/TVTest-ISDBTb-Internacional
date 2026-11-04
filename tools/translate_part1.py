# -*- coding: utf-8 -*-
import re

def replace_in_file(path, replacements):
    with open(path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    count = 0
    for old, new in replacements.items():
        if old in content:
            content = content.replace(old, new)
            count += 1
        else:
            print(f"Warning: target not found in {path}: {repr(old)[:60]}")
    
    with open(path, 'w', encoding='utf-8') as f:
        f.write(content)
    print(f"Updated {path}: {count}/{len(replacements)} replacements applied.")

# 1. Util.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\Util.cpp", {
    'return TEXT("日\\0月\\0火\\0水\\0木\\0金\\0土") + DayOfWeek * ((3 - sizeof(TCHAR)) + 1);':
        'static const TCHAR * const DayNames[] = { TEXT("Do"), TEXT("Lu"), TEXT("Ma"), TEXT("Mi"), TEXT("Ju"), TEXT("Vi"), TEXT("Sá") };\n\treturn DayNames[DayOfWeek];',
    'TEXT("ファイル名に使用できない文字 {:#02x} が含まれています。")':
        'TEXT("El nombre de archivo contiene un carácter no válido {:#02x}.")',
    'TEXT("ファイル名に使用できない文字 {:c} が含まれています。")':
        'TEXT("El nombre de archivo contiene un carácter no válido {:c}.")',
})

# 2. TitleBar.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\TitleBar.cpp", {
    'TEXT("最小化")': 'TEXT("Minimizar")',
    'TEXT("最大化")': 'TEXT("Maximizar")',
    'TEXT("全画面表示")': 'TEXT("Pantalla completa")',
    'TEXT("閉じる")': 'TEXT("Cerrar")',
    'StringCopy(pnmttdi->szText, TEXT("元のサイズに戻す"));':
        'StringCopy(pnmttdi->szText, TEXT("Restaurar tamaño"));',
    'StringCopy(pnmttdi->szText, TEXT("全画面表示解除"));':
        'StringCopy(pnmttdi->szText, TEXT("Salir de pantalla completa"));',
})

# 3. Panel.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\Panel.cpp", {
    'Menu.Append(1, TEXT("閉じる(&C)"));': 'Menu.Append(1, TEXT("&Cerrar"));',
    'Menu.Append(2, TEXT("切り離す(&F)"));': 'Menu.Append(2, TEXT("&Desacoplar"));',
    'InsertMenu(hmenu, 0, MF_BYPOSITION | MF_STRING | MF_ENABLED, SC_DOCKING, TEXT("ドッキング(&D)"));':
        'InsertMenu(hmenu, 0, MF_BYPOSITION | MF_STRING | MF_ENABLED, SC_DOCKING, TEXT("&Acoplar"));',
    '::AppendMenu(hmenu, MF_STRING | MF_ENABLED, PANEL_MENU_LEFT, TEXT("左へ(&L)"));':
        '::AppendMenu(hmenu, MF_STRING | MF_ENABLED, PANEL_MENU_LEFT, TEXT("A la &izquierda"));',
    '::AppendMenu(hmenu, MF_STRING | MF_ENABLED, PANEL_MENU_RIGHT, TEXT("右へ(&R)"));':
        '::AppendMenu(hmenu, MF_STRING | MF_ENABLED, PANEL_MENU_RIGHT, TEXT("A la &derecha"));',
    '::AppendMenu(hmenu, MF_STRING | MF_ENABLED, PANEL_MENU_TOP, TEXT("上へ(&T)"));':
        '::AppendMenu(hmenu, MF_STRING | MF_ENABLED, PANEL_MENU_TOP, TEXT("A&rriba"));',
    '::AppendMenu(hmenu, MF_STRING | MF_ENABLED, PANEL_MENU_BOTTOM, TEXT("下へ(&B)"));':
        '::AppendMenu(hmenu, MF_STRING | MF_ENABLED, PANEL_MENU_BOTTOM, TEXT("A&bajo"));',
})

# 4. PanelForm.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\PanelForm.cpp", {
    'm_pszClassName, TEXT("パネル"), m_hinst);':
        'm_pszClassName, TEXT("Panel"), m_hinst);',
})

# 5. MainWindow.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\MainWindow.cpp", {
    'PageInfo.pszTitle = TEXT("情報");': 'PageInfo.pszTitle = TEXT("Info");',
    'PageInfo.pszTitle = TEXT("番組表");': 'PageInfo.pszTitle = TEXT("Guía");',
    'PageInfo.pszTitle = TEXT("チャンネル");': 'PageInfo.pszTitle = TEXT("Canales");',
    'PageInfo.pszTitle = TEXT("操作");': 'PageInfo.pszTitle = TEXT("Control");',
    'PageInfo.pszTitle = TEXT("字幕");': 'PageInfo.pszTitle = TEXT("Subtít.");',
    'CONTAINER_ID_PANEL, &m_App.Panel.Form, TEXT("パネル"));':
        'CONTAINER_ID_PANEL, &m_App.Panel.Form, TEXT("Panel"));',
    'm_Panel.SetWindow(&m_App.Panel.Form, TEXT("パネル"));':
        'm_Panel.SetWindow(&m_App.Panel.Form, TEXT("Panel"));',
    'pPanel->SetWindow(&m_App.Panel.Form, TEXT("パネル"));':
        'pPanel->SetWindow(&m_App.Panel.Form, TEXT("Panel"));',
    '::AppendMenu(hmenu, MF_STRING | MF_ENABLED, PANEL_MENU_LEFT, TEXT("左へ(&L)"));':
        '::AppendMenu(hmenu, MF_STRING | MF_ENABLED, PANEL_MENU_LEFT, TEXT("A la &izquierda"));',
    '::AppendMenu(hmenu, MF_STRING | MF_ENABLED, PANEL_MENU_RIGHT, TEXT("右へ(&R)"));':
        '::AppendMenu(hmenu, MF_STRING | MF_ENABLED, PANEL_MENU_RIGHT, TEXT("A la &derecha"));',
    '::AppendMenu(hmenu, MF_STRING | MF_ENABLED, PANEL_MENU_TOP, TEXT("上へ(&T)"));':
        '::AppendMenu(hmenu, MF_STRING | MF_ENABLED, PANEL_MENU_TOP, TEXT("A&rriba"));',
    '::AppendMenu(hmenu, MF_STRING | MF_ENABLED, PANEL_MENU_BOTTOM, TEXT("下へ(&B)"));':
        '::AppendMenu(hmenu, MF_STRING | MF_ENABLED, PANEL_MENU_BOTTOM, TEXT("A&bajo"));',
    'SC_ABOUT, TEXT("バージョン情報(&A)"));':
        'SC_ABOUT, TEXT("&Acerca de TVTest..."));',
    'TEXT("このチャンネルは放送休止中です")':
        'TEXT("Este canal está fuera de transmisión")',
    'ShowErrorMessage(TEXT("ファイルへの書き出しでエラーが発生しました。"));':
        'ShowErrorMessage(TEXT("Error al escribir en el archivo."));',
    'm_App.StatusView.SetSingleText(TEXT("起動中..."));':
        'm_App.StatusView.SetSingleText(TEXT("Iniciando..."));',
    'TEXT("S/PDIFパススルー出力ができません。\\n")':
        'TEXT("No se pudo iniciar la salida S/PDIF passthrough.\\n")',
    'TEXT("デバイスがパススルー出力に対応しているか、\\n")':
        'TEXT("Compruebe si el dispositivo admite passthrough\\n")',
    'TEXT("またパススルー出力できるように設定されているか確認してください。")':
        'TEXT("y si está configurado correctamente.")',
    'TEXT("S/PDIFパススルー出力エラー")':
        'TEXT("Error de salida S/PDIF passthrough")',
    'StringFormat(szName, TEXT("サービス{}"), i + 1);':
        'StringFormat(szName, TEXT("Servicio {}"), i + 1);',
    'Length = StringFormat(pszText, MaxText, TEXT("音声{}"), StreamNumber + 1);':
        'Length = StringFormat(pszText, MaxText, TEXT("Audio {}"), StreamNumber + 1);',
    'Length = StringFormat(szText, TEXT("メイン"));':
        'Length = StringFormat(szText, TEXT("Principal"));',
    'Length = StringFormat(szText, TEXT("サブ{}"), SubGroupCount + 1);':
        'Length = StringFormat(szText, TEXT("Secundario {}"), SubGroupCount + 1);',
    'Menu.Append(0U, TEXT("音声なし"), MF_GRAYED);':
        'Menu.Append(0U, TEXT("Sin audio"), MF_GRAYED);',
    'StringCopy(szText, TEXT("メイン"));':
        'StringCopy(szText, TEXT("Principal"));',
    'StringFormat(szText, TEXT("サブ{}"), SubGroupCount + 1);':
        'StringFormat(szText, TEXT("Secundario {}"), SubGroupCount + 1);',
    'StringFormat(szText + Length, lengthof(szText) - Length, TEXT(": 映像{}"), VideoCount);':
        'StringFormat(szText + Length, lengthof(szText) - Length, TEXT(": Video {}"), VideoCount);',
    'const size_t Length = StringFormat(szText, TEXT("映像{}"), VideoCount);':
        'const size_t Length = StringFormat(szText, TEXT("Video {}"), VideoCount);',
    'StringCopy(szText + Length, TEXT(" (降雨対応放送)"), lengthof(szText) - Length);':
        'StringCopy(szText + Length, TEXT(" (Transmisión aux. lluvia)"), lengthof(szText) - Length);',
    'szText, TEXT("{}{}: 映像{}"),':
        'szText, TEXT("{}{}: Video {}"),',
    'Menu.Append(0U, TEXT("映像なし"), MF_GRAYED);':
        'Menu.Append(0U, TEXT("Sin video"), MF_GRAYED);',
    'm_App.OSDManager.ShowOSD(TEXT("●録画"));':
        'm_App.OSDManager.ShowOSD(TEXT("● Grabando"));',
    'm_App.OSDManager.ShowOSD(TEXT("■録画停止"));':
        'm_App.OSDManager.ShowOSD(TEXT("■ Grabación detenida"));',
    'm_App.Epg.ProgramGuide.SetMessage(TEXT("EPGファイルの読み込み中..."));':
        'm_App.Epg.ProgramGuide.SetMessage(TEXT("Cargando archivo EPG..."));',
    'APP_NAME TEXT("の録画ファイルの保存先の空き容量が少なくなっています。")':
        'APP_NAME TEXT(": Poco espacio libre en disco para guardar grabaciones.")',
    'TEXT("空き容量が少なくなっています。")':
        'TEXT("Poco espacio disponible en disco.")',
    'TEXT("録画ファイルの保存先の空き容量が少なくなっています")':
        'TEXT("Poco espacio libre para grabaciones")',
})
