#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
void solve() {
    cin >> n;
    vector<int> h(n + 1), dp(n + 1);
    for(int i = 1; i <= n; i++)
        cin >> h[i];
    dp[1] = h[1];
    for(int i = 2; i <= n; i++)
        dp[i] = min(dp[i - 1] + h[i] - 1, dp[i - 2] + h[i - 1] + max(0LL, h[i] - (i - 1)));
    cout << dp[n] << '\n';
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}