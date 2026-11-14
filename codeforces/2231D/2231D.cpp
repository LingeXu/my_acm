#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
string s;
void solve() {
    cin >> n >> s;
    vector<int> a(n), b(n + 1), c(n + 1);
    for(int i = 0; i < n; i++)  cin >> a[i];
    for(int i = 1; i <= n; i++) {
        cin >> c[i];
        if(i == 1)  b[i] = c[i];
        else    b[i] = -LLONG_MAX;
    }
    if(s[0] == '0') {
        a[0] = c[1];
        s[0] = '1';
    }
    if(s[0] == '1' && a[0] != c[1]) {
        cout << "No\n";
        return;
    }
    for(int i = 2; i <= n; i++) {
        if(c[i] < c[i - 1] || (c[i] > c[i - 1] && s[i - 1] == '1' && a[i - 1] <= 0)) {
            cout << "No\n";
            return;
        }
    }
    for(int i = n; i >= 2; ) {
        if(c[i] == c[i - 1]) {
            i--;
            continue;
        }
        b[i] = c[i];
        int j = i;
        while(j - 1 >= 0 && s[j - 1] == '1') {
            b[j - 1] = b[j] - a[j - 1];
            j--;
        }
        i = j - 1;
    }
    for(int i = 0; i < n; i++) {
        if(s[i] == '1') {
            b[i + 1] = b[i] + a[i];
            continue;
        }
        if(b[i + 1] == -LLONG_MAX) {
            a[i] = -1e12;
            b[i + 1] = b[i] + a[i];
        }
        else {
            a[i] = b[i + 1] - b[i];
            continue;
        }
    }
    int cur = 0, pre_mx = -LLONG_MAX;
    for(int i = 0; i < n; i++) {
        cur += a[i];
        pre_mx = max(pre_mx, cur);
        if(pre_mx != c[i + 1]) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
    for(int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << '\n';
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}