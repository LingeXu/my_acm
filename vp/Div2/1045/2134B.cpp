#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, k;
void solve() {
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) 
        cin >> a[i];
    for(int i = 0; i < n; i++)
        cout << a[i] + a[i] % (k + 1) * k << ' ';
    cout << '\n';
    return;
}
signed main() {
    cin >> t;
    while(t--)  solve();
    return 0;
}