#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, m;
void solve() {
    cin >> n >> m;
    int mn = n , mx = (n + 1) * n / 2;
    if(m > mx || m < mn) {
        cout << -1 << '\n';
        return ;
    }
    vector<int> a(n + 1);
    int cur = n, remain = m, l = 1, r = n;
    while(remain > 0 && cur > 0 && l >= 1 && l <= n && r >= 1 && r <= n && l <= r) {
        if(cur * (cur - 1) / 2 + 1 >= remain) {
            a[r] = cur;
            cur--;
            r--;
            remain--;
            continue;
        }
        else {
            a[l] = cur;
            remain -= cur;
            cur--;
            l++;
            continue;
        }
    }
    cout << a[1] << '\n';
    for(int i = 1; i < n; i++)
        cout << a[i] << ' ' << a[i + 1] << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}