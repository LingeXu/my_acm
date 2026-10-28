#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n);
    int ans = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(i % 2 == 0)
            ans += a[i];
        else    ans -= a[i];
    }
    int change = n - 1 - (n % 2 == 0 ? 1 : 0); 
    int pre_1_mn = LLONG_MAX, pre_2_mx = -LLONG_MAX;
    for(int i = 0; i < n; i++) {
        if(i % 2 == 0) {
            int cur = -2 * a[i] + i;
            if(i != 0)
                change = max(change, cur + pre_2_mx);
            pre_1_mn = min(pre_1_mn, 2 * a[i] + i);
        }
        else {
            int cur = 2 * a[i] + i;
            if(i != 0)
                change = max(change, cur - pre_1_mn);
            pre_2_mx = max(pre_2_mx, 2 * a[i] - i);
        }
    }
    cout << ans + max(0LL, change) << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}