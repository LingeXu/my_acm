#include <bits/stdc++.h>
using namespace std;
int t, l, r;
void solve() {
    cin >> l >> r;
    if(l == r && l == 0) {
        cout << 0 << '\n';
        return;
    }
    if(l > 0 || r < 0) {
        cout << r - l << '\n';
        return;
    }
    int rem = 2 * min(-l, r) + 2;
    if(rem >= r - l + 1) {
        cout << 0 << '\n';
        return;
    }
    cout << r - l + 1 - 2 * min(-l, r) - 2 << '\n';
    return;
}
int main() {
    cin >> t;
    while(t--)  solve();
    return 0;
}