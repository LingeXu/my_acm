#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, k;
string s;
void solve() {
    cin >> n >> k >> s;
    if(k == n / 2) {
        cout << k << '\n';
        return;
    }
    vector<int> c;
    int pre = -1;
    for(int i = 0; i < n; i++) {
        if(s[i] == '(')
            continue;
        c.push_back(i - pre - 2);
        pre = i;
    }

    /*for(int i : c)
        cout << i << ' ';
    cout << '\n';*/

    vector<int> pref_sum(n / 2 + 1);
    for(int i = 0; i < n / 2; i++)
        pref_sum[i + 1] = pref_sum[i] + c[i];

    /*for(int i = 1; i <= n / 2; i++)
        cout << pref_sum[i] << ' ';
    cout << '\n';*/

    deque< pair<int, int> > dq;
    int ans = 0, j = 2;
    for(int i = 1; i <= n / 2; i++) {
        while(!dq.empty() && dq.front().first <= i)  dq.pop_front();
        while(j <= min(n / 2, i + k + 1)) {
            while(!dq.empty() && pref_sum[j] > dq.back().second)    dq.pop_back();
            dq.push_back(make_pair(j, pref_sum[j]));
            j++;
        }
        if(dq.empty()) continue;
        int cur = dq.front().second - pref_sum[i] + 1;
        ans = max(ans, cur);

    }
    int front = 0;
    for (int i = 1; i <= min(k + 1, n / 2); i++)
        front = max(front, min(pref_sum[i] + k + 1, n / 2));
    ans = max(ans, front);   
    cout << ans << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}