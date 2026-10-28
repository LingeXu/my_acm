#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, x;
vector<int> a;
bool check(int y) {
    int need = 0;
    vector<int> b(a.begin(), a.end());
    for(int i = 0; i < n; i++) {
        int diff;
        if(i == 0) {
            diff = b[1] - b[0];
            if(diff > y) {
                need++;
                b[0] += y;
            }
            //cout << "y = " << y << ", need = " << need << '\n';
        }
        else if(i == n - 1) {
            diff = b[n - 1] - b[n - 2];
            if(diff > y)    need++;
            //cout << "y = " << y << ", need = " << need << '\n';
        }
        else {
            diff = min(b[i + 1] - b[i], b[i] - b[i - 1]);
            if(diff > y) {
                need++;
                b[i] += y;
            }
            //cout << "y = " << y << ", need = " << need << '\n';
        }
    }

    if(need > x)    return false;
    return true;
}
void solve() {
    cin >> n >> x;
    a.resize(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    int l = 1, r = a[n - 1] - a[0];
    int ans = -1;
    while(l <= r) {
        int mid = (l + r) / 2;
        if(check(mid)) {
            ans = mid;
            r = mid - 1;
            continue;
        }
        else    l = mid + 1;
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