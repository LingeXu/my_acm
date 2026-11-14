#include <bits/stdc++.h>
using namespace std;
int t, n, k;
void solve() {
    cin >> n >> k;
    int cnt_a = 0, cnt_b = 0;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(a[i] % 2 == 0)   cnt_a++;
    }
    for(int i = 0; i < n; i++) {
        cin >> b[i];
        if(b[i] % 2 == 0)   cnt_b++;
    }
    if(k % 2 == 1 && cnt_a < cnt_b) {
        cout << "NO\n";
        return;
    }
    if(k % 2 == 0 && cnt_a > cnt_b) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}