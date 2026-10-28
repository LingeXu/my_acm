//换根DP: 先求固定根(1)下的信息, 再 O(1) 把答案从父亲"平移"到儿子, 得到每个点为根的答案
//适用: 求"以每个节点为根"的某种统计(如子树到根距离和、经过每个点的路径贡献)
//需预定义: vector<int> graph[N];  int sz[N];  ll dp[N], ans[N];
//入口: dfs1(1, 0); ans[1] = dp[1]; dfs2(1, 0);

void dfs1(int u, int fa) {                     //第一遍: 求子树大小与"子树内节点到 u 的距离和"
    sz[u] = 1;
    dp[u] = 0;
    for(int v : graph[u]) {
        if(v == fa)
            continue;
        dfs1(v, u);
        sz[u] += sz[v];
        dp[u] += (dp[v] + sz[v]);              //v 子树里每个点多走一条边 (u, v)
    }
}

void dfs2(int u, int fa) {                     //第二遍: 换根, ans[v] 由 ans[u] 平移
    for(int v : graph[u]) {
        if(v == fa)
            continue;
        //根从 u 换到 v: v 子树内所有点少走一条边(-sz[v]), 其余点(n - sz[v])多走一条边
        ans[v] = ans[u] - sz[v] + (n - sz[v]);
        dfs2(v, u);
    }
}
//注意: 带边权时公式换成 ans[v] = ans[u] - w * sz[v] + w * (n - sz[v]) (w 为边 (u,v) 的权)
