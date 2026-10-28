//NTT 快速数论变换: 多项式乘法(卷积), O(n log n)
//原理: FFT 的单位根换成模意义下的原根幂; P = 998244353 = 119 * 2^23 + 1, 原根 g = 3
//      支持长度 <= 2^23 的卷积; 结果对 P 取模
//需预定义: 无(自带模 P 的快速幂, 不依赖全局 MOD)
//入口: ntt(a, n, 1) 正变换 / ntt(a, n, -1) 逆变换;  conv(A, B) 返回 A * B
//注意: n 必须是 2 的幂; 逆变换后要乘 n 的逆元(模板内已乘)

const ll P = 998244353, G = 3;  //用 P 避免与代码里已有的 MOD 冲突

ll qpow(ll a, ll n) {          //模 P 快速幂(NTT 内部专用)
    ll res = 1;
    while(n) {
        if(n & 1)    res = res * a % P;
        a = a * a % P;
        n >>= 1;
    }
    return res;
}

void ntt(vector<ll>& a, bool inv) {
    int n = a.size();
    vector<int> rev(n);
    for(int i = 0; i < n; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);   //位逆序置换
        if(i < rev[i])    swap(a[i], a[rev[i]]);
    }
    for(int len = 2; len <= n; len <<= 1) {                     //蝴蝶合并, 长度倍增
        ll wn = qpow(G, (P - 1) / len);                //本层单位根
        if(inv)    wn = qpow(wn, P - 2);               //逆变换用逆单位根
        for(int i = 0; i < n; i += len) {
            ll w = 1;
            for(int j = i; j < i + len / 2; j++) {
                ll u = a[j], v = a[j + len / 2] * w % P;
                a[j] = (u + v) % P;
                a[j + len / 2] = (u - v + P) % P;
                w = w * wn % P;
            }
        }
    }
    if(inv) {                                                  //逆变换除以 n
        ll inv_n = qpow(n, P - 2);
        for(ll& x : a)    x = x * inv_n % P;
    }
}

vector<ll> conv(vector<ll> a, vector<ll> b) {                  //卷积: 结果长度 = 两个长度和 - 1
    int need = a.size() + b.size() - 1;
    int n = 1;
    while(n < need)    n <<= 1;
    a.resize(n);
    b.resize(n);
    ntt(a, false);
    ntt(b, false);
    for(int i = 0; i < n; i++)    a[i] = a[i] * b[i] % P;    //点值相乘
    ntt(a, true);
    a.resize(need);
    return a;
}
//配套:
//1. 任意模数卷积: 三个 NTT 模数(998244353 / 1004535809 / 469762049)分别算再 CRT 合并, 或拆系数
//2. 多项式求逆/开方/exp: 在 NTT 基础上牛顿迭代, 区域赛较少直接考, 赛前过一遍板子即可
//3. 高精度整数乘法: 系数即十进制位, 卷积后逐位进位(注意 P 的精度)
