#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n);
    bool ok = false, ok1 = false;
    int sum = 0;
    for(int i = 0; i < n ;i++) {
        cin >> a[i];
        sum += a[i];
        if(a[i] != 1)   ok = true;
        if(a[i] != 1 && (i != 0 && i != n - 1))
            ok1 = true;
    }
    if(!ok) {
        cout << -1 << '\n';
        return;
    }
    if(!ok1) {
        cout << sum - (n - 1) << '\n';
        return;
    }
    if(ok1) {
        cout << sum - 1 << '\n';
        return;
    }
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}