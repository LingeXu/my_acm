#include <bits/stdc++.h>
using namespace std;
int t, n, q;
void solve() {
    cin >> n >> q;
    vector<int> d(q);
    for(int i = 0; i < q; i++)
        cin >> d[i];
    for(int i = 1; i < n; i++)
        cout << i << ' ' << i + 1 << '\n';
    int neighbor = n - 1;
    for(int i = 0; i < q; i++) {
        if(d[i] == neighbor) {
            cout << -1 << ' ' << -1 << ' ' << -1 << '\n';
            continue;
        }
        cout << n << ' ' << neighbor << ' ' << d[i] << '\n';
        neighbor = d[i];
        continue;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}