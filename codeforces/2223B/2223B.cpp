#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
int t, n;
bool Less(pair<int, int> &x, pair<int, int> &y) {
    return x.first * y.second < x.second * y.first;
}
bool More(pair<int, int> &x, pair<int, int> &y) {
    return x.first * y.second > x.second * y.first;
}
int quick_pow(int a, int p) {
    int res = 1, base = a % MOD;
    while(p) {
        if(p & 1)   res = res * base % MOD;
        p >>= 1;
        base = base * base % MOD;
    }
    return res;
}
int inv(int x) {
    return quick_pow(x, MOD - 2);
}
void solve() {
    cin >> n;
    vector<int> a(n), b(n);
    vector< pair<int, int> > a1, b1;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    for(int i = 0; i < n; i++)
        cin >> b[i];
    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++)
            a1.push_back({a[i], a[j]});
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            b1.push_back({b[i], b[j]});
            b1.push_back({b[j], b[i]});
        }
    }
    sort(a1.begin(), a1.end(), Less);
    sort(b1.begin(), b1.end(), Less);

    /*for(double i : a1)
        cout << i << ' ';
    cout << '\n';*/

    int sz_a = a1.size(), sz_b = b1.size();
    int i = 0, j = 0, cnt = 0, pre = 0;
    while(i < sz_a) {
        int cur = 0;
        while(j < sz_b && More(a1[i], b1[j])) {
            cur++;
            j++;
        }
        cnt += pre + cur;

        //cout << "cnt = " << cnt << '\n';

        pre += cur;
        i++;
    }

    //cout << "cnt = " << cnt << '\n';
    
    cout << cnt % MOD * inv(n * (n - 1)) % MOD << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}