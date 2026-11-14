#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, k, a, b, x, y;
void solve() {
    cin >> k >> a >> b >> x >> y;
    if(k < a && k < b) {
        cout << 0 << '\n';
        return;
    }
    if(a > b) {
        swap(a, b);
        swap(x, y);
    }
    if((k >= a && k < b) || x <= y) {
        cout << (k - a) / x + 1 << '\n';
        return;
    }
    int cnt = (k - b) / y + 1;
    int cur = k - cnt * y;
    if(cur >= a)
        cout << cnt + (cur - a) / x + 1 << '\n';
    else    cout << cnt << '\n';
}
signed main() {
    cin >> t;
    while(t--)  solve();
    return 0;
}