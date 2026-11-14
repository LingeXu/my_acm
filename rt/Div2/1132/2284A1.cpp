#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int t;
    cin >> t;
    while(t--) {
        int x;
        cin >> x;
        if(x % 2 == 0) {
            cout << x * x / 4 << '\n';
            continue;
        }
        else {
            int h = x / 2;
            cout << h * (h + 1) << '\n';
            continue;
        }
    }
    return 0;
}