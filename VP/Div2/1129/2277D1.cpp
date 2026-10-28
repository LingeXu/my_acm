#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
int t, l, r;
int f(int x) {
    if(x == 0)  return 0;
    if(x == 1)  return 1;
    if(x == 2)  return 3;
    if(x == 3)  return 2;
    int k = 63 - __builtin_clzll(x); 
    return min(k + 1 + f(x - (1LL << k) + 2), k + (1LL << (k + 1)) - x);
}
void solve() {
    cin >> l >> r;
    int ans = 0;
    for(int i = l; i <= r; i++)
        ans = (ans + f(i)) % MOD;
    cout << ans << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}