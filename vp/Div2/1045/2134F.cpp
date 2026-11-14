#include <bits/stdc++.h>
using namespace std;
int t, n, a, b;
void solve() {
    cin >> n >> a >> b;
    if(n % 2 == 0) {
        if(b % 2 == 1) {
            cout << "NO\n";
            return;
        }
        else {
            if(a <= b) {
                cout << "YES\n";
                return;
            }   
            if(a > b && a % 2 == 0) {
                cout << "YES\n";
                return;
            }     
            cout << "NO\n";
            return;
        }
    }
    else {
        if(b % 2 == 0) {
            cout << "NO\n";
            return;
        }
        else {
            if(a <= b) {
                cout << "YES\n";
                return;
            }
            if(a > b && a % 2 == 1) {
                cout << "YES\n";
                return;
            }
            cout << "NO\n";
            return;
        }
    }
}
int main() {
    cin >> t;
    while(t--)  solve();
    return 0;
}