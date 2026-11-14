#include <bits/stdc++.h>
using namespace std;
int t, n, k;
void solve() {
    cin >> n >> k;
    if(n == 2 * k) {
        cout << "! " << k << ' ' << k << endl;
        return;
    }
    vector<int> a, b;
    for(int i = 1; i <= k; i++) {
        cout << "? " << i << endl;
        int resp;
        cin >> resp;
        a.push_back(resp);
    }
    int rem = n % k;
    for(int i = n - rem + 1; i <= n; i++) {
        cout << "? " << i << endl;
        int resp;
        cin >> resp;
        b.push_back(resp);
    }
    for(int i = n - k + 1; i < n - rem + 1; i++) {
        cout << "? " << i << endl;
        int resp;
        cin >> resp;
        b.push_back(resp);
    }
    int idx = -1;
    for(int i = 0; i < k; i++) {
        if(a[i] != b[i]) {
            idx = i + 1;
            break;
        }
    }
    if(idx == -1) {
        cout << "! " << -1 << endl;
        return;
    } 
    int l = 0, r = (n - 1) / k, ans = -1;
    while(l <= r) {
        int mid = (l + r) / 2;
        cout << "? " << mid * k + idx << endl;
        int resp;
        cin >> resp;
        if(resp == a[idx - 1]) {
            ans = mid;
            l = mid + 1;
        }
        else    r = mid - 1;
    }
    int L = ans * k + idx - 1;
    int lim = L;
    for(int i = lim + 1; i < lim + 1 + k; i++) {
        if(a[i % k] == b[i % k])    continue;
        cout << "? " << i + 1 << endl;
        int resp;
        cin >> resp;
        if(resp == a[i % k])    L = i;
    }
    L = max(k - 1, L);
    int R = L + 1;
    while(R < n && a[R % k] == b[R % k])
        R++;
    R = min(n - k, R);
    if(L + 1 == R) {
        cout << "! " << L + 1 << ' ' << n - L - 1 << endl;
        return;
    }
    cout << "! " << -1 << endl;
    return;
}
int main() {
    cin >> t;
    while(t--)  solve();
    return 0;
}