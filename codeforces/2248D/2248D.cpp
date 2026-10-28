#include <bits/stdc++.h>
using namespace std;
int t, n, q;
string a, b;
void solve() {
    cin >> n >> q >> a >> b;
    vector<int> pref_cnt1(n + 1, 0), pref_cnt2(n + 1, 0), pref_cnt3(n + 1, 0), pref_cnt4(n + 1, 0);
    for(int i = 0; i < n; i++) {
        pref_cnt1[i + 1] = pref_cnt1[i] + (a[i] == '0' && b[i] == '0');
        pref_cnt2[i + 1] = pref_cnt2[i] + (a[i] == '0' && b[i] == '1');
        pref_cnt3[i + 1] = pref_cnt3[i] + (a[i] == '1' && b[i] == '0');
        pref_cnt4[i + 1] = pref_cnt4[i] + (a[i] == '1' && b[i] == '1');
    }
    while(q--) {
        int l, r;
        cin >> l >> r;
        int type1 = pref_cnt1[r] - pref_cnt1[l - 1];
        int type2 = pref_cnt2[r] - pref_cnt2[l - 1];
        int type3 = pref_cnt3[r] - pref_cnt3[l - 1];
        int type4 = pref_cnt4[r] - pref_cnt4[l - 1];
        if(type2 == type3) {
            cout << "YES\n";
            continue;
        }
        if(type2 > type3) {
            if(type3 + type1 + type4 >= type2) {
                cout << "YES\n";
                continue;
            }
            cout << "NO\n";
            continue;
        }
        if(type2 < type3) {
            if(type2 + type1 + type4 >= type3) {
                cout << "YES\n";
                continue;
            }
            cout << "NO\n";
            continue;
        }
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