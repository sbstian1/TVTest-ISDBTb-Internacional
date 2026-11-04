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

# 1. Capture.h
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\Capture.h", {
    'LPCTSTR GetName() const override { return TEXT("キャプチャ"); }':
        'LPCTSTR GetName() const override { return TEXT("Capturar"); }',
    'LPCTSTR GetName() const override { return TEXT("保存"); }':
        'LPCTSTR GetName() const override { return TEXT("Guardar"); }',
    'LPCTSTR GetName() const override { return TEXT("コピー"); }':
        'LPCTSTR GetName() const override { return TEXT("Copiar"); }',
})

# 2. ViewOptions.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\ViewOptions.cpp", {
    'TEXT("画像ファイル (*.bmp;*.gif;*.jpg;*.jpeg;*.png)\\0*.bmp;*.gif;*.jpg;*.jpeg;*.png\\0")':
        'TEXT("Archivos de imagen (*.bmp;*.gif;*.jpg;*.jpeg;*.png)\\0*.bmp;*.gif;*.jpg;*.jpeg;*.png\\0")',
    'TEXT("BMPファイル (*.bmp)\\0*.bmp\\0")':
        'TEXT("Archivos BMP (*.bmp)\\0*.bmp\\0")',
    'TEXT("GIFファイル (*.gif)\\0*.gif\\0")':
        'TEXT("Archivos GIF (*.gif)\\0*.gif\\0")',
    'TEXT("JPEGファイル (*.jpg;*.jpeg)\\0*.jpg;*.jpeg\\0")':
        'TEXT("Archivos JPEG (*.jpg;*.jpeg)\\0*.jpg;*.jpeg\\0")',
    'TEXT("PNGファイル (*.png)\\0*.png\\0")':
        'TEXT("Archivos PNG (*.png)\\0*.png\\0")',
    'TEXT("すべてのファイル\\0*.*\\0");':
        'TEXT("Todos los archivos\\0*.*\\0");',
})

# 3. StreamInfo.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\StreamInfo.cpp", {
    'TEXT("チャンネルファイル用フォーマット")':
        'TEXT("Formato para archivo de canales")',
    'Length = StringFormat(szText, TEXT("サービス{}"), i + 1);':
        'Length = StringFormat(szText, TEXT("Servicio {}"), i + 1);',
    'TEXT("ネットワークTS (NIT)")':
        'TEXT("Red TS (NIT)")',
    'TEXT("サービス{0} : SID {1:#04x} ({1}) / Type {2:#02x}")':
        'TEXT("Servicio {0} : SID {1:#04x} ({1}) / Tipo {2:#02x}")',
    'TEXT("ネットワークサービス (SDT)")':
        'TEXT("Servicios de red (SDT)")',
    'TEXT("サービス{0} ({1}) : SID {2:#04x} ({2}) / Type {3:#02x} / CA {4}")':
        'TEXT("Servicio {0} ({1}) : SID {2:#04x} ({2}) / Tipo {3:#02x} / CA {4}")',
    'TEXT("ブロードキャスタ (BIT)")':
        'TEXT("Difusor (BIT)")',
    'TEXT("ネットワーク{0} : ONID {1:#04x} ({1})")':
        'TEXT("Red {0} : ONID {1:#04x} ({1})")',
    'TEXT("SI伝送パラメータ")':
        'TEXT("Parámetros de transmisión SI")',
    'TEXT("バージョン {} / 更新日 {}/{:02}/{:02}")':
        'TEXT("Versión {} / Fecha de act. {}/{:02}/{:02}")',
    'TEXT("ブロードキャスタ")':
        'TEXT("Difusor")',
    'TEXT("地上分配システム")':
        'TEXT("Sistema de distribución terrestre")',
    'TEXT("衛星分配システム")':
        'TEXT("Sistema de distribución satelital")',
    'TEXT("有線分配システム")':
        'TEXT("Sistema de distribución por cable")',
    'TEXT("TSMF [53,15] 複数TS不可")':
        'TEXT("TSMF [53,15] Múltiples TS no admitidos")',
    'TEXT("単一TS")':
        'TEXT("TS único")',
})

# 4. AppCore.cpp & AppMain.cpp (Startup / error messages)
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\AppCore.cpp", {
    'OnError(&m_App.CoreEngine, TEXT("BonDriverの初期化ができません。"));':
        'OnError(&m_App.CoreEngine, TEXT("No se pudo inicializar BonDriver."));',
    'OnError(TEXT("録画ファイルのパスを作成できません。"));':
        'OnError(TEXT("No se pudo crear la ruta del archivo de grabación."));',
    'OnError(TEXT("録画ファイルの保存先フォルダの指定が正しくないか、パスが長過ぎます。"));':
        'OnError(TEXT("La carpeta de destino de grabación no es válida o la ruta es demasiado larga."));',
    'OnError(&m_App.RecordManager, TEXT("録画を開始できません。"));':
        'OnError(&m_App.RecordManager, TEXT("No se pudo iniciar la grabación."));',
    'OnError(&m_App.RecordManager, TEXT("録画ファイルを切り替えできません。"));':
        'OnError(&m_App.RecordManager, TEXT("No se pudo cambiar el archivo de grabación."));',
    'OnError(TEXT("サービスを選択できません。"));':
        'OnError(TEXT("No se pudo seleccionar el servicio."));',
})

replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\AppMain.cpp", {
    'APP_NAME TEXT(" は既に起動しています。\\n")':
        'APP_NAME TEXT(" ya se está ejecutando.\\n")',
    'TEXT("ウィンドウが見当たらない場合はタスクマネージャに隠れていますので\\n")':
        'TEXT("Si no encuentra la ventana, revise el Administrador de tareas\\n")',
    'TEXT("強制終了させてください。")':
        'TEXT("para finalizar el proceso.")',
    'MessageBox(nullptr, TEXT("ウィンドウが作成できません。"), nullptr, MB_OK | MB_ICONSTOP);':
        'MessageBox(nullptr, TEXT("No se pudo crear la ventana principal."), nullptr, MB_OK | MB_ICONSTOP);',
    'StatusView.SetSingleText(TEXT("プラグインを読み込んでいます..."));':
        'StatusView.SetSingleText(TEXT("Cargando plugins..."));',
    'StatusView.SetSingleText(TEXT("BonDriverの読み込み中..."));':
        'StatusView.SetSingleText(TEXT("Cargando BonDriver..."));',
    'Core.OnError(&CoreEngine, TEXT("BonDriverの初期化ができません。"));':
        'Core.OnError(&CoreEngine, TEXT("No se pudo inicializar BonDriver."));',
    'StatusView.SetSingleText(TEXT("空きポートを検索しています..."));':
        'StatusView.SetSingleText(TEXT("Buscando puertos disponibles..."));',
    'StatusView.SetSingleText(TEXT("チャンネル設定を読み込んでいます..."));':
        'StatusView.SetSingleText(TEXT("Cargando configuración de canales..."));',
    'TEXT("デコーダまたはレンダラの設定が正しくない可能性があります。\\n\\n")':
        'TEXT("La configuración del decodificador o renderizador puede ser incorrecta.\\n\\n")',
    'TEXT("設定ダイアログを表示しますか?")':
        'TEXT("¿Desea abrir el diálogo de configuración?")',
})

# 5. RecordOptions.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\RecordOptions.cpp", {
    'TEXT("現在のサービスのみ録画中です。\\r\\n")':
        'TEXT("Solo el servicio actual se encuentra en grabación.\\r\\n")',
    'TEXT("サービスの変更をすると正常に再生できなくなるかも知れません。\\r\\n")':
        'TEXT("Cambiar de servicio puede afectar la grabación en curso.\\r\\n")',
    'TEXT("サービスを変更しますか?")':
        'TEXT("¿Desea cambiar de servicio?")',
    'TEXT("変更の確認")':
        'TEXT("Confirmar cambio")',
    'TEXT("録画の設定がされています。\\r\\n")':
        'TEXT("Hay una grabación programada.\\r\\n")',
    'TEXT("終了すると録画は行われません。\\r\\n")':
        'TEXT("Si sale de la aplicación no se realizará la grabación.\\r\\n")',
    'TEXT("終了してもいいですか?")':
        'TEXT("¿Está seguro de que desea salir?")',
    'TEXT("作成しますか?")':
        'TEXT("¿Desea crearla?")',
})

# 6. TSProcessorErrorDialog.cpp & TSProcessorManager.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\TSProcessorErrorDialog.cpp", {
    'Message = TEXT("フィルターが見付かりません。");':
        'Message = TEXT("No se encontró el filtro.");',
    '::MessageBox(hDlg, Message.c_str(), TEXT("結果"), MB_OK | MB_ICONINFORMATION);':
        '::MessageBox(hDlg, Message.c_str(), TEXT("Resultado"), MB_OK | MB_ICONINFORMATION);',
    '::MessageBox(hDlg, TEXT("フィルターを選択してください。"), TEXT("お願い"), MB_OK | MB_ICONINFORMATION);':
        '::MessageBox(hDlg, TEXT("Por favor, seleccione un filtro."), TEXT("Aviso"), MB_OK | MB_ICONINFORMATION);',
})

replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\TSProcessorManager.cpp", {
    'TEXT("TSフィルターをオープンできません。")':
        'TEXT("No se pudo abrir el filtro TS.")',
})

# 7. VariableString sample strings
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\VariableString.cpp", {
    'pInfo->Channel.SetName(TEXT("アフリカ中央テレビ"));':
        'pInfo->Channel.SetName(TEXT("Canal Ejemplo HD"));',
    'pInfo->ServiceName = TEXT("アフテレ1");':
        'pInfo->ServiceName = TEXT("Servicio 1");',
    'pInfo->Event.EventName = TEXT("[二][字]今日のニュース");':
        'pInfo->Event.EventName = TEXT("[Dual][Sub] Noticias del Día");',
    'pInfo->Event.EventText = TEXT("本日のニュースをお伝えします。");':
        'pInfo->Event.EventText = TEXT("Emisión de noticias y actualidad.");',
})
