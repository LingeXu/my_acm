#include <bits/stdc++.h>
using namespace std;
int t, n;
string s1, s2;
void solve() {
    cin >> n >> s1 >> s2;
    int cnt0 = 0, cnt1 = 0;
    for(int i = 0; i < n; i++) {
        if(s1[i] == '0')    continue;
        if(i % 2 == 0)  cnt0++;
        else    cnt1++;
    }
    int cnt0_= 0, cnt1_ = 0;
    for(int i = 0; i < n; i++) {
        if(s2[i] == '1')    continue;
        if(i % 2 == 0)  cnt0_++;
        else    cnt1_++;
    }
    if(cnt0_ >= cnt1 && cnt1_ >= cnt0) {
        cout << "YES\n";
        return;
    }
    cout << "NO\n";
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}