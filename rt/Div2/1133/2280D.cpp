#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
#define N 200005
int t, n;
int dp[8][3];
bool has[3 * N];
void solve() {
    memset(dp, 0, sizeof(dp));
    memset(has, 0, sizeof(has));
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        has[a[i]] = true;
    }
    sort(a.begin(), a.end());
    dp[0][0] = 1;
    for(int i = a[n - 1]; i >= a[0]; i--) {
        int ndp[8][3] = {};
        for(int j = 0; j < 8; j++) {
            int cnt = __builtin_popcount(j);
            for(int k = 0; k < 3; k++) {
                int maxC = (has[i] ? 1 : 0);
                for(int c = 0; c <= maxC; c++) {
                    int nj = (j >> 1) | (c << 2);
                    int nc = k + (c == 1 && cnt != 2);
                    if(nc > 2)  continue;
                    ndp[nj][nc] = (ndp[nj][nc] + dp[j][k]) % MOD;
                }
            }
        }
        memcpy(dp, ndp, sizeof(dp));
    }
    int ans = -1;
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 3; j++)
            ans = (ans + dp[i][j]) % MOD;
    cout << ans << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}