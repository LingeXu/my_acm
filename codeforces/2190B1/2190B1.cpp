#include <bits/stdc++.h>
using namespace std;
int t, n;
string s;
void solve() {
    cin >> n >> s;
    vector<int> nxt(n + 1, -1);
    for(int i = n - 1; i >= 0; i--) {
        if(s[i] == '(')
            nxt[i] = i;
        else    nxt[i] = nxt[i + 1];
    }
    vector<int> cnt(n + 1, 0);
    for(int i = n - 1; i >= 0; i--) 
        cnt[i] = cnt[i + 1] + (s[i] == '(');
    int ans = 0;
    for(int i = 0; i < n - 1; i++) {
        if(s[i] == '(')
            continue;
        if(nxt[i] == -1)    continue;
        if(cnt[nxt[i] + 1] >= nxt[i] - i)
            ans = max(ans, n - 2 * (nxt[i] - i));
    }
    cout << (ans == 0 ? -1 : ans) << '\n';
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}