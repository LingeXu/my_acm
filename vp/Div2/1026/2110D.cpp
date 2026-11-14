#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 200005
int t, n, m;
vector<int> b, mx;
vector< pair<int, int> > graph[N];
bool check(int x) {
    fill(mx.begin(), mx.end(), -1);
    mx[1] = min(x, b[1]);
    for(int i = 1; i <= n; i++) {
        if(mx[i] == -1)
            continue;
        for(auto &e : graph[i]) {
            int v = e.second;
            int w = e.first;
            if(w > min(x, mx[i]))   continue;
            mx[v] = max(mx[v], min(mx[i] + b[v], x));
        }
    }
    return mx[n] != -1;
}
void solve() {
    cin >> n >> m;
    b.resize(n + 1);
    mx.resize(n + 1);
    for(int i = 1; i <= n; i++)
        graph[i].clear();
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
        sum += b[i];
    }
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({w, v});
    }
    int l = 0, r = sum, ans = -1;
    while(l <= r) {
        int mid = (l + r) / 2;
        if(check(mid)) {
            ans = mid;
            r = mid - 1;
        }
        else    l = mid + 1;
    }
    cout << ans << '\n';
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}