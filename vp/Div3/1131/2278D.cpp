#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a.begin() + 1, a.end());
    int c = 0, op = 0;
    for(int i = 1; i < n; i++) {
        if(i <= n - i) {
            c += i * (a[i + 1] - a[i]);
            op += a[i + 1] - a[i];
        }
        else {
            c += (n - i) * (a[i + 1] - a[i]);
            op += a[i + 1] - a[i];
        }
    }
    cout << c << ' ' << op << '\n';

}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}