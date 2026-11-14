#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
struct point {
    int x, y;
};
void solve() {
    cin >> n;
    vector<point> a(n);
    vector<int> x_pos, rk(n + 1);
    for(int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
        x_pos.push_back(a[i].x);
    }
    sort(x_pos.begin(), x_pos.end());
    x_pos.erase(unique(x_pos.begin(), x_pos.end()), x_pos.end());
    for(int i = 0; i < (int)x_pos.size(); i++)
        rk[x_pos[i]] = i;
    sort(a.begin(), a.end(), [](auto &p1, auto &p2){return p1.y < p2.y;});
    vector<int> pre_mx(n + 2, 0), pre_mn(n + 2, n + 1), suf_mx(n + 2, 0), suf_mn(n + 2, n + 1);
    for(int i = 0; i < n; i++) {
        pre_mx[i + 1] = max(pre_mx[i], a[i].x);
        pre_mn[i + 1] = min(pre_mn[i], a[i].x);
    }
    for(int i = n - 1; i >= 0; i--) {
        suf_mx[i + 1] = max(suf_mx[i + 2], a[i].x);
        suf_mn[i + 1] = min(suf_mn[i + 2], a[i].x);
    }
    int ans = 0;
    for(int i = 0; i < n - 1; i++) {
        if(a[i].y == a[i + 1].y)    continue;
        int l = max(pre_mn[i + 1], suf_mn[i + 2]), r = min(pre_mx[i + 1], suf_mx[i + 2]);
        if(l >= r)  continue;
        ans += rk[r] - rk[l];
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