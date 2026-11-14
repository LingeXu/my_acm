#include <bits/stdc++.h>
using namespace std;
int t, n, m;
void solve() {
    cin >> n >> m;
    if(m == 0) {
        if(n == 1) {
            cout << -1 << '\n';
            return;
        }
        if(n % 2 == 0) {
            cout << n << '\n';
            return;
        }
        cout << 2 * 2 + n - 1 << '\n';
        return;
    }
    if(m == 1) {
        if(n % 2 == 1) {
            cout << n << '\n';
            return;
        }
        if(n % 2 == 0) {
            cout << 2 * 2 + n - 1 << '\n';
            return;
        }
    }
    int cnt = __builtin_popcount(m);
    if(cnt >= n) {
        cout << m << '\n';
        return;
    }
    int diff = n - cnt;
    if(diff % 2 == 0) {
        cout << m + diff << '\n';
        return;
    }
    else {
        cout << m + diff + 1 << '\n';
        return;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}