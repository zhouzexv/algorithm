#include<bits/stdc++.h>
using namespace std;

int n,c;
int pre[54];
int dp[54][54][2];  //dp[i][j][0]表示在i处，dp[i][j][1]表示在j处 dp[i][j]表示i到j区间内的灯全部关闭时的最小能量消耗
int location[54]={0};


int cal(int x,int y,int left,int right)//计算在left到right区间内的灯已经关闭时，将x到y区间内的灯全部关闭的最小能量消耗
{
    return (location[y] - location[x]) * (pre[n] + pre[left-1] - pre[right]);//left到right区间内的灯已经关闭
}
int main()
{
    memset(pre,0,sizeof(pre));
    scanf("%d %d",&n,&c);
    for(int i=1;i<=n;i++)
    {
        int p;
        scanf("%d %d",&location[i], &p);
        pre[i]=pre[i-1]+p;//pre[i]表示前i个灯的总能量消耗
    }
    memset(dp,0x3f,sizeof(dp));
    dp[c][c][0]=0; dp[c][c][1]=0;
    for(int l=2;l<=n;l++) //枚举区间长度
        for(int i=1;i<=n-l+1;i++)//枚举区间长度l和左端点i
        {
            int j=i+l-1;
            dp[i][j][0]=min(dp[i+1][j][0]+cal(i,i+1,i+1,j),dp[i+1][j][1]+cal(i,j,i+1,j));//在i处关闭灯
            dp[i][j][1]=min(dp[i][j-1][0]+cal(i,j,i,j-1),dp[i][j-1][1]+cal(j-1,j,i,j-1));//在j处关闭灯
        }
    printf("%d\n",min(dp[1][n][0],dp[1][n][1]));
    return 0;
}

//注意尽量使每个dp[i][j]都更新，不要遗漏某些状态，否则可能会导致结果错误
//错误示范for(int j=c;j<=n;j++) 
//        for(int i=c-1;i>=1;i--)导致很多dp[][]状态没有更新，最终结果出错