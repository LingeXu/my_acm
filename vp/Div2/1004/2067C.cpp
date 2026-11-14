#include <bits/stdc++.h>
using namespace std;
int t, n;
void solve() {
    cin >> n;
    int cur = 10, rem = n % 10, last = rem, ans = 10;
    while(cur <= n) {
        int digit = (n % (10 * cur)) / cur;
        if(digit == 8)  ans = min(ans, rem + 1);
        int ti = (7 - digit + 10) % 10;
        ans = min(ans, ti + (rem < ti));
        cur *= 10;
        last = digit;
        rem += cur * last;
    }
    if(n >= 7)  ans = min(7, ans);
    cout << min((n % 10 + 3) % 10, ans) << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}