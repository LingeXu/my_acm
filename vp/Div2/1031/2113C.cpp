#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, m, k;
vector<vector<int>> pre_sum, ok;
int get_sum(int a, int b, int c, int d) {
    return pre_sum[c][d] - pre_sum[max(0LL, a - 1)][d] - pre_sum[c][max(0LL, b - 1)] + pre_sum[max(0LL, a - 1)][max(0LL, b - 1)];
}
void solve() {
    cin >> n >> m >> k;
    int cnt_g = 0;
    pre_sum.assign(n + 1, vector<int>(m + 1)), ok.assign(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for(int j = 0; j < m; j++) {
            if(s[j] == 'g') {
                cnt_g++;
                pre_sum[i][j + 1] = pre_sum[i - 1][j + 1] + pre_sum[i][j] - pre_sum[i - 1][j] + 1;
            }
            else     pre_sum[i][j + 1] = pre_sum[i - 1][j + 1] + pre_sum[i][j] - pre_sum[i - 1][j];
            if(s[j] == '.')  ok[i][j + 1] = 1;
        }
    }

    /*for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) 
            cout << pre_sum[i][j] << ' ';
        cout << '\n';
    }*/
   
    int ans = 0;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(ok[i][j] != 1)   continue;
            ans = max(ans, cnt_g - get_sum(max(0LL, i - k + 1), max(0LL, j - k + 1), min(n, i + k - 1), min(m, j + k - 1)));
        } 
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