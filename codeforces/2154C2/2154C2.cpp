#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXA = 200005;
int t, n;
vector<int> primes, spf(200020);
vector<bool> isprime(200020, true);
int stamp[MAXA + 5], cur_stamp = 0;
void euler_sieve(int n) {
    for(int i = 2; i <= n; i++) {
        if(isprime[i]) {
            spf[i] = i;
            primes.push_back(i);
        }
        for(int num : primes) {
            if(i * num > n)
                break;
            isprime[i * num] = false;
            spf[i * num] = num;
            if(i % num == 0)    break;
        }
    }
}
void solve() {
    cin >> n;
    vector<int> a(n), b(n);
    int even_cnt = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(a[i] % 2 == 0)
            even_cnt++;
    }
    for(int i = 0; i < n; i++)
        cin >> b[i];
    if(even_cnt >= 2) {
        cout << 0 << '\n';
        return;
    }
    vector<int> factors;
    ++cur_stamp;
    for(int i = 0; i < n; i++) {
        int x = a[i];
        while(x > 1) {
            int cur = spf[x];
            factors.push_back(cur);
            if(stamp[cur] != cur_stamp) {
                stamp[cur] = cur_stamp;
            }
            else {
                cout << 0 << '\n';
                return;
            }
            while(x % cur == 0)    x /= cur;
        }
    }
    if(even_cnt == 1) {
        int ans = LLONG_MAX, idx = -1;
        for(int i = 0; i < n; i++) {
            if(a[i] % 2 == 1)
                ans = min(ans, b[i]);
            else    idx = i;
        }
        int mn_add = LLONG_MAX;
        for(int num : factors) {
            if(a[idx] % num == 0)   continue;
            mn_add = min(mn_add, num - a[idx] % num);
        }
        if(mn_add != LLONG_MAX)
            ans = min(ans, mn_add * b[idx]);
        cout << ans << '\n';
        return;
    }
    int mn = LLONG_MAX, mn2 = LLONG_MAX, idx = -1;
    for(int i = 0; i < n; i++) {
        if(b[i] <= mn) {
            mn2 = mn;
            mn = b[i];
            idx = i;
        }
        else if(b[i] > mn && b[i] <= mn2)   mn2 = b[i];
        else    continue;
    }
    int ans = mn + mn2;
    if(mn == mn2) {
        for(int i = 0; i < n; i++) {
            if(b[i] >= ans)  continue;
            int v = a[i] + 1;
            while(v > 1) {
                int p = spf[v];
                if(stamp[p] == cur_stamp) {
                    ans = min(ans, b[i]);
                    break;
                }
                while(v % p == 0)   v /= p;
            }
        }
        cout << ans << '\n';
        return;
    }
    int mn_add = LLONG_MAX;
    for(int num : factors) {
        if(a[idx] % num == 0)
            continue;
        mn_add = min(mn_add, num - a[idx] % num);
    }
    if(mn_add != LLONG_MAX)
        ans = min(ans, mn_add * mn);
    for(int i = 0; i < n; i++) {
        if(i == idx || b[i] >= ans)  continue;
        int v = a[i] + 1;
        while(v > 1) {
            int p = spf[v];
            if(stamp[p] == cur_stamp) {
                ans = min(ans, b[i]);
                break;
            }
            while(v % p == 0)   v /= p;
        }
    }
    cout << ans << '\n';
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    euler_sieve(200005);
    cin >> t;
    while(t--)  solve();
    return 0;
}