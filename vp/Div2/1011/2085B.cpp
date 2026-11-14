#include <bits/stdc++.h>
using namespace std;
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n + 1);
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt += (a[i] == 0);
    }
    if(cnt == 0) {
        cout << 1 << '\n';
        cout << 1 << ' ' << n << '\n';
        return;
    }
    if(a[1] == 0 && a[n] == 0) {
        cout << 3 << '\n';
        cout << 1 << ' ' << n - 2 << '\n';
        cout << 2 << ' ' << 3 << '\n';
        cout << 1 << ' ' << 2 << '\n';
        return;
    }
    if((a[1] == 0 && a[n] != 0) || (a[1] != 0 && a[n] != 0)) {
        cout << 2 << '\n';
        cout << 1 << ' ' << n - 1 << '\n';
        cout << 1 << ' ' << 2 << '\n';
        return;
    }
    if(a[1] != 0 && a[n] == 0) {
        cout << 2 << '\n';
        cout << 2 << ' ' << n << '\n';
        cout << 1 << ' ' << 2 << '\n';
        return;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}