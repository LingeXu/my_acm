#include <bits/stdc++.h>
using namespace std;
#define N 500005
int t, n;
vector<int> a, graph[N];
void solve() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        graph[i].clear();
    a.resize(n + 1);
    for(int i = 1; i <= n; i++) 
        cin >> a[i];
    vector<int> ok(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        if(a[u] == a[v])    ok[a[u]] = 1;
    }
    vector<int> last(n + 1);
    for(int i = 1; i <= n; i++) {
        for(int v : graph[i]) {
            if(last[a[v]] == i)    ok[a[v]] = 1;
            else    last[a[v]] = i;
        }
    }
    for(int i = 1; i <= n; i++) {
        if(ok[i] == 1)   cout << 1;
        else    cout << 0;
    }
    cout << '\n';
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}