#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
int quick_pow(int a, int p) {
    int res = 1, base = a % MOD;
    while(p) {
        if(p & 1)   res = res * base % MOD;
        p >>= 1;
        base = base * base % MOD;
    }
    return res;
}
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    vector< pair<int, int> > mx_a(n + 1), mx_b(n + 1);
    for(int i =1; i <= n; i++)
        cin >> a[i];
    for(int i =1; i <= n; i++)
        cin >> b[i];
    if(n == 1) {
    
        cout << (quick_pow(2, a[1])+ quick_pow(2, b[1])) % MOD << '\n';
        return;
    }
    mx_a[1] = {1, a[1]};
    for(int i = 2; i <= n; i++) {
        
        if(a[i] > mx_a[i - 1].second) {
            mx_a[i] = {i, a[i]};
        }

        else {
            mx_a[i] = mx_a[i - 1];
        }
    }
    mx_b[1] = {1, b[1]};
    for(int i = 2; i <= n; i++) {
        
        if(b[i] > mx_b[i - 1].second) {
            mx_b[i] = {i, b[i]};
        }

        else {
            mx_b[i] = mx_b[i - 1];
        }
    }
    for(int i = 1; i <= n; i++) {
        //cout << "i = " << i << ", mxa = " << mx_a[i].second << ", mxb = " << mx_b[i].second << '\n';
        if(mx_a[i].second > mx_b[i].second) {
            cout << (quick_pow(2, mx_a[i].second) + quick_pow(2, b[i + 1 - mx_a[i].first])) % MOD << ' ';
        }
        else if(mx_a[i].second < mx_b[i].second) {
            cout << (quick_pow(2, mx_b[i].second) + quick_pow(2, a[i + 1 - mx_b[i].first])) % MOD << ' ';
        }
        else {
            if(b[i + 1 - mx_a[i].first] > a[i + 1 - mx_b[i].first]) {
                cout << (quick_pow(2, mx_a[i].second) + quick_pow(2, b[i + 1 - mx_a[i].first])) % MOD << ' ';
            }
            else {
                cout << (quick_pow(2, mx_b[i].second) + quick_pow(2, a[i + 1 - mx_b[i].first])) % MOD << ' ';
            }
        }
    }
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