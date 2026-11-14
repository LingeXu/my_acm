#include <bits/stdc++.h>
using namespace std;
int t, n, k, q;
void solve() {
    cin >> n >> k >> q;
    vector<int> type(n + 1);
    for(int i = 1; i <= q; i++) {
        int c, l, r;
        cin >> c >> l >> r;
        if(c == 1) {
            for(int j = l; j <= r; j++) {
                if(type[j] == 2 || type[j] == 3)
                    type[j] = 3;
                else    type[j] = 1;
            }
        }
        else {
            for(int j = l; j <= r; j++) {
                if(type[j] == 1 || type[j] == 3)
                    type[j] = 3;
                else    type[j] = 2;
            }
        }
    }
    int pre = -1;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        if(type[i] == 0) {
            a[i] = 1e9;
        }
        else if(type[i] == 1) {
            a[i] = k;
        }
        else if(type[i] == 2) {
            a[i] = (pre + 1) % k;
            pre = a[i];
        }
        else {
            a[i] = 1e9;
        }
    }
    for(int i = 1; i <= n; i++)
        cout << a[i] << ' ';
    cout << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}