#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;

#define ll long long
int n,m;
ll a[7][2];
vector<ll> leftsum;

ll powint(int x,int p)
{
    ll res=1;
    for(int i=1;i<=p;i++) res*=x;
    return res;
}

void dfs_left(int pos,int mid,ll sum)
{
    if(pos==mid)
    {
        leftsum.push_back(sum);
        return;
    }
    int k=a[pos][0];
    int p=a[pos][1];
    for(int i=1;i<=m;i++)
    {
        ll temp=k*powint(i,p);
        dfs_left(pos+1,mid,sum+temp);
    }
}

void dfs_right(int pos,int mid,ll sum,int &ans)
{
    if(pos==n)
    {
        auto left=lower_bound(leftsum.begin(),leftsum.end(),-sum);
        auto right=upper_bound(leftsum.begin(),leftsum.end(),-sum);
        ans+=right-left;
        return;
    }
    int k=a[pos][0];
    int p=a[pos][1];
    for(int i=1;i<=m;i++)
    {
        ll temp=k*powint(i,p);
        dfs_right(pos+1,mid,sum+temp,ans);
    }
}

int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++) cin>>a[i][0]>>a[i][1];
    dfs_left(0,n/2,0);
    sort(leftsum.begin(),leftsum.end());
    int ans=0;
    dfs_right(n/2,n/2,0,ans);
    cout<<ans<<endl;
    return 0;
}