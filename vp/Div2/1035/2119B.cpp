#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, px, py, qx, qy, n;
void solve() {
    cin >> n >> px >> py >> qx >> qy;
    int sum = 0, mx = 0;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        mx = max(mx, x);
        sum += x;
    }
    double dist = sqrt((px - qx) * (px - qx) + (py - qy) * (py - qy));
    if(2 * mx - sum > dist) {
        cout << "No\n";
        return;
    }
    if(sum < dist) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}