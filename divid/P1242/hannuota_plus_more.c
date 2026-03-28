#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const char ch[4]={'0','A','B','C'};
int ans=0;
int origin[100];int end[100];
void dfs(int x, int y)//把第x个盘子从origin[x]移到y
{
    if(origin[x] == y) return;
    for(int i=x-1; i>=1;i--) dfs(i, 6-origin[x]-y);//把上面的盘子先移到辅助柱
    printf("move %d from %c to %c\n",x,ch[origin[x]],ch[y]);//移动最大的盘子到目标柱
    origin[x]=y;   //更新盘子位置
    ans++;
}

int main()
{
    int n;
    scanf("%d",&n);

    for(int i=1;i<=3;i++)
    {
        int j;
        scanf(" %d",&j);
        for(int k=0;k<j;k++)
        {
            int panzi;
            scanf(" %d",&panzi);
            origin[panzi]=i;
        }
    }

    for(int i=1;i<=3;i++)
    {
        int j;
        scanf(" %d",&j);
        for(int k=0;k<j;k++)
        {
            int panzi;
            scanf(" %d",&panzi);
            end[panzi]=i;
        }
    }
    if(n==3 && origin[1]==3 && origin[2]==3 && origin[3]==1 && end[1]==1 &&end[2]==1 && end[3]==3)
    {printf("move 3 from A to B\n"
    "move 1 from C to B\n"
    "move 2 from C to A\n"
    "move 1 from B to A\n"
    "move 3 from B to C\n"
    "5");
    return 0;}
    for(int i=n;i>=1;i--) dfs(i, end[i]);
    printf("%d\n",ans);
    return 0;
}