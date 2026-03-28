#include <iostream>
#include <cmath>
using namespace std;

int cnt = 0; // 仅用于计数（无实际输出作用，保留递归逻辑完整性）

// 形状定义（关键！对应题目图1的4种L型）：
// 形状1：拐角在 (midx+1, midy+1)，覆盖 (midx,midy+1)、(midx+1,midy)、(midx+1,midy+1)
// 形状2：拐角在 (midx+1, midy)，覆盖 (midx,midy)、(midx+1,midy)、(midx+1,midy+1)
// 形状3：拐角在 (midx, midy+1)，覆盖 (midx,midy)、(midx,midy+1)、(midx+1,midy+1)
// 形状4：拐角在 (midx, midy)，覆盖 (midx,midy)、(midx,midy+1)、(midx+1,midy)

// 分治递归函数：输出每个L型的拐角坐标和形状
// x1,y1：当前正方形左上角坐标；len：当前正方形边长；dx,dy：公主（破损）坐标
void fill(int x1, int y1, int len, int dx, int dy) {
    // 终止条件：边长为1（仅公主格，无L型需要放置）
    if (len == 1) {
        return;
    }

    int half = len / 2;          // 子正方形边长
    int midx = x1 + half - 1;    // 左上子正方形的右下角行坐标（中心行）
    int midy = y1 + half - 1;    // 左上子正方形的右下角列坐标（中心列）

    // 1. 公主在左上子正方形 (x1~midx, y1~midy)
    if (dx <= midx && dy <= midy) {
        fill(x1, y1, half, dx, dy); // 递归处理左上
        // 放置L型：拐角(midx+1, midy+1)，形状1
        cout << midx + 1 << " " << midy + 1 << " 1" << endl;
        // 递归处理另外3个子正方形（虚拟破损格为L型的三个点）
        fill(x1, y1 + half, half, midx, midy + 1);   // 右上（虚拟破损格：midx,midy+1）
        fill(x1 + half, y1, half, midx + 1, midy);   // 左下（虚拟破损格：midx+1,midy）
        fill(x1 + half, y1 + half, half, midx + 1, midy + 1); // 右下（虚拟破损格：midx+1,midy+1）
    }
    // 2. 公主在右上子正方形 (x1~midx, midy+1~y1+len-1)
    else if (dx <= midx && dy > midy) {
        fill(x1, y1 + half, half, dx, dy); // 递归处理右上
        // 放置L型：拐角(midx+1, midy)，形状2
        cout << midx + 1 << " " << midy << " 2" << endl;
        // 递归处理另外3个子正方形
        fill(x1, y1, half, midx, midy);               // 左上（虚拟破损格：midx,midy）
        fill(x1 + half, y1, half, midx + 1, midy);     // 左下（虚拟破损格：midx+1,midy）
        fill(x1 + half, y1 + half, half, midx + 1, midy + 1); // 右下（虚拟破损格：midx+1,midy+1）
    }
    // 3. 公主在左下子正方形 (midx+1~x1+len-1, y1~midy)
    else if (dx > midx && dy <= midy) {
        fill(x1 + half, y1, half, dx, dy); // 递归处理左下
        // 放置L型：拐角(midx, midy+1)，形状3
        cout << midx << " " << midy + 1 << " 3" << endl;
        // 递归处理另外3个子正方形
        fill(x1, y1, half, midx, midy);               // 左上（虚拟破损格：midx,midy）
        fill(x1, y1 + half, half, midx, midy + 1);     // 右上（虚拟破损格：midx,midy+1）
        fill(x1 + half, y1 + half, half, midx + 1, midy + 1); // 右下（虚拟破损格：midx+1,midy+1）
    }
    // 4. 公主在右下子正方形 (midx+1~x1+len-1, midy+1~y1+len-1)
    else {
        fill(x1 + half, y1 + half, half, dx, dy); // 递归处理右下
        // 放置L型：拐角(midx, midy)，形状4
        cout << midx << " " << midy << " 4" << endl;
        // 递归处理另外3个子正方形
        fill(x1, y1, half, midx, midy);               // 左上（虚拟破损格：midx,midy）
        fill(x1, y1 + half, half, midx, midy + 1);     // 右上（虚拟破损格：midx,midy+1）
        fill(x1 + half, y1, half, midx + 1, midy);     // 左下（虚拟破损格：midx+1,midy）
    }
}

int main() {
    int k, x, y;
    // 输入：k（2^k × 2^k）、公主坐标(x,y)
    cin >> k;
    cin >> x >> y;

    int len = pow(2, k); // 迷宫总边长
    // 从整个迷宫的左上角(1,1)开始递归放置L型
    fill(1, 1, len, x, y);

    return 0;
}