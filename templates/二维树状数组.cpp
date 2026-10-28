//二维树状数组: 单点修改 + 矩形查询 / 矩形修改 + 单点查询(差分)
//思想: 把一维 BIT 扩展为按行、列双 lowbit 跳转; 复杂度 O(log^2 n)
//需预定义: ll tree[N][N];  下标 1-based
//注意: 二维 BIT 只能维护"可差分"的信息(和/异或等), 不维护 min/max

int lowbit(int x) {
    return x & (-x);
}

//单点 (x, y) 加 delta
void add(int x, int y, ll delta) {
    for(int i = x; i <= n; i += lowbit(i))
        for(int j = y; j <= m; j += lowbit(j))
            tree[i][j] += delta;
}

//查询矩形 [1, 1] ~ [x, y] 的和
ll query(int x, int y) {
    ll res = 0;
    for(int i = x; i > 0; i -= lowbit(i))
        for(int j = y; j > 0; j -= lowbit(j))
            res += tree[i][j];
    return res;
}

//查询矩形 [x1, y1] ~ [x2, y2]: query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1)
//配套: 矩形加 + 单点查: 用二维差分, add 打在四个角(左上 +delta, (x2+1,y1) -delta, (x1,y2+1) -delta, (x2+1,y2+1) +delta),
//      单点值 = query(x, y)
//      矩形加 + 矩形查: 需要 4 棵 BIT 维护 (i*j, i, j, 1) 的加权和, 较繁, 区域赛少见
