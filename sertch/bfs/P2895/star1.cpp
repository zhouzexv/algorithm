#include <iostream>
#include <queue>
#include <cstring>
#include <climits>
using namespace std;

// 定义最大坐标范围（根据T_i最大为1000，设400足够）
const int MAX = 400;
// 每个格子的最早烧焦时间，初始为极大数
int burn[MAX][MAX];
// 访问标记，避免重复入队
bool visited[MAX][MAX];
// 四个移动方向（上、下、左、右）
int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

struct Node {// BFS节点结构体
    int x, y, time;
    Node(int x_, int y_, int t_) : x(x_), y(y_), time(t_) {}
};

int main() {
    ios::sync_with_stdio(false);// 关闭流同步，加速输入输出
    cin.tie(nullptr);// 取消cin与cout的绑定

    // 初始化烧焦时间为极大数
    memset(burn, 0x3f, sizeof(burn));
    int M;
    cin >> M;

    for (int i = 0; i < M; ++i) {
        int x, y, t;
        cin >> x >> y >> t;
        // 更新撞击点的烧焦时间
        if (t < burn[x][y]) burn[x][y] = t;
        // 更新四个相邻格子的烧焦时间（忽略负数坐标）
        if (x - 1 >= 0 && t < burn[x - 1][y]) burn[x - 1][y] = t;
        if (x + 1 < MAX && t < burn[x + 1][y]) burn[x + 1][y] = t;
        if (y - 1 >= 0 && t < burn[x][y - 1]) burn[x][y - 1] = t;
        if (y + 1 < MAX && t < burn[x][y + 1]) burn[x][y + 1] = t;
    }

    // BFS初始化
    queue<Node> q;
    // 检查起点(0,0)是否在时刻0被烧焦
    if (burn[0][0] == 0) {
        cout << -1 << endl;
        return 0;
    }
    q.push(Node(0, 0, 0));
    visited[0][0] = true;

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();

        // 遍历四个方向
        for (auto& dir : dirs) {
            int nx = cur.x + dir[0];
            int ny = cur.y + dir[1];
            int nt = cur.time + 1;// 新时间为当前时间加1

            // 坐标合法（非负且不超过最大范围）
            if (nx < 0 || ny < 0 || nx >= MAX || ny >= MAX) continue;
            // 已访问过，跳过
            if (visited[nx][ny]) continue;
            // 新时间必须小于格子的烧焦时间（否则会被烧焦）
            if (nt >= burn[nx][ny]) continue;

            // 找到安全格子（永远不会被烧焦）
            if (burn[nx][ny] == 0x3f3f3f3f) {
                cout << nt << endl;
                return 0;
            }

            // 标记访问并入队
            visited[nx][ny] = true;
            q.push(Node(nx, ny, nt));
        }
    }

    // 所有可达格子都不安全
    cout << -1 << endl;
    return 0;
}