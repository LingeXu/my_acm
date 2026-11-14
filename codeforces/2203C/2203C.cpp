#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, s, m;
vector<int> cnt(64);
vector< pair<int, int> > m_pos;
bool check(int x) {
    vector< pair<int, int> > copy(m_pos.begin(), m_pos.end());
    for(int i = copy.size() - 1; i >= 0; i--) {
        //cout << m_pos[i].second << '\n';
        if(copy[i].second <= x)   continue;
        if(i == 0)  return false;
        int diff = copy[i].second - x;
        copy[i - 1].second += diff * (1LL << (copy[i].first - copy[i - 1].first));
    }
    return true;
}
void solve() {
    m_pos.clear();
    cnt.clear();
    cin >> s >> m;
    vector<int> s_pos;
    for(int i = 0; i < 64; i++) 
        if(((s >> i) & 1) == 1)
            s_pos.push_back(i);
    for(int i = 0; i < 64; i++) 
        if(((m >> i) & 1) == 1)
            m_pos.push_back({i, 0});

    /*for(int i : s_pos)
        cout << i << ' ';
    cout << '\n';
    for(auto i : m_pos)
        cout << i.first << ' ';
    cout << '\n';*/

    if(s_pos[0] < m_pos[0].first) {
        cout << -1 << '\n';
        return;
    }
    int i = (int)s_pos.size() - 1, j = (int)m_pos.size() - 1;
    while(i >= 0 && j >= 0) {
        while(i >= 0 && j >= 0 && s_pos[i] >= m_pos[j].first) {
            m_pos[j].second += (1LL << (s_pos[i] - m_pos[j].first));;
            i--;
        }
        if(i < 0 || j < 0)  break;
        j--;
    }

    /*for(auto i : m_pos)
        cout << i.second << ' ';
    cout << '\n';*/

    int l = 0, r = LLONG_MAX, ans = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(check(mid)) {
            ans = mid;
            r = mid - 1;
        }
        else    l = mid + 1;
    }
    cout << ans << '\n';
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}