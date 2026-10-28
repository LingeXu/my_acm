//常用宏定义: 缩写速查, 放头文件与 using namespace std 之后
//注意: 各模板的 #define N / #define M / #define INF 与这里重复时删掉一处;
//      fi/se 与结构体字段名冲突时删掉 fi/se 那两行

//---------------- 类型别名 ----------------
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;

//---------------- 常用常量 ----------------
#define INF 0x3f3f3f3f             //约 1e9, memset(a, 0x3f, sizeof(a)) 可初始化成它
#define INFLL 0x3f3f3f3f3f3f3f3fLL //约 4.5e18, 同理 memset
#define MOD 1000000007
#define MOD2 998244353

//---------------- 容器缩写 ----------------
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define fi first                  //pair 成员
#define se second

//---------------- 循环宏(可读性 vs 调试信息, 比赛常用) ----------------
//注意: 循环体里用逗号表达式/宏展开出逗号时, rep 宏会把逗号后的内容吞进边界, 谨慎使用
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define rep0(i, n) for(int i = 0; i < (n); i++)
#define per(i, a, b) for(int i = (a); i >= (b); i--)
#define trav(it, v) for(auto it = (v).begin(); it != (v).end(); it++)
#define forr(x, v) for(auto& x : (v))

//---------------- 最值/杂项 ----------------
#define ckmax(a, b) ((a) < (b) ? (a) = (b) : (a))     //a = max(a, b), 需保证 a 无副作用
#define ckmin(a, b) ((a) > (b) ? (a) = (b) : (a))
#define abs(x) ((x) < 0 ? -(x) : (x))                //与 cmath 冲突时二选一

//---------------- 调试 ----------------
//#define LOCAL              //本地评测时取消注释, 提交前注释掉
#ifdef LOCAL
#define debug(x) cerr << #x << " = " << (x) << endl;
#define debug2(x, y) cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#else
#define debug(x)
#define debug2(x, y)
#endif

//---------------- 可选: 全局开 long long ----------------
//CF 上流行的 "#define int long long" + "signed main()":
//优点: 不用区分 int/ll 溢出;  缺点: 内存翻倍、vector<int> 等 STL 会报错需全改 ll
////#define int long long
//signed main() { ... }          //此时 main 用 signed, 因为 int main 会被宏替换
