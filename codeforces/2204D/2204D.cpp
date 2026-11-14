#include <bits/stdc++.h>
using namespace std;
#define N 200005
int t, n, m;
vector<int> graph[N], color;
int bfs(int u) {
    int cnt_0 = 0, cnt_1 = 0;
    queue< pair<int, int> > q;
    color[u] = 0;
    q.push({u, 0});
    cnt_0++;
    bool ok = true;
    while(!q.empty()) {
        auto x = q.front();
        q.pop();
        for(int v : graph[x.first]) {
            if(color[v] == -1) {
                color[v] = 1 - x.second;
                if(color[v] == 0) {
                    //cout << "v = " << v << '\n';
                    cnt_0++;
                }
                else {
                    //cout << "v = " << v << '\n';
                    cnt_1++;
                }
                q.push({v, color[v]});
                continue;
            }
            if(color[v] == 1 - x.second)    continue;
            if(color[v] != 1 - x.second)    ok = false;
        }
    }
    //cout << "ok = " << ok << '\n';
    //cout << "cnt_0 = " << cnt_0 << ", cnt_1 = " << cnt_1 << '\n';
    if(!ok)
        return 0;
    return max(cnt_0, cnt_1);
}
void solve() {
    cin >> n >> m;
    color.assign(n + 1, -1);
    for(int i = 1; i <= n; i++)
        graph[i].clear();
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(color[i] == -1) {
            //cout << "i = " << i << ", bfs = " << bfs(i) << '\n';
            ans += bfs(i);
        }
    }
    cout << ans << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}