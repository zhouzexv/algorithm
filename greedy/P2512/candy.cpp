#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>

#define ll long long
ll n, total=0, ave;
const ll N=1000000+1;
ll a[N], b[N];

int main()
{
    scanf("%lld",&n);
    
    for(ll i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        total+=a[i];
    }
    ave=total/n;
    b[0]=0;
    for(ll i=1;i<n;i++)  b[i]=b[i-1]+ave-a[i];//前缀和
    std::sort(b,b+n);
    ll x=b[n/2];//取x为b的中位数
    ll ans=0;
    for(ll i=0;i<n;i++)
    {
        ans+=abs(b[i]-x);//计算每个小朋友需要的糖果数
    }
    printf("%lld\n",ans);

}