//虚树: 多次询问只涉及少量"关键点"时, 把树压缩到 O(k) 个点(关键点 + 它们的 LCA), 配合树形 DP
//建树: 关键点按 dfn 排序, 相邻点的 LCA 都加入, 再用单调栈按 dfn 顺序连边
//复杂度: 每次询问 O(k log k)(瓶颈在排序与 LCA), k = 关键点数
//需预定义: 原树邻接表 + 倍增 LCA(见 LCA.cpp);  dfn[N], depth[N];
//         struct Node { int to, w, next; } vt[2 * N];  int head2[N], edge_cnt;  (虚树用新前向星)
//入口: build_vt(关键点数组);  然后 dfs(虚树根) 做 DP;  注意每轮清空虚树

bool cmp_dfn(int x, int y) { return dfn[x] < dfn[y]; }

void add_vt(int u, int v, int w) {         //虚树加边(边权 = 原树上距离, 按题需)
    vt[++edge_cnt] = {v, w, head2[u]};
    head2[u] = edge_cnt;
}

vector<int> build_vt(vector<int> key) {    //返回虚树所有节点; key 需按 dfn 排序(内部会排)
    sort(key.begin(), key.end(), cmp_dfn);
    key.erase(unique(key.begin(), key.end()), key.end());
    int k = key.size();
    for(int i = 0; i + 1 < k; i++)         //相邻关键点的 LCA 必在虚树中(也必是"某两个关键点路径的拐点")
        key.push_back(get_lca(key[i], key[i + 1]));
    sort(key.begin(), key.end(), cmp_dfn);
    key.erase(unique(key.begin(), key.end()), key.end());
    //--- 单调栈连边: 栈内是"从根到当前点的链", 按 dfn 依次插入 ---
    vector<int> stk;
    for(int x : key) {
        while(!stk.empty() && get_lca(stk.back(), x) != stk.back())
            stk.pop_back();                //栈顶不是 x 的祖先则弹出(栈顶已经连好边)
        if(!stk.empty())    add_vt(stk.back(), x, depth[x] - depth[stk.back()]);
        stk.push_back(x);
    }
    return key;                            //stk 底 = 虚树根(key[0] 即 dfn 最小的点, 必为根)
}
//配套:
//1. 清空: 每次询问后遍历 key 重置 head2[x] = 0 并 edge_cnt = 0(不要 memset 整个 head2)
//2. DP 在虚树上与原树等价(虚树边压缩了链, 边权/贡献按压缩距离计)
//3. 关键点包含根的情况: 根不加也能自动成为 dfn 最小的关键点祖先? 需保证 1 在 key 中或 stk 处理
//4. 常见应用: 多组"选 k 个关键点求路径并/最小代价/两两距离和"的树形 DP
