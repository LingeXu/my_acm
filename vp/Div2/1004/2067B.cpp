#include <bits/stdc++.h>
using namespace std;
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n), cnt(n + 2);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    for(int i = 1; i <= n; i++) {
        if(cnt[i] == 0)
            continue;
        if(cnt[i] == 1) {
            cout << "No\n";
            return;
        }
        cnt[i + 1] += cnt[i] - 2;
    }
    if(cnt[n + 1] % 2 != 0) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}