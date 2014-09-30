#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

#ifdef DEBUG
ifstream in;
ofstream out;
#endif

#ifdef DEBUG
#define CIN  in
#define COUT  out
#else
#define CIN  cin
#define COUT cout
#endif


#define MAXN 100010
#define MAXK 15


#define CLR(vec) memset(vec, 0, sizeof(vec))


struct point{
    int id;
    int pos;
}table[MAXN];

double val[MAXN];       /*val  of the id*/
int knn[MAXN][MAXK];    /*nearest k pos for id*/


static void inline sort_bypos(struct point *tb, int n){
    for(int i = 1; i < n; i++){
            struct point tmp = tb[i];  
            int j;
            for(j = i - 1; j > 0 && tb[j].pos > tmp.pos; j--){
                           tb[j + 1] = tb[j];
            }
            tb[j + 1] = tmp;
    }
}


static void inline build_one_knn(struct point *tb, int idx, int n, int k)
{
    int lidx = idx - 1;
    int ridx = idx + 1;
    int cnt  = 0;
    int pos  = tb[idx].pos;

    while(cnt < k){
        do{
            if(lidx < 0){
                knn[idx][cnt] = tb[ridx++].id;
                break;
            }

            if(ridx >= n){
                knn[idx][cnt] =  tb[lidx--].id;
                break;
            }

            int flag = (tb[ridx].pos - pos) - (pos - tb[lidx].pos);
                
            if(flag < 0){
                knn[idx][cnt] =  tb[ridx++].id;
                break;
            }
            
            if(flag > 0){
                knn[idx][cnt] =  tb[lidx--].id;
                break;
            }

            if(tb[ridx].id < tb[lidx].id){
                knn[idx][cnt] = tb[ridx++].id;
            }else{
                knn[idx][cnt] =  tb[lidx--].id;
            }

        }while(0);
        cnt++;
    }
}

static void inline build_knn(int n, int k)
{
    struct point element;
    for(int i = 0; i < n; i++){
            scanf("%d%lf", &(element.pos), &val[i]);
            element.id = i + 1;         /*Notice:element.id = id + 1*/
            int j;                      /*insert sort here by id*/
            for(j = i - 1; j >= 0 && table[j].pos > element.pos; j--){
                            table[j + 1] = table[j];
            }
            table[j + 1] = element;
    }
    for(int idx = 0; idx < n; idx++)
            build_one_knn(table, idx, n, k);
}


int  main(void)
{
#ifdef DEBUG
      freopen("in", "r", stdin);
      freopen("out","w", stdout);
#endif
      int cases;
      int n, m, k;
      scanf("%d", &cases);
      for(int currCase = 1; currCase <= cases; currCase++){
                CLR(table);
                CLR(knn);
                CLR(val);
                scanf("%d%d%d", &n, &m, &k);
                double ans = 0.0;
                build_knn(n, k);    
                while(m--){
                    double tmp = 0.0;
                    int qidx;           
                    scanf("%d", &qidx);
                    int cnt = 0;
                    while(0 != knn[qidx][cnt]){
                            tmp += val[knn[qidx][cnt] - 1];
                            cnt++;
                    }
                    tmp /= cnt;
                    ans += tmp;
                    val[qidx] = tmp;
                }
                printf("%.6lf\n", ans);
      }
    return 0;
}



