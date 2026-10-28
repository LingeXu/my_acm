#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
void solve() {
    cin >> n;
    int ans = 0;
    vector<int> a(n);
    for(int i =0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.end(), [](auto &x, auto & y){return x > y;});
    for(int i = 0; i < n; i += 2) {
        ans += a[i];
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