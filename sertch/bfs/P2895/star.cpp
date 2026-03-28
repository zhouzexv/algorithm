#include<vector>
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
#include<cmath>
using namespace std;

const int N=50005;
const int dx[4]={1,1,-1,-1};
const int dy[4]={1,-1,1,-1};
int m;
int burn[N][N];
int vis[N][N];
int step[N][N];
int n=0;
queue<pair<int,int> > q;

int main()
{
    cin>>m;
    memset(burn,0x3f,sizeof(burn));
    for(int i=0;i<m;i++) 
    {
        int x,y,t;
        cin>>x>>y>>t;
        if(t<burn[x][y])burn[x][y]=t;
        // 更新四个相邻格子的烧焦时间（忽略负数坐标）
        if (x - 1 >= 0 && t < burn[x - 1][y]) burn[x - 1][y] = t;
        if (x + 1 < 400 && t < burn[x + 1][y]) burn[x + 1][y] = t;
        if (y - 1 >= 0 && t < burn[x][y - 1]) burn[x][y - 1] = t;
        if (y + 1 < 400 && t < burn[x][y + 1]) burn[x][y + 1] = t;
    }
    memset(vis,0,sizeof(vis));
    memset(step,0,sizeof(step));
    vis[0][0]=1;
    step[0][0]=0;
    q.push(make_pair(0,0));

    while(!q.empty())
    {
        int x=q.front().first;
        int y=q.front().second;
        n++;
        q.pop();
        for(int i=0;i<4;i++)
        {
            int nx=x+dx[i];
            int ny=y+dy[i];
            
        }
    }

}