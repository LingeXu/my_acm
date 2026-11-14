#include <bits/stdc++.h>
using namespace std;
int t, n;
vector<int> a, b;
vector<int> final(200005);
void solve() {
    cin >> n;
    a.resize(n + 1);
    b.resize(n + 1);
    for(int i = 1; i <= n; i++) 
        cin >> a[i];
    for(int i = 1; i <= n; i++) 
        cin >> b[i];
    for(int i = 1; i <= n; i++) {
        final[a[i]] = i;
        final[b[i]] = i;
    }
    for(int i = n; i >= 1; i--) {
        if(a[i] == b[i]) {
            cout << i << '\n';
            return;
        }
        if(final[a[i]] > i + 1 || final[b[i]] > i + 1) {
            cout << i << '\n';
            return;
        }
        if(i + 1 <= n && (a[i] == a[i + 1] || b[i] == b[i + 1])) {
            cout << i << '\n';
            return;
        }
    }
    cout << 0 << '\n';
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}