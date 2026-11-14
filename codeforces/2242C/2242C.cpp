#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, k;
void solve() {
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) 
        cin >> a[i];
    vector<int> cnt;
    for(int i = 0; i < n;) {
        int j = i;
        while(j < n && a[i] == a[j])    j++;
        cnt.push_back(j - i);
        i = j;
    }
    sort(cnt.begin(), cnt.end());

    /*for(int i : cnt)
        cout << i << ' ';
    cout << '\n';*/

    int sz = (int)cnt.size();
    vector<int> suff_sum(sz + 1), rem(sz + 1);
    for(int i = sz - 1; i >= 0; i--) {
        suff_sum[i] = suff_sum[i + 1] + cnt[i];
        if(i == 0)  rem[i] = suff_sum[i];
        else    rem[i] = suff_sum[i] - cnt[i - 1] * (sz - i);
    }
    rem[sz] = 0;

    /*for(int i = 0; i < sz; i++)
        cout << suff_sum[i] << ' ' << rem[i] << '\n';
    cout << '\n';*/

    int ans = 0;
    for(int i = 0; i < sz; i++) {
        if(i != 0 && cnt[i - 1] == cnt[i])  continue;
        int diff = k - rem[i];

        //cout << "i = " << i << ", diff = " << diff << '\n';

        if(diff >= 0 && diff % (sz - i) == 0)   ans++;
        if(diff < 0 && k > rem[i + 1] && (-diff) % (sz - i) == 0)    ans++;
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