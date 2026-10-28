#include <bits/stdc++.h>
using namespace std;
int t, l1, b1, l2, b2, l3, b3;
void solve() {
    cin >> l1 >> b1 >> l2 >> b2 >> l3 >> b3;
    if(l1 == l2 && l2 == l3 && b1 + b2 + b3 == l1) {
        cout << "YES\n";
        return;
    }
    if(b1 == b2 && b2 == b3 && l1 + l2 + l3 == b1) {
        cout << "YES\n";
        return;
    }
    if(b3 + b2 == b1 && l3 == l2 && l1 + l3 == b1) {
        cout << "YES\n";
        return;
    }
    if(l3 + l2 == l1 && b3 == b2 && b1 + b3 == l1) {
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