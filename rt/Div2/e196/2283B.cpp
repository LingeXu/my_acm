#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.end());
    int rem = 0;
    for(int i = 0; i < n; i++) {
        int cur = 1;
        for(int j = i + 1; j < n; j++) {
            if(a[j] % a[i] == 0)    cur++;
        }
        rem = max(rem, cur);
    }
    cout << n - rem << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}