#include <bits/stdc++.h>
using namespace std;
int t, l, r;
void solve() {
    cin >> l >> r;
    if(l == 1 && r == 1) {
        cout << 1 << '\n';
        return;
    }
    cout << r - l << '\n';
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}