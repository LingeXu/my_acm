#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int pre = -1, cnt = 0;
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        if(s != "yeshenle" && s != "zaoshanghao")   continue;
        if(s == "yeshenle") {
            if(pre == -1 || pre == 1) {
                cnt++;
                pre = 0;
            }
        }
        else {
            if(pre == -1) {
                cnt++;
                pre = 1;
            }
            pre = 1;
        }
    }

    cout << max(0, cnt) << '\n';
    return 0;
}