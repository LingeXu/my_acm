//位运算: GCC builtin 与常用位运算技巧速查(含 C++20 <bit> 对照)
//注意: __builtin_clz/ctz/__lg 对参数 0 行为未定义, 使用前保证 x != 0;
//      32 位版本(clz/ctz/popcount)只看 int 的低 32 位, 64 位数必须用带 ll 后缀的版本
//配套: 本文件依赖常用宏定义.cpp 的 typedef ll

//---------------- floor(log2) / 最高位 ----------------
//坑: 不要用 (int)log2(x)! 大整数时 double 精度不足, 如 2^59-1 会被舍入成 2^59 导致错 1
int highbit(ll x) { return 63 - __builtin_clzll(x); }   //floor(log2 x), 要求 x > 0
int bitlen(ll x)  { return 64 - __builtin_clzll(x); }   //x 的最少二进制位数, 要求 x > 0
//int 版本: 31 - __builtin_clz(x)

//---------------- 最低位 / lowbit ----------------
int lowpos(ll x) { return __builtin_ctzll(x); }         //最低 1 位的位置, 要求 x > 0
#define lowbit(x) ((x) & -(x))                          //只留最低的 1, x=0 得 0

//---------------- 1 的个数 / 奇偶(直接调用) ----------------
//__builtin_popcount(x)     //二进制中 1 的个数, 返回 int, 参数可为 0
//__builtin_popcountll(x)
//__builtin_parity(x)       //1 的个数 mod 2
//__builtin_parityll(x)
//__builtin_ffs(x)          //最低 1 位的下标(从 1 起), x=0 返回 0
//__builtin_ffsll(x)

//---------------- 2 的幂 ----------------
bool ispow2(ll x) { return x && !(x & (x - 1)); }
//向上取整到 2 的幂, 要求 0 < x <= 2^62(再大 1LL<<63 溢出, 换 ull)
ll roundup2(ll x) { return x <= 1 ? 1 : 1LL << (64 - __builtin_clzll(x - 1)); }

//---------------- 其他 builtin(直接调用) ----------------
//__builtin_bswap16(x) / __builtin_bswap32(x) / __builtin_bswap64(x)   //字节序翻转(大端<->小端)
//__builtin_add_overflow(a, b, &c)   //a+b 溢出返回 true, 结果写入 c
//__builtin_sub_overflow(a, b, &c)
//__builtin_mul_overflow(a, b, &c)   //三个参数必须同为 int 或同为 ll, 混用按 a 的类型算会误判
//超大数临时运算可用 __int128(约 1.7e38, 仅 GCC): (__int128)a * b

//---------------- C++20 <bit>(返回值均为 int, 参数 0 有定义) ----------------
//需 #include <bit>(C++20)放在头文件区, 与 __builtin 二选一即可
//std::bit_width(x)       //x=0 得 0; 否则 highbit(x) + 1
//std::popcount(x)        //自动按参数宽度
//std::countl_zero(x)     //前导 0 个数, x=0 返回位宽
//std::countr_zero(x)
//std::has_single_bit(x)  //2 的幂(含 1), x=0 返回 false
//std::bit_ceil(x)        //>=x 的最小 2 的幂, 0 得 1; 结果超出位宽则未定义
//std::bit_floor(x)       //<=x 的最大 2 的幂, 0 得 0
//std::rotl(x, s)         //循环左移 s 位(s 按位宽取模)
//std::rotr(x, s)

//---------------- 常用位运算技巧(直接调用) ----------------
//x & (x - 1)        //去掉最低位的 1
//x & -x             //只留最低位的 1(=lowbit)
//x | (x + 1)        //把最低位的 0 变成 1
//x ^ (x >> 1)       //二进制转格雷码; 逆变换: for(int f = x >> 1; f; f >>= 1) x ^= f;
//(n & m) == m       //组合数 C(n,m) 为奇数(卢卡斯定理推论)

//遍历所有为 1 的位:
//for(int t = x; t; t &= t - 1) { int b = t & -t; /* b 是当前最低位, 位置 = __builtin_ctz(b) */ }

//枚举 x 的非空子集(不含空集, 含 x 本身):
//for(int s = x; s; s = (s - 1) & x) { /* s */ }
//枚举 x 的超集(全集 [0, 1<<n)):
//for(int s = x; s < (1 << n); s = (s + 1) | x) { /* s */ }

//Gosper's hack: 从小到大枚举恰含 k 个 1 的数(组合枚举)
//for(int s = (1 << k) - 1; s < (1 << n); s = gosper(s))
ll gosper(ll x) { ll c = x & -x, r = x + c; return (((r ^ x) >> 2) / c) | r; }
