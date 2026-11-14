#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, m;
void solve() {
    cin >> n >> m;
    if(n == m) {
        cout << -1 << '\n';
        return;
    }
    int mx = max(n, m), cur = 1LL;
    while(cur < mx) cur <<= 1;
    cout << cur - mx << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}