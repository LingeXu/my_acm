#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    bool same = true;
    int ans = 0;
    for(int i = 31; i >= 0; i--) {
        if(!same) {
            ans += (1 << i);
            continue;
        }
        int cur = (a[0] & (1 << i));
        for(int j = 1; j < n; j++) {
            if((a[j] & (1 << i)) != cur) {
                same = false;
                ans += (1 << i);
                break;
            }
        }
        if(!same)   continue;
        ans += cur;
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