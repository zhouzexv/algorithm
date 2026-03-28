#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>

#define ll long long
const ll N=1000000+1;
int n;
ll a[N], b[N], c[N];

void swap(ll &a,ll &b)
{
    ll t=a;a=b;b=t;
}

void sort(ll a[],ll b[],int n)//√∞≈›≈≈–Ú
{
    for(int i=1;i<=n;i++)
    {
        for(int j=2;j<=n;j++)
        {
            if(a[j-1]*b[j-1]>a[j]*b[j])
            {
                swap(a[j-1],a[j]);
                swap(b[j-1],b[j]);
            }
        }
    }
}

int main()
{
    scanf("%d",&n);
    scanf("%lld %lld",&a[0],&b[0]);
    for(int i=1;i<=n;i++) scanf("%lld %lld",&a[i],&b[i]);
    sort(a,b,n);
    ll ans=0;
    ll front=a[0];
    for(int i=1;i<=n;i++) 
    {
        ans=(ans>front/b[i])?ans:(front/b[i]);
        front*=a[i];
    }
    printf("%lld",ans);
    return 0;
}
