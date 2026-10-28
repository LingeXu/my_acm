#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n + 1), d;
    for(int i = 1; i <= n; i++) 
        cin >> a[i];
    for(int i = 2; i <= n; i++)
        d.push_back(a[i] - a[i - 1]);
    int m = d.size();
    for(int i = 0; i < m;) {
        int j = i;
        while(j < m && (d[j] & 1) == (d[i] & 1))    j++;
        sort(d.begin() + i, d.begin() + j);
        i = j;
    }
    cout << a[1];
    int pre = a[1];
    for(int diff : d) {
        cout << ' ' << pre + diff;
        pre += diff;
    }
    cout << '\n';
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}