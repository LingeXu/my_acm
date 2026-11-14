#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, x, y;
int gcd(int x, int y) {
    if(y == 0)  return x;
    return gcd(y, x % y);
}
void solve() {
    cin >> n >> x >> y;
    bool ok = true;
    int g = gcd(x, y);
    for(int i = 1; i <= n; i++) {
        int num;
        cin >> num;
        int diff = abs(num - i);
        if(diff % g != 0)   ok = false;
    }
    if(ok)  cout << "YES\n";
    else    cout << "NO\n";
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}