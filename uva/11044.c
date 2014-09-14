#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>


typedef unsigned long long int ll;


int main(void)
{
#ifdef DEBUG
    freopen("./in", "r", stdin);
    freopen("./out", "w",  stdout);
    printf("Output\n");
#endif
    int cases, row, col, ans;
    scanf("%d", &cases);
        while(cases--){
            scanf("%d%d", &row, &col);   
                ans = 0;
                --row;
                --col;
                ans += row/3 + (row%3 ? 1 : 0);
                ans += col/3 + (col%3 ? 1 : 0);
                if( (row%3) && (col%3))
                    ++ans;
                printf("%d\n", ans);
        }
    return 0;
}




