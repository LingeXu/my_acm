#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, k;

/*vector<int> dp;
void solve() {
    cin >> n >> k;
    int groups = n / (k + 1);
    int r_mx = k * groups;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    dp.assign(r_mx + 1, -1);
    dp[0] = 0;
    for(int i = 0; i < n; i++) {
        vector<int> ndp(r_mx + 1, -1);
        for(int j = 0; j <= r_mx; j++) {
            if(dp[j] == -1)  continue;
            if(j + k <= r_mx)
                ndp[j + k] = max(ndp[j + k], dp[j] + a[i + 1]);
            if(j > 0)
                ndp[j - 1] = max(ndp[j - 1], dp[j]);
            else if(j == 0)  ndp[0] = max(ndp[0], dp[0]);
        }
        dp = ndp;
    }
    cout << dp[0] << '\n';
}*/

void solve() {
    cin >> n >> k;
    int groups = n / (k + 1);
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    priority_queue< int, vector<int>, greater<int> > pq;
    for(int i = n; i >= 1; i--) {
        pq.push(a[i]);
        while(pq.size() > (n - i + 1) / (k + 1))  pq.pop();
    }
    int sum = 0;
    while(!pq.empty()) {
        int x = pq.top();
        pq.pop();
        sum += x;
    }
    cout << sum << '\n';
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}