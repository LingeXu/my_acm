#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
struct interval {
    int l, r;
};
void solve() {
    cin >> n;
    vector<interval> a(n);
    int ans = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i].l >> a[i].r;
        ans += 2 * a[i].r - a[i].l;
    }
    sort(a.begin(), a.end(), [](auto &x, auto &y){return x.l + x.r < y.l + y.r;});
    if(n % 2 == 0) {
        for(int i = 0; i < n / 2; i++)
            ans -= a[i].l + a[i].r;
        cout << ans << '\n';
    }
    else {
        if(n == 1) {
            cout << a[0].r - a[0].l << '\n';
            return;
        }
        int pref_sum1 = 0, pref_sum2 = 0;
        for(int i = 0; i < n / 2; i++)
            pref_sum1 += a[i].l + a[i].r;
        pref_sum2 = pref_sum1 + a[n / 2].l + a[n / 2].r;
        int minus = LLONG_MAX;
        for(int i = 0; i < n; i++) {
            int cur = a[i].r;
            if(i < n / 2) {
                cur += pref_sum2;
                cur -= a[i].l + a[i].r;
            }
            else    cur +=  pref_sum1;
            minus = min(cur, minus);
        }
        cout << ans - minus << '\n';
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}