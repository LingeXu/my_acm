#include <bits/stdc++.h>
using namespace std;
int t, n, k;
void solve() {
    cin >> n >> k;
    vector<int> a(n);
    set<int> s;
    int mx = -1, idx = -1;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(i <= n - k) {
            s.insert(a[i]);
            if(a[i] > mx) {
                mx = a[i];
                idx = i;
            }
        }
    }
    int cur = 0;
    while(s.find(cur) != s.end()) {
        cur++;
    }
    int pos = -1;
    for(int i = n - k + 1; i < n; i++) {
        if(a[i] == cur) {
            pos = i;
            break;
        }
    }
    if(pos == -1 || cur == mx + 1) {
        cout << -1 << '\n';
        return;
    }
    cout << idx + 1 << ' ' << pos + 1 << '\n';
}
int main() {
    cin >> t;
    while(t--)  solve();
    return 0;
}