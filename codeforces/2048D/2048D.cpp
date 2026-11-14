#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, m;
void solve() {
    cin >> n >> m;
    vector<int> a(n), b(m), c;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    int rt = a[0];
    for(int i = 0; i < m; i++)
        cin >> b[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int cnt_low = 0;
    for(int i = 0; i < m; i++) {
        if(b[i] <= rt)  cnt_low++;
        else    c.push_back(b[i]);
    }
    int sz = c.size();
    vector<int> d(sz);
    int i = 0, j = 0;
    while(i < n && j < sz) {
        if(a[i] < c[j])
            i++;
        else {
            d[j] = n - i;
            j++;
        }
    }    
    for(int i = 1; i <= m; i++) {
        int ans = cnt_low / i;
        int rem = m % i;
        //cout << "ans = " << ans << ", rem = " << rem << '\n';
        for(int j = rem; j < sz; j += i)
            ans += (d[j] + 1);
        cout << ans << ' ';
    }
    cout << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}