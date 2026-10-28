//手调代码片段: 断言、打点、熔断、分段计时; 用机器定位, 别盯代码
//用法: 贴在 #include 之后; 提交前不用删, 全部挂在 LOCAL 下自动失效
//注意: assert 在定义 NDEBUG 时失效且本身有开销; 正式代码别留 CHECK

//---------------- 断言: 把"不应该发生"写成代码 ----------------
#define CHECK(c) do { if(!(c)) { \
    cerr << "CHECK failed L" << __LINE__ << ": " #c << '\n'; abort(); } } while(0)

CHECK(0 <= i && i < n);                                //每次下标访问前, 本地版
static int step = 0;
CHECK(++step < 10000000);                              //抓死循环: 计数器熔断
CHECK(pref[i] >= pref[i - 1]);                         //抓不变量: 前缀和应当单调
//好处: 在 bug 第一次出现的瞬间停住, 比事后打印准得多

//---------------- 打点 ----------------
#ifdef LOCAL
#define dbg(x)     cerr << "L" << __LINE__ << " " #x "=" << (x) << '\n'
#define dbg2(a, b) cerr << "L" << __LINE__ << " " #a "=" << (a) << " " #b "=" << (b) << '\n'
#else
#define dbg(x)
#define dbg2(a, b)
#endif

//调试走 stderr(无缓冲, 崩了也看得到), 正式输出走 stdout, 两者互不干扰
//用 printf 时先 setvbuf(stdout, nullptr, _IONBF, 0); 或每段 fflush(stdout)
//大数组别整个打: 打首尾/区间/哈希, 或先把 n 缩到 10
//调试输出本身会拖慢程序甚至 TLE, 所以必须挂 LOCAL

//---------------- 分段计时 ----------------
auto t0 = clock();
//... 要测的代码 ...
cerr << "seg1 " << 1.0 * (clock() - t0) / CLOCKS_PER_SEC << "s\n";

//---------------- 越界定位 ----------------
//本地把 a[i] 换成 a.at(i): 越界抛 std::out_of_range, gdb 的 catch throw 给行号
//-D_GLIBCXX_ASSERTIONS: 轻量, 查 vector/string 的 [] 越界
//-D_GLIBCXX_DEBUG: 很重, 能查迭代器失效(边遍历边 push_back 这种)

//---------------- 二分注释法(一个工具都没有时) ----------------
//把 solve() 后半段包进 #if 0 ... #endif, 崩不崩决定 bug 在前半还是后半
//重复 log n 次即可定位到具体几行, 比读代码快
