#include<bits/stdc++.h>
using namespace std;
#define ll long long int
ll L,R;
ll T;
const int MOD=1000000007;
ll dp[51][11]; //dp[i][j]表示长度为i，首位为j的数中所有数字之和
ll power[20], a[51];
// 记忆化数组：memo[pos][sum_prev][limit] = {count, sum}
// count：符合条件的数的个数；sum：这些数的数位和
pair<ll, ll> memo[20][200][2];

void init()//预处理dp数组
{
    for(int i=0;i<=9;i++) dp[1][i]=i;
    power[0]=1;
    for(int i=1;i<=18;i++) power[i]=power[i-1]*10%MOD;
    for(int i=2;i<=18;i++)
        for(int j=0;j<=9;j++)
        {
            dp[i][j]=j*power[i-1]%MOD;
            for(int k=0;k<=9;k++) dp[i][j]+=dp[i-1][k],dp[i][j]%=MOD;//dp[i][j]表示长度为i，首位为j的数中所有数字之和
        }
}

ll DP(ll x) //循环思路
{
    memset(a,0,sizeof(a));
    ll ans=0,w=1;
    while(x)//拆分数字
    {
        a[w++]=x%10;
        x/=10;
    }
    w--;
    for(int i=1; i<w; i++) //枚举位数小于x的位数的数字
        for(int j=1; j<=9; j++) //枚举1-9作为最高位
            ans=(ans+dp[i][j])%MOD;
    for(int i=1; i<a[w]; i++) //枚举位数与x相同但最高位比x最高位小的数字
        ans=(ans+dp[w][i])%MOD;
    int sum=a[w];
    for(int i=w-1; i>=1; i--) //枚举每一位
    {
        ans=(ans+sum*power[i-1]*a[i])%MOD; //当前位比x当前位小的数字
        for(int j=0; j<a[i]; j++) //枚举当前位数字
            ans=(ans+dp[i][j])%MOD;
        sum=(sum+a[i])%MOD;
    }
    return ans;
}

int main()
{
    cin>>T;
    init();
    while(T--) 
    {
        cin>>L>>R;
        ll ans = (DP(R+1) - DP(L) + MOD) % MOD;
        cout << ans << endl;
    }

    return 0;
}


// 递归函数：计算从pos位开始，前缀和为sum_prev，是否受限(limit)的所有数的{个数, 数位和}
pair<ll, ll> dfs(int pos, ll sum_prev, bool limit) {
    if (pos == 0) {
        // 边界：无更多位，返回1个数（空），数位和0
        return {1, 0};
    }
    // 若已计算过该状态，直接返回缓存结果
    if (memo[pos][sum_prev][limit].first != -1) {
        return memo[pos][sum_prev][limit];
    }
    // 当前位的最大取值（受限时不超过原数对应位）
    int max_d = limit ? a[pos] : 9;
    ll total_cnt = 0; // 总个数
    ll total_sum = 0; // 总数位和
    for (int d = 0; d <= max_d; d++) {
        bool new_limit = limit && (d == max_d); // 新的受限状态
        ll new_sum_prev = sum_prev + d; // 新的前缀和（累加当前位）
        // 递归处理低位，获取低位的个数和数位和
        auto [cnt, s] = dfs(pos - 1, new_sum_prev, new_limit);
        // 当前位的贡献：(前缀和 + 当前位) × 低位个数 + 低位数位和
        ll current_sum = ( (sum_prev % MOD) * (cnt % MOD) % MOD 
                          + (d % MOD) * (cnt % MOD) % MOD ) % MOD;
        current_sum = (current_sum + s % MOD) % MOD;
        // 累加总个数和总数位和
        total_cnt = (total_cnt + cnt) % MOD;
        total_sum = (total_sum + current_sum) % MOD;
    }
    // 缓存当前状态结果并返回
    return memo[pos][sum_prev][limit] = {total_cnt, total_sum};
}

// 计算[0, x-1]的所有数的数位和
ll DP(ll x) {
    if (x <= 0) return 0; // x=0时，[0,-1]无意义，返回0
    x--; // 转为计算[0, x]的和（即原[0, x-1]）
    memset(a, 0, sizeof(a));
    int w = 1; // 数位长度
    // 分解x的数位（从低位到高位存储，a[1]是个位，a[w]是最高位）
    while (x > 0) {
        a[w++] = x % 10;
        x /= 10;
    }
    w--;
    // 初始化记忆化数组（-1表示未计算）
    memset(memo, -1, sizeof(memo));
    // 从最高位开始递归，初始前缀和0，受限状态为true
    auto [cnt, sum] = dfs(w, 0, true);
    return sum % MOD;
}