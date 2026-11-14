#include <bits/stdc++.h>
using namespace std;
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    int ans = 0;
    for(int i = 0; i < n; ) {
        int j = i + 1;
        while(j < n && a[j] >= a[j - 1]) j++;
        while(j < n && a[j] <= a[j - 1])    j++;
        i = j;
        ans++;
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