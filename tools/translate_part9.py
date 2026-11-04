# -*- coding: utf-8 -*-
import sys, re
sys.stdout.reconfigure(encoding='utf-8')

extra = {
    "ChannelPanelProgress": "Panel Canales: Progreso barra 1",
    "ChannelPanelProgress2": "Panel Canales: Progreso barra 2",
    "ChannelPanelProgressBorder": "Panel Canales: Progreso borde",
    "ChannelPanelCurProgress": "Panel Canales: Progreso sel. barra 1",
    "ChannelPanelCurProgress2": "Panel Canales: Progreso sel. barra 2",
    "ChannelPanelCurProgressBorder": "Panel Canales: Progreso sel. borde",
    "ControlPanelBack": "Panel Control: Fondo 1",
    "ControlPanelBack2": "Panel Control: Fondo 2",
    "ControlPanelText": "Panel Control: Texto",
    "ControlPanelHighlightBack": "Panel Control: Sel. fondo 1",
    "ControlPanelHighlightBack2": "Panel Control: Sel. fondo 2",
    "ControlPanelHighlightText": "Panel Control: Sel. texto",
    "ControlPanelHighlightBorder": "Panel Control: Sel. borde",
    "ControlPanelCheckedBack": "Panel Control: Marcado fondo 1",
    "ControlPanelCheckedBack2": "Panel Control: Marcado fondo 2",
    "ControlPanelCheckedText": "Panel Control: Marcado texto",
    "ControlPanelCheckedBorder": "Panel Control: Marcado borde",
}

with open(r"F:\TVTEST PROJECT\TVTest-develop\src\ColorScheme.cpp", 'r', encoding='utf-8') as f:
    lines = f.readlines()

new_lines = []
for line in lines:
    m = re.search(r'TEXT\("([^"]+)"\)\s*,\s*TEXT\("([^"]+)"\)', line)
    if m and m.group(1) in extra:
        line = line.replace(f'TEXT("{m.group(2)}")', f'TEXT("{extra[m.group(1)]}")')
    new_lines.append(line)

with open(r"F:\TVTEST PROJECT\TVTest-develop\src\ColorScheme.cpp", 'w', encoding='utf-8') as f:
    f.writelines(new_lines)
