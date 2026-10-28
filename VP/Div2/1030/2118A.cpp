#include <bits/stdc++.h>
using namespace std;
int t, n, m;
void solve() {
    cin >> n >> m;
    for(int i = 1; i <= m; i++)
        cout << 1;
    for(int i = m + 1; i <= n; i++)
        cout << 0;
    cout << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}