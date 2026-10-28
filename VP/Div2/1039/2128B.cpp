#include <bits/stdc++.h>
using namespace std;
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    for(int i = 0; i <= n - 1 - i; i++) {
        if(i == n - 1 - i) {
            cout << 'L';
            break;
        }
        if(i % 2 == 0) {
            if(a[i] < a[n - 1 - i])
                cout << "LR";
            else    cout << "RL";
            continue;
        }
        else {
            if(a[i] < a[n - 1 - i])
                cout << "RL";
            else    cout << "LR";
            continue;
        }
    }
    cout << '\n';
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}