#include <bits/stdc++.h>
using namespace std;
int t, n;
bool judge(vector<int> &a) {
    map<int, bool> used;
    for(int i = 0; i < n; ) {
        if(used.count(a[i]))    return false;
        int j = i;
        used[a[i]] = true;
        while(j < n && a[j] == a[i])    j++;
        i = j;
    }
    return true;
}
void solve() {
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    if(judge(a)) {
        cout << "YES\n";
        return;
    }
    unordered_map<int, vector< pair<int, int> > > mp;
    for(int i = 0; i < n;) {
        int l = i, r = i;
        while(r < n && a[r] == a[l])    r++;
        mp[a[i]].push_back(make_pair(l, r - 1));
        if((int)mp[a[i]].size() > 3) {
            cout << "NO\n";
            return;
        }
        i = r;
    }  
    vector<int> ex1, ex2;
    for(auto &[val, v] : mp) {
        if((int)v.size() > 1) {
            for(auto &span : v) {
                ex1.push_back(span.first);
                ex1.push_back(span.second);
                if(span.first - 1 >= 0)
                    ex2.push_back(span.first - 1);
                if(span.second + 1 < n)
                    ex2.push_back(span.second + 1);
            }
            break;
        }
    } 
    sort(ex1.begin(), ex1.end());
    ex1.erase(unique(ex1.begin(), ex1.end()), ex1.end());
    sort(ex2.begin(), ex2.end());
    ex2.erase(unique(ex2.begin(), ex2.end()), ex2.end());
    for(int id1 : ex1) {
        for(int id2 : ex2) {
            swap(a[id1], a[id2]);
            if(judge(a)) {
                cout << "YES\n";
                return;
            }
            swap(a[id1], a[id2]);
        }
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