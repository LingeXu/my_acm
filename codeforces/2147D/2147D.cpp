#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.end(), greater<int>());
    int s_a = 0, s_b = 0;
    vector< pair<int, int> > record;
    for(int i = 0; i < n;) {
        int j = i;
        while(j < n && a[j] == a[i])    j++;
        int cnt = j - i;
        if(a[i] % 2 == 0) {
            s_a += cnt * (a[i] / 2);
            s_b += cnt * (a[i] / 2);
        }
        else    record.push_back(make_pair(cnt, a[i]));
        i = j;
    }
    sort(record.begin(), record.end(), [](const auto x, const auto y){return x.first > y.first;});
    for(int i = 0; i < (int)record.size(); i++) {
        if(i % 2 == 0) {
            s_a += record[i].first * (record[i].second / 2 + 1);
            s_b += record[i].first * (record[i].second / 2);
        }
        else {
            s_a += record[i].first * (record[i].second / 2);
            s_b += record[i].first * (record[i].second / 2 + 1);
        }
    }
    cout << s_a << ' ' << s_b << '\n';
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}