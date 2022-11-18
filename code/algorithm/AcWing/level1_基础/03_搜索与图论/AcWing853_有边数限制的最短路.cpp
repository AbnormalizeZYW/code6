// 问题:
// 给定一个 n 个点 m 条边的有向图, 图中可能存在重边和自环, 边权可能为负数
// 请你求出从 1 号点到 n 号点的最多经过 k 条边的最短距离, 如果无法从 1 号点走到 n 号点, 输出 impossible
// 
// for 循环 n 次
//	   for 遍历所有边 {a,b,w} (a -> b 的所有边, 权重是 w)
//		   循环的时候遍历所有边
//		   dist[b] = min(dist[b], dist[a] + w)		
//		   
// 该算法证明了所有 dist[b] <= dist[a] + w -> 三角不等式  
// 
// 
// 如果有最短路的话, 那么负权回路是不一定存在的
// 如果有负权回路的话, 那么最短路是不一定存在的
// 如果负环不在 1~n 号点的路径上那就不影响, 负环在 1~n 号点某一路径当中的时候, 才会影响
// 一圈的回路是 < 0, 就会越更新越小
// 
// 如果第 n 次迭代后又更新某些边, 因为有 n 个点就有 n-1 条边, 所以, 根据抽屉原理
// n 次迭代后还有第 n 条边, 那么就存在环
// 
// 存在一条最短路径, 最短路径的边是个数 >= n
// 
// 如果限制了最短路经过边的个数的话是否有负环也就无所谓了
// 
// 类似问题: 有飞往 1~N 点的飞机, 每一次换乘, 乘客的心情都会下降, 求 1~N 的距离  
// 
// bellman_ford: 每次循环暴力枚举每一条边
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 510, M = 10010;

int n, m, k;
int dist[N], backup[N];

struct Edge
{
    int a, b, w;
}edges[M];

// 为什么要备份
//   1    1
// 1 -> 2 -> 3
// |_________|
//     w:3
// 假设求 1~3 号点的距离, 但是最短路径不能超过一条, 所以只有 1~3 号点直接走
// 但是每次循环每条边都更新, 所以会导致, 1->2->3 的边被更新成 2
// 所以最短路径就变成 2, 但其实一次更新, 更新了两条边
// 因为会用更新了的边去更新下一条边, 所以备份可以保证只使用上次迭代的结果
// 简单来说, 如果不备份更新到的边就不止相邻边了
// 3 3 1

// 1 2 1
// 2 3 1
// 1 3 3
// 
//   1     1
// 1 -> 2 -> 3
//  \   | 1 
// 3 \  v
//      3

int bellman_ford()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    // 求不经过超过 k 条边, 迭代 k 次
    for (int i = 0; i < k; ++ i )
    {
        // 每次在新的迭代前, 备份一下 dist 数组 -> backup
        memcpy(backup, dist, sizeof dist);
        for (int j = 0; j < m; ++ j )
        {
            // edges[i]:第 i 条边
            int a = edges[j].a, b = edges[j].b, w = edges[j].w;
            // b : a连接出去的边, a : 点 + w = a->b 的距离 
            dist[b] = min(dist[b], backup[a] + w);
        }
    }
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    
    for (int i = 0; i < m; ++ i )
    {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        edges[i] = {a, b, w};
    }
    bellman_ford();
    // 负权边, 可能两点 
    if (dist[n] > 0x3f3f3f3f / 2) puts("impossible");
    else printf("%d\n", dist[n]);
    return 0;
}