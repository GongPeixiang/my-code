#include <stdio.h>

#define MAXN 6

double S, C, L, P0;
int N;
struct Stop {
    double d, p;
} stop[MAXN + 5];

int main() 
{
    scanf("%lf %lf %lf %lf %d", &S, &C, &L, &P0, &N);
    stop[0].d = 0, stop[0].p = P0;
    for (int i = 1; i <= N; ++i) 
        scanf("%lf %lf", &stop[i].d, &stop[i].p);

    stop[N + 1].d = S, stop[N + 1].p = 0;
    int cur = 0;
    double oil = 0.0, cost = 0.0;
    int flg = 1;

    while (cur < N + 1) {
        double lim = C * L + stop[cur].d;
        if (stop[cur + 1].d > lim) {
            flg = 0;
            break;
        }

        // 找第一个比当前便宜的站
        int mp = -1;
        for (int i = cur + 1; i <= N + 1 && stop[i].d <= lim; ++i) {
            if (stop[i].p < stop[cur].p) {
                mp = i;
                break;
            }
        }

        if (mp != -1) {
            // 有更便宜的站，只加刚好能到的油
            double need = (stop[mp].d - stop[cur].d) / L;
            if (need > oil) {
                cost += (need - oil) * stop[cur].p;
                oil = 0;
            } else {
                oil -= need;
            }
            cur = mp;
        } else {
            // 没有更便宜的站，找范围内最便宜的
            mp = cur + 1;
            for (int i = cur + 1; i <= N + 1 && stop[i].d <= lim; ++i) {
                if (stop[i].p < stop[mp].p) 
                    mp = i;
            }
            cost += (C - oil) * stop[cur].p;
            oil = C - (stop[mp].d - stop[cur].d) / L;
            cur = mp;
        }
    }

    if (!flg) 
        printf("No Solution\n");
    else 
        printf("%.2lf\n", cost);

    return 0;
}