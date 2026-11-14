#include <bits/stdc++.h>
using namespace std;
int t, n, k;
void solve() {
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    if(n == k) {
        for(int i = 1; i < n; i += 2) {
            if(a[i] == (i + 1) / 2)
                continue;
            cout << (i + 1) / 2 << '\n';
            return;
        }
        cout << k / 2 + 1 << '\n';
        return;
    }
    if(n - k >= 1) {
        for(int i = 1; i <= 1 + n - k; i++) {
            if(a[i] != 1) {
                cout << 1 << '\n';
                return;
            }
        }
        cout << 2 << '\n';
        return;
    }
    /*int ans = 1;
    for(int i = 1; i < n; i += 2) {
        if(i == n - 1) {
            //ans++;
            break;
        }
        if(a[i] == (i + 1) / 2 && a[i + 1] == (i + 1) / 2)
            ans++;
        else    break;
    }
    cout << ans << '\n';*/
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}