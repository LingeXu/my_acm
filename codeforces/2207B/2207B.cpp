#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, m, l;
void solve() {
    cin >> n >> m >> l;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    if(m == 1) {
        cout << l - a[n - 1] << '\n';
        return;
    }
    vector<int> record(m);
    int now = 0;
    for(int i = 1; i <= l; i++) {
        record[min(m, n + 1 - now) - 1]++;
        sort(record.begin(), record.end(), [](auto &x, auto &y){return x > y;});
        if(now < n && i == a[now]) {
            record[0] = 0;
            sort(record.begin(), record.end(), [](auto &x, auto &y){return x > y;});
            now++;
        }
    }
    cout << record[0] << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}