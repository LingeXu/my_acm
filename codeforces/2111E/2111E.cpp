#include <bits/stdc++.h>
using namespace std;
int t, n, q;
string s;
vector<vector<set<int>>> op(3, vector<set<int>>(3));
void solve() {
    cin >> n >> q >> s;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            op[i][j].clear();
    char x, y;
    for(int i = 0; i < q; i++) {
        cin >> x >> y;
        if(x == 'a' && y == 'b')    op[0][1].insert(i);
        else if(x == 'a' && y == 'c')    op[0][2].insert(i);
        else if(x == 'b' && y == 'a')    op[1][0].insert(i);
        else if(x == 'b' && y == 'c')    op[1][2].insert(i);
        else if(x == 'c' && y == 'a')    op[2][0].insert(i);
        else if(x == 'c' && y == 'b')    op[2][1].insert(i);
    }
    for(int i = 0; i < n; i++) {
        if(s[i] == 'a')
            continue;
        if(s[i] == 'b') {
            if(!op[1][0].empty()){
                s[i] = 'a';
                op[1][0].erase(op[1][0].begin());
                continue;
            }
            if(!op[1][2].empty()) {
                auto it = op[2][0].lower_bound(*op[1][2].begin());
                if(it != op[2][0].end()) {
                    s[i] = 'a';
                    op[1][2].erase(op[1][2].begin());
                    op[2][0].erase(it);
                }
                continue;
            }
        }
        else if(s[i] == 'c') {
            if(!op[2][0].empty()){
                s[i] = 'a';
                op[2][0].erase(op[2][0].begin());
                continue;
            }
            if(!op[2][1].empty()) {
                auto it = op[1][0].lower_bound(*op[2][1].begin());
                if(it != op[1][0].end()) {
                    s[i] = 'a';
                    op[2][1].erase(op[2][1].begin());
                    op[1][0].erase(it);
                    continue;
                }
                s[i] = 'b';
                op[2][1].erase(op[2][1].begin());
                continue;
            }
        }
    }
    cout << s << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}