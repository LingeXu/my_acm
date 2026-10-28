#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;

        int cur = 1;

        while(cur <= 10 * n) {
            cur *= 10;
            
        }
        cout << cur - 1 - n << '\n';
    }
    return 0;
}