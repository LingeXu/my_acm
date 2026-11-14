#include <bits/stdc++.h>
using namespace std;
int ans = 0;
bool is_neighbor(char c1, char c2) {
    if((int)(c1 - c2) == 1) 
        return true;
    return false;
}
void dfs(string &s, int cur) {
    ans = max(ans, cur);
    int sz = s.size();
    if(sz == 1)  return;
    for(int i = 0; i < sz; i++) {
        if((i + 1 < sz && is_neighbor(s[i], s[i + 1])) || (i - 1 >= 0 && is_neighbor(s[i], s[i - 1]))) {
            string news = s.substr(0, i) + s.substr(i + 1);

            //cout << "i = " << i << '\n';
            //cout << "news = " << news << '\n';

            dfs(news, cur + 1);
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    string s;
    cin >> n >> s;
    for(int i = 26; i >= 2; i--) {
        char c = 'a' + i - 1;
        bool change = true;
        while(change) {
            change = false;
            for(int i = 0; i < s.size(); i++) {
                if(s[i] != c)   continue;
                char aim = c - 1;
                bool ok = (i == 0 && s[i + 1] == aim) || (i == (int)s.size() - 1 && s[i - 1] == aim) || (s[i - 1] == aim || s[i + 1] == aim);
                if(ok) {
                    s.erase(s.begin() + i);
                    change = true;
                    break;
                }
            }
        }
    }

    //cout << "s = " << s << '\n';

    cout << n - (int)s.size() << '\n';
    return 0;
}