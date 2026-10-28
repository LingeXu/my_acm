#手调技巧(命令篇): 用工具定位错误, 不靠盯代码
#流程: 复现 -> 缩小输入 -> 让工具指出位置 -> 再问为什么
#四个正交手段: sanitizer / 断言 / gdb / 随机对拍

#---------------- 编译选项对照(本地专用) ----------------
#-g                                符号信息; 没有它 gdb/ASan 都给不出行号
#-fsanitize=address                堆/栈越界, use-after-free, 栈溢出
#-fsanitize=undefined              有符号溢出/除零/非法移位/空指针解引用
#-fno-sanitize-recover=all         第一次 UB 就 abort(默认打印后继续跑)
#-D_GLIBCXX_ASSERTIONS             vector/string 的 [] 越界(轻量, 本地常开)
#-D_GLIBCXX_DEBUG                  迭代器失效/容器越界(很重, 只本地用)
#-ftrivial-auto-var-init=pattern   未初始化变量填脏值, 结果不再随机(GCC 12+)
#-Wall -Wextra -Wshadow            常见笔误 + 变量遮蔽

#推荐"调试编译"(慢 2~3 倍、内存涨 2~3 倍, 只查错不测时限):
g++ -std=c++17 -g -O1 -fsanitize=address,undefined \
    -fno-omit-frame-pointer -D_GLIBCXX_ASSERTIONS -Wall -Wextra -o a a.cpp

#---------------- 段错误 第 1 步: sanitizer(命中率最高) ----------------
g++ -std=c++17 -g -O1 -fsanitize=address -o a a.cpp && ./a < in.txt
#输出只看两处:
#  #0 ... in main /home/icpc/a.cpp:7:23      <- 越界发生在这行
#  allocated by thread T0 ... a.cpp:4:20     <- 谁申请的这块内存
#两者对不上 = 数组开小 / 写越界
#顺带能抓: stack-overflow(深递归), heap-use-after-free, global-buffer-overflow

#---------------- 段错误 第 2 步: gdb 一行流 ----------------
g++ -std=c++17 -g -O0 -o a a.cpp
gdb -q -batch -ex 'run < in.txt' -ex 'bt' -ex 'frame 0' -ex 'info locals' ./a

#---------------- 段错误 第 3 步: core dump ----------------
#注意: Ubuntu 常把 core 交给 apport, 找不到 core 就直接回第 1/2 步
ulimit -c unlimited
./a < in.txt                      #崩了会留 core
gdb ./a core                      #然后 bt

#---------------- 段错误 第 4 步: 一个工具都没有时 ----------------
#1. cerr 打点(cerr 每行 flush, 崩了也不丢), 看停在哪两行之间
#2. 二分注释: 后半段包进 #if 0 ... #endif, 崩不崩决定 bug 在前还是后
#3. vector 的 [] 临时换 .at(): 越界抛 std::out_of_range, 配 catch throw 给行号
#   用法: gdb -q -batch -ex 'catch throw' -ex run -ex bt ./a
#4. -D_GLIBCXX_ASSERTIONS: 多数越界当场 abort 并报行号

#---------------- gdb 够用版 ----------------
#break a.cpp:42            下断点; b solve 按函数名下
#run < in.txt              跑; Ctrl+C 打断死循环
#bt / bt full              调用栈(崩了第一件事)
#frame 2 / f 2             切栈帧
#info locals / p i         看变量; p a[3] 看数组元素
#p v / p *it               看容器/迭代器
#watch i                   i 被改时停(抓谁改坏了它)
#next / step / finish      单步 / 进函数 / 出函数
#until 50                  跑到第 50 行
#list / disas              源码 / 汇编
#continue / kill / quit    继续 / 终止 / 退出

#---------------- 死循环 / TLE ----------------
timeout 2 ./a < in.txt            #退出码 124 = 超时
#gdb 里 run 后按 Ctrl+C -> bt, 直接看卡在哪个循环
/usr/bin/time -v ./a < in.txt > /dev/null   #耗时 + 内存峰值
#分段计时(代码里): auto t0 = clock(); ...; cerr << 1.0*(clock()-t0)/CLOCKS_PER_SEC;

#---------------- 对拍(WA 最强武器) ----------------
#gen 用 mt19937 或 python 写; 小数据 n<=8 最容易暴露逻辑错
#!/bin/bash
g++ -O2 -std=c++17 -o gen gen.cpp
g++ -O2 -std=c++17 -o brute brute.cpp
g++ -O2 -std=c++17 -o a a.cpp
for i in $(seq 1 2000); do
    ./gen > in.txt
    ./brute < in.txt > o1.txt
    timeout 2 ./a < in.txt > o2.txt || { echo "RE $i"; cp in.txt fail.txt; break; }
    diff -w o1.txt o2.txt > /dev/null || { echo "WA $i"; cp in.txt fail.txt; break; }
done
#失败立刻存 fail.txt, 再用 gdb/ASan 在 fail.txt 上跑: ./a < fail.txt

#---------------- 边界数据手测清单 ----------------
#n=1, n=2, 全相同, 已排序/逆序, 含 0 与负数, 1e9/1e18 附近(溢出)
#图: 不连通/重边/自环/单点; 字符串: 全同/空/单字符; 多测: 1 组与 1000 组

#---------------- RE / MLE 常见成因 ----------------
#RE 随机: 数组开小(最常见), n 与 MAXN 对不上, 多测没重置
#RE 必现 + 深递归: 栈溢出 -> ulimit -s unlimited 或改迭代; ASan 报 stack-overflow
#RE: 除零/模零, 负数下标 v[-1], 整数溢出
#结果随机: 未初始化变量 -> valgrind memcheck 或 -ftrivial-auto-var-init=pattern
#MLE: /usr/bin/time -v 看峰值; vector 反复 push_back 的容量翻倍; 多测没清
#本地过 OJ 挂: 本地用 -O2 复现(UB 常在优化后显形), 再上 UBSan
#            然后查 long long / 多测清空 / 数组上限 / 输出格式

#---------------- 交互题 ----------------
#每次输出后必须 flush: cout << x << endl; 或 cout.flush(), 否则互相等 -> TLE
#调试信息一律写 stderr, stdout 只放正式交互内容
