#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, k;
void solve() {
    cin >> n >> k;
    unordered_map<int, int> mp;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        mp[x]++;
    }
    int cur = 0, now = 0;
    while(mp.count(cur) && now + mp[cur] >= (cur + 1) * k) {
        now += mp[cur];
        cur++;
        
    }
    cout << cur << '\n';
}
signed main() {
    cin >> t;
    while(t--)  solve();
    return 0;
}