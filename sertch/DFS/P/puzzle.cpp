#include<vector>
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

const int MAX = 1005;
int n,m;
char puzzle[MAX][MAX];
int visited[MAX][MAX];
int ans[1000005][2];
int fin[MAX][MAX];
int d[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int start_x[1000005],start_y[1000005];
int cnt=0;

void dfs(int x,int y)
{
    cnt++;
    ans[cnt][0]=x,ans[cnt][1]=y;
    for(int i=0;i<4;i++)
    {
        int nx = x + d[i][0];
        int ny = y + d[i][1];
        if(nx<1||ny<1||nx>n||ny>n) continue;
        if(visited[nx][ny]) continue;
        if(puzzle[nx][ny] == puzzle[x][y]) continue;
        visited[nx][ny] = 1;
        dfs(nx,ny);
    }
}

int main()
{
    cin>>n>>m;
    memset(visited,0,sizeof(visited));
    memset(fin,0,sizeof(fin));

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            cin>>puzzle[i][j];
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(!visited[i][j])
            {
                visited[i][j] = 1;cnt=0;
                dfs(i,j);
                for(int k=1;k<=cnt;k++)
                    fin[ans[k][0]][ans[k][1]] = cnt;
            }
        }
    for(int i=1;i<=m;i++)
    {
        cin>>start_x[i]>>start_y[i];
        cout<<fin[start_x[i]][start_y[i]]<<endl;
    }
}
