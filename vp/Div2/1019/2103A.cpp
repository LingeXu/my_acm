#include <bits/stdc++.h>
using namespace std;
int t, n;
void solve() {
    cin >> n;
    int cnt = 0;
    vector<bool> a(101);
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if(!a[x]) {
            a[x] = true;
            cnt++;
        }
        else    continue;
    }
    cout << cnt << '\n';
}
int main() {
    cin >> t;
    while(t--)  solve();
    return 0;
}