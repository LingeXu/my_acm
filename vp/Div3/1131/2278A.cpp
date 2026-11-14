#include <bits/stdc++.h>
using namespace std;
int t, n, m;
void solve() {
    cin >> n >> m;
    string s1, s2;
    cin >> s1 >> s2;
    vector<int> cnt(26);
    for(char c : s1)
        cnt[c - 'a']++;
    for(char c : s2)
        cnt[c - 'a']--;
    if(cnt['s' - 'a'] != 1 || cnt['i' - 'a'] != 1 || cnt['x' - 'a'] != 1) {
        cout << "NO\n";
        return;
    }
    for(int i = 0; i < 26; i++) {
        if(i == 's' - 'a' || i == 'i' - 'a' || i == 'x' - 'a')  continue;
        if(cnt[i] != 0) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}