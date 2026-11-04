import os
import re

src_dir = r"F:\TVTEST PROJECT\TVTest-develop\src"
cjk_re = re.compile(r'[\u3040-\u30ff\u3400-\u4dbf\u4e00-\u9fff]')
text_str_re = re.compile(r'(?:TEXT|LIBISDB_STR|_T)\s*\(\s*"([^"]+)"\s*\)')
rc_str_re = re.compile(r'"([^"]*[\u3040-\u30ff\u3400-\u4dbf\u4e00-\u9fff][^"]*)"')

results = []

for root, dirs, files in os.walk(src_dir):
    for f in files:
        if not (f.endswith('.cpp') or f.endswith('.h') or f.endswith('.rc')):
            continue
        if f in ['TVTestPlugin.h', 'TVTestInterface.h']:
            continue
        full_path = os.path.join(root, f)
        
        # Read file with tolerant encoding
        try:
            with open(full_path, 'r', encoding='utf-8') as fp:
                lines = fp.readlines()
        except UnicodeDecodeError:
            try:
                with open(full_path, 'r', encoding='cp932') as fp:
                    lines = fp.readlines()
            except Exception:
                continue

        file_matches = []
        for line_num, line in enumerate(lines, 1):
            stripped = line.strip()
            # Skip pure comment lines
            if stripped.startswith('//') or stripped.startswith('/*') or stripped.startswith('*'):
                continue
            
            if f.endswith('.rc'):
                m = rc_str_re.findall(line)
                if m:
                    file_matches.append((line_num, line.strip(), m))
            else:
                m = text_str_re.findall(line)
                cjk_m = [s for s in m if cjk_re.search(s)]
                if cjk_m:
                    file_matches.append((line_num, line.strip(), cjk_m))

        if file_matches:
            results.append((full_path, file_matches))

out_path = r"F:\TVTEST PROJECT\japanese_strings.txt"
with open(out_path, 'w', encoding='utf-8') as fp:
    for full_path, matches in results:
        fp.write(f"=== {full_path} ===\n")
        for line_num, line, strings in matches:
            fp.write(f"  Line {line_num}: {strings} -> {line}\n")
        fp.write("\n")

print(f"Total files with UI strings in Japanese: {len(results)}")
