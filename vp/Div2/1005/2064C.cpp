#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)  cin >> a[i];
    int ans = 0, l = 0, r = n - 1;
    for(int i = 0; i < n; i++) {
        if(a[i] >= 0) {
            ans += a[i];
            l++;
        }
        else {

            break;
        }
    }
    for(int i = n - 1; i >= 0; i--) {
        if(a[i] < 0) {
            ans -= a[i];
            r--;
        }
        else {
          
            break;
        }
    }

    //cout << "ans = " << ans << '\n';
    //cout << "l = " << l << ", r = "  << r << '\n';

    vector< pair<int, int> > record;
    int p = -1;
    for(int i = l; i <= r; ) {
        int j = i, cur = 0;
        while(j <= r && ((p == -1 && a[j] < 0) || (p == 1 && a[j] >= 0))) {
            cur += abs(a[j]);
            j++;
        }
        record.push_back(make_pair(cur, p));
        p *= -1;
        i = j;
    }

    /*cout << "Test:\n";
    for(auto &[val, p] : record)
        cout << "val = " << val << ", p = " << p << '\n';
    cout << '\n';*/
    
    int sz = record.size(), all_even = 0;
    vector<int> dp(sz / 2 + 1);
    for(int i = 0; i < sz / 2; i++) {
        all_even += record[i * 2 + 1].first;
        dp[i + 1] = max(dp[i] + record[i * 2].first, all_even);
    }
    cout << ans + dp[sz / 2] << '\n';
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}