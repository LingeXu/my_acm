#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, m;
void solve(){
    cin >> n >> m;
    vector<int> dp(n + 2, 0);
    dp[0] = 1;
    for(int i = n; i >= 1; i--) {
        vector<int> cur(n + 2, 0);
        for(int j = 0; j <= n - i + 1; j++) {
            if(j - 1 >= 0)  cur[j] = (cur[j] + dp[j - 1]) % m;
            cur[j] = (cur[j] + i % m * (j + 1) % m * dp[j]) % m;
        }
        for(int j = 0; j <= n - i + 1; j++)
            dp[j] = cur[j];
    }
    int ans = 0;
    for(int i = 0; i <= n; i++)
        ans = (ans + dp[i]) % m;
    cout << ans << '\n';
    return;
}
signed main(){
    ios::sync_with_stdio(false); 
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}