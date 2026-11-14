#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
void solve() {
    cin >> n;
    vector<int> d(n + 1);
    for(int i = 1; i <= n; i++)
        cin >> d[i];
    vector< pair<int, int> > h(n + 1), span(n + 1);
    for(int i = 1; i <= n; i++)
        cin >> h[i].first >> h[i].second;
    int cur_mn = 0, cur_mx = 0;
    span[0] = {0, 0};
    for(int i = 1; i <= n; i++) {
        if(d[i] != -1) {
            cur_mn += d[i];
            cur_mx += d[i];
            if(cur_mn > h[i].second || cur_mx < h[i].first) {
                cout << -1 << '\n';
                return;
            }
            cur_mx = min(cur_mx, h[i].second);
            cur_mn = max(cur_mn, h[i].first);
            span[i] = {cur_mn, cur_mx};
        }
        else {
            cur_mx++;
            if(cur_mn > h[i].second || cur_mx < h[i].first) {
                cout << -1 << '\n';
                return;
            }
            if(cur_mx == h[i].first)    d[i] = 1;
            if(cur_mn == h[i].second)   d[i] = 0;
            cur_mx = min(cur_mx, h[i].second);
            cur_mn = max(cur_mn, h[i].first);
            span[i] = {cur_mn, cur_mx};
        }
    }
    int now = span[n].first;
    for(int i = n; i >= 1; i--) {
        if(d[i] != -1) {
            now -= d[i];
            continue;
        }
        else {
            if(now - 1 >= span[i].first && now - 1 <= span[i].second) {
                now--;
                d[i] = 1;
            }
            else    d[i] = 0;
        }
    }
    for(int i = 1; i <= n; i++)
        cout << d[i] << ' ';
    cout << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}