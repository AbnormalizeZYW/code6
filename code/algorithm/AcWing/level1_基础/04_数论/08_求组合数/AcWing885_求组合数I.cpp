#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2010, mod = 1e9 + 7;
int c[N][N];

// C(6,2) = 6*5/2*1 = 6!/2!*(6-2)! = 6!/2!*4! = 15 
// c[i][j] 实际含义是从 a 中选出 b 个的所有方案数
// 第一大类:包含物品的所有方案数, 第二大类:不包含物品的所有方案数
// 包含: c[i - 1][j - 1]:从剩下 a-1 个物品中选出 b-1 个
// 不包含: c[i - 1][j]: 从剩下 a-1 个物品中选出 b 个
// c[i][j] = c[i - 1][j] + c[i - 1][j - 1]
// 所有方案数 = 选择和不选择
void init()
{
    for (int i = 0; i < N; ++ i )
        for (int j = 0; j <= i; ++ j )  // j 永远不会大于 i, 例: 当 i = 6, j <= 6, 遍历总方案数 
            if (!j) c[i][j] = 1;        // 从 i 个物品中选 0 个物品只有 1 中方案
            else c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
}

int main()
{
    int n; scanf("%d", &n);
    init();
    while (n -- )
    {
        int a, b; scanf("%d%d", &a, &b);
        printf("%d\n", c[a][b]);
    }
    return 0;
}