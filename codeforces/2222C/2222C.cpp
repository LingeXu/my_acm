#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n), b;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        b.push_back(a[i]);
    }
    sort(b.begin(), b.end());
    int aim = b[n / 2];
    vector<int> big(n + 1), small(n + 1);
    for(int i = 1; i <= n; i++) {
        big[i] = big[i - 1] + (a[i - 1] > aim);
        small[i] = small[i - 1] + (a[i - 1] < aim);
    }
    vector<int> dp(n + 1, -1);
    dp[0] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = i - 1; j >= 0; j -= 2) {
            if(dp[j] == -1)
                continue;
            int bigger = big[i] - big[j], smaller = small[i] - small[j], cnt = i - j - bigger - smaller;
            
            //cout << "i = " << i << ", j = " << j << '\n';
            //cout << "bigger = " << bigger << ", smaller = " << smaller << "cnt = " << cnt << '\n';

            if(abs(bigger - smaller) <= cnt && cnt > 0)
                dp[i] = max(dp[i], dp[j] + 1);
        }
    }

    /*for(int i = 1; i <= n; i++)
        cout << dp[i] << ' ';
    cout << '\n';*/

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