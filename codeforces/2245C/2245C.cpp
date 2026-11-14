#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, k;
void solve() {
    cin >> n >> k;
    k ^= n;
    if(n == 1) {
        if(k == 0) {
            cout << "YES\n";
            cout << 0 << '\n';
        }
        else    cout << "NO\n";
        return;
    }
    if(k == 0) {
        cout << "YES\n";
        for(int i = 1; i < n; i++)
            cout << i << ' ';
        cout << 0 << '\n';
        return;
    }
    if(__builtin_clzll(k) < __builtin_clzll(n - 1)) {
        cout << "NO\n";
        return;
    }
    else {
        cout << "YES\n";
        vector<int> ans, used(n, 0);
        for(int i = 0; i < 64; i++) {
            if(((k >> i) & 1LL) == 1LL) {
                //cout << "i = " << i << '\n';
                ans.push_back(1LL << i);
                used[1LL << i] = 1;
            }
        }
        for(int i = 1; i < n; i++)
            if(!used[i])
                cout << i << ' ';
        cout << 0 << ' ';
        for(int i : ans)
            cout << i << ' ';
        cout << '\n';
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}