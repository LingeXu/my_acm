#include <bits/stdc++.h>
using namespace std;
int t, n;
string s1, s2;
void solve() {
    cin >> n;
    cin >> s1 >> s2;
    int cnt1 = 0, cnt2 = 0;
    for(char c : s1)
        if(c == 'f')
            cnt1++;
    for(char c : s2)
        if(c == 'f')
            cnt2++;
    if((cnt1 + cnt2 ) % 2 == 0) {
        cout << 0 << '\n';
        return;
    }
    cout << 1 << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}