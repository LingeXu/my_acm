#include <bits/stdc++.h>
using namespace std;
int t, n;
void solve() {
    cin >> n;
    int cnt = 0;
    bool has_other = false;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(x == 1)  cnt++;
        else    has_other = true;
    }
    if(!has_other) {
        if(cnt % 2 == 0) {
            cout << "Bob\n";
            return;
        }
        else {
            cout << "Alice\n";
            return;
        }
    }
    if(cnt % 2 == 0) {
        cout << "Alice\n";
        return;
    }
    cout << "Bob\n";
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}