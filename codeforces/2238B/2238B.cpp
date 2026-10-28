#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
void solve() {
    cin >> n;
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int cur = n / i;
        ans += cur * cur;
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