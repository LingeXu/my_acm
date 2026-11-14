#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, w, h, a, b, x1, y_1, x2, y2;
void solve() {
    cin >> w >> h >> a >> b >> x1 >> y_1 >> x2 >> y2;
    if(x1 == x2) {
        if(abs(y_1 - y2) % b == 0) {
            cout << "Yes\n";
            return;
        }
        cout << "No\n";
        return;
    }
    if(y_1 == y2) {
        if(abs(x1 - x2) % a == 0) {
            cout << "Yes\n";
            return;
        }
        cout << "No\n";
        return;
    }
    if(abs(x1 - x2) % a == 0 || abs(y_1 - y2) % b == 0) {
        cout << "Yes\n";
        return;
    }
    cout << "No\n";
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}