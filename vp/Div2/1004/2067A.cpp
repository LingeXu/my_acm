#include <bits/stdc++.h>
using namespace std;
int t, x, y;
void solve() {
    cin >> x >> y;
    if(y - x == 1) {
        cout << "Yes\n";
        return;
    }
    if((x - y + 1) % 9 == 0 && x - y + 1 > 0) {
        cout << "Yes\n";
        return;
    }
    cout << "No\n";
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}