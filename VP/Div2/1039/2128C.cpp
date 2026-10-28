#include <bits/stdc++.h>
using namespace std;
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    if(n == 1) {
        cout << "YES\n";
        return;
    }
    int mn = a[0];
    for(int i = 1; i < n; i++) {
        if(a[i] > 2 * mn - 1) {
            cout << "NO\n";
            return;
        }
        mn = min(mn, a[i]);
    }
    cout << "YES\n";
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}