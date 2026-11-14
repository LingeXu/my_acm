#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> c(n);
        for (int i = 0; i < n; ++i) {
            int cur = 0, x;
            for (int j = 0; j < n; ++j) {
                cin >> x;
                if (x == 1) ++cur;  
                else        cur = 0;
            }
            c[i] = cur;
        }

        sort(c.begin(), c.end());
        int ans = 0;
        for (int x : c)
            if (x >= ans) ++ans;

        cout << ans << '\n';
    }
    return 0;
}