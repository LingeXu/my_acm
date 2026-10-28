#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, a, b, c, d;
void solve() {
    cin >> a >> b >> c >> d;
    if(a >= b) {
        swap(a, b);
        swap(c, d);
    }
    if(c <= b) {
        cout << c - a + d - b << '\n';
        return;
    }
    else {
        cout << b - a + min(c, d) - b + abs(c - d) << '\n';
        return;
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}