#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
int sum(int x) {
    int res = 0;
    for(int i = 1; i <= x; i++)
        res += x / i * i;
    return res;
}
void solve() {
    cin >> n;
    int l = 0, r = n, ans = -1;
    while(l <= r) {
        int mid = (l + r) / 2;
        if(sum(mid) >= n) {
            ans = mid;
            r = mid - 1;
        }
        else    l = mid + 1;
    }
    cout << ans << '\n';
    int rem = n;
    vector<int> group(ans + 1);
    for(int i = ans; i >= 1; i--) {
        group[i] = min(ans, rem) / i;
        rem -= group[i] * i;
    }
    int idx = 1;
    for(int i = ans; i >= 1; i--) {
        for(int j = idx; j < idx + group[i]; j++) 
            for(int k = 1; k <= i; k++)
                cout << j << ' ';
        idx += group[i];
    }
    cout << '\n';
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}