#include <bits/stdc++.h>
using namespace std;
int t, x, y, z;
void solve() {
    cin >> x >> y >> z;
    if(max(max(x, y), z) == x) {
        for(int i = 1; i <= x+ y + z; i++) {
            cout << 'P';
        }
        cout << '\n';
        return;
    }
    if(max(max(x, y), z) == y) {
        for(int i = 1; i <= x+ y + z; i++) {
            cout << 'R';
        }
        cout << '\n';
        return;
    }
    for(int i = 1; i <= x+ y + z; i++) {
        cout << 'S';
    }
    cout << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}