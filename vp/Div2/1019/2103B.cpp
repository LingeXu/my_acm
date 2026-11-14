#include <bits/stdc++.h>
using namespace std;
int t, n;
string s;
void solve() {
    cin >> n >> s;
    char cur = '0';
    int cnt = 0;
    int cnt0 = 0, cnt1 = 0;
    for(char c : s) {
        if(c == '0')    cnt0++;
        else    cnt1++;
        if(c == cur) {
            cnt++;
        }
        else {
            cnt += 2;
        }
        cur = c;
    }
    int cnt_1 = 0, cnt_2 = 0;
    for(int i = 0; i < n - 1; i++) {
        if(s[i] == '0' && s[i + 1] == '1')  cnt_1++;
        else if(s[i] == '1' && s[i + 1] == '0')  cnt_2++;
    }
    if(s[0] == '1') cnt_1++;
    if(cnt_1 >= 2 || cnt_2 >= 2) {
        cout << cnt - 2 << '\n';
    }
    else {
        char aim = s.back();
        if(aim == '0') {
            if(cnt_1 > 0) {
                cout << cnt - 1 << '\n';
                return;
            }
        }
        if(aim == '1') {
            if(cnt_2 > 0) {
                cout << cnt - 1 << '\n';
                return;
            }
        }
        cout << cnt << '\n';
    }
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}