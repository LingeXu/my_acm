#include <bits/stdc++.h>
using namespace std;
int n;
string s;
void solve() {
    cin >> n >> s;
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == '0')
            cnt++;
    }
    int ans = 0;
    for(int i = 0; i < cnt; i++)
        if(s[i] == '1')
            ans++;
    cout << ans << '\n';
}
int main() {
    int t;
    cin >> t;
    while(t--)  solve();
    return 0;
}