#!/usr/bin/env python3
"""重建 templates/templates.txt: 按 templates2pdf.py 的 SECTIONS 顺序拼接各模板源文件(.cpp/.sh)。

规则:
- 每个 SECTIONS 条目 (marker, title, chapter) 对应一个 .cpp/.sh 文件: 文件中存在以 marker 开头
  的注释行(marker 自带 // 或 # 前缀; 要求 marker 后跟非单词字符或行尾, 避免 //线段树 误匹配 //线段树合并);
- 一个文件可含多个 marker(如 trie.cpp 同时含 //trie 与 //AC自动机), 文件内容只在
  第一个 marker 处输出一次, 后续 marker 靠文件内注释行切分;
- 若 marker 没有任何文件包含(LIS/LCS/gcd 这类只存在于 txt 的小节), 保留当前
  templates.txt 中的原段;
- 拼接顺序严格等于 SECTIONS 顺序, 保证 templates2pdf.py 的 assert 通过。

用法: python3 tools/build_templates_txt.py   (修改模板文件后运行, 再跑 templates2pdf.py 出 PDF)
"""
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TPL = os.path.join(ROOT, "templates")
TXT = os.path.join(TPL, "templates.txt")


def parse_sections():
    """从 templates2pdf.py 抽取 SECTIONS 列表 [(marker, title, chapter), ...]"""
    src = open(os.path.join(ROOT, "tools", "templates2pdf.py"), encoding="utf-8").read()
    entries = re.findall(r'\s*\("((?://|#)[^"]+)",\s*"([^"]+)",\s*"([^"]+)"\)', src)
    assert entries, "未解析到 SECTIONS"
    return entries


def marker_re(marker):
    """标记行: marker 之后必须是非单词字符或行尾(避免 //线段树 误匹配 //线段树合并)"""
    return re.compile(r"^" + re.escape(marker) + r"(?=\W|$)")


def contains_marker(lines, marker):
    pat = marker_re(marker)
    return any(pat.match(ln) for ln in lines)


def main():
    entries = parse_sections()
    markers = [m for m, _, _ in entries]

    old_lines = open(TXT, encoding="utf-8").read().splitlines()
    # 当前 txt 中每个 marker 的起始行号(新模板不在旧 txt 中, 跳过)
    pos = {}
    for k, m in enumerate(markers):
        pat = marker_re(m)
        hits = [i for i, ln in enumerate(old_lines) if pat.match(ln)]
        if len(hits) == 1:
            pos[k] = hits[0]
        elif len(hits) > 1:
            sys.exit(f"标记 {m} 在 templates.txt 中出现 {len(hits)} 次")

    # marker -> 包含它的文件内容
    file_of = {}
    srcs = sorted(glob.glob(os.path.join(TPL, "*.cpp")) + glob.glob(os.path.join(TPL, "*.sh")))
    for fp in srcs:
        with open(fp, encoding="utf-8") as f:
            lines = f.read().splitlines()
        for k, m in enumerate(markers):
            if k not in file_of and contains_marker(lines, m):
                file_of[k] = lines
    # 同一文件的多个 marker 必须连续(如 //trie 与 //AC自动机), 否则切分会错位
    by_file = {}
    for k, lines in file_of.items():
        by_file.setdefault(id(lines), []).append(k)
    for ks in by_file.values():
        assert ks == list(range(ks[0], ks[0] + len(ks))), \
            f"同一文件的标记不连续: {[markers[k] for k in ks]}"

    out = []
    emitted_files = set()
    for k, (m, _, _) in enumerate(entries):
        if k in file_of:
            fid = id(file_of[k])
            if fid in emitted_files:
                continue  # 文件内容已在前一个 marker 处输出
            out.extend(file_of[k])
            emitted_files.add(fid)
        elif k in pos:  # txt 专属小节: 保留原段 [pos[k], 下一标记处)
            end = next((pos[j] for j in range(k + 1, len(markers)) if j in pos), len(old_lines))
            out.extend(old_lines[pos[k]:end])
        else:
            sys.exit(f"标记 {m} 既无对应文件也不在 templates.txt 中")
        while out and out[-1] == "":  # 去掉段尾空行, 保证重复重建结果一致
            out.pop()
        out.append("")  # 小节间空行

    while out and out[-1] == "":
        out.pop()
    # 自检: 每个标记在结果中恰好出现一次(与 templates2pdf.py 的 parse 断言一致)
    for m in markers:
        pat = marker_re(m)
        hits = [i for i, ln in enumerate(out) if pat.match(ln)]
        if len(hits) != 1:
            sys.exit(f"自检失败: 标记 {m} 出现 {len(hits)} 次(可能是标记互为前缀, 如 //线段树 vs //线段树合并)")
    with open(TXT, "w", encoding="utf-8") as f:
        f.write("\n".join(out) + "\n")
    print(f"已重建 {TXT}: {len(entries)} 个小节, {len(out)} 行")


if __name__ == "__main__":
    main()
