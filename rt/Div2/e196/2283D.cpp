#include <bits/stdc++.h>
using namespace std;
#define N 300005
int t, n;
vector<int> graph[N];
bool bfs(int u, int ans) {
    vector<int> group(n + 1, -1);
    queue<int> q;
    group[u] = 0;
    for(int v : graph[u]) {
        q.push(v);
        group[v] = v;
    }
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        for(int v : graph[x]) {
            if(group[v] != - 1) 
                continue;
            group[v] = group[x];
            q.push(v);
        }
    }
    for(int i = 1; i <= n; i++) {
        if(i == u)  continue;
        if(group[i] != group[ans - i])
            return true;
    }
    return false;
}
void solve() {
    ios::sync_with_stdio(false);
    cin.tie(0);
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
    if(n % 2 == 0) {
        cout << 1 + n << '\n';
        return;
    }
    if(bfs(1, n + 2)) {
        cout << n + 2 << '\n';
        return;
    }
    if(bfs((n + 1) / 2, n + 1)) {
        cout << n + 1 << '\n';
        return;
    }
    cout << n << '\n';
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}
