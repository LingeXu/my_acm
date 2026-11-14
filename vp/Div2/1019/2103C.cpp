#include <bits/stdc++.h>
using namespace std;
int t, n, k;
bool check(vector<int> &b) {
    int n = b.size();
    vector<int> pref_sum(n + 1), suf_mx(n);
    suf_mx[n - 1] = -0x3f3f3f3f;
    for(int i = 0; i < n; i++) 
        pref_sum[i + 1] = pref_sum[i] + b[i];
    for(int i = n - 2; i >= 1; i--)
        suf_mx[i] = max(suf_mx[i + 1], pref_sum[i + 1]);

    /*for(int i = 1; i <= n; i++)
        cout << pref_sum[i] << ' ';
    cout << '\n';
    for(int i = 1; i <= n - 2; i++)
        cout << suf_mx[i] << ' ';
    cout << '\n';*/

    for(int i = 0; i <= n - 3; i++)     
        if(pref_sum[i + 1] >= 0 && suf_mx[i + 1] >= pref_sum[i + 1])
            return true;
    return false;
}
void solve() {
    cin >> n >> k;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(a[i] <= k)   b[i] = 1;
        else    b[i] = -1;
    }
    int idx1 = -1, idx2 = -1, cur1 = 0, cur2 = 0;
    for(int i = 0; i < n; i++) {
        cur1 += b[i];
        if(cur1 >= 0 && idx1 == -1) {
            idx1 = i;
            break;
        }
    }
    for(int i = n - 1; i >= 0; i--) {
        cur2 += b[i];
        if(cur2 >= 0 && idx2 == -1) {
            idx2 = i;
            break;
        }
    }
    if(idx1 != -1 && idx2 != -1 && idx1 + 1 < idx2) {
        cout << "YES\n";
        return;
    }
    if(check(b)) {
        cout << "YES\n";
        return;
    }
    reverse(b.begin(), b.end());
    if(check(b)) {
        cout << "YES\n";
        return;
    }
    cout << "NO\n";
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}