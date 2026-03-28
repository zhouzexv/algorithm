#include <bits/stdc++.h>

using namespace std;

// 递归函数：n个盘子从source经auxiliary移到target
void hanoi(int n, char source, char auxiliary, char target) {
    if (n == 1) {
        cout << "移动盘子 1 从 " << source << " 到 " << target << endl;
        return;
    }
    hanoi(n-1, source, target, auxiliary);  // 移n-1个到辅助柱
    cout << "移动盘子 " << n << " 从 " << source << " 到 " << target << endl;
    hanoi(n-1, auxiliary, source, target);  // 移n-1个到目标柱
}

int main() {
    int n = 3;  // 可修改盘子数量
    hanoi(n, 'A', 'B', 'C');
    return 0;
}

