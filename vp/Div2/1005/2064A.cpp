#include <bits/stdc++.h>
using namespace std;
int t, n;
string s;
void solve() {
    cin >> n >> s;
    int idx = -1;
    for(int i = 0; i < n; i++) {
        if(s[i] == '1') {
            idx = i;
            break;
        }
    }
    if(idx == -1) {
        cout << 0 << '\n';
        return;
    }
    int pre = 1, ans = 1;
    for(int i = idx + 1; i < n; i++) {
        if(s[i] - '0' == pre)   continue;
        else {
            ans++;
            pre = s[i] - '0';
        }
    }
    cout << ans << '\n';
}
int main() {
    cin >> t;
    while(t--)  solve();
    return 0;
}