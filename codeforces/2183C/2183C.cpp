#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, m, k;
vector<int> c(200006);
int f(int l, int r) {
    return l + r + max(l, r) - 1;
}
void solve() {
    cin >> n >> m >> k;
    int rem_l = k - 1, rem_r = n - k;
    if(f(rem_l, rem_r) <= m) {
        cout << n << '\n';
        return;
    }
    int ans = 0;
    for(int i = 0; i <= rem_l; i++) {
        if(2 * i - 1 > m)   break;
        int l = 0, r = rem_r, dist = -1;
        while(l <= r) {
            int mid = (l + r) / 2;
            if(f(i, mid) <= m) {
                dist = mid;
                l = mid + 1;
            }
            else    r = mid - 1;
        }
        ans = max(ans, i + dist + 1);
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