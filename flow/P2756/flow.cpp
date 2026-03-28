#include <iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstdio>
using namespace std;
//dinic算法
const int INF=0x3f3f3f3f;
struct Edge
{
    int to,cap,rev;//to为边的终点,cap为边的容量,rev为反向边的编号
    Edge(int to,int cap,int rev):to(to),cap(cap),rev(rev){}
};
vector<Edge> edges[105];
int level[105];//记录每个点的层数
int cur[105];//当前弧优化,记录上一次从u点出发的边的编号
int m,n,s,t;
void addEdge(int u,int v,int cap)
{
    edges[u].push_back(Edge(v,cap,edges[v].size()));
    edges[v].push_back(Edge(u,0,edges[u].size()-1));
}

bool bfs(int s,int t)//构建分层图
{
    memset(level,-1,sizeof(level));
    queue<int> q;
    level[s]=0;//源点的层数为0
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=0;i<edges[u].size();i++)
        {
            Edge &e=edges[u][i];
            if(level[e.to]==-1 && e.cap>0)//如果该点未被访问过且该边有流量
            {
                level[e.to]=level[u]+1;//该点的层数为当前点的层数+1
                q.push(e.to);//将该点入队
            }
        }
    }
    return level[t]!=-1;//如果汇点的层数为-1,则说明汇点不可达,返回false
}

int dfs(int u, int t, int flow)//从u点出发,到达汇点t,流量为flow
{
    if(u==t) return flow;//如果当前点为汇点,则返回流量
    for(int &i=cur[u];i<edges[u].size();i++)//当前弧优化,从上次出发的边的编号开始遍历
    {
        Edge &e=edges[u][i];
        if(level[e.to]==level[u]+1 && e.cap>0)//如果该点为当前点的下一层且该边有流量
        {
            int min_flow=dfs(e.to,t,min(flow,e.cap));//递归到下一层,流量为当前流量和该边流量的较小值
            if(min_flow>0)//如果下一层有流量
            {
                e.cap-=min_flow;//当前边流量减少
                edges[e.to][e.rev].cap+=min_flow;//反向边流量增加
                return min_flow;//返回流量
            }
        }
    }
    return 0;//如果遍历完所有边都没有流量,则返回0
}

int dinic(int s, int t)
{
    int max_flow=0;
    while(bfs(s,t))//如果汇点可达
    {
        memset(cur,0,sizeof(cur));//当前弧优化,将所有点的当前弧编号重置为0
        while (int flow=dfs(s,t,INF)) max_flow+=flow;//将源点到汇点的流量加入最大流量
    }
    return max_flow;//返回最大流量
}

int main()
{
    cin>>m>>n;
    s=0,t=n+1;
    for(int i=1;i<=m;i++)
    {
        addEdge(s,i,1);
    }
    for(int i=m+1;i<=n;i++)
    {
        addEdge(i,t,1);
    }
    int u,v;
    while(cin>>u>>v)
    {
        if(u==-1 && v==-1) break;
        addEdge(u,v,1);
    }
    cout<< dinic(s,t)<<endl;
    for(int u=1;u<=m;u++)
    {
        for(Edge e: edges[u])
        {
            if(e.to>=m+1 && e.to<=n && e.cap==0)
            {
                cout<<u<<" "<<e.to<<endl;
                break;
            }
        }
    }

    return 0;
}