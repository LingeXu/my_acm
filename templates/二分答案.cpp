//二分答案: 答案单调(能 check 通过则更大的/更小的也通过)时, 在值域上二分
//"求最小可行值"模板: check(mid) 通过则收缩右界; 求最大可行值方向相反
//需预定义: bool check(int mid);  (判定"mid 是否可行", 常配贪心/前缀和)
int Left = 0, Right = 1e9;
int ans = -1;
while(Left <= Right) {
    int mid = Left + (Right - Left) / 2;
    if(check(mid)) {
        ans = mid;
        Right = mid - 1;    //是Right = Mid - 1还是Left = Mid + 1视具体情况而定
    }
    else    Left = mid + 1;
}