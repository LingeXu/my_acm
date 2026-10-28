#include <bits/stdc++.h>
using namespace std;
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n);
    int even_cnt = 0, odd_cnt = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(a[i] % 2 == 0)
            even_cnt++;
        else    odd_cnt++;
    }
    if(odd_cnt % 2 == 0 || even_cnt + odd_cnt == 1) {
        cout << "Moggity\n";
        return;
    }
    if(even_cnt == 0 && odd_cnt == 3) {
        cout << "Larpity\n";
        return;
    }
    if(even_cnt == 0) {
        cout << "Moggity\n";
        return;
    }
    if(even_cnt == 1 && odd_cnt == 1) {
        cout << "Larpity\n";
        return;
    }
    if(even_cnt > 1 && odd_cnt == 1) {
        cout << "Moggity\n";
        return;
    }
    if(even_cnt > 0 && odd_cnt != 1) {
        cout << "Moggity\n";
        return;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}