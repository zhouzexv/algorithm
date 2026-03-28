#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

const int M = 2005;
const int N = 105;
const int D = 256; // 边权最大255，足够覆盖
int n, m;
// dis[i][j]：从1到i，路径中最大边权为j时的最小总权和
int dis[N][D];
int ans; // 初始化移到main中，用大数初始化
vector<vector<pair<int, int>>> adj;

// 状态结构体：s=总权和，u=当前顶点，k=路径中最大边权
struct State {
    int s, u, k;
    // 定义构造函数，支持不同参数个数（方便emplace调用）
    State(int s_, int u_, int k_) : s(s_), u(u_), k(k_) {}
    // 重载大于号，用于小根堆排序
    bool operator>(const State& other) const {
        return s > other.s;
    }
};

// 优先队列：小根堆，按总权和升序
priority_queue<State, vector<State>, greater<State>> pq;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    adj.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // 移除错误的边权修改逻辑
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    // 初始化dis数组为无穷大
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < D; j++) {
            dis[i][j] = 0x3f3f3f3f;
        }
    }
    dis[1][0] = 0;
    // 正确传入三个参数：s=0, u=1, k=0
    pq.emplace(0, 1, 0);

    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        int s = cur.s;
        int u = cur.u;
        int k = cur.k;

        // 关键：判断当前状态是否为无效状态（已被更优状态更新）
        if (s > dis[u][k]) {
            continue;
        }

        // 遍历邻接边
        for (auto [v, w] : adj[u]) {
            int newk = max(k, w);
            int news = s + w;

            // 松弛操作：若新状态更优，则更新并入队
            if (news < dis[v][newk]) {
                dis[v][newk] = news;
                pq.emplace(news, v, newk);
            }
        }
    }

    // 初始化ans为无穷大，计算最小总代价（总权和+最大边权）
    ans = 0x3f3f3f3f;
    for (int i = 0; i < D; i++) {
        if (dis[n][i] != 0x3f3f3f3f) {
            ans = min(ans, dis[n][i] + i);
        }
    }

    cout << ans << endl;
    return 0;
}