#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"

int main()
{
    int L,N,M;
    scanf("%d %d %d",&L,&N,&M);
    int rocks[N];
    for(int i=0;i<N ;i++)
        scanf("%d",&rocks[i]);
    int left=1,right=L,mid; 
    int count=0;//记录移除的石子数
    int result=0;

    while(left<=right)
    {
        mid=(right + left) / 2;
        int last=0; //记录上一个石子的位置
        count=0;
        for(int i=0; i<N; i++)
        {
            if(rocks[i] - last < mid) //如果当前石子和上一个石子的距离小于mid，则移除当前石子
            { 
                count++;
            }
            else//否则保留当前石子，并更新上一个石子的位置
            {
                last=rocks[i];
            }
        }
        
        if(L-last < mid)//最后一块石子到终点的距离小于mid，也需要移除
        {
            count++;
        }

        if(count <= M)
        {
            left = mid + 1;//尝试更大的最小距离
            result = mid;
        }
        else
        {
            right = mid - 1;//尝试更小的最小距离
        }
    }
    printf("%d\n",result);
    return 0;

}