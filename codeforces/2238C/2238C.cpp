#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 200020
int t, n;
vector<int> graph[N], depth(N, 0);
void init(int u, int fa) {
    depth[u] = 1;
    for(int v : graph[u]) {
        if(v == fa)
            continue;
        init(v, u);
        depth[u] = max(depth[u], depth[v] + 1);
    }
}
int dfs(int u, int fa) {
    int res = 0, child = 0, mx_depth = 0, sec_depth = 0;
    for(int v : graph[u]) {
        if(v == fa)
            continue;
        child++;
        if(depth[v] >= mx_depth) {
            sec_depth = mx_depth;
            mx_depth = depth[v];
        }
        else if(depth[v] < mx_depth && depth[v] >= sec_depth)   sec_depth = depth[v];
        res += dfs(v, u);
    }
    if(child == 0)  return 1;
    if(child == 1)  return res + 1;
    else    return res + 1 + sec_depth;
}
void solve() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        depth[i] = 0;
        graph[i].clear();
    }
    for(int i = 2; i <= n; i++) {
        int fa;
        cin >> fa;
        graph[fa].push_back(i);
        graph[i].push_back(fa);
    }
    init(1, 0);
    cout << dfs(1, 0) << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}