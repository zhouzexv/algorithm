#include<bits/stdc++.h>
using namespace std;

int fa[1005],n,m;
struct node
{
    int u,v,t;
}a[100005];

int find(int x)//并查集查找
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}

void merge(int x,int y)//并查集合并 
{
    int fx=find(x);
    int fy=find(y);
    fa[fx]=fy;
}

bool check()
{
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(fa[i]==i) cnt++;
        if(cnt>1) return false;
    }
    return true;
}

bool cmp(node x,node y)
{
    return x.t<y.t;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++) cin>>a[i].u>>a[i].v>>a[i].t;
    sort(a+1,a+1+m,cmp);
    for(int i=1;i<=m;i++)
    {
        merge(a[i].u,a[i].v);
        if(check())
        {
            cout<<a[i].t<<endl;
            return 0;
        }
    }
    cout<<-1<<endl;
    return 0;
}