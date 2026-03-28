#include<vector>
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
#include<cmath>
using namespace std;

int n,a,b;
int k[205];
int vis[205];
int step[205];
queue<int> q;

int main()
{
    cin>>n>>a>>b;
    if(a==b)
    {
        cout<<"0"<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++) cin>>k[i];
    memset(vis,0,sizeof(vis));
    memset(step,0,sizeof(step));
    vis[a]=1;
    step[a]=0;
    q.push(a);
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        
        int nx=x+k[x];
        int ny=x-k[x];
        if(nx>0&&nx<=n&&!vis[nx]) 
        {
            vis[nx]=1;
            step[nx]=step[x]+1;
            q.push(nx);
            if(nx==b) break;
        }
        if(ny>0&&ny<=n&&!vis[ny]) 
        {
            vis[ny]=1;
            step[ny]=step[x]+1;
            q.push(ny);
            if(ny==b) break;
        }
        
    }
    if(step[b]==0) cout<<"-1"<<endl;
    else cout<<step[b]<<endl;
}