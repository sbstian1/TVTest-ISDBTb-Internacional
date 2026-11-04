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

# 1. ProgramGuide.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\ProgramGuide.cpp", {
    'StringCopy(pszName, TEXT("すべてのチャンネル"), MaxName);':
        'StringCopy(pszName, TEXT("Todos los canales"), MaxName);',
    'StringFormat(pszName, MaxName, TEXT("チューニング空間 {}"), Group + 1);':
        'StringFormat(pszName, MaxName, TEXT("Espacio de sintonización {}"), Group + 1);',
    'TEXT("この番組表から"),': 'TEXT("De esta guía de programas"),',
    'TEXT("全ての番組から"),': 'TEXT("De todos los programas"),',
    'TEXT(" - 番組表を作成しています...")': 'TEXT(" - Creando guía de programas...")',
    'TEXT("番組表を作成しています...")': 'TEXT("Creando guía de programas...")',
    'TEXT(" - 番組表の取得中... [{}/{}] 残り約{}分")': 'TEXT(" - Obteniendo guía... [{}/{}] Restan aprox. {} min")',
    'TEXT("1週間表示")': 'TEXT("Vista semanal (1 semana)")',
    'TEXT("一日前へ")': 'TEXT("Día anterior")',
    'TEXT("一日後へ")': 'TEXT("Día siguiente")',
    'TEXT("チャンネル一覧表示へ")': 'TEXT("Ver lista de canales")',
    'TEXT("今日"),': 'TEXT("Hoy"),',
    'TEXT("明日"),': 'TEXT("Mañana"),',
    'TEXT("2日後"),': 'TEXT("En 2 días"),',
    'TEXT("3日後"),': 'TEXT("En 3 días"),',
    'TEXT("4日後"),': 'TEXT("En 4 días"),',
    'TEXT("5日後"),': 'TEXT("En 5 días"),',
    'TEXT("6日後"),': 'TEXT("En 6 días"),',
    'TEXT("7日後"),': 'TEXT("En 7 días"),',
    'TEXT("選択文字列を検索(&S)")': 'TEXT("&Buscar texto seleccionado")',
    'LPCTSTR GetName() const override { return TEXT("チューナー"); }':
        'LPCTSTR GetName() const override { return TEXT("Sintonizador"); }',
    'LPCTSTR GetName() const override { return TEXT("日時"); }':
        'LPCTSTR GetName() const override { return TEXT("Fecha y hora"); }',
    'LPCTSTR GetName() const override { return TEXT("前へ"); }':
        'LPCTSTR GetName() const override { return TEXT("Anterior"); }',
    'LPCTSTR GetName() const override { return TEXT("次へ"); }':
        'LPCTSTR GetName() const override { return TEXT("Siguiente"); }',
    'StringCopy(szText, TEXT("今日"));':
        'StringCopy(szText, TEXT("Hoy"));',
    'StringCopy(szText, TEXT("現在"));':
        'StringCopy(szText, TEXT("Ahora"));',
    'StringFormat(szText, TEXT("{}時～"), TimeInfo.Hour);':
        'StringFormat(szText, TEXT("{}:00 ~"), TimeInfo.Hour);',
    'TEXT("{:02}時～")':
        'TEXT("{:02}:00 ~")',
    'StringFormat(szText, TEXT("{}時～"), Hour);':
        'StringFormat(szText, TEXT("{}:00 ~"), Hour);',
    '{TEXT("TunerMenu"), TEXT("チューナーメニュー")},':
        '{TEXT("TunerMenu"), TEXT("Menú de sintonizador")},',
    '{TEXT("DateMenu"),  TEXT("日付メニュー")},':
        '{TEXT("DateMenu"),  TEXT("Menú de fecha")},',
    '{TEXT("Favorites"), TEXT("番組表選択ボタン")},':
        '{TEXT("Favorites"), TEXT("Botón de selección de guía")},',
    '{TEXT("DateBar"),   TEXT("日付バー")},':
        '{TEXT("DateBar"),   TEXT("Barra de fecha")},',
    '{TEXT("TimeBar"),   TEXT("時刻バー")},':
        '{TEXT("TimeBar"),   TEXT("Barra de hora")},',
})

# 2. ProgramSearch.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\ProgramSearch.cpp", {
    'TEXT("番組名と番組情報"),': 'TEXT("Nombre e información del programa"),',
    'TEXT("番組名"),': 'TEXT("Nombre del programa"),',
    'TEXT("番組情報"),': 'TEXT("Información del programa"),',
    'TEXT("無料"),': 'TEXT("Gratuito"),',
    'TEXT("有料"),': 'TEXT("De pago"),',
    'DlgComboBox_SetCueBanner(hDlg, IDC_EVENTSEARCH_SETTINGSLIST, TEXT("設定名"));':
        'DlgComboBox_SetCueBanner(hDlg, IDC_EVENTSEARCH_SETTINGSLIST, TEXT("Nombre del perfil"));',
    'TEXT("名前を入力してください。")': 'TEXT("Por favor, ingrese un nombre.")',
    'TEXT("設定の保存")': 'TEXT("Guardar configuración")',
    'pSettings == nullptr ? TEXT("保存") : TEXT("上書き")':
        'pSettings == nullptr ? TEXT("Guardar") : TEXT("Sobrescribir")',
    'TEXT("設定の削除")': 'TEXT("Eliminar configuración")',
    'StringFormat(szText, TEXT("{} 個選択"), CheckCount);':
        'StringFormat(szText, TEXT("{} seleccionados"), CheckCount);',
    'StringCopy(szText, TEXT("指定なし"));':
        'StringCopy(szText, TEXT("Sin especificar"));',
    'lvc.pszText = const_cast<LPTSTR>(TEXT("チャンネル"));':
        'lvc.pszText = const_cast<LPTSTR>(TEXT("Canal"));',
    'lvc.pszText = const_cast<LPTSTR>(TEXT("日時"));':
        'lvc.pszText = const_cast<LPTSTR>(TEXT("Fecha y hora"));',
    'lvc.pszText = const_cast<LPTSTR>(TEXT("番組名"));':
        'lvc.pszText = const_cast<LPTSTR>(TEXT("Nombre del programa"));',
    'TEXT("正規表現が利用できません。")':
        'TEXT("No se puede utilizar la expresión regular.")',
    'StatusFormat.Append(TEXT("指定ジャンルから "));':
        'StatusFormat.Append(TEXT("De géneros seleccionados: "));',
    'StatusFormat.AppendFormat(TEXT("{} に一致する番組"), m_SearchSettings.Keyword);':
        'StatusFormat.AppendFormat(TEXT("Programas que coinciden con \"{}\""), m_SearchSettings.Keyword);',
    'StatusFormat.Append(TEXT("指定ジャンルの番組"));':
        'StatusFormat.Append(TEXT("Programas del género seleccionado"));',
    'StatusFormat.Append(TEXT("すべての番組"));':
        'StatusFormat.Append(TEXT("Todos los programas"));',
    'TEXT(" {} 件 ({}.{:02} 秒)")':
        'TEXT(" {} resultados ({}.{:02} s)")',
})

# 3. FeaturedEvents.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\FeaturedEvents.cpp", {
    'lvg.pszTask = const_cast<LPTSTR>(TEXT("選択"));':
        'lvg.pszTask = const_cast<LPTSTR>(TEXT("Seleccionar"));',
    '{COMMAND_CHECKALL,    TEXT("すべて選択")},':
        '{COMMAND_CHECKALL,    TEXT("Seleccionar todo")},',
    '{COMMAND_UNCHECKALL,  TEXT("すべて解除")},':
        '{COMMAND_UNCHECKALL,  TEXT("Deseleccionar todo")},',
    '{COMMAND_INVERTCHECK, TEXT("選択の反転")},':
        '{COMMAND_INVERTCHECK, TEXT("Invertir selección")},',
    'lvc.pszText = const_cast<LPTSTR>(TEXT("名前"));':
        'lvc.pszText = const_cast<LPTSTR>(TEXT("Nombre"));',
    'lvc.pszText = const_cast<LPTSTR>(TEXT("キーワード"));':
        'lvc.pszText = const_cast<LPTSTR>(TEXT("Palabra clave"));',
    'lvc.pszText = const_cast<LPTSTR>(TEXT("ジャンル"));':
        'lvc.pszText = const_cast<LPTSTR>(TEXT("Género"));',
})

# 4. ProgramGuideTool.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\ProgramGuideTool.cpp", {
    '{TEXT("nid"),          TEXT("ネットワークID")},':
        '{TEXT("nid"),          TEXT("ID de Red")},',
    '{TEXT("tsid"),         TEXT("ストリームID")},':
        '{TEXT("tsid"),         TEXT("ID de Stream")},',
    '{TEXT("tvpid"),        TEXT("iEPGファイル")},':
        '{TEXT("tvpid"),        TEXT("Archivo iEPG")},',
    '{TEXT("duration-sec"), TEXT("番組の長さ(秒単位)")},':
        '{TEXT("duration-sec"), TEXT("Duración del programa (segundos)")},',
    '{TEXT("duration-min"), TEXT("番組の長さ(分単位)")},':
        '{TEXT("duration-min"), TEXT("Duración del programa (minutos)")},',
    'TEXT("パスが長すぎます。")':
        'TEXT("La ruta es demasiado larga.")',
    'TEXT("iEPGファイルの書き出しができません。")':
        'TEXT("No se pudo exportar el archivo iEPG.")',
    'TEXT("実行ファイル(*.exe;*.bat)\\0*.exe;*.bat\\0")':
        'TEXT("Archivos ejecutables (*.exe;*.bat)\\0*.exe;*.bat\\0")',
    'TEXT("すべてのファイル\\0*.*\\0")':
        'TEXT("Todos los archivos\\0*.*\\0")',
})

# 5. Record.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\Record.cpp", {
    'TEXT("呼び出しが不正です。")':
        'TEXT("Llamada no válida.")',
    'TEXT("既に録画中です。")':
        'TEXT("Ya se está grabando.")',
    'DlgComboBox_AddString(hDlg, IDC_RECORD_WRITEPLUGIN, TEXT("使用しない (TS出力)"));':
        'DlgComboBox_AddString(hDlg, IDC_RECORD_WRITEPLUGIN, TEXT("No usar (salida TS)"));',
    'TEXT("TSファイル(*.ts)\\0*.ts\\0すべてのファイル\\0*.*\\0")':
        'TEXT("Archivos TS (*.ts)\\0*.ts\\0Todos los archivos\\0*.*\\0")',
    'ofn.lpstrTitle = TEXT("保存ファイル名");':
        'ofn.lpstrTitle = TEXT("Nombre de archivo de grabación");',
    'TEXT("指定された開始時刻を既に過ぎています。")':
        'TEXT("La hora de inicio especificada ya ha pasado.")',
    'TEXT("指定された停止時刻を既に過ぎています。")':
        'TEXT("La hora de fin especificada ya ha pasado.")',
    'TEXT("ファイル名を入力してください。")':
        'TEXT("Por favor, introduzca un nombre de archivo.")',
    'TEXT("保存先フォルダを入力してください。")':
        'TEXT("Por favor, introduzca la carpeta de destino.")',
    'TEXT("作成しますか?")':
        'TEXT("¿Desea crearla?")',
})

# 6. Plugin.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\Plugin.cpp", {
    'TEXT("DLLがロードできません。(エラーコード {:#x})")':
        'TEXT("No se pudo cargar la DLL. (Código de error {:#x})")',
    'TEXT("ビット用のプラグインではないか、ファイルが破損している可能性があります。")':
        'TEXT("Puede que no sea un plugin compatible con esta arquitectura o el archivo esté dañado.")',
    'SetErrorAdvise(TEXT("必要なランタイムがインストールされていない可能性があります。"));':
        'SetErrorAdvise(TEXT("Es posible que no estén instalados los runtimes necesarios."));',
    'SetErrorText(TEXT("TVTGetVersion()関数のアドレスを取得できません。"));':
        'SetErrorText(TEXT("No se pudo obtener la dirección de TVTGetVersion()."));',
    'SetErrorText(TEXT("対応していないバージョンです。"));':
        'SetErrorText(TEXT("Versión del plugin no compatible."));',
    'SetErrorText(TEXT("TVTGetPluginInfo()関数のアドレスを取得できません。"));':
        'SetErrorText(TEXT("No se pudo obtener la dirección de TVTGetPluginInfo()."));',
    'SetErrorText(TEXT("プラグインの情報を取得できません。"));':
        'SetErrorText(TEXT("No se pudo obtener la información del plugin."));',
    'SetErrorText(TEXT("TVTInitialize()関数のアドレスを取得できません。"));':
        'SetErrorText(TEXT("No se pudo obtener la dirección de TVTInitialize()."));',
    'SetErrorText(TEXT("プラグインの初期化でエラー発生しました。"));':
        'SetErrorText(TEXT("Ocurrió un error al inicializar el plugin."));',
    '::AppendMenu(hmenu, MF_STRING | MF_GRAYED, 0, TEXT("なし"));':
        '::AppendMenu(hmenu, MF_STRING | MF_GRAYED, 0, TEXT("Ninguno"));',
    'lvc.pszText = const_cast<LPTSTR>(TEXT("ファイル名"));':
        'lvc.pszText = const_cast<LPTSTR>(TEXT("Archivo"));',
    'lvc.pszText = const_cast<LPTSTR>(TEXT("プラグイン名"));':
        'lvc.pszText = const_cast<LPTSTR>(TEXT("Nombre del plugin"));',
    'lvc.pszText = const_cast<LPTSTR>(TEXT("説明"));':
        'lvc.pszText = const_cast<LPTSTR>(TEXT("Descripción"));',
    'lvc.pszText = const_cast<LPTSTR>(TEXT("著作権"));':
        'lvc.pszText = const_cast<LPTSTR>(TEXT("Copyright"));',
})

# 7. ChannelScan.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\ChannelScan.cpp", {
    'TEXT("この BonDriver はプリセットとチャンネルが異なっている可能性があります。\\n")':
        'TEXT("Este BonDriver puede tener canales diferentes a los predeterminados.\\n")',
    'TEXT("プリセットを使用せずに、スキャンを行うことをお勧めします。\\n")':
        'TEXT("Se recomienda escanear sin usar los preajustes.\\n")',
    'TEXT("プリセットを読み込みますか？")':
        'TEXT("¿Desea cargar los preajustes?")',
    'TEXT("プリセット読み込み")':
        'TEXT("Cargar preajustes")',
    'TEXT("このチューニング空間にはチャンネルがありません。\\n")':
        'TEXT("No hay canales en este espacio de sintonización.\\n")',
    'TEXT("正しいチューニング空間が選択されているか、\\n")':
        'TEXT("Compruebe si seleccionó el espacio correcto\\n")',
    'TEXT("チューナーが正しく設定されているか確認してください。")':
        'TEXT("o si el sintonizador está configurado adecuadamente.")',
    'TEXT("元あったチャンネルのうち、以下の{}{}のチャンネルが検出されませんでした。\\n\\n")':
        'TEXT("De los canales anteriores, los siguientes {}{} no fueron detectados:\\n\\n")',
    'TEXT("\\n検出されなかったチャンネルを残しますか？")':
        'TEXT("\\n¿Desea conservar los canales que no fueron detectados?")',
    'TEXT("問い合わせ")':
        'TEXT("Consulta")',
    'TEXT("{} のチャンネルスキャン結果を\\n以下の BonDriver にも反映させますか？\\n\\n")':
        'TEXT("¿Desea aplicar los resultados del escaneo de {}\\ntambién a los siguientes BonDriver?\\n\\n")',
    'TEXT("{}チャンネルのうち、{}回のチャンネル変更が BonDriver に受け付けられませんでした。\\n")':
        'TEXT("De {} canales, {} cambios de canal no fueron aceptados por el BonDriver.\\n")',
    'TEXT("(受信できるチャンネルが全てスキャンできていれば問題はありません)")':
        'TEXT("(Si todos los canales recibibles fueron escaneados, no hay inconveniente)")',
    'TEXT("チャンネル変更の要求が BonDriver に受け付けられないため、スキャンを行えませんでした。")':
        'TEXT("No se pudo escanear porque el BonDriver no aceptó la solicitud de cambio de canal.")',
    'TEXT("タイムアウトのためチャンネル変更ができません。")':
        'TEXT("Tiempo de espera agotado al cambiar de canal.")',
})

# 8. EpgCapture.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\EpgCapture.cpp", {
    'TEXT("コマンドラインオプションでEPG情報を取得しないように指定されているため、\\n番組表の取得ができません。")':
        'TEXT("No se puede obtener la guía porque se deshabilitó la descarga de EPG por línea de comandos.")',
    'TEXT("録画中は番組表の取得を行えません。")':
        'TEXT("No se puede obtener la guía de programas durante una grabación.")',
    'TEXT("ネットワーク再生及びファイル再生では番組表の取得はできません。")':
        'TEXT("No se puede obtener la guía durante la reproducción en red o desde archivo.")',
})
