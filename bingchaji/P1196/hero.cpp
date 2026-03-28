#include<bits/stdc++.h>
using namespace std;

int fa[30005],dis[30005];

int find(int x)//查找x的根节点
{
    if(fa[x]==x) return x;
    int root=find(fa[x]);
    dis[x]+=dis[fa[x]];
    return fa[x]=root;
}

int merge(int i,int j)//将i合并到j上
{
    int rooti=find(i);
    int rootj=find(j);
    fa[rooti]=rootj;
    dis[rooti]+=abs(dis[i]-dis[j]);
    return 0;
}

int main()
{
    int T;
    cin>>T;
    for(int i=0;i<30005;i++) 
    {
        fa[i]=i;
        dis[i]=0;
    }
    while(T--)
    {
        int n,m;char command;
        cin>>command>>n>>m;
        int fn=find(n);
        int fm=find(m);
        if(command=='M')
        {
            merge(fn,fm);
        }
        else if(command=='C')
        {
            if(fn!=fm) cout<<"-1"<<endl;
            else cout<<abs(dis[n]-dis[m])<<endl;
        }
    }
    return 0;
}