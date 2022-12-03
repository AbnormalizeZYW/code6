// 给定一个整数 n 和 m 个不同的质数 p1,p2,…,pm
// 请你求出 1~n 中能被 p1,p2,…,pm 中的至少一个数整除的整数有多少个
// 例: 1 2 3 4 5 6 7 8 9 10 能被 2 或 3 整除的数
//     ^ ^ ^     ^   ^ ^ ^
// ans: 7
//
// 容斥原理:
//    S₂: {2,4,6,8,10} 能被 2 整除的数
//    S₃: {3,6,9}
//    |S₂∪S₃| = |S₁| + |S₂| - |S₂ ∩ S₃| => 这个公式就对应着容斥原理的方案数
// 
// 选一次的数加上选两次的数, 显然里面有数被重复算了, 所以就要减去即能被 S₂ 整除且能被 S₃ 整除的数
//  - |S₁| + |S₂| - |S₂ ∩ S₃| = 5 + 3 - 1
//
// 求 1~n 中 p 的倍数即 ⌊n/p⌋, 因为给定的是质数, 所以数与数之间两两互质, 所以如果求能被 k 个同时整除的数 |Sₚ₁ ∩ Sₚ₂ ∩ ... ∩ Sₚₖ|
// 也就是 ⌊n/Sₚ₁*Sₚ₂*...*Sₚₖ⌋
// 例: (2,3) = 1, 所以只要能被 6 整除, 就是能被 2 个数同时整除的 

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 20;

int n, m;
int p[N];

// 1) 先证明了每个方案选或者不选最多有 m^2 种方案
// 2) 枚举每一种方案, 用容斥的公式求出最终集合数的个数 (只要有一层覆盖即可)
// 
int main()
{
    scanf("%d%d", &n, &m);      // n:1~n 的数, m:属于 m 个这些数的倍数
    for (int i = 0; i < m; ++ i ) scanf("%d", &p[i]);

    int res = 0;
    for (int i = 1; i < 1 << m; ++ i )  // 一共有 2^n 种方案数, 枚举方案 i 中有几个 1
    {
        // t:表示当前所有质数的乘积, cnt 统计 i 中包含几个 1 (当前方案中有几个集合)
        // 因为是质数所以直接除最小公倍数算出的几倍才没有冗余
        int t = 1, cnt = 0;     
        for (int j = 0; j < m; ++ j )   // 当前选法中有几个集合
            if (i >> j & 1)     // 如果当前这一位是 1 就 cnt 加一并且 t 乘上当前质数
            {
                cnt ++ ;
                // p 的范围可能很大, 会超过 n, 超过 n 就不用算了
                if ((LL)t * p[j] > n)
                {
                    t = -1;
                    break;
                }
                t *= p[j];  
            }

        // 奇数个集合就应该加上, 偶数个集合减去
        if (t != -1) 
        {
            if (cnt % 2) res += n / t;
            else res -= n / t;
        }
    }

    cout << res << endl;
    
    return 0;
}