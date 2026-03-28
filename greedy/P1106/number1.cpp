#include <bits/stdc++.h>
using namespace std;
#define ll long long int 
char s[300];
int k,l;
int c[250][250];

int* func(int a[],int k,int l)
{
    if(k==0) return a;
    for(int i=0,j=0;i<l;i++)
    {
        if(a[i]>a[i+1])
        {
            continue;
        }
        c[k-1][j++]=a[i];
    }
    return func(c[k-1],k-1,l-1);
}

int main()
{
    cin>>s>>k;
    l=strlen(s);
    int a[l];
    for(int i=0;i<l;i++) a[i]=s[i]-'0';
    func(a,k,l);
    int flag=0;
    for(int i=0;i<l-k;i++) 
    {
        if(c[0][i]!=0) flag=1;
        if(flag!=0) cout<<c[0][i];
    }
    if(flag==0)cout<<0;
    return 0;
}