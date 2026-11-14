#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
void solve() {
    cin >> n;
    int clz = __builtin_clzll(n);
    int sz = 64 - clz + 1;
    int aim = (1LL << sz) - 1;
    vector<int> d(n + 1, 0);
    for(int i = n; i >= 1; i--) {
        int sz1 = 64 - __builtin_clzll(i);
        if(((aim >> sz1) & 1) == 1) {
            d[i] = 1;
            aim = aim ^ (i << 1);
        }
        else {
            d[i] = 0;
            aim = aim ^ i;
        }
    }
    for(int i = 1; i <= n; i++)
        cout << d[i] << ' ';
    cout << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}