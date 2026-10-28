#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define N 500005
int t, n, q;
int ans[N];
vector<int> graph[N];
void dfs(int u, int fa) {
    if(fa == 1)  return;
    ans[u] = ans[fa] + 1;
    for(int v : graph[u]) {
        if(v == fa)
            continue;
        dfs(v, u);
    }
}
void solve() {
    cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        ans[i] = 0;
        graph[i].clear();
    }
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(n, 0);
    int l = 0;
    while(q--) {
        int x;
        cin >> x;
        l = max(l, ans[x]);
    }
    cout << max(ans[1] - 1, l) << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}