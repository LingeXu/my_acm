#include <bits/stdc++.h>
using namespace std;
int t, n, q;
string s;
void solve() {
    cin >> n >> q >> s;
    vector<int> c, cnt_0(n + 1), cnt_1(n + 1), con_0(n + 1), con_1(n + 1);
    for(int i = 0; i < n; i++) 
        c.push_back((s[i] - '0') ^ (i % 2));
    for(int i = 1; i <= n; i++) {
        cnt_0[i] = cnt_0[i - 1] + (c[i - 1] == 0);
        cnt_1[i] = cnt_1[i - 1] + (c[i - 1] == 1);
        if(i == n) {
            con_0[i] = con_0[i - 1];
            con_1[i] = con_1[i - 1];
            continue;
        }
        con_0[i] = con_0[i - 1] + (c[i - 1] == 0 && c[i] == 0);
        con_1[i] = con_1[i - 1] + (c[i - 1] == 1 && c[i] == 1);
    }
    while(q--) {
        int l, r, k;
        cin >> l >> r >> k;
        if(l == r) {
            cout << "YES\n";
            continue;
        }
        int need = min(cnt_0[r] - cnt_0[l - 1] - (con_0[r - 1] - con_0[l - 1]), cnt_1[r] - cnt_1[l - 1] - (con_1[r - 1] - con_1[l - 1]));
        if(need <= k) {
            cout << "YES\n";
            continue;
        }
        cout << "NO\n";
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}