//floyd: 全源最短路, O(n^3); k 必须放最外层(前 k 个点作中转点的阶段划分)
//需预定义: int dist[N][N];  初始化: dist[i][i] = 0, 有边赋权, 其余 INF
int dist[N][N];
void floyd() {
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                if(dist[i][k] != INF && dist[k][j] != INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}