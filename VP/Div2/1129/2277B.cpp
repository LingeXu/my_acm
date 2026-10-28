#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
void solve() {
    cin >> n;
    int mn = LLONG_MAX;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        mn = min(mn, x);
    }
    if(n - 1 >= mn) {
        cout << n << '\n';
        return;
    }
    cout << 0 << '\n';
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}