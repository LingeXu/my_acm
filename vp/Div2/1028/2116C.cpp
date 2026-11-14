#include <bits/stdc++.h>
using namespace std; 
int t, n;
vector<int> a, d;
struct inf {
    int val, cnt, id;
};
int bfs() {
    queue< inf > q;
    for(int i = 0; i < n; i++) {
        q.push({a[i], 0, i});
        d[a[i]] = 0;
    }
    while(!q.empty()) {
        auto x = q.front();
        q.pop();
        for(int i = x.id + 1; i < n; i++) {
            int cur = gcd(x.val, a[i]);
            if(cur == 1)
                return x.cnt + 1;
            if(d[cur] == 0x3f3f3f3f) {
                q.push({cur, x.cnt + 1, i});
                d[cur] = x.cnt + 1;
            }
        }
    }
    return -1;
}
void solve() {
    cin >> n;
    a.resize(n);
    d.assign(5005, 0x3f3f3f3f);
    int g = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        g = gcd(g, a[i]);
    }
    int cnt = 0;
    for(int i = 0; i < n; i++) {
    
        if(a[i] == g)   cnt++;
    }

    if(cnt > 0) {
        cout << n - cnt << '\n';
        return;
    }
    for(int i = 0; i < n; i++) {
        a[i] /= g;
    }
    cout << bfs() + n - 1 << '\n';
    return;
}
signed main( ){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}