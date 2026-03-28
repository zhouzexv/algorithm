#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<cstring>
using namespace std;

const int M=500005;
int n,m,cnt=0,idx=0;
int dfn[M],low[M],instack[M];//dfn[i]表示i点的时间戳,low[i]表示i点及其子树中最小的时间戳,instack[i]表示i点是否在栈中
stack<int> s;
vector<int> graph[M];
struct ascc{
    int size;
    vector <int> scc;
    ascc(int _size=0,vector<int> _scc={}):size(_size),scc(_scc){}
} scclist[M];

void tarjan(int u)
{
    dfn[u]=low[u]=++idx;
    s.push(u);
    instack[u]=1;
    for(int v: graph[u])
    {
        if(!dfn[v])//如果v点未被访问过
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(instack[v])//如果v点在栈中,说明u点到v点有一条回边
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u])
    {
        cnt++;
        vector<int> scc;
        int v;
        do{
            v=s.top();
            s.pop();
            instack[v]=0;
            scc.push_back(v);
        }while(u!=v);
        sort(scc.begin(),scc.end());
        scclist[cnt]=ascc(scc.size(),scc);
    }

}

bool cmp(ascc a,ascc b)
{
    return a.size>b.size;
}

int main()
{
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        int u,v,flag;
        cin>>u>>v>>flag;
        graph[u].push_back(v);
        if(flag==2) graph[v].push_back(u);
    }
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(instack,0,sizeof(instack));
    idx=0;
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i]) tarjan(i);
    }
    sort(scclist+1,scclist+cnt+1,cmp);
    cout<<scclist[1].size<<endl;
    for(int i=0;i<scclist[1].size;i++)
        cout<<scclist[1].scc[i]<<" ";
    return 0;
    
}