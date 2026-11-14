#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, l, r;
void solve() {
    cin >> n >> l >> r;
    vector<int> a(n + 1), b, c;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(i <= r)   b.push_back(a[i]);
        if(i >= l)   c.push_back(a[i]);
    }
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());
    int ans1 = 0;
    for(int i = 0; i < r - l + 1; i++)
        ans1 += b[i];
    int ans2 = 0;
    for(int i = 0; i < r - l + 1; i++)
        ans2 += c[i];
    cout << min(ans1, ans2) << '\n';
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}