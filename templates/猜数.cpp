//猜数(交互题二分): 在 [l, r] 内猜一个数, 评测机返回 -1(大了)/0(猜中)/1(小了)
//注意: 交互题不能快读快写/关闭同步, 每次输出后必须 flush(cout << endl 自带 flush)
while(l <= r) {
    int mid = l + ((r - l) >> 1);
    cout << "? " << mid << endl;
    int resp;
    cin >> resp;
    if(resp == 0) {
        cout << "! " << mid << endl;
        return 0;
    }   
    else if(resp == -1) r = mid - 1;
    else    l = mid + 1;
}
cout << "! " << l << endl;