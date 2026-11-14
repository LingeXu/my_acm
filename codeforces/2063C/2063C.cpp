#include <bits/stdc++.h>
using namespace std;
int t, n;
void solve() {
    cin >> n;
    vector<int> deg(n + 1, 0);
    vector< vector<int> > graph(n + 1, vector<int>());
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        deg[u]++;
        deg[v]++;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<int> ord;
    for(int i = 1; i <= n; i++) {
        ord.push_back(i);
        sort(graph[i].begin(), graph[i].end());
    }
    sort(ord.begin(), ord.end(), [&](int x, int y){return deg[x] > deg[y];});
    int ans = 0;
    auto adj = [&](int u, int v) {
        auto it = lower_bound(graph[u].begin(), graph[u].end(), v);
        if(it == graph[u].end() || *it != v)    return false;
        return true;
    };
    for(int i = 1; i <= n; i++) {
        for(int j : ord) {
            if(j == i)  continue;
            if(adj(i, j))   continue;
            else    ans =  max(ans, deg[i] + deg[j] - 1);
            break;
        }
        for(int j : graph[i])
            ans = max(ans, deg[i] + deg[j] - 2);
    }
    cout << ans << '\n';
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}