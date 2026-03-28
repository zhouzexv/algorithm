#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

const int N=1000005;
char s[N];
int sa[N],x[N],y[N],c[N],height[N],wt[N];
/*sa[i]表示排名为i的后缀的起始位置,
x[i]表示后缀i的第一个字符的排名,
y[i]表示排名为i的后缀的第一个字符的排名,
c[i]表示排名为i的后缀的数量,
height[i]表示排名为i的后缀与排名为i-1的后缀的最长公共前缀*/
//x[sa[i]]表示排名为i的后缀的第一个字符的排名
//y[sa[i]]表示排名为i的后缀的第二个字符的排名
//x[y[i]]表示排名为i的后缀的第二个字符的排名

int n,m;

void output(int x)
{
    if(!x) {putchar('0'); return;}
    int l=0;
    while(x)
    {
        wt[++l]=x%10+'0';
        x/=10;
    }
    for(int i=l;i;i--) putchar(wt[i]);
}

void get_sa()
{
    for(int i=1;i<=n;i++) c[x[i]=s[i]]++;//统计每个字符出现的次数,c[x[i]]表示排名为i的后缀的第一个字符的排名的数量
    for(int i=2;i<=m;i++) c[i]+=c[i-1];//前缀和
    for(int i=n;i>=1;i--) sa[c[x[i]]--]=i;//根据字符的排名,将字符排序,sa[c[x[i]]]表示排名为i的后缀的起始位置
    for(int k=1;k<=n;k<<=1)
    {
        int num=0;
        for(int i=n-k+1;i<=n;i++) y[++num]=i;//将所有长度为k的后缀的排名排序
        for(int i=1;i<=n;i++) if(sa[i]>k) y[++num]=sa[i]-k;//将所有长度为k的后缀的排名排序
        for(int i=1;i<=m;i++) c[i]=0;//重置c数组
        for(int i=1;i<=n;i++) c[x[i]]++;//统计每个字符出现的次数
        for(int i=2;i<=m;i++) c[i]+=c[i-1];//前缀和
        for(int i=n;i>=1;i--) sa[c[x[y[i]]]--]=y[i],y[i]=0;//根据字符的排名,将字符排序,sa[c[x[y[i]]]]表示排名为i的后缀的起始位置
        swap(x,y);//将x数组和y数组交换,方便下一次排序
        x[sa[1]]=1;num=1;//将排名为1的后缀的排名设为1
        for(int i=2;i<=n;i++)
        {
            if(y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]) 
                x[sa[i]]=num;//如果排名为i的后缀与排名为i-1的后缀的前k个字符相同,则排名也相同
            else x[sa[i]]=++num;//否则排名不同
        }
        if(num==n) break;
        m=num;
    }
    for(int i=1;i<=n;i++) output(sa[i]),putchar(' ');
}

int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);m=255;
    get_sa();
}