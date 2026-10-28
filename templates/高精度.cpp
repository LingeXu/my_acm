//高精度: 大整数十进制 vector 存储(低位在前), 支持加法/减法/乘法; 除法较复杂不常考
//适用: 无模数且答案超出 64 位的题目(如大斐波那契、大组合数)
//注意: 能取模就取模, 高精度是最后手段; 也可用 __int128(128 位, 支持 +-*/% 比较)
//需预定义: 无(传入 vector<int> a 表示数, a[0] = 最低位);  返回同格式
//注意: 输入/输出需辅助函数: 字符串转 vector, 输出倒序

vector<int> big_from_string(const string& s) {     //"123" -> {3, 2, 1}
    vector<int> a(s.size());
    for(int i = 0; i < (int)s.size(); i++)    a[s.size() - 1 - i] = s[i] - '0';
    return a;
}

void big_print(const vector<int>& a) {             //输出, 0 要特判
    if(a.empty())    cout << 0;
    for(int i = a.size() - 1; i >= 0; i--)    cout << a[i];
}

vector<int> big_add(const vector<int>& a, const vector<int>& b) {
    vector<int> c;
    int carry = 0;
    for(int i = 0; i < max(a.size(), b.size()) || carry; i++) {
        if(i < (int)a.size())    carry += a[i];
        if(i < (int)b.size())    carry += b[i];
        c.push_back(carry % 10);
        carry /= 10;
    }
    return c;
}

//a >= b 返回 true(都为非负)
bool big_ge(const vector<int>& a, const vector<int>& b) {
    if(a.size() != b.size())    return a.size() > b.size();
    for(int i = a.size() - 1; i >= 0; i--)
        if(a[i] != b[i])    return a[i] > b[i];
    return true;
}

vector<int> big_sub(const vector<int>& a, const vector<int>& b) {   //a >= b, 结果非负
    vector<int> c = a;
    for(int i = 0; i < (int)b.size(); i++) {
        c[i] -= b[i];
        if(c[i] < 0) {                          //借位
            c[i] += 10;
            c[i + 1]--;
        }
    }
    while(c.size() > 1 && c.back() == 0)    c.pop_back();   //去前导零
    return c;
}

vector<int> big_mul(const vector<int>& a, const vector<int>& b) {   //朴素 O(n*m), n <= 5000 可接受
    vector<int> c(a.size() + b.size());
    for(int i = 0; i < (int)a.size(); i++) {
        int carry = 0;
        for(int j = 0; j < (int)b.size(); j++) {
            int t = c[i + j] + a[i] * b[j] + carry;
            c[i + j] = t % 10;
            carry = t / 10;
        }
        c[i + b.size()] += carry;              //逐位进位写法, 避免中间溢出
    }
    while(c.size() > 1 && c.back() == 0)    c.pop_back();
    return c;
}
//配套:
//1. 高精度乘低精度(int): 每一位乘 x 再统一进位, O(n)
//2. 高精度除法: 二分答案 + 乘法验算, 或逐位试商(复杂); 优先用 __int128 或取模
//3. 压位(每 9 位存一个 int)可大幅提速, 区域赛用到再说
