#include <bits/stdc++.h>
using namespace std;
int n;
void solve() {
    cin >> n;
    vector<int> a(n), b(n + 1);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(i % 2 == 0)  b[a[i]] = 1;
        else    b[a[i]] = -1;
    }
    int suff_sum = 0;
    for(int i = n; i >= 1; i--) {
        suff_sum += b[i];
        if((n - i) % 2 == 0 && abs(suff_sum) != 1) {
            cout << "NO\n";
            return;
        }
        if((n - i) % 2 == 1 && suff_sum != 0) {
            cout << "NO\n";
            return;
        } 
    }
    cout << "YES\n";
    return;
}
int main() {
    int t;
    cin >> t;
    while(t--)  solve();
    return 0;
}