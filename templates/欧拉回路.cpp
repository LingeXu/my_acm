//欧拉回路/路径: Hierholzer 算法, O(n + m)
//判定(无向图): 欧拉回路 <=> 连通且所有点度数为偶;  欧拉路径(非回路) <=> 连通且恰有两个奇度点
//判定(有向图): 欧拉回路 <=> 基图连通且每点入度 = 出度;  路径 <=> 恰有一对 (出-入=1, 入-出=1) 的点
//需预定义: 链式前向星存图(见 Dinic.cpp 的存法);  int vis_edge[2 * M];  起点 s
//注意: 无向图走一条边要标记正反两条(vis_edge[i] = vis_edge[i ^ 1] = 1); 结果 vector 里是逆序

vector<int> path;                          //结果路径(逆序: 终点在前), 最后 reverse 一下

void dfs(int u) {                          //Hierholzer: 有边就走, 走完的边删掉
    for(int& i = head[u]; i; i = e[i].next) {          //i 是引用: 相当于删边走(当前弧)
        if(vis_edge[i])    continue;
        vis_edge[i] = vis_edge[i ^ 1] = 1;             //标记正反向边(有向图只标 i)
        int v = e[i].to;
        dfs(v);
    }
    path.push_back(u);                     //回溯时记录 = 逆序, 结束时 reverse
}
//调用: dfs(s); reverse(path.begin(), path.end());
//      欧拉路径且需要字典序最小: 对每个点的出边排序, 或权值小优先的堆优化
//配套:
//1. 无向图欧拉路径起点: 任取一个奇度点(回路则任取); 有向图: 出-入=1 的点
//2. 判定连通性: 并查集或从 s dfs 后检查 vis_edge 是否覆盖所有有边的点
//3. 混合图(有向+无向边)欧拉回路: 无向边定向后调整入出度, 网络流判定, 区域赛少见
