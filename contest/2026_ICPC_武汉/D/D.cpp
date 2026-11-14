#include <bits/stdc++.h>
using namespace std;
#define N 200005
int n, m;
bool vis[N];
vector<int> a, graph[N], order[N], parent, depth;
void dfs(int u, int fa) {
    for(int v : graph[u]) {
        if(v == fa)
            continue;
        if(a[v] == a[u] + 1 && parent[v] == 0) {
            order[u].push_back(v);
            parent[v] = u;
            dfs(v, u);
        }
    }
}
void dfs2(int u, int d) {
    vis[u] = true;
    depth[u] = d;
    for(int v : order[u]) {
        if(vis[v])  continue;
        dfs2(v, d + 1);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    a.assign(n + 1, 0);
    parent.assign(n + 1, 0);
    depth.assign(n + 1, -1);
    int root = -1;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(a[i] == 0)   root = i;
    }
    for(int i = 1; i <= n; i++) {
        int cnt;
        cin >> cnt;
        for(int j = 1; j <= cnt; j++) {
            int v;
            cin >> v;
            graph[i].push_back(v);
            //graph[v].push_back(i);
        }
    }

    /*for(int i = 1; i <= n; i++) {
        for(int j : graph[i])
            cout << j << ' ';
        cout << '\n';
    }*/

    dfs(root, 0);

    /*for(int i = 1; i <= n; i++) {
        for(int j : order[i])
            cout << j << ' ';
        cout << '\n';
    }*/

    for(int i = 1; i <= n; i++) {
        for(int v : graph[i]) {
            if(parent[v] == i)
                continue;
            order[i].push_back(v);
        }
    }
    dfs2(root, 0);
    for(int i = 1; i <= n; i++) {
        if(depth[i] != a[i]) {
            cout << -1 << '\n';
            return 0;
        }
    }
    cout << root << '\n';
    for(int i = 1; i <= n; i++) {
        for(int j : order[i])
            cout << j << ' ';
        cout << '\n';
    }
}