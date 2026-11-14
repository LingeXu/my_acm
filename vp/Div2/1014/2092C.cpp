#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n);
    int cnt_odd = 0, sum = 0, mx = -1;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
        if(a[i] % 2 == 1)   cnt_odd++;
        sum += a[i];
    }
    if(cnt_odd == n || cnt_odd == 0) {
        cout << mx << '\n';
        return;
    }
    cout << sum - cnt_odd + 1 << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}