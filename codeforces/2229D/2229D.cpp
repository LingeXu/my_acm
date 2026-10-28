#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
vector<int> a, b;
bool check(int x) {
    int zero = 0, one = 0, pre = -1;
    for(int i = 0; i < n; i++) {
        int cur = 0;
        if(a[i] >= x)   cur++;
        if(b[i] >= x)   cur++;
        if(cur == 1)    continue;
        if(cur == 0 && pre != 0)    zero++;
        if(cur == 2)    one++;
        pre = cur;
    }
    if(one > zero)  return true;
    return false;
}
void solve() {
    cin >> n;
    a.resize(n);
    b.resize(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    for(int i = 0; i < n; i++)
        cin >> b[i];   
    int l = 1, r = 2 * n, ans = -1;
    while(l <= r) {
        int mid = (l + r) / 2;
        if(check(mid)) {
            ans = mid;
            l = mid + 1;
        }
        else    r = mid - 1;
    }
    cout << ans << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}