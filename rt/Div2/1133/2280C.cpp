#include <bits/stdc++.h>
using namespace std;
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    int mx = -1, idx = -1;
    for(int i = 0; i < n - 1; i++) {
        if(abs(a[i + 1] - a[i]) > mx) {
            mx = abs(a[i + 1] - a[i]);
            idx = i;
        }
    }
    vector<int> pref_mx(n), suff_mx(n);
    pref_mx[0] = -1;
    for(int i = 1; i < n; i++)
        pref_mx[i] = max(pref_mx[i - 1], abs(a[i] - a[i - 1]));
    suff_mx[n - 1] = -1;
    for(int i = n - 2; i >= 0; i--)
        suff_mx[i] = max(suff_mx[i + 1], abs(a[i + 1] - a[i]));
    int ans = mx;
    a[idx] *= 2;
    int ans2 = -1;
    for(int i = 0; i < n - 1; i++) 
        if(abs(a[i + 1] - a[i]) > ans2) 
            ans2 = abs(a[i + 1] - a[i]);
    ans = min(ans, ans2);
    a[idx] /= 2;
    a[idx + 1] *= 2;
    int ans3 = -1;
    for(int i = 0; i < n - 1; i++) 
        if(abs(a[i + 1] - a[i]) > ans3) 
            ans3 = abs(a[i + 1] - a[i]);
    ans = min(ans, ans3);
    a[idx + 1] /= 2;

    //cout << "ans = " << ans << '\n';

    if(idx > 0) {
        int internal = -1;
        for(int i = idx - 1; i > 0; i--) {
            internal = max(internal, 2 * abs(a[i + 1] - a[i]));
            int cur = internal;
            cur = max(max(cur, max(pref_mx[i - 1], suff_mx[idx + 1])), max(abs(2 * a[i] - a[idx + 1]), abs(abs(2 * a[idx] - a[i - 1]))));
            ans = min(ans, cur);
        }
        internal = max(internal, 2 * abs(a[1] - a[0]));
        int cur = internal;
        cur = max(max(cur, suff_mx[idx + 1]), abs(2 * a[0] - a[idx + 1]));
        ans = min(ans, cur);
    }

    //cout << "ans = " << ans << '\n';

    if(idx + 1 < n - 1) {
        int internal = -1;
        for(int i = idx + 2; i < n - 1; i++) {
            internal = max(internal, 2 * abs(a[i] - a[i - 1]));
            int cur = internal;
            cur = max(max(cur, max(pref_mx[idx], suff_mx[i + 1])), max(abs(2 * a[i] - a[idx]), abs(abs(2 * a[idx + 1] - a[i + 1]))));
            ans = min(ans, cur);
        }
        internal = max(internal, 2 * abs(a[n - 1] - a[n - 2]));
        int cur = internal;
        cur = max(max(cur, pref_mx[idx]), abs(2 * a[n - 1] - a[idx]));
        ans = min(ans, cur);
    }

    cout << ans << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}