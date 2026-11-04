# -*- coding: utf-8 -*-
import sys
sys.stdout.reconfigure(encoding='utf-8')

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

# 8. GeneralOptions.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\GeneralOptions.cpp", {
    'TEXT("BonDriver の検索フォルダを選択してください。")':
        'TEXT("Seleccione la carpeta de búsqueda de BonDriver.")',
    'TEXT("すべてのファイル\\0*.*\\0");':
        'TEXT("Todos los archivos\\0*.*\\0");',
    'TEXT("BonDriverの選択")':
        'TEXT("Seleccionar BonDriver")',
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
