//树上最大独立集: 从树上选取若干个互不相邻的结点, 求它们的最大权值和
//需预定义: vector<int> graph[N];  int dp[N][2], w[N];  (dp[u][0/1] = 不选/选 u 时子树答案)
//入口: dfs(root, 0);  答案 = max(dp[root][0], dp[root][1])
void dfs(int u, int fa) {
    dp[u][0] = 0;       //不选u
    dp[u][1] = w[u];    //选u
    for(int v : graph[u]) {
        if(v == fa)
            continue;
        dfs(v, u);
        dp[u][0] += max(dp[v][0], dp[v][1]);
        dp[u][1] += dp[v][0];
    }
}