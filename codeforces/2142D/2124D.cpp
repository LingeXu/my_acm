#include <bits/stdc++.h>
using namespace std;
int t, n, k;
void solve() {
    cin >> n >> k;
    vector<int> a(n), b(n), c;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(a.begin(), a.end());
    int aim = a[k - 1];
    for(int i = 0; i < n; i++) {
        if(b[i] > aim)
            continue;
        c.push_back(b[i]);
    }
    int m = c.size(), cnt = 0, l = 0, r = m - 1;
    while(true) {
        while(0 <= l && l < m && 0 <= r && r < m && l < r && c[l] == c[r]) {
            l++;
            r--;
        }
        if(l >= r) {
            cout << "YES\n";
            return;
        }
        if(c[l] != aim && c[r] != aim) {
            cout << "NO\n";
            return;
        }
        if(c[l] == aim) {
            l++;
            if(++cnt > m - k + 1) {
                cout << "NO\n";
                return;
            }
            continue;
        }
        else {
            r--;
            if(++cnt > m - k + 1) {
                cout << "NO\n";
                return;
            }
            continue;
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}