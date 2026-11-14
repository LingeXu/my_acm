#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
int t, n;
string s;
int f[5005], dp[5005][5005], cnt[2];
void init() {
    dp[1][0] = 0, dp[1][1] = 1;
    for(int i = 2; i <= 5000; i++)
        for(int j = 1; j <= i; j++)
            dp[i][j] = (dp[i - 1][j] * j % MOD + dp[i - 1][j - 1]) % MOD;
    f[2] = 1;
    f[3] = 1;
    f[4] = 1;
    for(int i = 5; i <= 5000; i++)
        f[i] = (f[i - 2] + f[i - 3]) % MOD;
}
void solve() {
    cnt[0] = cnt[1] = 0;
    cin >> n >> s;
    int ans = 1, sum = 0;
    for(int i = 0; i < n;) {
        int j = i;
        while(j < n && (((s[j] - '0') ^ (j % 2)) == ((s[i] - '0') ^ (i % 2))))
            j++;
        int sz = j - i;

        //cout << "sz = " << sz << '\n';

        if(sz >= 2) {
            sum += 2 * sz;
            ans = ans * f[sz] % MOD;
        }
        else {
            sum++;
            cnt[s[i] - '0']++;
        }
        i = j;
    }
    int cnt_0 = 0;
    for(int i = 1; i <= cnt[0]; i++)
        cnt_0 = (cnt_0 + dp[cnt[0]][i]) % MOD;
    int cnt_1 = 0;
    for(int i = 1; i <= cnt[1]; i++)
        cnt_1 = (cnt_1 + dp[cnt[1]][i]) % MOD;
    if(cnt[0] == 0)
        cnt_0 = 1;
    if(cnt[1] == 0)
        cnt_1 = 1; 

    //cout << "cnt_0 = " << cnt_0 << '\n';
    //cout << "cnt_1 = " << cnt_1 << '\n';

    cout << sum << ' ' << (ans * cnt_0) % MOD * cnt_1 % MOD << '\n';
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    cin >> t;
    while(t--)  solve();
    return 0;
}