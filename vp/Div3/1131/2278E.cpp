#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n), odd, even;
    int sum = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
        if(i % 2 == 0)  even.push_back(a[i]);
        else    odd.push_back(a[i]);
    }
    sort(even.begin(), even.end());
    sort(odd.begin(), odd.end());
    int i = 0, j = 0;
    while(i < (int)even.size() && j < (int)odd.size()) {
        int cur = even[i] + odd[i];
        if(cur >= 0)    break;
        sum -= 2 * cur;
        i++;
        j++;
    }
    cout << sum << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}