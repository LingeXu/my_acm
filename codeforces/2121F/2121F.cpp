#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, s, x;
void solve() {
    cin >> n >> s >> x;
    vector<int> a(n + 1), pref_sum(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        pref_sum[i] = pref_sum[i - 1] + a[i];
    }
    map<int, int> cnt;
    int l = 1, ans = 0;
    for(int r = 1; r <= n; r++) {
        if(a[r] > x) {
            cnt.clear();
            l = r + 1;
        }
        else if(a[r] == x) {
            while(l <= r) {
                cnt[pref_sum[l - 1]]++;
                l++;
            }
        }
        ans += cnt[pref_sum[r] - s];
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