#include <bits/stdc++.h>
using namespace std;
#define int long long
int tt, n, k, q;
struct light {
    int p, d;
};
void solve() {
    cin >> n >> k;
    vector<light> l(n);
    for(int i = 0; i < n; i++)
        cin >> l[i].p;
    for(int i = 0; i < n; i++)
        cin >> l[i].d;
    cin >> q;
    int a;
    while(q--) {
        cin >> a;
        set<tuple<int, int, int>> s;
        int pos = a, t = 0, direction = 1;
        for(int i = 0; i < n; i++)
            if(l[i].p == pos && l[i].d == 0)
                direction = -1;
        bool found = true, ok = true;
        while(found) {
            if(direction == 1) {
                found = false;
                for(int i = 0; i < n; i++) {
                    if(l[i].p <= pos)  continue;
                    if((l[i].p - l[i].d + t - pos) % k == 0) {
                        found = true;
                        t = (t + (l[i].p - pos) % k) % k;
                        pos = l[i].p;
                        direction = 0;
                        //cout << "t = " << t << ", pos = " << pos << ", direction = " << direction << '\n';
                        if(s.find({t, pos, direction}) != s.end()) {
                            ok = false;
                            cout << "NO\n";
                            break;
                        }
                        s.emplace(t, pos, direction);
                        break;
                    }
                }    
                if(!ok) break;
            }  
            else {
                found = false;
                for(int i = n - 1; i >= 0; i--) {
                    if(l[i].p >= pos)  continue;
                    if((l[i].p + l[i].d - t - pos) % k == 0) {
                        found = true;
                        t = (t + (pos - l[i].p) % k) % k;
                        pos = l[i].p;
                        direction = 1;
                        //cout << "t = " << t << ", pos = " << pos << ", direction = " << direction << '\n';
                        if(s.find({t, pos, direction}) != s.end()) {
                            ok = false;
                            cout << "NO\n";
                            break;
                        }
                        s.emplace(t, pos, direction);
                        break;
                    }
                }
                if(!ok) break;
            }
        }
        if(ok)  cout << "YES\n";
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> tt;
    while(tt--)  solve();
    return 0;
}