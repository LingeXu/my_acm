#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, l, r, k;
void solve() {
    cin >> n >> l >> r >> k;
    if(n % 2 == 1) {
        cout << l << '\n';
        return;
    }
    if(n == 2) {
        cout << -1 << '\n';
        return;
    }
    int a = __builtin_clzll(l), b = __builtin_clzll(r);
    if(a == b) {
        cout << -1 << '\n';
        return;
    }
    if(k == n || k == n - 1) {
        cout << (1LL << (64 - a)) << '\n';
        return;
    }
    cout << l << '\n';
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}