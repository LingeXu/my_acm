#include <bits/stdc++.h>
using namespace std;
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n);
    vector<int> cnt(n + 1, 0);
    vector<int> banned, ok(n, 1);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    for(int i = 0; i < n; i++) {
        if(cnt[a[i]] > 1) {
            banned.push_back(i);
            ok[i] = 0;
        }
    }
    int ans = 0, l = -1, r = -1;
    for(int i = 0; i < n; i++) {
        if(ok[i] == 0)  continue;
        int pos = lower_bound(banned.begin(), banned.end(), i) - banned.begin();
        int cur;
        if(pos == (int)banned.size()) {
            cur = n - i;
        }
        else {
            cur = banned[pos] - i;
        }
        if(cur > ans) {
            ans = cur;
            l = i + 1;
            r = ((pos == (int)banned.size()) ? n : banned[pos]);
        }
    }
    if(l == -1 && r == -1) {
        cout << 0 << '\n';
        return;
    }
    cout << l << ' ' << r << '\n';
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}