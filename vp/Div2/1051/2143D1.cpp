#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
#define N 305
int dp[2][N][N];
int t, n;
void solve() {
    memset(dp, 0, sizeof(dp));
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    int mx = 0, m = 0;
    dp[0][0][0] = 1;
    dp[0][a[0]][0] = 1;
    for(int i = 0; i < n - 1; i++) {
        mx = max(mx, a[i]);
        if(a[i] > m && a[i] < mx)   m = a[i];
        for(int j = 0; j <= mx; j++)
            for(int k = 0; k <= min(m, j); k++)
                dp[(i + 1) % 2][j][k] = dp[i % 2][j][k];
        for(int j = 0; j <= mx; j++) {
            for(int k = 0; k <= min(m, j); k++) {
                if(a[i + 1] >= j) {
                    dp[(i + 1) % 2][a[i + 1]][k] = (dp[(i + 1) % 2][a[i + 1]][k] + dp[i % 2][j][k]) % MOD;
                    continue;
                }
                if(a[i + 1] >= k && a[i + 1] < j) {
                    dp[(i + 1) % 2][j][a[i + 1]] = (dp[(i + 1) % 2][j][a[i + 1]] + dp[i % 2][j][k]) % MOD;
                    continue;
                }
                if(a[i + 1] < k)    continue;
            }
        }
    }
    int ans = 0;
    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= i; j++)
            ans = (ans + dp[(n - 1) % 2][i][j]) % MOD;
    cout << ans << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}