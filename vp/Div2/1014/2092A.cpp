#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i< n; i++)
        cin >> a[i];
    sort(a.begin(), a.end());
    cout << a.back() - a[0] << '\n';
}
signed main() {
    cin >> t;
    while(t--)  solve();
    return 0;
}