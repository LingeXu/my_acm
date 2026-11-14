#include <bits/stdc++.h>
using namespace std;
int t, a, b, c, d;
void solve() {
    cin >> a >> b >>c >> d;
    if(min(a, c) >= min(b, d)) {
        cout << "Gellyfish\n";
        return;
    }
    cout << "Flower\n";
}
int main() {
    cin >> t;
    while(t--)  solve();
    return 0;
}