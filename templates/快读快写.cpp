//快读快写: fread 整块读入 + 缓冲输出, 大量 IO 时比 cin/scanf 快数倍
//用法: read(n); read(x); write(ans); writeln(); flush();
//     多组数据读到文件尾即停: while(read(n)) { ... }   (read 返回是否成功)
//注意: 不能与 cin/scanf/cout/printf 混用; 支持负数; 读字符串会跳过空白
//配套: 常用宏定义缩写见 常用宏定义.cpp

char buf[1 << 22], *p1 = buf, *p2 = buf;               //输入缓冲, 1<<22 = 4MB, 可按需调大

inline char gc() {                                     //取一个字符; 缓冲空则整块 fread
    if(p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, 1 << 22, stdin);
        if(p1 == p2)    return EOF;
    }
    return *p1++;
}

inline bool read(int& x) {                             //读 int, 返回是否成功(文件尾返回 false)
    char c = gc();
    while(c <= ' ' && c != EOF)    c = gc();           //跳过空白; c<=' ' 同时覆盖 \n \r \t
    if(c == EOF)    return false;
    bool neg = (c == '-');
    if(neg)    c = gc();
    x = 0;
    while(c > ' ') {                                   //读到空白即结束
        x = x * 10 + (c - '0');
        c = gc();
    }
    if(neg)    x = -x;
    return true;
}

inline bool read(ll& x) {                              //读 ll, 逻辑同上
    char c = gc();
    while(c <= ' ' && c != EOF)    c = gc();
    if(c == EOF)    return false;
    bool neg = (c == '-');
    if(neg)    c = gc();
    x = 0;
    while(c > ' ') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    if(neg)    x = -x;
    return true;
}

inline bool read(char& c) {                            //读单个非空白字符
    c = gc();
    while(c <= ' ' && c != EOF)    c = gc();
    return c != EOF;
}

inline bool read(string& s) {                          //读字符串(跳过前导空白, 到空白为止)
    char c = gc();
    while(c <= ' ' && c != EOF)    c = gc();
    if(c == EOF)    return false;
    s.clear();
    while(c > ' ') {
        s.push_back(c);
        c = gc();
    }
    return true;
}

//---------------- 快写: 先写缓冲, 满/结束时 flush 一次输出 ----------------
char out[1 << 22];
int out_pos = 0;

inline void flush() {                                  //把缓冲刷到 stdout(程序结束前必须调用一次)
    if(out_pos) {
        fwrite(out, 1, out_pos, stdout);
        out_pos = 0;
    }
}

inline void putc(char c) {
    if(out_pos == (1 << 22))    flush();
    out[out_pos++] = c;
}

inline void write(int x) {
    if(x < 0) {
        putc('-');
        x = -x;
    }
    if(x >= 10)    write(x / 10);
    putc(x % 10 + '0');
}

inline void write(ll x) {
    if(x < 0) {
        putc('-');
        x = -x;
    }
    if(x >= 10)    write(x / 10);
    putc(x % 10 + '0');
}

inline void write(char c) { putc(c); }

inline void write(const string& s) {
    for(char c : s)    putc(c);
}

inline void writeln() { putc('\n'); }                  //换行

//多参数连续输出: write(a); putc(' '); write(b); writeln();  (空格/换行自己控制最灵活)
//配套: 输出浮点数用 snprintf 到 char tmp[] 再 write(tmp): char tmp[64]; snprintf(tmp, 64, "%.6f", x);
