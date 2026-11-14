/*
 * Problem J. Number Game  (2026 ICPC Asia Wuhan Regional)
 *
 * Operation: pick a sub-multiset S, all its elements become mex(S).
 *
 * Key facts
 *  - mex(S) <= |S|  (S must contain 0,1,...,mex(S)-1).
 *    Hence if exactly k elements are ever touched ("created"), every created
 *    value is <= k.  A value > n therefore has to be kept untouched.
 *  - So A -> B iff  A == B, or
 *      exists k and C subset of B, |C| = k, all values of C <= k,
 *      B\C is a sub-multiset of A,   and   C can be generated from scratch
 *      with k elements (write C in J(k)).
 *
 * Characterisation of J(k)   (reverse / "building" view)
 *    Build C element by element.  Let s be the number of elements placed so far.
 *    One forward operation with mex v and |S| = q  places q copies of v with
 *    q >= v.  In the building order such a group can be placed only when the
 *    current size s satisfies  v - s <= q, i.e. it "jumps" the size to v while
 *    consuming exactly v-s copies (minimum is optimal).  Anything else must be
 *    placed as a single element, which is possible only when its value <= s.
 *    C is in J(k)  iff  repeatedly preferring such "blocks" consumes C exactly.
 *
 * For a fixed k the elements that *must* be created are the surplus
 * e(v)=max(0,cntB(v)-cntA(v)); the remaining k-sum(e) created elements are
 * taken as the smallest available ones (smallest is easiest to build).
 * Try every k from n downwards.
 */
#include <bits/stdc++.h>
using namespace std;

/* ---- C (a multiset of size k, all values in [0,k]) in J(k)?  O(k log k) ---- */
static bool inJ(const vector<int>& C)
{
    int k = (int)C.size();
    if (k == 0) return true;
    vector<int> cnt(k + 1, 0);
    for (int x : C) { if (x < 0 || x > k) return false; cnt[x]++; }

    int sz = 1; while (sz < k + 1) sz <<= 1;
    vector<int> mx(2 * sz, INT_MIN), sum(2 * sz, 0);   // mx = cnt[v]-v , sum = cnt[v]
    for (int v = 0; v <= k; v++) { mx[sz + v] = cnt[v] - v; sum[sz + v] = cnt[v]; }
    for (int p = sz - 1; p >= 1; p--) {
        mx[p] = max(mx[2 * p], mx[2 * p + 1]);
        sum[p] = sum[2 * p] + sum[2 * p + 1];
    }
    auto update = [&](int v) {
        int p = sz + v; mx[p] = cnt[v] - v; sum[p] = cnt[v];
        for (p >>= 1; p; p >>= 1) {
            mx[p] = max(mx[2 * p], mx[2 * p + 1]);
            sum[p] = sum[2 * p] + sum[2 * p + 1];
        }
    };
    // rightmost v in [lo,hi] with cnt[v]-v >= need
    function<int(int,int,int,int,int,int)> rightmost =
        [&](int p, int l, int r, int lo, int hi, int need)->int {
        if (r < lo || hi < l || mx[p] < need) return -1;
        if (l == r) return l;
        int mid = (l + r) >> 1;
        int res = rightmost(2*p+1, mid+1, r, lo, hi, need);
        if (res != -1) return res;
        return rightmost(2*p, l, mid, lo, hi, need);
    };
    // leftmost v in [lo,hi] with cnt[v] > 0
    function<int(int,int,int,int,int)> leftmost =
        [&](int p, int l, int r, int lo, int hi)->int {
        if (r < lo || hi < l || sum[p] == 0) return -1;
        if (l == r) return l;
        int mid = (l + r) >> 1;
        int res = leftmost(2*p, l, mid, lo, hi);
        if (res != -1) return res;
        return leftmost(2*p+1, mid+1, r, lo, hi);
    };

    int s = 0, remaining = k;
    while (remaining > 0) {
        int v = rightmost(1, 0, sz - 1, s + 1, k, -s);   // a "block": v>s, cnt[v] >= v-s
        if (v != -1) {
            int q = v - s;
            cnt[v] -= q; update(v); remaining -= q; s = v;
        } else {
            int u = leftmost(1, 0, sz - 1, 0, min(s, k)); // a single element of value <= s
            if (u == -1) return false;
            cnt[u]--; update(u); remaining--; s++;
        }
    }
    return true;
}

int main()
{
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        int n; scanf("%d", &n);
        vector<int> A(n), B(n);
        for (auto& x : A) scanf("%d", &x);
        for (auto& x : B) scanf("%d", &x);

        vector<int> ca(n + 1, 0), cb(n + 1, 0);
        vector<int> abig, bbig;                        // values > n
        for (int x : A) { if (x <= n) ca[x]++; else abig.push_back(x); }
        for (int x : B) { if (x <= n) cb[x]++; else bbig.push_back(x); }
        sort(abig.begin(), abig.end());
        sort(bbig.begin(), bbig.end());

        if (abig == bbig) {                            // A == B ?
            bool same = true;
            for (int v = 0; v <= n; v++) if (ca[v] != cb[v]) { same = false; break; }
            if (same) { puts("YES"); continue; }
        }

        bool bigOk = true;                             // values > n can never be created
        for (size_t i = 0, j = 0; j < bbig.size(); ) {
            while (i < abig.size() && abig[i] < bbig[j]) i++;
            if (i < abig.size() && abig[i] == bbig[j]) { i++; j++; }
            else { bigOk = false; break; }
        }
        if (!bigOk) { puts("NO"); continue; }

        vector<int> prefForced(n + 2, 0), prefMin(n + 2, 0);
        vector<int> suffMax(n + 2, INT_MIN), prefB(n + 2, 0);
        for (int v = 0; v <= n; v++) {
            prefForced[v + 1] = prefForced[v] + max(0, cb[v] - ca[v]);
            prefMin[v + 1]    = prefMin[v]    + min(ca[v], cb[v]);
            prefB[v + 1]      = prefB[v]      + cb[v];
        }
        for (int v = n; v >= 0; v--) suffMax[v] = max(suffMax[v + 1], cb[v] - ca[v]);

        int cntBig = (int)bbig.size();
        bool ans = false;
        for (int k = n; k >= 0 && !ans; k--) {
            if (suffMax[k + 1] > 0) continue;                       // B value > k is not keepable
            int forcedKeep = (prefB[n + 1] - prefB[k + 1]) + cntBig; // B elements > k, all kept
            if (prefMin[k + 1] + forcedKeep < n - k) continue;      // cannot keep enough
            int E = prefForced[k + 1];                              // must be created
            if (E > k) continue;
            if (prefB[k + 1] < k) continue;                         // too few B elements <= k

            vector<int> C; C.reserve(k);
            for (int v = 0; v <= k; v++)
                for (int t = cb[v] - ca[v]; t > 0; t--) C.push_back(v);
            int need = k - E;
            for (int v = 0; v <= k && need > 0; v++) {
                int avail = cb[v] - max(0, cb[v] - ca[v]);
                int take = min(avail, need);
                for (int t = 0; t < take; t++) C.push_back(v);
                need -= take;
            }
            if (need > 0) continue;
            if (inJ(C)) ans = true;
        }
        puts(ans ? "YES" : "NO");
    }
    return 0;
}
