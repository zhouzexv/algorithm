#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;

int n,m,x,y;
int step[500][500];
int vis[500][500];
const int dx[8]={-2,-2,-1,-1,1,1,2,2};
const int dy[8]={-1,1,-2,2,-2,2,-1,1};
queue<pair<int,int> > q;

int main()
{
    cin>>n>>m>>x>>y;
    memset(step,-1,sizeof(step));
    memset(vis,0,sizeof(vis));
    step[x][y]=0;
    vis[x][y]=1;
    q.push(make_pair(x,y));
    while(!q.empty())
    {
        int x=q.front().first;
        int y=q.front().second;
        q.pop();
        for(int i=0;i<8;i++)
        {
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(nx<1||nx>n||ny<1||ny>m||vis[nx][ny]) continue;
            vis[nx][ny]=1;
            step[nx][ny]=step[x][y]+1;
            q.push(make_pair(nx,ny));
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cout<<step[i][j]<<" ";
        }
        cout<<endl;
    }
}