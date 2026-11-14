//卡哈希: 防 unordered_map / unordered_set 在 anti-hash 数据上退化成 O(n^2)
//原理: 出题人构造一批 key, 让 std::hash 把它们全塞进同一个桶, 单次操作退化成链表遍历;
//      splitmix64 把 key 彻底打散, 再加一个运行期随机偏移, 预先构造的冲突就全部失效
//代价: 每次哈希多几次乘法/移位(约 2~3 倍常数), 换来期望 O(1), 1e5 级数据基本无感
//注意: 需要 <chrono> <cstdint>(bits/stdc++.h 已含); 随机偏移必须是 static, 同一次运行内保持一致
//配套: 多组数据清空见 多组数据与时间戳.cpp, tuple/pair 的哈希见 tuple.cpp 的 TupleHash 一节

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;                        //先加黄金分割常数, 让 0 也不再是不动点
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);                           //每步都把高位混进低位, 输出雪崩
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);            //u64 溢出回绕是良定义的, 不用特判
    }
};

//---------------- 用法: 换掉哈希模板参数 ----------------
unordered_map<int, int, custom_hash> mp;                //map<键, 值, 哈希>
unordered_map<ll, int, custom_hash> mp2;                //ll 键直接可用, 形参本来就是 uint64_t
unordered_set<int, custom_hash> st;                     //set<键, 哈希>
//int / ll / char 等整型都会隐式转成 uint64_t, 不必为每种键重写一份 hasher

//---------------- 为什么会被卡, 这样改为什么有效 ----------------
//GCC 的 std::hash<int> 基本是恒等映射, 桶数又取质数: key 全取该质数的倍数, 就全挤进同一个桶,
//1e5 次插入/查询退化成链表遍历, 这就是 CF 上说的"被 anti-hash 数据 hack 了"
//splitmix64 的输出与输入没有线性关系, FIXED_RANDOM 又取自运行时刻, 每次运行都不同,
//出题人无法预先埋好必然冲突的 key, 要卡只能靠运气; 而随机哈希的期望复杂度仍是 O(1)

//---------------- 使用细节 ----------------
mp.max_load_factor(0.7);                                //先调低装载因子, 冲突更少(空间换时间)
mp.reserve(n * 2);                                      //再按数据量给够桶, 避免插入途中反复 rehash
//这两行在大量插入之前调用; 多组数据每组 clear() 即可, 桶会保留, 不用重建
//只查不插时用 find / count: mp[x] 在 key 不存在时会插入 {x, 0}, 让 size 虚增、遍历变慢
if(mp.find(x) != mp.end())    ans += mp[x];

//---------------- pair / 自定义结构体 ----------------
//unordered_map 不认识 pair, 要自己写 hasher: 两个 32 位 int 拼成一个 uint64_t 即可
struct pair_hash {
    size_t operator()(const pii& p) const {
        uint64_t key = ((uint64_t)(uint32_t)p.first << 32) | (uint32_t)p.second;
        return custom_hash{}(key);                      //拼成唯一 key, 再交给 splitmix64
    }
};
unordered_map<pii, int, pair_hash> pm;
//多字段结构体 / tuple: 逐字段喂进 splitmix64 再异或, 写法见 tuple.cpp 的 TupleHash 一节
//注意: 拼接必须保证单射(上面的写法对两个 32 位 int 是单射), 否则不同 key 会互相覆盖

//---------------- 兜底与选择 ----------------
//数据 1e5、时限宽松时, map<int, int> 的稳定 O(log n) 往往比提心吊胆的 unordered_map 更省心
//需要按 key 有序遍历时本来也只能用 map; unordered_map 适合只做增删查、数据量大的场合
