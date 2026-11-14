#include <bits/stdc++.h>
using namespace std;
int t, n;
void solve() {
    cin >> n;
    cout << "? " << 1 << ' ' << n << endl;
    int resp;
    cin >> resp;
    if(resp == n || resp == 0) {
        cout << "! NO" << endl;
        return;
    }
    cout << "? " << resp + 1 << ' ' << n << endl;
    int resp2;
    cin >> resp2;
    if(resp2 == 0) {
        cout << "! NO" << endl;
    }
    else {
        cout << "! YES" << endl;
    }
}
int main() {
    cin >> t;
    while(t--)  solve();
    return 0;
}