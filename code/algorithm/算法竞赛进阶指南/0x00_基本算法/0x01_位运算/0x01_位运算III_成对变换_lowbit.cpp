#include <iostream>

using namespace std;
// "成对变换":
// 通过计算可发现:
// 当 n 为偶数时, n xor 1 等于 n + 1
// 当 n 为奇数时, n xor 1 等于 n - 1
// 因此差值为 1 的两对可以构成 "成对变换"
// 该性质常用于邻接表的边集存储, 在无向边的图中将正反方向的边分别存储在邻接表数组的 n 与 n+1 位置( n 为偶数)
// 就可以 n xor 1 的运算获得当前边 (x,y) 和 反向边(y,x)
//
// lowbit 运算:
// 取出 "最低位为 1 以及后面所有的 0"
// 步骤: 
// 先将 n 取反, 此时第 k 位变成 0, 第 0~k-1 位都是 1
// 再让 n = n + 1, 此时因为进位, 第 k 位变成 1, 0~k-1 位都变成 0, 最后和原来的数相与, 取出状态(除了第 k 位和 0~k-1, 都相反)

void lowbit(int n)
{
    return n &= (~n + 1);
}

// lowbit 配和 Hash 可以找出整除二进制表示下所有是 1 的位, 所花费时间与 1 的个数同级
