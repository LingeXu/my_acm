#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<array<int, 3>> ops;
    for (int k = 1; k <= n; k++) {
        if (k >= 2)         ops.push_back({k, 1, k});      
        if (k + 1 <= n - 1) ops.push_back({k, k + 1, n});  
    }
    cout << ops.size() << '\n';
    for (auto &o : ops)
        cout << o[0] << ' ' << o[1] << ' ' << o[2] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}