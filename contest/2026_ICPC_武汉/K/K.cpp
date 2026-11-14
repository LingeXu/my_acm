#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
#define N 200005
int t, n, ans;
vector<int> graph[N], a, b, fac(200006), sz1, sz2;
void init() {
    fac[0] = 1;
    for(int i = 1; i <= 200005; i++)
        fac[i] = fac[i - 1] * i % MOD;
}
int quick_pow(int a, int p) {
    int res = 1, base = a % MOD;
    while(p) {
        if(p & 1)   res = res * base % MOD;
        p >>= 1;
        base = base * base % MOD;
    }
    return res;
}
int inv(int x) {
    return quick_pow(x, MOD - 2);
}
int dfs1(int u) {
    if(sz1[u] != 0LL)
        return sz1[u];
    int res = 1;
    for(int v : graph[u]) 
        if(b[v] > a[u]) 
            res += dfs1(v);
    return sz1[u] = res;
}
int dfs2(int u) {
    if(sz2[u] != 0LL)
        return sz2[u];
    int res = 1;
    for(int v : graph[u]) 
        if(b[u] < a[v]) 
            res += dfs2(v);
    return sz2[u] = res;
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) 
        graph[i].clear();
        
    //cout << "fac = " << fac[n] << '\n';

    for(int i = 2; i <= n; i++) {
        int fa;
        cin >> fa;
        graph[fa].push_back(i);
    }
    a.assign(n + 1, 0LL);
    b.assign(n + 1, 0LL);
    sz1.assign(n + 1, 0LL);
    sz2.assign(n + 1, 0LL);
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= n; i++)
        cin >> b[i];
    ans = fac[n];
    for(int i = 1; i <= n; i++) {
        //cout << "i = " << i << '\n';
        //cout << "dfs1 = " << dfs1(i) << '\n';
        //cout << "dfs2 = " << dfs2(i) << '\n';
        cout << '\n';
        ans = ans * inv(dfs1(i)) % MOD;
        ans = ans * inv(dfs2(i)) % MOD;
    }
    cout << ans << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    cin >> t;
    while(t--)  solve();
    return 0;
}