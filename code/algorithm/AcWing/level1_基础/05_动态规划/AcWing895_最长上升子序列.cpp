

// 给定一个长度为 N 的数列, 求数值严格单调递增的子序列的长度最长是多少
// 数据范围:
// 1 ≤ N ≤ 1000
// −10^9 ≤ 数列中的数 ≤ 10^9
//
// 状态表示: 在符合递增的情况下, 求每个以 i 位置结尾的值的能扩到的子序列长度
//     属性: max
//     集合: 划分为 i 组     
// 状态计算: if (a[i] > a[j]) f[i] = max(f[i], f[j] + 1) 
// 时间复杂度: O(n^2)
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010, INF = 1e9;

int n;
int a[N];
int f[N];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++ i ) cin >> a[i];
    
    for (int i = 0; i <= n; ++ i ) f[i] = -INF;
    
    for (int i = 1; i <= n; ++ i )
    {
        f[i] = 1; 
        for (int j = 1; j < i; ++ j )
            if (a[i] > a[j]) f[i] = max(f[i], f[j] + 1);    
        // f[i]: 以 i 结尾的最长递增子序列
        // f[j]+1: 以 j 结尾的最长递增子序列
        // 为什么要求 max: 
        //     - 如果不求 max, 在 a[i] > a[j] 的情况下, 如果自己的递增子序列是最长的
        //       但是后面又出现了 a[i] > a[j], 但是这个 a[j] 的子序列并不是最长, 
        //       那么自己的就会被更新掉          
    }

    int ans = f[1];
    for (int i = 2; i <= n; ++ i ) ans = max(ans, f[i]);

    cout << ans << endl;
    return 0;
}