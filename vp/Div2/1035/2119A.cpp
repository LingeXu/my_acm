#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, a, b, x, y;
void solve() {
    cin >> a >> b >> x >> y;
    if(a == b) {
        cout << 0 << '\n';
        return;
    }
    if(a > b) {
        if(a % 2 == 0 || a - b >= 2) {
            cout << -1 << '\n';
            return;
        }
        if(a % 2 == 1 && a - b == 1) {
            cout << y << '\n';
            return;
        }
    }
    if(x <= y) {
        cout << x * (b - a) << '\n';
        return;
    }
    if((b - a) % 2 == 0) {
        cout << (b - a) / 2 * (x + y) << '\n';
        return;
    }
    if((b - a) % 2 == 1) {
        int num = (b - a) / 2;
        if(a % 2 == 0) {
            cout << (num + 1) * y + num * x << '\n';
            return;
        }
        else {
            cout << num * y + (num + 1) * x << '\n';
            return;
        }
    }
}
signed main() {
    cin >> t;
    while(t--)  solve();
    return 0;
}