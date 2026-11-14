#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    int ans = 0;
    for(int i = 2; i <= n; i += 2) {
        if(i == n) {
            if(a[i] >= a[i - 1])
                continue;
            int diff = a[i - 1] - a[i];
            ans += diff;
            a[i - 1] = a[i];
        }
        else {
            if(a[i - 1] + a[i + 1] <= a[i])
                continue;
            int diff = a[i - 1] + a[i + 1] - a[i];
            if(diff <= a[i + 1]) {
                a[i + 1] -= diff;
                ans += diff;
                continue;
            }
            else {
                a[i - 1] -= (diff - a[i + 1]);
                a[i + 1] = 0;
                ans += diff;
                continue;
            }
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