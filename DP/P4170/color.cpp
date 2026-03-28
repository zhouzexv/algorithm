#include<bits/stdc++.h>
char s[60];
int n;
int dp[60][60];//dp[i][j]表示从i到j涂色的最小次数
int color[60];
using namespace std;

int main()
{
    cin>>s;
    n=strlen(s);
    for(int i=0;i<n;i++) dp[i][i] = 1;
    for(int l=1;l<n;l++) //l表示长度
    {
        for(int i=0;i<n-l;i++)
        {
            int j=i+l;
            if(s[i]==s[j]) dp[i][j] = dp[i][j-1];
            else 
            {
                dp[i][j] = dp[i][i] + dp[i+1][j];
                for(int k=i+1; k<j;k++)
                {
                    dp[i][j]=min(dp[i][j],dp[i][k] + dp[k+1][j]);
                }
            }
        }
    }
    printf("%d",dp[0][n-1]);
    return 0;
}