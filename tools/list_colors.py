# -*- coding: utf-8 -*-
import sys, re
sys.stdout.reconfigure(encoding='utf-8')

with open(r"F:\TVTEST PROJECT\TVTest-develop\src\ColorScheme.cpp", 'r', encoding='utf-8') as f:
    lines = f.readlines()

for num, line in enumerate(lines, 1):
    if 70 <= num <= 306:
        m = re.findall(r'TEXT\("([^"]+)"\)', line)
        if len(m) >= 2 and re.search(r'[\u3040-\u30ff\u3400-\u4dbf\u4e00-\u9fff]', m[1]):
            print(f"{num}: {m[0]} -> {m[1]}")
