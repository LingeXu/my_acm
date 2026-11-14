#include <bits/stdc++.h>
using namespace std;
int t, n;
int c[3] = {0, 1, 2};
string s;
vector<int> cnt(3);
unordered_map<int, char> mp;
void solve() {
    cin >> n >> s;
    cnt.assign(3, 0);
    for(char c : s) {
        if(c == 'L')    cnt[0]++;
        else if(c == 'I')   cnt[1]++;
        else    cnt[2]++;
    }
    sort(c, c + 3, [](int x, int y){return cnt[x] < cnt[y];});
    int big = c[2], medium = c[1], small = c[0];
    char aim[2] = {mp[big], mp[medium]};
    bool ok[2] = {false, false};
    int rem[2] = {cnt[big] - cnt[small], cnt[medium] - cnt[small]};
    if(rem[0] == n && rem[1] == 0) {
        cout << -1 << '\n';
        return;
    }

    /*cout << "Test:\n";
    cout << "aim[0] = " << aim[0] << ", aim[1] = " << aim[1] << '\n';
    cout << "rem[0] = " << rem[0] << ", rem[1] = " << rem[1] << '\n';
    cout << '\n'; */

    cout << 2 * (rem[0] + rem[1]) << '\n';
    for(int i = n - 1; i >= 0; i--) {
        for(int j = 0; j < 2; j++) {
            if(!ok[j] && s[i] == aim[j]) {
                bool leftok = (i > 0 && s[i] != s[i - 1]);
                bool rightok = (i < n - 1 && s[i] != s[i + 1]);
                if(leftok) {
                    ok[j] = true;
                    for(int k = i; k < i + 2 * rem[j]; k++)
                        cout << k << '\n';
                    continue;
                }
                if(rightok) {
                    ok[j] = true;
                    for(int k = 1; k <= 2 * rem[j]; k++)
                        cout << i + 1 << '\n';
                    continue;
                }
            }
        }
    }
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    mp.insert(make_pair(0, 'L'));
    mp.insert(make_pair(1, 'I'));
    mp.insert(make_pair(2, 'T'));
    cin >> t;
    while(t--)  solve();
    return 0;
}