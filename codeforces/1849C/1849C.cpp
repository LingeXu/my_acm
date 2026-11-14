#include <bits/stdc++.h>
using namespace std;
int t, n, m;
string s;
void solve() {
    cin >> n >> m >> s;
    vector<int> nxt_1(n + 1, n);
    for(int i = n - 1; i >= 0; i--) {
        if(s[i] == '1')
            nxt_1[i] = i;
        else    nxt_1[i] = nxt_1[i + 1];
    }
    vector<int> pre_0(n, -1);
    for(int i = 0; i < n; i++) {
        if(s[i] == '0') {
            pre_0[i] = i;
            continue;
        }
        if(i > 0)   pre_0[i] = pre_0[i - 1];
    }

    /*cout << "Test:\n";
    for(int i = 0; i < n; i++)
        cout << "nxt = " << nxt_1[i] << '\n';
    for(int i = 0; i < n; i++)
        cout << "pre = " << pre_0[i] << '\n';*/

    int ans = 0;
    bool no_change = false;
    map< pair<int, int>, int > mp;
    while(m--) {
        int l, r;
        cin >> l >> r;
        int L = nxt_1[l - 1], R = pre_0[r - 1];
        if(L > R) {
            if(!no_change) {
                no_change = true;
                ans++;
            }
            continue;
        }

        //cout << "L = " << L << ", R = " << R << '\n';

        if(!mp.count(make_pair(L, R))) {
            ans++;
            mp[make_pair(L, R)] = 1;
        }
    }
    cout << ans << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}