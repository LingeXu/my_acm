//tuple: 元组打包解包、多关键字比较、多返回值; pair 是它的二元特例
//需 #include <tuple>(pair 在 <utility>); 结构化绑定(见"解包"一节)要 C++17
//口诀: make_tuple 造, get<i> 取, tie 拆, 比较天然按字典序
//配套: 比较器写法见 lambda自定义比较.cpp, exgcd 多返回值见 扩展欧几里得.cpp

//---------------- 构造与取值 ----------------
tuple<int, int, string> t = make_tuple(1, 2, "abc");   //类型由实参自动推导
tuple<int, ll, char> z(1, 2LL, 'c');                   //显式写类型, 括号构造
tuple<int, int> v = {1, 2};                            //列表初始化, 短元组更方便
get<0>(t) = 5;                                         //get 的下标是模板参数, 必须是编译期常量
cout << get<1>(t) << ' ' << get<2>(t);                 //2 abc
//get 也能用在 pair 上: get<0>(p) 等价 p.first, 但可读性不如 .first

//make_tuple 会退化类型(去引用/去 const), tie 保留引用, 这是两者最大的区别
int w = 1;
auto t1 = make_tuple(w);                               //tuple<int>, 拷贝一份, 之后改 w 不影响 t1
auto t2 = tie(w);                                      //tuple<int&>, 改 get<0>(t2) 就是改 w

//---------------- 解包: tie 与结构化绑定 ----------------
int a; ll b; string c;
tie(a, b, c) = t;                                      //tie 生成引用元组, 按位置赋给已有变量
tie(a, ignore) = make_tuple(3, 4);                     //ignore 占位, 跳过不想要的元素
pair<int, int> p = {2, 3};
tie(a, b) = p;                                         //pair 也能直接拆, 不必先转成 tuple
//C++17 结构化绑定: 声明的同时拆开, 是 tie 的现代写法
auto [p0, p1, p2] = t;                                 //拷贝: 改 p0 不影响 get<0>(t)
auto& [r0, r1, r2] = t;                                //引用: r0 = 9 会让 get<0>(t) 也变成 9
const auto& [q0, q1, q2] = t;                          //只读引用: string/结构体这类大对象别用拷贝
for(auto& [k, val] : mp) { ... }                       //遍历 map / vector<pair> 一样适用

//---------------- 多返回值 ----------------
//返回 tuple 比"引用出参"干净, 也比为此单写一个 struct 省事
tuple<int, int, int> exgcd(int a, int b) {
    if(b == 0)    return {a, 1, 0};                    //a*1 + b*0 = a
    auto [g, x, y] = exgcd(b, a % b);                  //先拆再套公式, 免去一堆 get
    return {g, y, x - a / b * y};
}

auto [g, x, y] = exgcd(a, b);                          //调用处一行拿到三个结果

//---------------- 比较: 逐元素字典序 ----------------
//元组自带 == != < <= > >=, 从第 0 个元素比到最后, 第一个不等就出结果
tuple<int, int> s1 = {1, 2}, s2 = {1, 3};
bool less = s1 < s2;                                   //true: 第 0 个相等, 第 1 个 2 < 3
vector<tuple<int, int, int>> vec;
sort(vec.begin(), vec.end());                          //默认升序 = 按 (第0, 第1, 第2) 排序
//自定义结构体按多关键字排序: tie 只绑引用不拷贝, 比 make_tuple 省一次复制
sort(e.begin(), e.end(), [](const Edge& x, const Edge& y) {
    return tie(x.w, x.v) < tie(y.w, y.v);              //先 w 后 v 升序
});
//降序把两个 tie 交换位置(比 sort 后 reverse 少一次遍历)

//---------------- 常见用法 ----------------
//1. Dijkstra 小根堆: 一个 tuple 装 (距离, 点, 父边), greater 让它按字典序出堆
priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<>> pq;
pq.push({0, 1, 0});
auto [d, u, fa] = pq.top();                            //弹出的就是 dist 最小的点
pq.pop();
//2. 去重/有序: set<tuple<...>> 天然按字典序, 拿来存 (l, r, k) 这类状态
set<tuple<int, int, int>> st;
st.insert({l, r, k});
//3. tuple_cat 拼接两个元组, 结果类型自动推导
auto t3 = tuple_cat(t, make_tuple(4.0));               //tuple<int,int,string,double>
//4. apply 把元组展开成函数实参, 免去逐个 get
apply([](int p, int q, const string& s) { cout << p + q << s; }, t);
//5. 编译期查询: tuple_size 元素个数, tuple_element 第 i 个元素的类型
constexpr int sz = tuple_size<decltype(t)>::value;     //3
using First = tuple_element<0, decltype(t)>::type;     //int
//pair 也算 tuple-like: apply / tuple_size / tuple_element / get 一样能用, 不必先转 tuple

//---------------- 当 key: 自己写 hash ----------------
//std::hash 不支持 tuple/pair, 塞进 unordered_map/set 要手写, 且必须顺序敏感
struct TupleHash {
    size_t operator()(const tuple<int, int, int>& t) const {
        size_t h = 0;
        auto mix = [&h](size_t v) { h = (h * 1000003ULL) ^ (v + 0x9e3779b97f4a7c15ULL); };
        apply([&mix](auto... x) { (mix(hash<decltype(x)>()(x)), ...); }, t);  //C++17 折叠
        return h;
    }
};
unordered_map<tuple<int, int, int>, int, TupleHash> hmp;

//---------------- 坑 ----------------
//1. get<i> 的 i 是模板参数, 运行期变量取不了; 想按下标循环只能用 apply 或递归
//2. tie 只能绑左值: tie(1, a) 编译不过; 不用的位写 ignore
//3. 结构化绑定 auto [x, y] = ... 是拷贝, 大对象务必 const auto&
//4. 转换只保证一个方向: tuple<int,int> t = make_pair(1,2) 是 C++11 就有的;
//   pair<int,int> p = make_tuple(1,2) C++23 才进标准, 评测机老 GCC 上会挂, 手写 get<0>/get<1>
//5. tuple 与 pair 之间(C++23 前)没有 < 也没有 ==, 想比就先 tie 成同一类
//6. 元素个数不同的 tuple 之间连 == 都不给, 编译期就 static_assert 报错
//7. 比较要求每个元素都支持 <(== 则要求 ==); 元素是结构体时要自己写 operator<
//8. cout 不能直接输出 tuple/pair, 要逐个 get; 浮点元素比较仍有 eps 问题
//9. tuple 底层就是个 struct, 没有额外开销, 但字段一多可读性骤降, 复杂状态还是写 struct
