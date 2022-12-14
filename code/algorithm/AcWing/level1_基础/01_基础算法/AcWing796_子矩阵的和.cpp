// https://www.acwing.com/problem/content/798/
//
// s[i,j] 含义: 从这个点起左上角所有数的和
// 
//  __|__|__|__|__
//	__|__|__|__|__
//	__|ij|__|__|__
//	__|__|__|__|__
//	  |  |  |  |
// 
// 1) s[i,j] 如何计算
//	  公式: S[i][j] = S[i-1,j] + S[i,j-1] - S[i-1,j-1] + a[i,j] 
//		   S[i-1,j]   (上面格子为起点前缀和)
//         S[i,j-1]   (以加左格子起点的前缀和)
//		   S[i-1,j-1] (减去左斜上角前缀和) -> 因为加过重复的
//         a[i,j]     (加上点上的数)
//  
//     1  2  3  4  5
//   __|__|__|__|__|
// 1
//   __|__|__|__|__|
// 2   
//   __|__|__|__|__|
// 3   |  |  |        左上角: (3,2) 
//   __|__|__|__|__|  右下角: (5,3)
// 4   |  |  |
//	 __|__|__|__|__|
// 5   |  |  |
//   __|__|__|__|__|
// 6   
//   __|__|__|__|__|
//  
// 
// 2) (x1,y1), (x2,y2) 这一子矩阵所有数的和该如何计算 ?
//    公式 : S[x2, y2] - S[x1-1, y2] - S[x2, y1-1] + S[x1-1, y1-1] 
//    
//    -S[x1-1,y2]   (减去右上角前缀和)
//    -S[x2,y1-1]   (减去左下角前缀和)
//    +S[x1-1,y1-1] (加回左上角前缀和)

#include <iostream>

using namespace std;

const int N = 1010;

int s[N][N];

int main()
{
    int n, m, q;
    scanf("%d%d%d", &n,&m,&q);
    
    for (int i = 1; i <= n; ++ i )
        for (int j = 1; j <= m; ++ j )
            scanf("%d", &s[i][j]);
    
    // 初始化前缀和数组
    for (int i = 1; i <= n; ++ i )
        for (int j = 1; j <= m; ++ j )
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + s[i][j];
    
    // 询问
    while (q -- )
    {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        printf("%d\n", s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1]);
    }
    
    return 0;
}