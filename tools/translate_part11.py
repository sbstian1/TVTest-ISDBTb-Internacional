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

# 1. InitialSettings.cpp (Diálogo de primera configuración al abrir TVTest)
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\InitialSettings.cpp", {
    'TEXT("すべてのファイル\\0*.*\\0");':
        'TEXT("Todos los archivos\\0*.*\\0");',
    'TEXT("{0} のデコーダが見付からないため、{0} の映像は再生できません。\\n")':
        'TEXT("No se encontró decodificador para {0}, por lo que no se podrá reproducir.\\n")',
    'TEXT("映像を再生するにはデコーダをインストールしてください。")':
        'TEXT("Para reproducir video, instale el decodificador correspondiente.")',
    '::MessageBox(hDlg, Message.c_str(), TEXT("お知らせ"), MB_OK | MB_ICONINFORMATION);':
        '::MessageBox(hDlg, Message.c_str(), TEXT("Información"), MB_OK | MB_ICONINFORMATION);',
    'TEXT("CyberLink のデコーダとデフォルトレンダラの組み合わせで、\\n")':
        'TEXT("Con la combinación del decodificador CyberLink y el renderizador predeterminado,\\n")',
    'TEXT("一部の番組で比率がおかしくなる現象が出る事があるため、\\n")':
        'TEXT("la relación de aspecto puede verse afectada en algunos programas,\\n")',
    'TEXT("レンダラをデフォルト以外にすることをお奨めします。\\n")':
        'TEXT("por lo que se recomienda seleccionar otro renderizador.\\n")',
    'TEXT("現在の設定を変更しますか?")':
        'TEXT("¿Desea cambiar la configuración actual?")',
    'hDlg, e.pszMessage, TEXT("注意"),':
        'hDlg, e.pszMessage, TEXT("Atención"),',
    'TEXT("作成しますか?")':
        'TEXT("¿Desea crearla?")',
})

# 2. ChannelScan.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\ChannelScan.cpp", {
    'TEXT("チャンネルスキャン")':
        'TEXT("Escaneo de canales")',
    'TEXT("お知らせ")':
        'TEXT("Información")',
})

# 3. StreamInfo.cpp (Parámetros y reportes de la transmisión TS)
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\StreamInfo.cpp", {
    'TEXT("メディアタイプ {}({}) / 運用パターン {} / EIT[other]フラグ {} / 伝送範囲 {}日 / 周期 {}秒")':
        'TEXT("Tipo de medio {}({}) / Patrón {} / EIT[other] {} / Rango de transmisión {} días / Ciclo {} s")',
    'TEXT("セグメント数 {} / 周期 {}秒")':
        'TEXT("Segmentos: {} / Ciclo: {} s")',
    'StringFormat(szText, TEXT("NIT : 周期 {}秒"), Table.NIT.TableCycle);':
        'StringFormat(szText, TEXT("NIT : Ciclo {} s"), Table.NIT.TableCycle);',
    'StringFormat(szText, TEXT("SDT[actual] : 周期 {}秒"), Table.SDT.TableCycle);':
        'StringFormat(szText, TEXT("SDT[actual] : Ciclo {} s"), Table.SDT.TableCycle);',
    'StringFormat(szText, TEXT("SDT[other] : 周期 {}秒"), Table.SDT.TableCycle);':
        'StringFormat(szText, TEXT("SDT[other] : Ciclo {} s"), Table.SDT.TableCycle);',
    'TEXT("EIT[p/f actual] : H-EIT[p/f]周期 {}秒 / M-EIT周期 {}秒 / L-EIT周期 {}秒 / M-EIT番組数 {} / L-EIT番組数 {}")':
        'TEXT("EIT[p/f actual] : H-EIT[p/f] Ciclo {} s / M-EIT {} s / L-EIT {} s / Prog. M-EIT {} / Prog. L-EIT {}")',
    'StringFormat(szText, TEXT("EIT[p/f actual] : 周期 {}秒"), Table.EIT_PF.TableCycle);':
        'StringFormat(szText, TEXT("EIT[p/f actual] : Ciclo {} s"), Table.EIT_PF.TableCycle);',
    'StringFormat(szText, TEXT("EIT[p/f other] : 周期 {}秒"), Table.EIT_PF.TableCycle);':
        'StringFormat(szText, TEXT("EIT[p/f other] : Ciclo {} s"), Table.EIT_PF.TableCycle);',
    'StringFormat(szText, TEXT("SDTT : 周期 {}秒"), Table.SDTT.TableCycle);':
        'StringFormat(szText, TEXT("SDTT : Ciclo {} s"), Table.SDTT.TableCycle);',
    'StringFormat(szText, TEXT("BIT : 周期 {}秒"), Table.BIT.TableCycle);':
        'StringFormat(szText, TEXT("BIT : Ciclo {} s"), Table.BIT.TableCycle);',
    'StringFormat(szText, TEXT("NBIT[msg] : 周期 {}秒"), Table.NBIT.TableCycle);':
        'StringFormat(szText, TEXT("NBIT[msg] : Ciclo {} s"), Table.NBIT.TableCycle);',
    'StringFormat(szText, TEXT("NBIT[ref] : 周期 {}秒"), Table.NBIT.TableCycle);':
        'StringFormat(szText, TEXT("NBIT[ref] : Ciclo {} s"), Table.NBIT.TableCycle);',
    'StringFormat(szText, TEXT("LDT : 周期 {}秒"), Table.LDT.TableCycle);':
        'StringFormat(szText, TEXT("LDT : Ciclo {} s"), Table.LDT.TableCycle);',
    'StringFormat(szText, TEXT("CDT : 周期 {}秒"), Table.CDT.TableCycle);':
        'StringFormat(szText, TEXT("CDT : Ciclo {} s"), Table.CDT.TableCycle);',
    'TEXT("地上ブロードキャスタID {} / ブロードキャスタ種別 {} / 系列ID [{}]")':
        'TEXT("ID Difusor terrestre {} / Tipo {} / ID Red [{}]")',
    'TEXT("関連BS/CSブロードキャスタ{0} : ONID {1:#04x} ({1}) / ブロードキャスタID {2}")':
        'TEXT("Difusor BS/CS relacionado {0} : ONID {1:#04x} ({1}) / ID Difusor {2}")',
    'TEXT("ブロードキャスタID {} / {}")':
        'TEXT("ID Difusor {} / {}")',
    'TEXT("TSID {0:#04x} ({0}) / エリア {1} / ガードインターバル {2} / 伝送モード {3}")':
        'TEXT("TSID {0:#04x} ({0}) / Área {1} / Intervalo de guarda {2} / Modo transmisión {3}")',
    'szText, TEXT("周波数{} : {} MHz")':
        'szText, TEXT("Frecuencia {} : {} MHz")',
    'TEXT("TS{0} : TSID {1:#04x} ({1}) / 周波数 {2}.{3:05} GHz")':
        'TEXT("TS{0} : TSID {1:#04x} ({1}) / Frecuencia {2}.{3:05} GHz")',
    'TEXT("TS{0} : TSID {1:#04x} ({1}) / 周波数 {2}.{3:04} MHz / {4} / 変調 {5}")':
        'TEXT("TS{0} : TSID {1:#04x} ({1}) / Frecuencia {2}.{3:04} MHz / {4} / Modulación {5}")',
})

# 4. Accelerator.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\Accelerator.cpp", {
    '::lstrcpy(szText + i, TEXT("\\n(押したキーとデータを教えてもらえれば対応できるかも知れません。)"));':
        '::lstrcpy(szText + i, TEXT("\\n(Consulte la documentación de la tecla o su asignación de hardware.)"));',
    'TEXT("対応していないキーが押されました。"), nullptr, TEXT("ごめん")':
        'TEXT("Se presionó una tecla no compatible."), nullptr, TEXT("Aviso")',
})

# 5. ChannelDisplay.cpp
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\ChannelDisplay.cpp", {
    'pTuningSpace->SetName(TEXT("地上"));':
        'pTuningSpace->SetName(TEXT("Terrestre (TDT)"));',
})

# 6. Logger / Status / Notificaciones
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\AppCore.cpp", {
    'TEXT("チャンネルファイルが古いので再スキャンをお薦めします。")':
        'TEXT("El archivo de canales es antiguo, se recomienda realizar un reescaneo.")',
    'TEXT("ストリームの変化を検知しました。(TSID {} / SID {})")':
        'TEXT("Se detectó un cambio en el flujo de transmisión (TSID {} / SID {})")',
    'TEXT("ワンセグモードを{}にします。"), f1Seg ? TEXT("オン") : TEXT("オフ")':
        'TEXT("Modo 1-Seg: {}."), f1Seg ? TEXT("Activado") : TEXT("Desactivado")',
    'TEXT("録画開始 {}")':
        'TEXT("Inicio de grabación: {}")',
    'TEXT("録画停止 {} (出力TSサイズ {} Bytes / 書き出しエラー回数 {})")':
        'TEXT("Fin de grabación: {} (Tamaño de salida: {} bytes / Errores de escritura: {})")',
    'TEXT("録画一時停止")':
        'TEXT("Grabación pausada")',
    'TEXT("録画再開")':
        'TEXT("Grabación reanudada")',
    'TEXT("録画ファイルを切り替えました {}")':
        'TEXT("Archivo de grabación cambiado a: {}")',
})

replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\AppMain.cpp", {
    'TEXT("設定を読み込んでいます...")':
        'TEXT("Cargando configuración...")',
    'TEXT("設定を保存しています...")':
        'TEXT("Guardando configuración...")',
    'TEXT("複数起動が禁止されています。")':
        'TEXT("La ejecución de múltiples instancias no está permitida.")',
    'TEXT("既存のプロセスにメッセージを送信できません。")':
        'TEXT("No se pudo comunicar con el proceso existente.")',
})

replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\TVTest.cpp", {
    'TEXT("TOTで時刻合わせを行いました。({}/{}/{} {}:{:02}:{:02})")':
        'TEXT("Sincronización de hora TOT realizada ({}/{}/{} {}:{:02}:{:02})")',
    'TEXT("EPG データを読み込みました。")':
        'TEXT("Datos EPG cargados.")',
    'TEXT("EPG データを読み込めませんでした。")':
        'TEXT("No se pudieron cargar los datos EPG.")',
    'TEXT("EDCB の EPG データを読み込みました。")':
        'TEXT("Datos EPG de EDCB cargados.")',
    'TEXT("EDCB の EPG データを読み込めませんでした。")':
        'TEXT("No se pudieron cargar los datos EPG de EDCB.")',
    'TEXT(") 起動 ********")':
        'TEXT(") Iniciado ********")',
    'TEXT("******** 終了 ********")':
        'TEXT("******** Finalizado ********")',
})

# 7. LibISDB Video Renderers (Error messages al inicializar renderer de video)
replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\LibISDB\LibISDB\Windows\Viewer\DirectShow\VideoRenderers\VideoRenderer_EVR.cpp", {
    'LIBISDB_STR("EVR のインスタンスを作成できません。")':
        'LIBISDB_STR("No se pudo crear la instancia de EVR.")',
    'LIBISDB_STR("IMFVideoDisplayControl を取得できません。")':
        'LIBISDB_STR("No se pudo obtener IMFVideoDisplayControl.")',
    'LIBISDB_STR("EVR をフィルタグラフに追加できません。")':
        'LIBISDB_STR("No se pudo añadir EVR al grafo de filtros.")',
    'LIBISDB_STR("映像レンダラを構築できません。")':
        'LIBISDB_STR("No se pudo inicializar el renderizador de video.")',
})

replace_in_file(r"F:\TVTEST PROJECT\TVTest-develop\src\LibISDB\LibISDB\Windows\Viewer\DirectShow\VideoRenderers\VideoRenderer_MPCVideoRenderer.cpp", {
    'LIBISDB_STR("MPC Video Renderer のインスタンスを作成できません。")':
        'LIBISDB_STR("No se pudo crear la instancia de MPC Video Renderer.")',
    'LIBISDB_STR("IKeyFrameInfo を取得できません。")':
        'LIBISDB_STR("No se pudo obtener IKeyFrameInfo.")',
    'LIBISDB_STR("MPC Video Renderer をフィルタグラフに追加できません。")':
        'LIBISDB_STR("No se pudo añadir MPC Video Renderer al grafo de filtros.")',
    'LIBISDB_STR("映像レンダラを構築できません。")':
        'LIBISDB_STR("No se pudo inicializar el renderizador de video.")',
})
