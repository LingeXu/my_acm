//李超线段树: 插入直线/线段, 查询若干 x 处的最大/最小函数值, O(log V) 单次
//思想: 每个节点存"在该节点区间中点取值最优"的直线, 插入时与旧直线比较,
//      中点更劣的一条下放到较优的那一侧继续递归
//需预定义: struct Line { ll k, b; };  直线 y = kx + b;  值域 [1, V](离散化或直接下标)
//         Line tree[4 * N];  tree[p] = 节点 p 区间内"中点处最优"的直线, 初始 k = 0, b = -INFLL
//入口: insert(1, 1, V, line);  查询 query(1, 1, V, x)

struct Line {
    ll k, b;
    ll get(ll x) const { return k * x + b; }
};
Line seg[4 * N];

void insert(int p, int l, int r, Line cur) {
    if(l == r) {
        if(cur.get(l) > seg[p].get(l))    seg[p] = cur;   //叶子直接比较
        return;
    }
    int mid = (l + r) >> 1;
    if(cur.get(mid) > seg[p].get(mid))    swap(seg[p], cur);   //保证 seg[p] 在中点最优
    if(cur.get(l) > seg[p].get(l))    insert(2 * p, l, mid, cur);      //cur 在左侧更优 -> 下放左
    else if(cur.get(r) > seg[p].get(r))    insert(2 * p + 1, mid + 1, r, cur);  //右侧更优 -> 下放右
    //else: cur 处处不如 seg[p], 丢弃
}

ll query(int p, int l, int r, int x) {     //查询 x 处的最大值: 路径上所有直线的 max
    ll res = seg[p].get(x);
    if(l == r)    return res;
    int mid = (l + r) >> 1;
    if(x <= mid)    res = max(res, query(2 * p, l, mid, x));
    else    res = max(res, query(2 * p + 1, mid + 1, r, x));
    return res;
}
//配套:
//1. 插入线段(限定定义域): 递归到区间完全落在定义域内再插直线, 复杂度 O(log^2 V)
//2. 求最小值: 把上面所有 > 换成 <, 初始 b = INFLL
//3. 应用: 斜率优化 DP(转移 min(y_j - k_i * x_j + ...) 化为"给一堆直线查最小取值"),
//   f[i] = min(f[j] + (i-j)^2) 类凸优化问题可直接李超树, 不用写决策单调性
