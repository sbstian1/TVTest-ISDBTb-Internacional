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

# 1. Accelerator.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\Accelerator.cpp", {
    '{APPCOMMAND_VOLUME_UP,                         TEXT("音量+")},':
        '{APPCOMMAND_VOLUME_UP,                         TEXT("Volumen +")},',
    '{APPCOMMAND_VOLUME_DOWN,                       TEXT("音量-")},':
        '{APPCOMMAND_VOLUME_DOWN,                       TEXT("Volumen -")},',
    '{APPCOMMAND_VOLUME_MUTE,                       TEXT("消音")},':
        '{APPCOMMAND_VOLUME_MUTE,                       TEXT("Silenciar")},',
    '{APPCOMMAND_MEDIA_PLAY_PAUSE,                  TEXT("再生/一時停止")},':
        '{APPCOMMAND_MEDIA_PLAY_PAUSE,                  TEXT("Reproducir / Pausar")},',
    '{APPCOMMAND_MEDIA_PLAY,                        TEXT("再生")},':
        '{APPCOMMAND_MEDIA_PLAY,                        TEXT("Reproducir")},',
    '{APPCOMMAND_MEDIA_PAUSE,                       TEXT("一時停止")},':
        '{APPCOMMAND_MEDIA_PAUSE,                       TEXT("Pausar")},',
    '{APPCOMMAND_MEDIA_STOP,                        TEXT("停止")},':
        '{APPCOMMAND_MEDIA_STOP,                        TEXT("Detener")},',
    '{APPCOMMAND_MEDIA_RECORD,                      TEXT("録音/録画")},':
        '{APPCOMMAND_MEDIA_RECORD,                      TEXT("Grabar")},',
    '{APPCOMMAND_MEDIA_CHANNEL_UP,                  TEXT("チャンネル+")},':
        '{APPCOMMAND_MEDIA_CHANNEL_UP,                  TEXT("Canal +")},',
    '{APPCOMMAND_MEDIA_CHANNEL_DOWN,                TEXT("チャンネル-")},':
        '{APPCOMMAND_MEDIA_CHANNEL_DOWN,                TEXT("Canal -")},',
    '{APPCOMMAND_MEDIA_PREVIOUSTRACK,               TEXT("前のトラック")},':
        '{APPCOMMAND_MEDIA_PREVIOUSTRACK,               TEXT("Pista anterior")},',
    '{APPCOMMAND_MEDIA_NEXTTRACK,                   TEXT("次のトラック")},':
        '{APPCOMMAND_MEDIA_NEXTTRACK,                   TEXT("Pista siguiente")},',
    '{APPCOMMAND_MEDIA_REWIND,                      TEXT("巻き戻し")},':
        '{APPCOMMAND_MEDIA_REWIND,                      TEXT("Rebobinar")},',
    '{APPCOMMAND_MEDIA_FAST_FORWARD,                TEXT("早送り")},':
        '{APPCOMMAND_MEDIA_FAST_FORWARD,                TEXT("Avance rápido")},',
    '{APPCOMMAND_BROWSER_BACKWARD,                  TEXT("戻る")},':
        '{APPCOMMAND_BROWSER_BACKWARD,                  TEXT("Atrás")},',
    '{APPCOMMAND_BROWSER_FORWARD,                   TEXT("進む")},':
        '{APPCOMMAND_BROWSER_FORWARD,                   TEXT("Adelante")},',
    '{APPCOMMAND_BROWSER_HOME,                      TEXT("ホーム")},':
        '{APPCOMMAND_BROWSER_HOME,                      TEXT("Inicio")},',
    '{APPCOMMAND_BROWSER_STOP,                      TEXT("中止")},':
        '{APPCOMMAND_BROWSER_STOP,                      TEXT("Detener navegador")},',
    '{APPCOMMAND_BROWSER_FAVORITES,                 TEXT("お気に入り")},':
        '{APPCOMMAND_BROWSER_FAVORITES,                 TEXT("Favoritos")},',
    '{APPCOMMAND_BROWSER_REFRESH,                   TEXT("更新")},':
        '{APPCOMMAND_BROWSER_REFRESH,                   TEXT("Actualizar")},',
    '{APPCOMMAND_BROWSER_SEARCH,                    TEXT("Web検索")},':
        '{APPCOMMAND_BROWSER_SEARCH,                    TEXT("Buscar en Web")},',
    '{APPCOMMAND_NEW,                               TEXT("新規作成")},':
        '{APPCOMMAND_NEW,                               TEXT("Nuevo")},',
    '{APPCOMMAND_OPEN,                              TEXT("開く")},':
        '{APPCOMMAND_OPEN,                              TEXT("Abrir")},',
    '{APPCOMMAND_SAVE,                              TEXT("保存")},':
        '{APPCOMMAND_SAVE,                              TEXT("Guardar")},',
    '{APPCOMMAND_PRINT,                             TEXT("印刷")},':
        '{APPCOMMAND_PRINT,                             TEXT("Imprimir")},',
    '{APPCOMMAND_CLOSE,                             TEXT("閉じる")},':
        '{APPCOMMAND_CLOSE,                             TEXT("Cerrar")},',
    '{APPCOMMAND_UNDO,                              TEXT("元に戻す")},':
        '{APPCOMMAND_UNDO,                              TEXT("Deshacer")},',
    '{APPCOMMAND_REDO,                              TEXT("やり直し")},':
        '{APPCOMMAND_REDO,                              TEXT("Rehacer")},',
    '{APPCOMMAND_CUT,                               TEXT("切り取り")},':
        '{APPCOMMAND_CUT,                               TEXT("Cortar")},',
    '{APPCOMMAND_COPY,                              TEXT("コピー")},':
        '{APPCOMMAND_COPY,                              TEXT("Copiar")},',
    '{APPCOMMAND_PASTE,                             TEXT("貼り付け")},':
        '{APPCOMMAND_PASTE,                             TEXT("Pegar")},',
    '{APPCOMMAND_FIND,                              TEXT("検索")},':
        '{APPCOMMAND_FIND,                              TEXT("Buscar")},',
    '{APPCOMMAND_HELP,                              TEXT("ヘルプ")},':
        '{APPCOMMAND_HELP,                              TEXT("Ayuda")},',
    '{APPCOMMAND_CORRECTION_LIST,                   TEXT("訂正候補")},':
        '{APPCOMMAND_CORRECTION_LIST,                   TEXT("Corrección")},',
    '{APPCOMMAND_SPELL_CHECK,                       TEXT("スペルチェック")},':
        '{APPCOMMAND_SPELL_CHECK,                       TEXT("Ortografía")},',
    'm_ListView.InsertColumn(COLUMN_COMMAND, TEXT("機能"));':
        'm_ListView.InsertColumn(COLUMN_COMMAND, TEXT("Función"));',
    'm_ListView.InsertColumn(COLUMN_KEY, TEXT("キー"));':
        'm_ListView.InsertColumn(COLUMN_KEY, TEXT("Tecla"));',
    'm_ListView.InsertColumn(COLUMN_APPCOMMAND, TEXT("マルチメディアキー"));':
        'm_ListView.InsertColumn(COLUMN_APPCOMMAND, TEXT("Tecla multimedia"));',
    'DlgComboBox_AddString(hDlg, IDC_ACCELERATOR_KEY, TEXT("なし"));':
        'DlgComboBox_AddString(hDlg, IDC_ACCELERATOR_KEY, TEXT("Ninguna"));',
    'DlgComboBox_AddString(hDlg, IDC_ACCELERATOR_APPCOMMAND, TEXT("なし"));':
        'DlgComboBox_AddString(hDlg, IDC_ACCELERATOR_APPCOMMAND, TEXT("Ninguna"));',
    'TEXT("既に [{}] に割り当てられています。\\n割り当て直しますか?")':
        'TEXT("Ya está asignada a [{}].\\n¿Desea reasignarla?")',
    '::MessageBox(hDlg, szText, TEXT("確認"), MB_YESNO | MB_ICONEXCLAMATION)':
        '::MessageBox(hDlg, szText, TEXT("Confirmación"), MB_YESNO | MB_ICONEXCLAMATION)',
    '::lstrcpy(szText, TEXT("データ : "));':
        '::lstrcpy(szText, TEXT("Datos : "));',
})

# 2. AppCommand.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\AppCommand.cpp", {
    'TEXT("BonDriver切替 : {}")': 'TEXT("Cambiar BonDriver : {}")',
    'TEXT("プラグイン有効/無効 : {}")': 'TEXT("Activar/Desactivar plugin : {}")',
    'TEXT("{} 有効/無効")': 'TEXT("{} Activar/Desactivar")',
    'TEXT("現在の画像を取得できません。\\n")': 'TEXT("No se pudo capturar la imagen actual.\\n")',
    'TEXT("レンダラやデコーダを変えてみてください。")': 'TEXT("Pruebe cambiando el renderizador o decodificador.")',
    'TEXT("画像キャプチャ")': 'TEXT("Captura de pantalla")',
    'TEXT("クリップボードにデータを設定できません。")': 'TEXT("No se pudieron copiar los datos al portapapeles.")',
    'TEXT("画像の保存でエラーが発生しました。")': 'TEXT("Ocurrió un error al guardar la imagen.")',
    'TEXT("既に設定されている録画があります。\\n")': 'TEXT("Ya existe una grabación programada.\\n")',
    'TEXT("録画を開始すると既存の設定が破棄されます。\\n")': 'TEXT("Al iniciar la grabación se descartará la configuración existente.\\n")',
    'TEXT("録画を開始してもいいですか?")': 'TEXT("¿Desea iniciar la grabación?")',
    'TEXT("録画開始の確認")': 'TEXT("Confirmar inicio de grabación")',
    'ofn.lpstrTitle = TEXT("BonDriverの選択");': 'ofn.lpstrTitle = TEXT("Seleccionar BonDriver");',
})

# 3. PanAndScanOptions.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\PanAndScanOptions.cpp", {
    'TEXT("2.39:1 シネスコ")': 'TEXT("2.39:1 Cinemascope")',
    'TEXT("2.35:1 シネスコ")': 'TEXT("2.35:1 Cinemascope")',
    'TEXT("1.85:1 ビスタ(米)")': 'TEXT("1.85:1 Vista (EE. UU.)")',
    'TEXT("1.66:1 ビスタ(欧)")': 'TEXT("1.66:1 Vista (Europa)")',
    'lvc.pszText = const_cast<LPTSTR>(TEXT("名前"));':
        'lvc.pszText = const_cast<LPTSTR>(TEXT("Nombre"));',
    'lvc.pszText = const_cast<LPTSTR>(TEXT("設定"));':
        'lvc.pszText = const_cast<LPTSTR>(TEXT("Configuración"));',
    'TEXT("設定ファイル(*.ini)\\0*.ini\\0")':
        'TEXT("Archivo de conf. (*.ini)\\0*.ini\\0")',
    'TEXT("パン&スキャン設定の読み込み")':
        'TEXT("Cargar configuración de Pan & Scan")',
    'TEXT("パン&スキャン設定の保存")':
        'TEXT("Guardar configuración de Pan & Scan")',
    'TEXT("入力された値が正しくありません。")':
        'TEXT("El valor ingresado no es válido.")',
    'TEXT("ファイルを作成できません。")':
        'TEXT("No se pudo crear el archivo.")',
    'TEXT("パン&スキャン{}")':
        'TEXT("Pan & Scan {}")',
})

# 4. TSProcessorOptions.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\TSProcessorOptions.cpp", {
    '{TEXT("チューナー"),     LVCFMT_LEFT},': '{TEXT("Sintonizador"),   LVCFMT_LEFT},',
    '{TEXT("ネットワークID"), LVCFMT_RIGHT},': '{TEXT("ID de Red"),      LVCFMT_RIGHT},',
    '{TEXT("サービスID"),     LVCFMT_RIGHT},': '{TEXT("ID de Servicio"), LVCFMT_RIGHT},',
    '{TEXT("処理"),           LVCFMT_LEFT},': '{TEXT("Procesamiento"),  LVCFMT_LEFT},',
    '{TEXT("モジュール"),     LVCFMT_LEFT},': '{TEXT("Módulo"),         LVCFMT_LEFT},',
    '{TEXT("デバイス"),       LVCFMT_LEFT},': '{TEXT("Dispositivo"),    LVCFMT_LEFT},',
    '{TEXT("フィルター"),     LVCFMT_LEFT},': '{TEXT("Filtro"),         LVCFMT_LEFT},',
    'TEXT("TSプロセッサーはありません")': 'TEXT("No hay procesadores TS")',
    'TEXT("(指定なし)")': 'TEXT("(Sin especificar)")',
    'Settings.fEnableProcessing ? TEXT("有効") : TEXT("無効")':
        'Settings.fEnableProcessing ? TEXT("Habilitado") : TEXT("Deshabilitado")',
})

# 5. DirectWriteOptionsDialog.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\DirectWriteOptionsDialog.cpp", {
    'TEXT("自動"),': 'TEXT("Automático"),',
    'TEXT("アンチエイリアシングなし"),': 'TEXT("Sin suavizado (sin antialias)"),',
    'TEXT("GDI互換(2値互換)"),': 'TEXT("Compatible con GDI (binario)"),',
    'TEXT("GDI互換"),': 'TEXT("Compatible con GDI"),',
    'TEXT("水平アンチエイリアシング"),': 'TEXT("Suavizado horizontal"),',
    'TEXT("水平/垂直アンチエイリアシング"),': 'TEXT("Suavizado bidireccional (H/V)"),',
    'TEXT("アウトライン"),': 'TEXT("Contorno"),',
    'TEXT("フラット"),': 'TEXT("Plano"),',
})

# 6. Capture.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\Capture.cpp", {
    'const LPCTSTR CAPTURE_TITLE_TEXT = TEXT("キャプチャ");':
        'const LPCTSTR CAPTURE_TITLE_TEXT = TEXT("Captura");',
    'TEXT("画像の保存ができません。")':
        'TEXT("No se pudo guardar la imagen.")',
    'TEXT("クリップボードにデータを設定できません。")':
        'TEXT("No se pudieron copiar los datos al portapapeles.")',
})

# 7. ChannelInput.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\ChannelInput.cpp", {
    'TEXT("無効"),': 'TEXT("Deshabilitado"),',
    'TEXT("単キー"),': 'TEXT("Tecla única"),',
    'TEXT("連続入力"),': 'TEXT("Entrada secuencial"),',
    'DlgComboBox_AddString(hDlg, IDC_CHANNELINPUT_TIMEOUTMODE, TEXT("確定"));':
        'DlgComboBox_AddString(hDlg, IDC_CHANNELINPUT_TIMEOUTMODE, TEXT("Confirmar"));',
    'DlgComboBox_AddString(hDlg, IDC_CHANNELINPUT_TIMEOUTMODE, TEXT("キャンセル"));':
        'DlgComboBox_AddString(hDlg, IDC_CHANNELINPUT_TIMEOUTMODE, TEXT("Cancelar"));',
})

# 8. Controller.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\Controller.cpp", {
    'lvc.pszText = const_cast<LPTSTR>(TEXT("ボタン"));':
        'lvc.pszText = const_cast<LPTSTR>(TEXT("Botón"));',
    'lvc.pszText = const_cast<LPTSTR>(TEXT("コマンド"));':
        'lvc.pszText = const_cast<LPTSTR>(TEXT("Comando"));',
    'DlgComboBox_AddString(hDlg, IDC_CONTROLLER_COMMAND, TEXT("なし"));':
        'DlgComboBox_AddString(hDlg, IDC_CONTROLLER_COMMAND, TEXT("Ninguno"));',
})
