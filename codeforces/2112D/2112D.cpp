#include <bits/stdc++.h>
using namespace std;
#define N 200005
int t, n, root = -1, new_root = -1;
vector<int> graph[N];
void dfs(int u, int fa, int d) {
    for(int v : graph[u]) {
        if(v == fa)
            continue;
        if(u == root && v == new_root)  continue;
        if(d == 0)  cout << u << ' ' << v << '\n';
        else    cout << v << ' ' << u << '\n';
        dfs(v, u, d ^ 1);
    }
}
void solve() {
    root = -1;
    new_root = -1;
    cin >> n;
    for(int i = 1; i <= n; i++)
        graph[i].clear();
    vector<int> deg(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }
    for(int i = 1; i <= n; i++) {
        if(deg[i] == 2) {
            root = i;
            break;
        }
    }
    if(root == -1) {
        cout << "NO\n";
        return;
    }
    new_root = graph[root][0];
    cout << "YES\n";
    cout << root << ' ' << new_root << '\n';
    dfs(new_root, root, 1);
    dfs(root, 0, 1);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}