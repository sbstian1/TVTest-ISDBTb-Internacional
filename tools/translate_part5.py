# -*- coding: utf-8 -*-
import sys
sys.stdout.reconfigure(encoding='utf-8')

with open(r"F:\TVTEST PROJECT\TVTest-develop\src\VariableString.cpp", 'r', encoding='utf-8') as f:
    text = f.read()

replacements = {
    '{TEXT("date"),                  TEXT("年月日")}': '{TEXT("date"),                  TEXT("Año/Mes/Día")}',
    '{TEXT("year"),                  TEXT("年")}': '{TEXT("year"),                  TEXT("Año (4 dígitos)")}',
    '{TEXT("year2"),                 TEXT("年(下2桁)")}': '{TEXT("year2"),                 TEXT("Año (2 dígitos)")}',
    '{TEXT("month"),                 TEXT("月")}': '{TEXT("month"),                 TEXT("Mes")}',
    '{TEXT("month2"),                TEXT("月(2桁)")}': '{TEXT("month2"),                TEXT("Mes (2 dígitos)")}',
    '{TEXT("day"),                   TEXT("日")}': '{TEXT("day"),                   TEXT("Día")}',
    '{TEXT("day2"),                  TEXT("日(2桁)")}': '{TEXT("day2"),                  TEXT("Día (2 dígitos)")}',
    '{TEXT("time"),                  TEXT("時刻(時+分+秒)")}': '{TEXT("time"),                  TEXT("Hora (H+M+S)")}',
    '{TEXT("hour"),                  TEXT("時")}': '{TEXT("hour"),                  TEXT("Hora")}',
    '{TEXT("hour2"),                 TEXT("時(2桁)")}': '{TEXT("hour2"),                 TEXT("Hora (2 dígitos)")}',
    '{TEXT("minute"),                TEXT("分")}': '{TEXT("minute"),                TEXT("Minuto")}',
    '{TEXT("minute2"),               TEXT("分(2桁)")}': '{TEXT("minute2"),               TEXT("Minuto (2 dígitos)")}',
    '{TEXT("second"),                TEXT("秒")}': '{TEXT("second"),                TEXT("Segundo")}',
    '{TEXT("second2"),               TEXT("秒(2桁)")}': '{TEXT("second2"),               TEXT("Segundo (2 dígitos)")}',
    '{TEXT("day-of-week"),           TEXT("曜日(漢字)")}': '{TEXT("day-of-week"),           TEXT("Día de la semana")}',

    '{TEXT("start-date"),            TEXT("年月日")}': '{TEXT("start-date"),            TEXT("Año/Mes/Día")}',
    '{TEXT("start-year"),            TEXT("年")}': '{TEXT("start-year"),            TEXT("Año (4 dígitos)")}',
    '{TEXT("start-year2"),           TEXT("年(下2桁)")}': '{TEXT("start-year2"),           TEXT("Año (2 dígitos)")}',
    '{TEXT("start-month"),           TEXT("月")}': '{TEXT("start-month"),           TEXT("Mes")}',
    '{TEXT("start-month2"),          TEXT("月(2桁)")}': '{TEXT("start-month2"),          TEXT("Mes (2 dígitos)")}',
    '{TEXT("start-day"),             TEXT("日")}': '{TEXT("start-day"),             TEXT("Día")}',
    '{TEXT("start-day2"),            TEXT("日(2桁)")}': '{TEXT("start-day2"),            TEXT("Día (2 dígitos)")}',
    '{TEXT("start-time"),            TEXT("時刻(時+分+秒)")}': '{TEXT("start-time"),            TEXT("Hora (H+M+S)")}',
    '{TEXT("start-hour"),            TEXT("時")}': '{TEXT("start-hour"),            TEXT("Hora")}',
    '{TEXT("start-hour2"),           TEXT("時(2桁)")}': '{TEXT("start-hour2"),           TEXT("Hora (2 dígitos)")}',
    '{TEXT("start-minute"),          TEXT("分")}': '{TEXT("start-minute"),          TEXT("Minuto")}',
    '{TEXT("start-minute2"),         TEXT("分(2桁)")}': '{TEXT("start-minute2"),         TEXT("Minuto (2 dígitos)")}',
    '{TEXT("start-second"),          TEXT("秒")}': '{TEXT("start-second"),          TEXT("Segundo")}',
    '{TEXT("start-second2"),         TEXT("秒(2桁)")}': '{TEXT("start-second2"),         TEXT("Segundo (2 dígitos)")}',
    '{TEXT("start-day-of-week"),     TEXT("曜日(漢字)")}': '{TEXT("start-day-of-week"),     TEXT("Día de la semana")}',

    '{TEXT("end-date"),              TEXT("年月日")}': '{TEXT("end-date"),              TEXT("Año/Mes/Día")}',
    '{TEXT("end-year"),              TEXT("年")}': '{TEXT("end-year"),              TEXT("Año (4 dígitos)")}',
    '{TEXT("end-year2"),             TEXT("年(下2桁)")}': '{TEXT("end-year2"),             TEXT("Año (2 dígitos)")}',
    '{TEXT("end-month"),             TEXT("月")}': '{TEXT("end-month"),             TEXT("Mes")}',
    '{TEXT("end-month2"),            TEXT("月(2桁)")}': '{TEXT("end-month2"),            TEXT("Mes (2 dígitos)")}',
    '{TEXT("end-day"),               TEXT("日")}': '{TEXT("end-day"),               TEXT("Día")}',
    '{TEXT("end-day2"),              TEXT("日(2桁)")}': '{TEXT("end-day2"),              TEXT("Día (2 dígitos)")}',
    '{TEXT("end-time"),              TEXT("時刻(時+分+秒)")}': '{TEXT("end-time"),              TEXT("Hora (H+M+S)")}',
    '{TEXT("end-hour"),              TEXT("時")}': '{TEXT("end-hour"),              TEXT("Hora")}',
    '{TEXT("end-hour2"),             TEXT("時(2桁)")}': '{TEXT("end-hour2"),             TEXT("Hora (2 dígitos)")}',
    '{TEXT("end-minute"),            TEXT("分")}': '{TEXT("end-minute"),            TEXT("Minuto")}',
    '{TEXT("end-minute2"),           TEXT("分(2桁)")}': '{TEXT("end-minute2"),           TEXT("Minuto (2 dígitos)")}',
    '{TEXT("end-second"),            TEXT("秒")}': '{TEXT("end-second"),            TEXT("Segundo")}',
    '{TEXT("end-second2"),           TEXT("秒(2桁)")}': '{TEXT("end-second2"),           TEXT("Segundo (2 dígitos)")}',
    '{TEXT("end-day-of-week"),       TEXT("曜日(漢字)")}': '{TEXT("end-day-of-week"),       TEXT("Día de la semana")}',

    '{TEXT("tot-date"),              TEXT("年月日")}': '{TEXT("tot-date"),              TEXT("Año/Mes/Día")}',
    '{TEXT("tot-year"),              TEXT("年")}': '{TEXT("tot-year"),              TEXT("Año (4 dígitos)")}',
    '{TEXT("tot-year2"),             TEXT("年(下2桁)")}': '{TEXT("tot-year2"),             TEXT("Año (2 dígitos)")}',
    '{TEXT("tot-month"),             TEXT("月")}': '{TEXT("tot-month"),             TEXT("Mes")}',
    '{TEXT("tot-month2"),            TEXT("月(2桁)")}': '{TEXT("tot-month2"),            TEXT("Mes (2 dígitos)")}',
    '{TEXT("tot-day"),               TEXT("日")}': '{TEXT("tot-day"),               TEXT("Día")}',
    '{TEXT("tot-day2"),              TEXT("日(2桁)")}': '{TEXT("tot-day2"),              TEXT("Día (2 dígitos)")}',
    '{TEXT("tot-time"),              TEXT("時刻(時+分+秒)")}': '{TEXT("tot-time"),              TEXT("Hora (H+M+S)")}',
    '{TEXT("tot-hour"),              TEXT("時")}': '{TEXT("tot-hour"),              TEXT("Hora")}',
    '{TEXT("tot-hour2"),             TEXT("時(2桁)")}': '{TEXT("tot-hour2"),             TEXT("Hora (2 dígitos)")}',
    '{TEXT("tot-minute"),            TEXT("分")}': '{TEXT("tot-minute"),            TEXT("Minuto")}',
    '{TEXT("tot-minute2"),           TEXT("分(2桁)")}': '{TEXT("tot-minute2"),           TEXT("Minuto (2 dígitos)")}',
    '{TEXT("tot-second"),            TEXT("秒")}': '{TEXT("tot-second"),            TEXT("Segundo")}',
    '{TEXT("tot-second2"),           TEXT("秒(2桁)")}': '{TEXT("tot-second2"),           TEXT("Segundo (2 dígitos)")}',
    '{TEXT("tot-day-of-week"),       TEXT("曜日(漢字)")}': '{TEXT("tot-day-of-week"),       TEXT("Día de la semana")}',

    '{TEXT("event-duration-hour"),   TEXT("時間")}': '{TEXT("event-duration-hour"),   TEXT("Horas")}',
    '{TEXT("event-duration-hour2"),  TEXT("時間(2桁)")}': '{TEXT("event-duration-hour2"),  TEXT("Horas (2 dígitos)")}',
    '{TEXT("event-duration-min"),    TEXT("分")}': '{TEXT("event-duration-min"),    TEXT("Minutos")}',
    '{TEXT("event-duration-min2"),   TEXT("分(2桁)")}': '{TEXT("event-duration-min2"),   TEXT("Minutos (2 dígitos)")}',
    '{TEXT("event-duration-sec"),    TEXT("秒")}': '{TEXT("event-duration-sec"),    TEXT("Segundos")}',
    '{TEXT("event-duration-sec2"),   TEXT("秒(2桁)")}': '{TEXT("event-duration-sec2"),   TEXT("Segundos (2 dígitos)")}',

    '{TEXT("channel-name"),          TEXT("チャンネル名")}': '{TEXT("channel-name"),          TEXT("Nombre del canal")}',
    '{TEXT("channel-no"),            TEXT("チャンネル番号")}': '{TEXT("channel-no"),            TEXT("Número de canal")}',
    '{TEXT("channel-no2"),           TEXT("チャンネル番号(2桁)")}': '{TEXT("channel-no2"),           TEXT("Número de canal (2 dígitos)")}',
    '{TEXT("channel-no3"),           TEXT("チャンネル番号(3桁)")}': '{TEXT("channel-no3"),           TEXT("Número de canal (3 dígitos)")}',
    '{TEXT("event-name"),            TEXT("番組名")}': '{TEXT("event-name"),            TEXT("Nombre del programa")}',
    '{TEXT("event-title"),           TEXT("番組タイトル")}': '{TEXT("event-title"),           TEXT("Título del programa")}',
    '{TEXT("event-mark"),            TEXT("番組情報マーク")}': '{TEXT("event-mark"),            TEXT("Marca de info. del programa")}',
    '{TEXT("event-id"),              TEXT("イベントID")}': '{TEXT("event-id"),              TEXT("ID de Evento")}',
    '{TEXT("service-name"),          TEXT("サービス名")}': '{TEXT("service-name"),          TEXT("Nombre de servicio")}',
    '{TEXT("service-id"),            TEXT("サービスID")}': '{TEXT("service-id"),            TEXT("ID de Servicio")}',
    '{TEXT("tuner-filename"),        TEXT("チューナーファイル名")}': '{TEXT("tuner-filename"),        TEXT("Archivo del sintonizador")}',
    '{TEXT("tuner-name"),            TEXT("チューナー名")}': '{TEXT("tuner-name"),            TEXT("Nombre del sintonizador")}',

    '{TEXT("sep-hyphen"),            TEXT("-(ハイフン)区切り")}': '{TEXT("sep-hyphen"),            TEXT("Separador - (guion)")}',
    '{TEXT("sep-slash"),             TEXT("/(スラッシュ)区切り")}': '{TEXT("sep-slash"),             TEXT("Separador / (barra)")}',
    '{TEXT("sep-backslash"),         TEXT("\\\\(バックスラッシュ)区切り")}': '{TEXT("sep-backslash"),         TEXT("Separador \\\\ (barra invertida)")}',

    '{TEXT("現在日時"),     DateTimeParams': '{TEXT("Fecha y hora actual"), DateTimeParams',
    '{TEXT("番組開始日時"), StartTimeParams': '{TEXT("Inicio del programa"),  StartTimeParams',
    '{TEXT("番組終了日時"), EndTimeParams': '{TEXT("Fin del programa"),     EndTimeParams',
    '{TEXT("TOT日時"),      TotTimeParams': '{TEXT("Fecha y hora TOT"),     TotTimeParams',
    '{TEXT("番組の長さ"),   EventDurationParams': '{TEXT("Duración"),          EventDurationParams',
    '{TEXT("区切り"),       SeparatorParams': '{TEXT("Separador"),         SeparatorParams',
}

cnt = 0
for k, v in replacements.items():
    if k in text:
        text = text.replace(k, v)
        cnt += 1
    else:
        print(f"Not found: {k}")

with open(r"F:\TVTEST PROJECT\TVTest-develop\src\VariableString.cpp", 'w', encoding='utf-8') as f:
    f.write(text)

print(f"VariableString.cpp updated: {cnt}/{len(replacements)}")
