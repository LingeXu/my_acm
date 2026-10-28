#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<ll> rnd(m);
        for (auto& v : rnd) v = rng();
        vector<ll> ev(n + 2);
        for (int i = 0; i < m; ++i) {
            int l, r;
            cin >> l >> r;
            ev[l] ^= rnd[i];
            ev[r + 1] ^= rnd[i];
        }
        vector<ll> sig(n + 1);
        ll cur = 0;
        for (int x = 1; x <= n; ++x) {
            cur ^= ev[x];
            sig[x] = cur;
        }

        vector<ll> sorted = sig;
        sort(sorted.begin() + 1, sorted.end());
        int C = unique(sorted.begin() + 1, sorted.end()) - (sorted.begin() + 1);
        vector<int> cls(n + 1);
        for (int x = 1; x <= n; ++x)
            cls[x] = lower_bound(sorted.begin() + 1, sorted.begin() + 1 + C, sig[x]) - sorted.begin();
        vector<vector<int>> spots(C + 1);
        for (int x = 1; x <= n; ++x) spots[cls[x]].push_back(x);
        vector<int> lastSpot(n + 1);
        for (int c = 1; c <= C; ++c)
            for (int x : spots[c]) lastSpot[x] = spots[c].back();
        vector<pair<int, int>> ranges;  
        for (int c = 1; c <= C; ++c) {
            auto& p = spots[c];
            for (size_t t = 0; t + 1 < p.size(); ++t)
                ranges.emplace_back(p[t + 1] - 1, p[t]);
        }
        sort(ranges.begin(), ranges.end());
       
        vector<int> forced;
        int last = -1;
        for (auto [r, l] : ranges) {
            if (last >= l) continue;
            forced.push_back(r);
            last = r;
        }
        int M = (int)forced.size();
        vector<int> F(n + 1);
        for (int p : forced) F[p + 1]++;
        for (int x = 1; x <= n; ++x) F[x] += F[x - 1];

        auto runSweep = [&](int h0) -> pair<int, vector<char>> {
            vector<char> isOpen(M, 0), quota(C + 1, 0);
            int count = 0, ptr = 0;
            vector<int> stk;
            for (int x = 1; x <= n; ++x) {
                while (ptr < M && forced[ptr] < x) {
                    stk.push_back(ptr);
                    ++ptr;
                }
                int T = (F[x] + 1 - h0 + 1) / 2;  // ceil((F[x]+1-h0)/2)
                if (T > count) {
                    int c = cls[x];
                    while (!stk.empty() && isOpen[stk.back()]) stk.pop_back();
                    int idx = stk.empty() ? -1 : stk.back();
                    if (!quota[c] && (idx == -1 || lastSpot[x] == x)) {
                        quota[c] = 1;
                    } else if (idx != -1) {
                        isOpen[idx] = 1;
                        count++;
                    } else {
                        return {INT_MAX, {}};
                    }
                }
            }
            return {count, isOpen};
        };

        int best = INT_MAX, bestH = 0;
        vector<char> bestOpen;
        for (int h0 = 0; h0 <= 1; ++h0) {
            auto [cnt, isOpen] = runSweep(h0);
            if (h0 + cnt < best) {
                best = h0 + cnt;
                bestH = h0;
                bestOpen = isOpen;
            }
        }
        int k = best;
        
        vector<int> opens, closes;
        if (bestH == 1) opens.push_back(1);
        for (int i = 0; i < M; ++i) {
            if (bestOpen[i]) opens.push_back(forced[i] + 1);
            else closes.push_back(forced[i]);
        }
        cout << k << "\n";
        for (size_t j = 0; j < opens.size(); ++j) {
            int r = (j < closes.size()) ? closes[j] : n;
            cout << opens[j] << " " << r << "\n";
        }
    }
    return 0;
}