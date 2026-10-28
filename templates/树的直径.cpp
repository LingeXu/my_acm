//树的直径: 树上最长路径长度, 两种求法
//法一: 树形 dp, O(n), 一遍 dfs 同时求直径与路径(需存每个节点向下的最长/次长链)
//法二: 两次 dfs, O(n), 只适用于边权非负; 第一次找最远点, 第二次从最远点再找最远点
//需预定义: vector< pair<int, int> > graph[N];  (pair 为 (边权, 邻点))

//法一: 树上dp
int dfs(int u, int fa) {
    int max1 = 0, max2 = 0;                    //max1/max2 = u 向下最长/次长链
    for(auto& e : graph[u]) {
        int w = e.first, v = e.second;
        if(v == fa)
            continue;
        int d = dfs(v, u) + w;
        if(d > max1) {
            max2 = max1;
            max1 = d;
        }
        else if(d > max2)   max2 = d;
    }
    ans = max(ans, max1 + max2);               //直径 = 经过 u 的最长链 + 次长链, 取全局最大
    return max1;
}

//法二: 两次dfs (要求边权非负)
void dfs(int u, int fa, int d) {
    parent[u] = fa;
    dis[u] = d;
    if(d > dis[far])    far = u;               //far = 当前最远点
    for(auto& e : graph[u]) {
        int w = e.first, v = e.second;
        if(v == fa)
            continue;
        dfs(v, u, d + w);
    }
}

int get_diameter() {
    far = 1;
    dfs(1, 0, 0);                              //第一次: 从任意点出发找最远点 node1
    node1 = far;
    far = node1;
    dfs(node1, 0, 0);                          //第二次: 从 node1 出发, 最远点 node2
    node2 = far;
    return dis[far];                           //dis[node2] 即直径长度
}
//配套: 直径中点 = 树上一点, 到直径两端距离差最小; 所有点的最远点必是直径端点之一
