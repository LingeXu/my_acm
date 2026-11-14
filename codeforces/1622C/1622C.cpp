#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, k;
void solve() {
    cin >> n >> k;
    vector<int> a(n);
    int sum = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    sort(a.begin(), a.end());
    vector<int> diff_sum(n);
    for(int i = 1; i < n; i++)
        diff_sum[i] = diff_sum[i - 1] + (a[n - i] - a[0]);
    int diff = sum - k;
    if(diff <= 0) {
        cout << 0 << '\n';
        return;
    }
    int ans = LLONG_MAX;
    for(int i = 0; i <= n - 1; i++) {
        int cur = diff - diff_sum[i];
        if(cur <= 0) {
            ans = min(ans, i);
            break;
        }
        ans = min(ans, i + cur / (i + 1) + (cur % (i + 1) != 0));
    }
    cout << ans << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}