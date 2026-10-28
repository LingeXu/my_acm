# 2272D 构造正确性暴力验证:
# 枚举 n<=6 的所有森林, 对所有合法的加边方式求最优 MIS,
# 与公式 (存在大树 -> sum(每棵树MIS); 全单点 -> k-1) 及构造结果三方比对
import itertools

def mis_size(n, edges):
    # 全图上暴力最大独立集
    best = 0
    for mask in range(1 << n):
        ok = True
        for u, v in edges:
            if (mask >> u) & 1 and (mask >> v) & 1:
                ok = False
                break
        if ok:
            best = max(best, mask.bit_count())
    return best

def mis_comp(comp, edges):
    # 只统计组件 comp 内部顶点的最大独立集
    pos = {v: i for i, v in enumerate(comp)}
    m = len(comp)
    best = 0
    for mask in range(1 << m):
        ok = True
        for u, v in edges:
            if u in pos and (mask >> pos[u]) & 1 and (mask >> pos[v]) & 1:
                ok = False
                break
        if ok:
            best = max(best, mask.bit_count())
    return best

def solve_forest(n, edges):
    # 连通分量
    parent = list(range(n))
    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x
    for u, v in edges:
        parent[find(u)] = find(v)
    comps = {}
    for v in range(n):
        comps.setdefault(find(v), []).append(v)
    comp_list = list(comps.values())
    k = len(comp_list)

    U = sum(mis_comp(comp, edges) for comp in comp_list)

    # 枚举所有把 k 棵树连成一棵树的加边方式, 取最优 MIS
    cross = []
    for i in range(k):
        for j in range(i + 1, k):
            for a in comp_list[i]:
                for b in comp_list[j]:
                    cross.append((a, b))
    OPT = -1
    if k == 1:
        OPT = mis_size(n, edges)
    else:
        for added in itertools.combinations(cross, k - 1):
            cid = {}
            for idx, comp in enumerate(comp_list):
                for v in comp:
                    cid[v] = idx
            dsu = list(range(k))
            def f2(x):
                while dsu[x] != x:
                    dsu[x] = dsu[dsu[x]]
                    x = dsu[x]
                return x
            for a, b in added:
                dsu[f2(cid[a])] = f2(cid[b])
            if len({f2(i) for i in range(k)}) != 1:
                continue
            OPT = max(OPT, mis_size(n, edges + list(added)))

    # 公式: 存在大小>=2 的树 -> 上界 sum(MIS_i) 可达; 全单点 -> 星形 k-1
    formula = U if (k == 1 or any(len(c) >= 2 for c in comp_list)) else k - 1

    # 构造: 中心树取叶子的邻居 y (一定可被某个 MIS 排除), 其余树各取一顶点连到 y
    my_edges = []
    if k > 1:
        big = [c for c in comp_list if len(c) >= 2]
        if big:
            c = big[0]
            deg = {v: 0 for v in c}
            for u, v in edges:
                if u in c:
                    deg[u] += 1
                    deg[v] += 1
            leaf = [v for v in c if deg[v] == 1][0]
            y = None
            for u, v in edges:
                if u == leaf and v in c:
                    y = v
                elif v == leaf and u in c:
                    y = u
            assert y is not None
            for other in comp_list:
                if other is not c:
                    my_edges.append((y, other[0]))
        else:
            for other in comp_list[1:]:
                my_edges.append((comp_list[0][0], other[0]))
    got = mis_size(n, edges + my_edges)
    assert got == OPT == formula, (n, edges, OPT, got, formula, my_edges)

for n in range(1, 7):
    all_edges = list(itertools.combinations(range(n), 2))
    cnt = 0
    for mask in range(1 << len(all_edges)):
        edges = [all_edges[i] for i in range(len(all_edges)) if mask >> i & 1]
        parent = list(range(n))
        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x
        ok = True
        for u, v in edges:
            ru, rv = find(u), find(v)
            if ru == rv:
                ok = False
                break
            parent[ru] = rv
        if not ok:
            continue
        solve_forest(n, edges)
        cnt += 1
    print(f"n={n}: {cnt} 个森林全部通过")
print("ALL OK")
