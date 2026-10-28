//严格次小生成树: 边权和严格大于 MST 的最小生成树, O(m log m + n log n)
//思想: 先求 MST, 枚举每条非树边 (u, v, w), 替换 MST 上 u-v 路径中"最大的比 w 小的边"
//      对每条非树边: 答案候选 = MST权值 + w - max1(路径最大边, 若 < w) 或 w - max2(最大边 == w 时用次大)
//需预定义: 倍增数组 fa[LOG][N], mx1[LOG][N], mx2[LOG][N](路径最大/严格次大边权);
//          depth[N];  vector<pair<int,int>> tree[N](MST 树的邻接表, pair 为 (边权, 邻点));
//          struct edge { int u, v, w; };  vector<edge> non_tree(非树边集);  并查集(见 kruskal.cpp)
//入口: kruskal 时记录 MST 边与非树边; dfs(1, 0) 预处理倍增; second_mst(mst_sum) 枚举非树边

void dfs(int u, int par) {                 //预处理倍增(最大/严格次大边权)
    for(int k = 1; k < LOG; k++) {
        fa[k][u] = fa[k - 1][fa[k - 1][u]];
        mx1[k][u] = max(mx1[k - 1][u], mx1[k - 1][fa[k - 1][u]]);   //两段的最大值
        //严格次大: 两段的最大/次大混合取"小于最大值的最大者", 注意两段最大值相等的情况
        int c1 = mx1[k - 1][u], c2 = mx1[k - 1][fa[k - 1][u]];
        int m2 = max(mx2[k - 1][u], mx2[k - 1][fa[k - 1][u]]);
        if(c1 != c2)    m2 = max(m2, min(c1, c2));   //两段最大值不同, 较小的那个也是候选次大
        mx2[k][u] = m2;
    }
    for(auto& e : tree[u]) {
        int v = e.second, w = e.first;
        if(v == par)    continue;
        depth[v] = depth[u] + 1;
        fa[0][v] = u;
        mx1[0][v] = w;                     //到父亲的边权
        mx2[0][v] = -INF;
        dfs(v, u);
    }
}

pair<int, int> path_max(int u, int v) {    //u-v 路径上的最大边与严格次大边
    int big = -INF, sec = -INF;
    auto upd = [&](int m1, int m2) {       //把一段(最大 m1, 次大 m2)合并进答案
        if(m1 > big) {
            sec = max(big, m2);
            big = m1;
        }
        else if(m1 < big)    sec = max(sec, m1);    //注意 m1 == big 时不能用作次大
        else    sec = max(sec, m2);
    };
    if(depth[u] < depth[v])    swap(u, v);
    for(int k = LOG - 1; k >= 0; k--)      //抬深度, 沿途合并
        if(depth[u] - (1 << k) >= depth[v]) {
            upd(mx1[k][u], mx2[k][u]);
            u = fa[k][u];
        }
    if(u == v)    return {big, sec};
    for(int k = LOG - 1; k >= 0; k--)
        if(fa[k][u] != fa[k][v]) {
            upd(mx1[k][u], mx2[k][u]);
            upd(mx1[k][v], mx2[k][v]);
            u = fa[k][u];
            v = fa[k][v];
        }
    upd(mx1[0][u], mx2[0][u]);
    upd(mx1[0][v], mx2[0][v]);
    return {big, sec};
}

ll second_mst(ll mst_sum) {                //主流程: 枚举非树边
    ll ans = INFLL;
    for(auto& e : non_tree) {              //非树边集
        auto [big, sec] = path_max(e.u, e.v);
        if(e.w > big)    ans = min(ans, mst_sum + e.w - big);        //正常替换
        else if(sec != -INF)    ans = min(ans, mst_sum + e.w - sec); //最大边 == w, 换次大
        //若 sec == -INF 且 e.w == big: 无严格次小方案(该非树边不产生)
    }
    return ans;
}
//配套: 非严格次小生成树: 只需维护路径最大边, ans = min(mst + w - big)
//      单次询问用 LCA; 多次修改边权用树剖 + 线段树维护最大/次大
