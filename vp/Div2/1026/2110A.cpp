#include <bits/stdc++.h>
using namespace std;
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    if(n == 1) {
        cout << 0 << '\n';
        return;
    }
    sort(a.begin(), a.end());
    if((a[0] + a[n - 1]) % 2 == 0) {
        cout << 0 << '\n';
        return;
    }
    if(a[0] % 2 == 1) {
        int first_even = -1;
        for(int i = 0; i < n; i++) {
            if(a[i] % 2 == 0) {
                first_even = i;
                break;
            }
        }
        int last_odd = n;
        for(int i = n - 1; i >= 0; i--) {
            if(a[i] % 2 != 0) {
                last_odd = i;
                break;
            }
        }
        cout << min(n - 1, min(first_even, n - last_odd - 1)) << '\n';
        return;
    }
    else {
        int first_odd = -1;
        for(int i = 0; i < n; i++) {
            if(a[i] % 2 != 0) {
                first_odd = i;
                break;
            }
        }
        int last_even = n;
        for(int i = n - 1; i >= 0; i--) {
            if(a[i] % 2 == 0) {
                last_even = i;
                break;
            }
        }
        cout << min(min(first_odd, n - last_even - 1), n - 1) << '\n';
        return;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}