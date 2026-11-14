#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, s;
void solve() {
    cin >> n >> s;
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        int dx, dy, x, y;
        cin >> dx >> dy >> x >> y;
        if(x == y && dx == dy)  continue;
        if(x + y == s && dx + dy == 0)  continue;
        cnt++;
    }
    cout << n - cnt << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> t;
    while(t--)  solve();
    return 0;
}