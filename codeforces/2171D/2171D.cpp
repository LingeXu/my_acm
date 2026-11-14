#include <bits/stdc++.h>
using namespace std;
int t, n;
void solve() {
    cin >> n;
    int mn = n + 1;
    bool ok = true;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        mn = min(mn, x);
        if(mn == n - i + 1 && i != n)
            ok = false;
    }
    if(ok)  cout << "Yes\n";
    else    cout << "No\n";
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}