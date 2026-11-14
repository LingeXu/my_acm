#include <bits/stdc++.h>
using namespace std;
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n);
    unordered_map<int, int> mp;
    bool ok = false;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(++mp[a[i]] == 2) {
            ok = true;
        }
    }
    if(ok) {
        cout << "YES\n";
        return;
    }
    cout << "NO\n";
    return;
}
int main() {
    int t;
    cin >> t;
    while(t--)  solve();
    return 0;
}