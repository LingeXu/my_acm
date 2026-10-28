#Linux环境速查: 比赛机(Ubuntu/GNOME)的窗口、复制粘贴与终端命令
#原则: Tab 补全 / Ctrl+R 搜历史 / 选中即复制 + 中键粘贴, 这三条够用
#注意: 终端里 Ctrl+C 是"中断进程"不是复制; Ctrl+V 在终端里没用

#---------------- 先背这 6 个 ----------------
#Ctrl+Alt+T      打开终端
#Ctrl+Shift+V    终端里粘贴(或 Shift+Insert / 鼠标中键 / 右键菜单)
#Ctrl+Shift+C    终端里复制(更常用: 鼠标选中即复制)
#Ctrl+C          中断正在跑的程序
#Alt+F10         窗口最大化/还原(或双击标题栏)
#Super+Up        最大化; Super+Down 还原; Super+Left/Right 半屏

#---------------- 窗口与桌面(GNOME) ----------------
#Super                活动概览, 找窗口/启动器
#Alt+Tab              切窗口; Alt+F4 关闭; Alt+F9 最小化
#Alt+F7 / Alt+F8      移动窗口 / 调整大小(窗口跑出屏幕时救命)
#F11                  终端/浏览器/编辑器全屏
#PrtSc / Shift+PrtSc  全屏截图 / 选区截图(Alt+PrtSc 为当前窗口)
#Ctrl+Alt+F3~F6       切字符终端(图形卡死时); Ctrl+Alt+F1/F2 回图形
#Super+L              锁屏, 别手滑
#Ctrl+Shift+T         终端新标签; Ctrl+PageUp/Down 切标签
#KDE/XFCE 大同小异; 记不住就用鼠标: 双击标题栏 = 最大化, 拖到屏幕顶端也是

#---------------- 复制粘贴的四类场景 ----------------
#1. 浏览器/PDF -> 终端: 浏览器 Ctrl+C, 终端 Ctrl+Shift+V(最稳: Shift+Insert)
#2. 终端 -> 浏览器: 鼠标选中(自动进主选区) -> 浏览器中键; 或 Ctrl+Shift+C 再 Ctrl+V
#3. 终端 -> 终端: 同上
#4. 命令行取剪贴板: xclip -selection clipboard -o (X11) / wl-paste (Wayland)
#样例输入最快: 选中样例 -> 终端里点中键
#VSCode 终端: Ctrl+Shift+C/V; 没有选中时 Ctrl+C 仍是中断; 右键 Paste 一定行
#粘贴出 ^[[200~ : 终端 bracketed paste 不兼容, 换 Shift+Insert

#---------------- 位置与文件 ----------------
pwd                               #我在哪
ls -la                            #全部(含隐藏); ls -lh 看大小
cd /home/icpc                     #进目录; cd - 回上一个; cd ~ 回家; Tab 补全路径
mkdir -p a/b/c                    #建多层目录
cp -r dir1 dir2                   #复制目录
mv a.cpp b.cpp                    #改名/移动
rm -rf dir                        #删除! 先 ls 确认再回车
touch x.txt                       #建空文件
du -sh *                          #各文件/目录占多大
df -h                             #磁盘剩多少

#---------------- 看内容与找东西 ----------------
cat -n a.cpp                      #带行号看
less a.cpp                        #翻页: /搜索 n下一个 q退出
head -n 20 in.txt                 #前 20 行; tail -f 追日志
grep -rn "segfault" .             #递归搜文本
grep -c "1" out.txt               #数匹配行数
find . -name "*.cpp"              #按名字找文件
which g++                         #命令装在哪

#---------------- 文本处理(看输出/对拍用) ----------------
wc -l out.txt                     #行数
sort -n nums.txt                  #按数值排序; uniq -c 去重计数(先 sort)
diff -w o1.txt o2.txt             #忽略空白比较
sed -n '10,20p' a.cpp             #只打印 10~20 行
awk '{print $2}' f.txt            #取第 2 列

#---------------- 重定向与管道 ----------------
./a < in.txt > out.txt            #输入输出文件
./a 2> err.txt                    #只收 stderr
./a 2>&1 | tail -20               #错误一起看最后 20 行
./a | tee log.txt                 #同时显示并存文件

#---------------- 进程与历史 ----------------
ps aux | grep a                   #找进程
top                               #看 CPU/内存(htop 更好)
kill -9 12345                     #强杀; pkill -9 -f a.out 按名字强杀
jobs                              #后台任务; Ctrl+Z 挂起, bg/fg 切前后台
#Ctrl+R: 在终端里搜历史命令(先打关键字再按)

#---------------- 编译与计时 ----------------
g++ -std=c++17 -O2 -Wall -Wextra -o a a.cpp
./a < in.txt
./a                               #手动敲输入, 最后 Ctrl+D 结束
#耗时 + 内存峰值(看 Maximum resident set size):
/usr/bin/time -v ./a < in.txt > /dev/null
time ./a < in.txt                 #快速看 real/user/sys
ulimit -s unlimited               #放开栈(深递归); 不行就 ulimit -s 262144

#---------------- 卡死救援 ----------------
#程序死循环: Ctrl+C; gdb 里 Ctrl+C 再 bt
#终端刷屏停不下来: Ctrl+C; 乱了就 reset
#图形卡死: Ctrl+Alt+F3 登录 -> pkill -9 -f code -> Ctrl+Alt+F1/F2 回来
#窗口跑出屏幕: Alt+F7 拖回, 或 Super+↑

#---------------- 开赛 3 分钟自检 ----------------
g++ --version | head -1; gdb --version | head -1; python3 --version
#ASan 能不能用(本地查错全靠它):
echo 'int main(){return 0;}' > t.cpp
g++ -std=c++17 -O2 -g -fsanitize=address,undefined t.cpp -o t && ./t && echo "ASan OK"
/usr/bin/time -v true 2>&1 | grep Maximum
ulimit -s
