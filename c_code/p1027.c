#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXS 100

struct City {
    double x[4], y[4];
    int t;
} city[MAXS];

int N, S, T, A, B;
double f[4 * MAXS + 5][4 * MAXS + 5];

static inline double get_min(double a, double b) { return a < b ? a : b; }

double solve() 
{
    // double用0x7f, int用0x3f
    memset(f, 0x7f, sizeof(f));
    // 初始化
    for (int i = 0; i < 4 * S; ++i) {
        for (int j = 0; j < 4 * S; ++j) {
            int ci = i / 4, cj = j / 4;
            int idi = i - ci * 4, idj = j - cj * 4;
            if (ci == cj) {
                f[j][i] = f[i][j] = sqrt(pow(city[ci].x[idi]-city[ci].x[idj], 2) 
                + pow(city[ci].y[idi]-city[ci].y[idj], 2)) * city[ci].t;
            } else {
                f[j][i] = f[i][j] = sqrt(pow(city[ci].x[idi]-city[cj].x[idj], 2) 
                + pow(city[ci].y[idi]-city[cj].y[idj], 2)) * T;
            }
        }
    }
    // 三重循环
    for (int k = 0; k < 4 * S; ++k) {
        for (int i = 0; i < 4 * S; ++i) {
            for (int j = 0; j < 4 * S; ++j) {
                f[i][j] = get_min(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }
    double ans = 0x7f7f7f7f;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int a = A * 4 + i, b = B * 4 + j;
            ans = get_min(ans, f[a][b]);
        }
    }
    return ans;
}

int main() 
{
    scanf("%d", &N);
    while (N--) {
        memset(city, 0, sizeof(city));
        scanf("%d %d %d %d", &S, &T, &A, &B);
        --A, --B;
        double x[4], y[4];
        for (int i = 0; i < S; ++i) {
            for (int j = 0; j < 3; ++j) {
                scanf(" %lf %lf", &city[i].x[j], &city[i].y[j]);
                x[j] = city[i].x[j], y[j] = city[i].y[j];
            }
            scanf("%d", &city[i].t);
            double l12 = (x[0]-x[1])*(x[0]-x[1]) + (y[0]-y[1])*(y[0]-y[1]);
            double l23 = (x[1]-x[2])*(x[1]-x[2]) + (y[1]-y[2])*(y[1]-y[2]);
            double l13 = (x[0]-x[2])*(x[0]-x[2]) + (y[0]-y[2])*(y[0]-y[2]);
            if (l12 > l13 && l12 > l23) {
                x[3] = x[0] + x[1] - x[2];
                y[3] = y[0] + y[1] - y[2];
            } else if (l13 > l12 && l13 > l23) {
                x[3] = x[0] + x[2] - x[1];
                y[3] = y[0] + y[2] - y[1];
            } else {
                x[3] = x[1] + x[2] - x[0];
                y[3] = y[1] + y[2] - y[0];
            }
            city[i].x[3] = x[3], city[i].y[3] = y[3];
        }
        double ans = solve();
        printf("%.1lf\n", ans);
    }
    return 0;
}