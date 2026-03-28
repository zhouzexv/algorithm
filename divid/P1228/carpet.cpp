#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
#define ll long long

int k;
ll x,y;
ll n=1;

int where(ll x,ll y,ll n)
{
    if(x<=n/2&&y<=n/2) return 1;
    if(x<=n/2&&y>n/2) return 2;
    if(x>n/2&&y<=n/2) return 3;
    if(x>n/2&&y>n/2) return 4;
}

int solve(ll x,ll y,ll n)
{
    if(n==2)
    {
        switch(where(x,y,n))
        {
            case 1: printf("%lld %lld %lld\n",x+1,y+1,1); return 1;
            case 2: printf("%lld %lld %lld\n",x+1,y,2); return 2;
            case 3: printf("%lld %lld %lld\n",x,y+1,3); return 3;
            case 4: printf("%lld %lld %lld\n",x,y,4); return 4;
        }
    }
    switch(where(x,y,n))
    {
        case 1: 
            solve(n/2+1,n/2+1,n/2); 
            solve(n/2,n/2+1,n/2);
            solve(n/2+1,n/2,n/2);
            solve(x,y,n/2); 
            break;
        case 2: solve(x,y,n/2); break;
        case 3: solve(x,y,n/2); break;
        case 4: solve(x,y,n/2); break;
    }
}

int main()
{
    scanf("%d",&k);
    scanf("%lld %lld",&x,&y);
    for(int i=1;i<=k;i++) n*=2;

}
