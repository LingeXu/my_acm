#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++)  cin >> a[i];
    int ans = n * (n + 1) / 2;
    for(int i = 1; i < n; i++)
        if(a[i] > a[i + 1])
            ans += i * (n - i);
    cout << ans << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}
