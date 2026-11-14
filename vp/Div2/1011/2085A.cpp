#include <bits/stdc++.h>
using namespace std;
int t, n, k;
string s;
void solve() {
    cin >> n >> k >> s;
    string s1 = s;
    reverse(s.begin(), s.end());
    string s2 = s;
    int num = -1;
    bool ok = true;
    for(int i = 0; i < n; i++) {
        if(num == -1)
            num = s1[i] - 'a';
        if(num != -1 && num != s1[i] - 'a') {
            ok = false;
            break;
        }
    }
    if(ok) {
        cout << "NO\n";
        return;
    }
    if(s1 >= s2 && k == 0) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}