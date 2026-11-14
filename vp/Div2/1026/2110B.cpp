#include <bits/stdc++.h>
using namespace std;
int t;
string s;
void solve() {
    cin >> s;
    int cur = 0;
    for(int i = 0; i < (int)s.size(); i++) {
        if(s[i] == '(')
            cur--;
        else    cur++;
        if(cur == 0 && i < (int)s.size() - 1) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}