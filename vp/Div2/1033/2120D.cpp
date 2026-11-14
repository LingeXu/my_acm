#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9 + 7;
int t, a, b, k, n;
int quick_pow(int a, int p) {
    int res = 1, base = a;
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
int C(int n, int m) {
    int res = 1;
    for(int i = n; i > n - m; i--)
        res = res * i % MOD;
    for(int i = 1; i <= m; i++)
        res = res * inv(i) % MOD;
    return res;
}
void solve() {
    cin >> a >> b >> k;
    n = (k * (a - 1) + 1) % MOD;
    //cout << "n = " << n << '\n';
    cout << n << ' ' << (k * C(n, a) % MOD * (b - 1) + 1) % MOD << '\n';
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}