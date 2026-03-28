#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
const ll N=1000000+1;
int n;
ll a[N], b[N], c[N];

void swap(ll &a,ll &b)
{
    ll t=a;a=b;b=t;
}

void sort(ll a[],ll b[],int n)//冒泡排序
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

vector<int> multiply(vector<int> num, ll x) {
    int carry = 0;
    for (int i = 0; i < num.size(); ++i) {
        ll product = (ll)num[i] * x + carry;
        num[i] = product % 10;
        carry = product / 10;
    }
    while (carry > 0) {
        num.push_back(carry % 10);
        carry /= 10;
    }
    return num;
}

// 高精度除法：将高精度数（低位在前）除以ll类型数，返回商（低位在前），余数通过引用返回
vector<int> divide(vector<int> num, ll y, ll &remainder) {
    vector<int> quotient;
    remainder = 0;
    // 除法需从高位开始计算，先反转转为高位在前
    reverse(num.begin(), num.end());
    for (int i = 0; i < num.size(); ++i) {
        remainder = remainder * 10 + num[i];
        int q = remainder / y;
        remainder %= y;
        if (q != 0 || !quotient.empty()) { // 避免前导零
            quotient.push_back(q);
        }
    }
    if (quotient.empty()) { // 商为0的情况
        quotient.push_back(0);
    }
    reverse(quotient.begin(), quotient.end()); // 转回低位在前
    return quotient;
}

// 比较两个高精度数（低位在前）的大小：a >= b返回true
bool isGreaterOrEqual(vector<int> a, vector<int> b) {
    if (a.size() != b.size()) {
        return a.size() > b.size();
    }
    // 从高位（最后一个元素）开始比较
    for (int i = a.size() - 1; i >= 0; --i) {
        if (a[i] != b[i]) {
            return a[i] > b[i];
        }
    }
    return true; // 相等
}

int main() {
    scanf("%d", &n);
    scanf("%lld %lld", &a[0], &b[0]); // 国王的右手数未使用
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", &a[i], &b[i]);
    }
    
    // 原排序逻辑不变
    sort(a, b, n);
    
    // 初始化front为国王左手数（高精度，低位在前）
    vector<int> front;
    ll king_a = a[0];
    if (king_a == 0) {
        front.push_back(0);
    } else {
        while (king_a > 0) {
            front.push_back(king_a % 10);
            king_a /= 10;
        }
    }
    
    vector<int> max_reward;
    max_reward.push_back(0); // 初始最大奖赏为0
    
    for (int i = 1; i <= n; i++) {
        ll current_b = b[i];
        ll rem;
        // 计算当前大臣的奖赏：front / current_b
        vector<int> reward = divide(front, current_b, rem);
        
        // 更新最大奖赏
        if (isGreaterOrEqual(reward, max_reward)) {
            max_reward = reward;
        }
        
        // 更新front：乘以当前大臣的左手数
        front = multiply(front, a[i]);
    }
    
    // 输出最大奖赏（从高位到低位）
    for (int i = max_reward.size() - 1; i >= 0; --i) {
        printf("%d", max_reward[i]);
    }
    printf("\n");
    
    return 0;
}
