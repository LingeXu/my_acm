//交互题裁判: 管道式本地评测机, 把你的提交程序当子进程跑, 模拟 CF 交互器, 提交代码零改动
//用法:
//  g++ -std=c++17 -O2 sol.cpp -o sol                // 编译提交程序(一行都不用改)
//  g++ -std=c++17 -O2 交互题本地裁判.cpp -o judge
//  ./judge ./sol < test.txt                          // test.txt 格式见"按题修改 1"
//  ./judge ./sol < test.txt 2>trace.txt              // 完整对话在 stderr(TRACE=1 时)
//  调试建议: g++ -g -fsanitize=address,undefined sol.cpp -o sol   // 段错误/越界直接定位
//能抓的四类错: 没 flush 卡死 / 查询超限 / 非法查询 / 答案错误; 程序 cerr 原样上屏, 可断点
//若对话突然卡住不动: 基本是程序忘了 flush(endl 换成 '\n' 忘了加)或死循环, Ctrl+C 即可
//批量随机对拍: 用同目录的 交互题对拍.py(同协议批量裁判, 失败自动存回放文件)
//通用部分(直接抄): 建管道/fork, 逐行读写协议, -1 与超限惯例, 崩溃与挂起检测
//按题修改: 1 输入格式 / 2 模拟与响应 / 3 答案校验, 以 CF2134E Power Boxes 为例

#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

const int TRACE = 1;    // 1: 把双方每行对话打到 stderr; 0: 只打印判题结果

//---------------- 按题修改 1: 测试文件格式与隐藏数据 ----------------
//test.txt(裁判自己的 stdin, 不发给程序):
//  t
//  每组一行: n  a[1] a[2] ... a[n]      // a 是隐藏答案, 裁判用来模拟与判答案
//例(CF2134E, t=2):
//  2
//  3 2 1 2
//  4 1 1 2 2
struct Case {
    int n;
    vector<int> a;         // 原始答案(1-indexed), 最后判 "!" 时比较
    vector<int> arr;       // 当前排列(1-indexed), swap 永久生效
    int limit, used;
    Case(int n_, vector<int> a_) : n(n_), a(a_), arr(a_), limit((3 * n_ + 1) / 2), used(0) {
        //limit = ceil(3n/2): CF2134E 每组查询上限
    }
};

//---------------- 按题修改 2: 每条指令的模拟 ----------------
//合法指令(参数已检查): 返回需要回写的响应; 空串 = 无响应(程序不会读, 什么都不写)
string simulate(Case& st, const string& op, int x) {
    if(op == "swap") {
        swap(st.arr[x], st.arr[x + 1]);
        return "";
    }
    //throw x: 球从 x 出发, 每次向前跳当前盒子的能量, 返回总跳跃次数
    int pos = x, jumps = 0;
    while(pos <= st.n) { pos += st.arr[pos]; jumps++; }
    return to_string(jumps);
}

//---------------- 按题修改 3: 判 "!" 答案 ----------------
//got 是程序给出的 1..n(原始位置)的答案, 与隐藏 a 比较
bool check_answer(Case& st, const vector<int>& got) {
    return got == st.a;
}

//---------------- 通用: 管道框架(直接抄, 不用改) ----------------
int main(int argc, char** argv) {
    if(argc < 2) {
        fprintf(stderr, "用法: %s <提交程序二进制> < test.txt\n", argv[0]);
        return 2;
    }

    //1. 两根管道: p2c 裁判->程序(stdin), c2p 程序->裁判(stdout); stderr 原样继承
    int p2c[2], c2p[2];
    pipe(p2c); pipe(c2p);
    pid_t pid = fork();
    if(pid < 0) { perror("fork"); return 2; }
    if(pid == 0) {                                   // 子进程: 管道接到 stdin/stdout 再 exec
        dup2(p2c[0], STDIN_FILENO);
        dup2(c2p[1], STDOUT_FILENO);
        close(p2c[0]); close(p2c[1]); close(c2p[0]); close(c2p[1]);
        execl(argv[1], argv[1], (char*)nullptr);
        perror("execl");                             // 跑不到这里 = 路径/权限错误
        _exit(127);
    }
    close(p2c[0]); close(c2p[1]);
    FILE* fin  = fdopen(c2p[0], "r");                // 读程序 stdout(阻塞读行, 等价评测机)
    FILE* fout = fdopen(p2c[1], "w");                // 写程序 stdin
    if(!fin || !fout) { perror("fdopen"); return 2; }

    //2. 读测试文件(裁判自己的 stdin, 与子进程无关)
    int t;
    if(scanf("%d", &t) != 1) { fprintf(stderr, "judge: 读测试文件失败\n"); return 2; }

    char line[65536];                                // 按题调整: 答案行很长时加大
    int cases_ok = 0;
    bool failed = false;

    //3. 先写测试文件头(CF 惯例第一行是 t; 无 t 的题删掉这行, 格式按题改)
    fprintf(fout, "%d\n", t);
    fflush(fout);

    for(int tc = 1; tc <= t && !failed; tc++) {
        //---------------- 按题修改 1b: 读本组隐藏数据, 并把本组输入发给程序 ----------------
        int n;
        scanf("%d", &n);
        vector<int> a(n + 1);
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        Case st(n, a);
        fprintf(fout, "%d\n", n);                    // 程序读到的本组输入(每题格式不同)
        fflush(fout);
        if(TRACE) fprintf(stderr, "[case %d] judge> %d\n", tc, n);

        //---------------- 通用: 本组对话循环 ----------------
        bool answered = false;
        while(!failed && !answered) {
            if(!fgets(line, sizeof line, fin)) {     // EOF: 没给答案就退出了
                fprintf(stderr, "case %d: 程序提前退出(EOF), 判负\n", tc);
                failed = true; break;
            }
            string s = line;
            while(s.size() && (s.back() == '\n' || s.back() == '\r')) s.pop_back();
            if(s.empty()) continue;
            if(TRACE) fprintf(stderr, "[case %d] sol> %s\n", tc, s.c_str());

            stringstream ss(s);
            string op;
            ss >> op;
            if(op == "!") {
                vector<int> got(n + 1);
                bool ok = true;
                for(int i = 1; i <= n; i++)
                    if(!(ss >> got[i])) ok = false;
                if(!ok) {
                    fprintf(stderr, "case %d: ! 后面数字数量/格式不对\n", tc);
                    fprintf(fout, "-1\n"); fflush(fout);
                    failed = true; break;
                }
                answered = true;
                if(check_answer(st, got)) {
                    fprintf(stderr, "case %d: OK (查询 %d 次, 上限 %d)\n", tc, st.used, st.limit);
                    cases_ok++;
                } else {
                    fprintf(stderr, "case %d: WA, 答案与隐藏数据不符\n", tc);
                    failed = true;
                }
            } else {
                int x;
                if(!(ss >> x)) {                     // 无法解析的输出
                    fprintf(stderr, "case %d: 无法解析: %s\n", tc, s.c_str());
                    fprintf(fout, "-1\n"); fflush(fout);
                    failed = true; break;
                }
                //计数与超限(评测机惯例: 超限回 -1 并结束; 哪些操作计入次数按题确认)
                if(++st.used > st.limit) {
                    fprintf(stderr, "case %d: 查询超限(%d > %d), 回 -1\n", tc, st.used, st.limit);
                    fprintf(fout, "-1\n"); fflush(fout);
                    failed = true; break;
                }
                //---------------- 按题修改 2b: 参数合法性 ----------------
                bool valid = (op == "throw" && 1 <= x && x <= n)
                          || (op == "swap"  && 1 <= x && x <= n - 1);
                if(!valid) {
                    fprintf(stderr, "case %d: 非法查询 %s %d, 回 -1\n", tc, op.c_str(), x);
                    fprintf(fout, "-1\n"); fflush(fout);
                    failed = true; break;
                }
                //模拟并回写(无响应的指令不写, 程序那边不会读)
                string resp = simulate(st, op, x);
                if(resp.empty()) {
                    if(TRACE) fprintf(stderr, "[case %d] judge> (无响应)\n", tc);
                } else {
                    fprintf(fout, "%s\n", resp.c_str());
                    fflush(fout);                    // 管道是全缓冲, 必须 flush!
                    if(TRACE) fprintf(stderr, "[case %d] judge> %s\n", tc, resp.c_str());
                }
            }
        }
    }

    //---------------- 通用: 收尾(防子进程挂起把裁判拖死) ----------------
    if(!failed) {
        int status = 0;
        bool exited = false;
        for(int i = 0; i < 100; i++) {               // 判完后最多等 ~2 秒
            if(waitpid(pid, &status, WNOHANG) == pid) { exited = true; break; }
            usleep(20000);                           // <unistd.h>, POSIX(macOS/Linux 都有)
        }
        if(exited) {
            if(WIFSIGNALED(status))
                fprintf(stderr, "judge: 程序被信号 %d 杀死(%s), 大概率段错误/除零\n",
                        WTERMSIG(status), strsignal(WTERMSIG(status)));
        } else {
            kill(pid, SIGKILL);
            waitpid(pid, nullptr, 0);
            fprintf(stderr, "judge: 判完后程序不退出(EOF 后死循环?), 已强杀\n");
        }
    } else {
        kill(pid, SIGKILL);                          // 已判负, 杀掉还在跑的程序
        waitpid(pid, nullptr, 0);
    }
    fprintf(stderr, failed ? "VERDICT: 失败(已 AC %d 组)\n" : "VERDICT: 全部通过(%d 组)\n", cases_ok);
    return failed ? 1 : 0;
}
