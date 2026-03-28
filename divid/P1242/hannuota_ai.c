#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10
#define QUEUE_SIZE 100000

const char ch[4] = {'0','A','B','C'};

// 状态结构体
typedef struct {
    int pos[MAX_N + 1];     // pos[i]表示第i个盘子的位置(1-3)
    int step;
    int move_disk, from, to; // 记录导致此状态的移动
    int parent_idx;         // 父状态在队列中的索引
} State;

State queue[QUEUE_SIZE];
int visited[19683]; // 3^10 = 59049 < 19683

// 状态编码
int encode(int *pos, int n) {
    int res = 0;
    int base = 1;
    for (int i = 1; i <= n; i++) {
        res += (pos[i]-1) * base;  // 柱子编号1-3转为0-2
        base *= 3;
    }
    return res;
}

// 检查状态是否相等
int is_target(int *pos, int *target, int n) {
    for (int i = 1; i <= n; i++) {
        if (pos[i] != target[i]) return 0;
    }
    return 1;
}

// 找到柱子上最上面的盘子（编号最小的）
int get_top_disk(int *pos, int pole, int n) {
    int min_disk = n + 1;
    for (int i = 1; i <= n; i++) {
        if (pos[i] == pole && i < min_disk) {
            min_disk = i;
        }
    }
    return (min_disk <= n) ? min_disk : -1;
}

// 打印移动序列
void print_moves(int final_idx) {
    int moves[1000][3];  // [disk, from, to]
    int len = 0;
    int idx = final_idx;
    
    // 回溯收集所有移动
    while (queue[idx].parent_idx != -1) {
        moves[len][0] = queue[idx].move_disk;
        moves[len][1] = queue[idx].from;
        moves[len][2] = queue[idx].to;
        len++;
        idx = queue[idx].parent_idx;
    }
    
    // 倒序输出
    for (int i = len-1; i >= 0; i--) {
        printf("move %d from %c to %c\n", 
               moves[i][0], ch[moves[i][1]], ch[moves[i][2]]);
    }
}

// BFS求解
int bfs_solve(int n, int *start, int *target) {
    int front = 0, rear = 0;
    memset(visited, 0, sizeof(visited));
    
    // 初始状态
    for (int i = 1; i <= n; i++) {
        queue[rear].pos[i] = start[i];
    }
    queue[rear].step = 0;
    queue[rear].parent_idx = -1;
    queue[rear].move_disk = queue[rear].from = queue[rear].to = 0;
    
    // 检查初始状态是否就是目标
    if (is_target(queue[rear].pos, target, n)) {
        printf("0\n");
        return 0;
    }
    
    visited[encode(queue[rear].pos, n)] = 1;
    rear++;
    
    while (front < rear) {
        State current = queue[front++];
        
        // 尝试所有可能的移动
        for (int from_pole = 1; from_pole <= 3; from_pole++) {
            int disk = get_top_disk(current.pos, from_pole, n);
            if (disk == -1) continue;  // 此柱子无盘子
            
            for (int to_pole = 1; to_pole <= 3; to_pole++) {
                if (from_pole == to_pole) continue;
                
                // 检查是否可以移动到目标柱子
                int top_on_to = get_top_disk(current.pos, to_pole, n);
                if (top_on_to == -1 || top_on_to > disk) {
                    // 可以移动，生成新状态
                    State next = current;
                    next.pos[disk] = to_pole;
                    next.step++;
                    next.move_disk = disk;
                    next.from = from_pole;
                    next.to = to_pole;
                    next.parent_idx = front - 1;  // 指向当前状态
                    
                    // 检查是否达到目标状态
                    if (is_target(next.pos, target, n)) {
                        print_moves(rear);
                        printf("move %d from %c to %c\n", disk, ch[from_pole], ch[to_pole]);
                        printf("%d\n", next.step);
                        return next.step;
                    }
                    
                    // 检查是否已访问
                    int code = encode(next.pos, n);
                    if (!visited[code] && rear < QUEUE_SIZE - 1) {
                        visited[code] = 1;
                        queue[rear++] = next;
                    }
                }
            }
        }
    }
    
    return -1; // 无解
}

int main() {
    int n;
    scanf("%d", &n);
    
    int start[MAX_N + 1] = {0};
    int target[MAX_N + 1] = {0};
    
    // 读取初始状态
    for(int i = 1; i <= 3; i++) {
        int count;
        scanf(" %d", &count);
        for(int k = 0; k < count; k++) {
            int disk;
            scanf(" %d", &disk);
            start[disk] = i;
        }
    }

    // 读取目标状态
    for(int i = 1; i <= 3; i++) {
        int count;
        scanf(" %d", &count);
        for(int k = 0; k < count; k++) {
            int disk;
            scanf(" %d", &disk);
            target[disk] = i;
        }
    }
    
    bfs_solve(n, start, target);
    
    return 0;
}