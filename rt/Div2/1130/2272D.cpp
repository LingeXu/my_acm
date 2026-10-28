#include <bits/stdc++.h>
using namespace std;
int t, k, n;
void solve() {
    cin >> k;
    int cur = 0, idx = -1, aim = -1;
    bool found = false;
    while(k--) {
        cur++;
        bool ok = true;
        cin >> n;
        vector<int> graph[n + 1];
        if(n == 1)
            ok = false;
        vector<int> deg(n + 1, 0);
        for(int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
            deg[u]++;
            deg[v]++;
        }
        if(!found && ok) {
            found = true;
            idx = cur;
            for(int i = 1; i <= n; i++) {
                if(deg[i] == 1) {
                    aim = graph[i][0];
                    break;
                }
            }
        }
    }
    if(idx == -1 && aim == -1) {
        idx = 1;
        aim = 1;
    }
    for(int i = 1; i <= cur; i++) 
        if(i != idx)
            cout << idx << ' ' << aim << ' ' << i << ' ' << 1 << '\n';
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}