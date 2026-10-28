#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, c;
void solve() {
    cin >> n >> c;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    bool ok1 = true;
    int ans = 0;
    for(int i = 0; i < n; i++) {
        cin >> b[i];
        int diff = a[i] - b[i];
        if(diff < 0)    ok1 = false;
        ans += diff;
    }
    if(ok1) {
        cout << ans << '\n';
        return;
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    bool ok2 = true;
    for(int i = 0; i < n; i++) {
        if(a[i] < b[i]) {
            ok2 = false;
            break;
        }
    }
    if(!ok2) {
        cout << -1 << '\n';
        return;
    }
    cout << ans + c << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}