// 什么是最大匹配 ?
// 要了解匈牙利算法必须先理解下面的概念:
//  匹配: 在图论中, 一个「匹配」是一个边的集合, 其中任意两条边都没有公共顶点
//  最大匹配: 一个图所有匹配中, 所含匹配边数最多的匹配, 称为这个图的最大匹配
// 下面是一些补充概念:
//  完美匹配: 如果一个图的某个匹配中, 所有的顶点都是匹配点, 那么它就是一个完美匹配
//  交替路: 从一个未匹配点出发, 依次经过非匹配边, 匹配边, 非匹配边… 形成的路径叫交替路
//  增广路: 从一个未匹配点出发, 走交替路, 如果途径另一个未匹配点(出发的点不算), 则这条交替 路称为增广路(agumenting path)

#include <iostream>
#include <cstring>

using namespace std;

const int N = 510, M = 100010;

int n1, n2, m;
int h[N], ne[M], e[M], idx;
bool st[N];
int match[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

int find(int x)
{
    // 遍历所有邻点
    for (int i = h[x]; i != -1; i = ne[i])
    {
        int j = e[i];   
        if (!st[j])     // 如果这一轮模拟匹配中, 这个点尚未被预定
        {
            st[j] = true;   // x 就预定这个 j
            if (!match[j] || find(match[j]))    // 如果 j 没有匹配, 或 j 还可以匹配其他点, 配对成功
            {
                match[j] = x;
                return true;
            }
        }
    }
    // 全部都被预定了, 配对失败
    return false;
}

int main()
{
    memset(h, -1, sizeof h);
    scanf("%d%d%d", &n1, &n2, &m);
    while (m -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
    }

    int res = 0;
    for (int i = 1; i <= n1; ++ i )
    {
        memset(st, false, sizeof st);   // 因为每次模拟匹配的预定情况都是不一样的所以每轮模拟都要初始化
        if (find(i)) ++ res; 
    }
    
    printf("%d\n", res);
    return 0;
}   