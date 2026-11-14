#include <bits/stdc++.h>
using namespace std;
#define N 200005
int t, n, q;
int msb(int x) {
    return 31 - __builtin_clz(x);
}
void solve() {
    cin >> n >> q;
    vector<int> a(n), suff_xor(n + 1);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    for(int i = n - 1; i >= 0; i--)
        suff_xor[i] = suff_xor[i + 1] ^ a[i];
    vector< vector<int> > nxt(32, vector<int>(n + 1, -1));
    for(int b = 0; b<= 31; b++) {
        for(int i = 0; i <= n; i++) {
            if(i == n) {
                nxt[b][i] = nxt[b][i - 1];
                continue;
            }
            if(msb(a[i]) >= b) {
                nxt[b][i] = i;
                continue;
            }
            if(i - 1 >= 0)  nxt[b][i] = nxt[b][i - 1];
        }
    }

    /*for(int b = 3; b >= 0; b--) 
        for(int i = 0; i <= 4; i++)
            cout << "b = " << b << ", i = " << i << ", nxt = " << nxt[b][i] << '\n';*/

    while(q--) {
        int x;
        cin >> x;
        int cur_val = x, ans = 0, cur_pos = n, nxt_pos = nxt[msb(cur_val)][n - 1] + 1;
        while(cur_pos > 0) {
            ans += cur_pos - nxt_pos;
            cur_pos = nxt_pos;
            cur_val = x ^ suff_xor[cur_pos];
            if(cur_pos == 0 || cur_val < a[cur_pos - 1])    break;
            cur_val ^= a[cur_pos - 1];
            ans++;
            cur_pos--;
            if(cur_pos == 0 || cur_val == 0)    break;
            nxt_pos = nxt[msb(cur_val)][cur_pos - 1] + 1;
        }
        cout << ans << ' ';
    }
    cout << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}