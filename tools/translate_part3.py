# -*- coding: utf-8 -*-

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

# 1. EpgOptions.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\EpgOptions.cpp", {
    'ofn.lpstrFilter = TEXT("すべてのファイル\\0*.*\\0");':
        'ofn.lpstrFilter = TEXT("Todos los archivos\\0*.*\\0");',
    'ofn.lpstrTitle = TEXT("EPGファイル名");':
        'ofn.lpstrTitle = TEXT("Nombre de archivo EPG");',
    'BrowseFolderDialog(hDlg, szFolder, TEXT("EPGデータのフォルダ"))':
        'BrowseFolderDialog(hDlg, szFolder, TEXT("Carpeta de datos EPG"))',
    'ofn.lpstrTitle = TEXT("ロゴファイル名");':
        'ofn.lpstrTitle = TEXT("Nombre de archivo de logos");',
    'BrowseFolderDialog(hDlg, szFolder, TEXT("ロゴのフォルダ"))':
        'BrowseFolderDialog(hDlg, szFolder, TEXT("Carpeta de logos"))',
})

# 2. EventInfoPopup.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\EventInfoPopup.cpp", {
    'Formatter.AppendFormat(TEXT("\\r\\n■ 映像： {}"), pszVideo);':
        'Formatter.AppendFormat(TEXT("\\r\\n■ Video: {}"), pszVideo);',
    'Formatter.Append(TEXT("\\r\\n■ 音声： "));':
        'Formatter.Append(TEXT("\\r\\n■ Audio: "));',
    'Formatter.Append(TEXT("主: "));':
        'Formatter.Append(TEXT("Princ: "));',
    'Formatter.Append(TEXT(" / 副: "));':
        'Formatter.Append(TEXT(" / Sec: "));',
    'Formatter.AppendFormat(TEXT("\\r\\n■ ジャンル： {}"), pszGenre);':
        'Formatter.AppendFormat(TEXT("\\r\\n■ Género: {}"), pszGenre);',
    'Formatter.AppendFormat(TEXT("\\r\\n■ イベントID： {:#04x}"), m_EventInfo.EventID);':
        'Formatter.AppendFormat(TEXT("\\r\\n■ ID de Evento: {:#04x}"), m_EventInfo.EventID);',
    'TEXT(" (イベント共有 サービスID {:#04x} / イベントID {:#04x})")':
        'TEXT(" (Evento compartido Serv. {:#04x} / Evento {:#04x})")',
    'pszAudio = TEXT("Mono 二カ国語");':
        'pszAudio = TEXT("Mono dual");',
    'Menu.Append(1, TEXT("番組名をコピー(&C)"));':
        'Menu.Append(1, TEXT("&Copiar nombre del programa"));',
    'Menu.Append(COMMAND_COPY, TEXT("コピー(&C)"));':
        'Menu.Append(COMMAND_COPY, TEXT("&Copiar"));',
    'Menu.Append(COMMAND_SELECTALL, TEXT("すべて選択(&A)"));':
        'Menu.Append(COMMAND_SELECTALL, TEXT("Seleccionar &todo"));',
    'Menu.Append(COMMAND_COPYEVENTNAME, TEXT("番組名をコピー(&E)"));':
        'Menu.Append(COMMAND_COPYEVENTNAME, TEXT("Copiar nombr&e del programa"));',
})

# 3. EventInfoUtil.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\EventInfoUtil.cpp", {
    'Menu.Append(COMMAND_COPY, TEXT("コピー(&C)"));':
        'Menu.Append(COMMAND_COPY, TEXT("&Copiar"));',
    'Menu.Append(COMMAND_SELECTALL, TEXT("すべて選択(&A)"));':
        'Menu.Append(COMMAND_SELECTALL, TEXT("Seleccionar &todo"));',
})

# 4. Favorites.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\Favorites.cpp", {
    '::InsertMenu(hmenu, 0, MF_BYPOSITION | MF_STRING | MF_GRAYED, 0, TEXT("なし"));':
        '::InsertMenu(hmenu, 0, MF_BYPOSITION | MF_STRING | MF_GRAYED, 0, TEXT("Ninguno"));',
    '::AppendMenu(hmenu, MF_STRING | MF_GRAYED, 0, TEXT("なし"));':
        '::AppendMenu(hmenu, MF_STRING | MF_GRAYED, 0, TEXT("Ninguno"));',
    'Menu.Append(IDC_FAVORITES_DELETE, TEXT("削除(&D)"));':
        'Menu.Append(IDC_FAVORITES_DELETE, TEXT("&Eliminar"));',
    'Menu.Append(IDC_FAVORITES_RENAME, TEXT("名前の変更(&R)"));':
        'Menu.Append(IDC_FAVORITES_RENAME, TEXT("&Cambiar nombre"));',
    'Menu.Append(IDC_FAVORITES_PROPERTIES, TEXT("プロパティ(&P)..."));':
        'Menu.Append(IDC_FAVORITES_PROPERTIES, TEXT("&Propiedades..."));',
    'pNewFolder->SetName(TEXT("新規フォルダ"));':
        'pNewFolder->SetName(TEXT("Nueva carpeta"));',
})

# 5. Logger.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\Logger.cpp", {
    'lvc.pszText = const_cast<LPTSTR>(TEXT("日時"));':
        'lvc.pszText = const_cast<LPTSTR>(TEXT("Fecha y hora"));',
    'lvc.pszText = const_cast<LPTSTR>(TEXT("内容"));':
        'lvc.pszText = const_cast<LPTSTR>(TEXT("Contenido"));',
    '::MessageBox(hDlg, TEXT("保存ができません。"), nullptr, MB_OK | MB_ICONEXCLAMATION);':
        '::MessageBox(hDlg, TEXT("No se pudo guardar el registro."), nullptr, MB_OK | MB_ICONEXCLAMATION);',
    '::MessageBox(hDlg, szMessage, TEXT("ログ保存"), MB_OK | MB_ICONINFORMATION);':
        '::MessageBox(hDlg, szMessage, TEXT("Guardar registro"), MB_OK | MB_ICONINFORMATION);',
})

# 6. MessageDialog.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\MessageDialog.cpp", {
    'CRichEditUtil::AppendText(hwndEdit, TEXT("\\n\\nWindowsのエラーメッセージ :\\n"), &cfBold);':
        'CRichEditUtil::AppendText(hwndEdit, TEXT("\\n\\nMensaje de error de Windows:\\n"), &cfBold);',
    'Menu.Append(IDC_ERROR_COPY, TEXT("コピー(&C)"));':
        'Menu.Append(IDC_ERROR_COPY, TEXT("&Copiar"));',
    'Formatter.Append(TEXT("Windowsのエラーメッセージ:\\n"));':
        'Formatter.Append(TEXT("Mensaje de error de Windows:\\n"));',
})

# 7. ProgramGuideOptions.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\ProgramGuideOptions.cpp", {
    'FavoriteInfo.Name = TEXT("お気に入りチャンネル");':
        'FavoriteInfo.Name = TEXT("Canales favoritos");',
    'FavoriteInfo.Label = TEXT("お気に入り");':
        'FavoriteInfo.Label = TEXT("Favoritos");',
    'DlgComboBox_AddString(hDlg, IDC_PROGRAMGUIDEOPTIONS_BEGINHOUR, TEXT("現在時"));':
        'DlgComboBox_AddString(hDlg, IDC_PROGRAMGUIDEOPTIONS_BEGINHOUR, TEXT("Hora actual"));',
    'StringFormat(szText, TEXT("{}時"), i);':
        'StringFormat(szText, TEXT("{}:00"), i);',
    'DlgComboBox_AddString(hDlg, IDC_PROGRAMGUIDEOPTIONS_PROGRAMLDOUBLECLICK, TEXT("何もしない"));':
        'DlgComboBox_AddString(hDlg, IDC_PROGRAMGUIDEOPTIONS_PROGRAMLDOUBLECLICK, TEXT("No hacer nada"));',
    'DlgComboBox_AddString(hDlg, IDC_PROGRAMGUIDEOPTIONS_PROGRAMLDOUBLECLICK, TEXT("iEPG関連付け実行"));':
        'DlgComboBox_AddString(hDlg, IDC_PROGRAMGUIDEOPTIONS_PROGRAMLDOUBLECLICK, TEXT("Ejecutar iEPG asociado"));',
    'lvc.pszText = const_cast<LPTSTR>(TEXT("名前"));':
        'lvc.pszText = const_cast<LPTSTR>(TEXT("Nombre"));',
    'lvc.pszText = const_cast<LPTSTR>(TEXT("コマンド"));':
        'lvc.pszText = const_cast<LPTSTR>(TEXT("Comando"));',
})

# 8. GeneralOptions.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\GeneralOptions.cpp", {
    'BrowseFolderDialog(hDlg, szDirectory, TEXT("BonDriver の検索フォルダを選択してください。"))':
        'BrowseFolderDialog(hDlg, szDirectory, TEXT("Seleccione la carpeta de búsqueda de BonDriver."))',
    'ofn.lpstrFilter = TEXT("すべてのファイル\\0*.*\\0");':
        'ofn.lpstrFilter = TEXT("Todos los archivos\\0*.*\\0");',
    'ofn.lpstrTitle = TEXT("BonDriverの選択");':
        'ofn.lpstrTitle = TEXT("Seleccionar BonDriver");',
})

# 9. DriverOptions.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\DriverOptions.cpp", {
    'DlgComboBox_AddString(m_hDlg, IDC_DRIVEROPTIONS_INITCHANNEL_SPACE, TEXT("すべて"));':
        'DlgComboBox_AddString(m_hDlg, IDC_DRIVEROPTIONS_INITCHANNEL_SPACE, TEXT("Todos"));',
    'DlgComboBox_AddString(m_hDlg, IDC_DRIVEROPTIONS_INITCHANNEL_CHANNEL, TEXT("指定なし"));':
        'DlgComboBox_AddString(m_hDlg, IDC_DRIVEROPTIONS_INITCHANNEL_CHANNEL, TEXT("Sin especificar"));',
    'TEXT("設定する BonDriver を選択してください")':
        'TEXT("Seleccione el BonDriver a configurar")',
})

# 10. HomeDisplay.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\HomeDisplay.cpp", {
    'return TEXT("お気に入り");': 'return TEXT("Favoritos");',
    'return TEXT("最近見たチャンネル");': 'return TEXT("Canales recientes");',
    'return TEXT("注目の番組");': 'return TEXT("Programas destacados");',
    'pszText = TEXT("注目の番組を表示するには、右クリックメニューの [注目の番組の設定] から検索条件を登録します。");':
        'pszText = TEXT("Para ver programas destacados, registre criterios de búsqueda en [Configurar programas destacados] del menú clic derecho.");',
    'pszText = TEXT("検索された番組はありません。");':
        'pszText = TEXT("No se encontraron programas.");',
})

# 11. ChannelHistory.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\ChannelHistory.cpp", {
    '::InsertMenu(hmenu, 0, MF_GRAYED, 0, TEXT("なし"));':
        '::InsertMenu(hmenu, 0, MF_GRAYED, 0, TEXT("Ninguno"));',
})

# 12. MenuOptions.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\MenuOptions.cpp", {
    'StringCopy(pszText, TEXT("　<区切り>"), MaxLength);':
        'StringCopy(pszText, TEXT("  <Separador>"), MaxLength);',
})

# 13. SideBarOptions.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\SideBarOptions.cpp", {
    'lvi.pszText = const_cast<LPTSTR>(TEXT("(区切り)"));':
        'lvi.pszText = const_cast<LPTSTR>(TEXT("(Separador)"));',
    'StringCopy(szText, TEXT("(区切り)"));':
        'StringCopy(szText, TEXT("(Separador)"));',
})

# 14. Taskbar.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\Taskbar.cpp", {
    'm_pTaskbarList->SetOverlayIcon(m_hwnd, hico, TEXT("録画中"));':
        'm_pTaskbarList->SetOverlayIcon(m_hwnd, hico, TEXT("Grabando"));',
})

# 15. InformationPanel.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\InformationPanel.cpp", {
    'Menu.Append(1, TEXT("コピー(&C)"));':
        'Menu.Append(1, TEXT("&Copiar"));',
    'Menu.Append(2, TEXT("すべて選択(&A)"));':
        'Menu.Append(2, TEXT("Seleccionar &todo"));',
    'TEXT(" 終了予定{}/{}/{}")':
        'TEXT(" Fin est. {}/{}/{}")',
})

# 16. CaptionPanel.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\CaptionPanel.cpp", {
    'TEXT("ファイルを保存できません。")':
        'TEXT("No se pudo guardar el archivo.")',
    'StringFormat(szText, TEXT("言語{}"), i + 1);':
        'StringFormat(szText, TEXT("Idioma {}"), i + 1);',
})
