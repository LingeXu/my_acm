
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, k;
void solve() {
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++)  cin >> a[i];
    sort(a.begin(), a.end());                 
    int c = 1; 
    while(c < n && a[n - 1 - c] == a[n - 1]) ++c;   
    if(k < c || k > n)  {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    vector<int> ans;
    for(int i = n - k; i < n; ++i) ans.push_back(a[i]);  
    for(int i = n - k - 1; i >= 0; --i) ans.push_back(a[i]);
    for(int i : ans)
        cout << i << ' ';
    cout << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}
