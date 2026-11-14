#include <bits/stdc++.h>
using namespace std;
int t, n;
void solve() {
    cin >> n;
    int mx = 0;
    for(int i = 1; i <= n; i++)
        mx += abs(i - (n + 1 - i));
    cout << mx / 2 + 1 << '\n';
}
int main() {
    cin >> t;
    while(t--)  solve();
    return 0;
}