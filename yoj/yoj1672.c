#include <stdio.h>
// 丑数问题

#define MAXK 2000
typedef unsigned long long ull;

ull p[3], K, num[MAXK];

int main() 
{
    scanf("%llu %llu %llu %llu", &p[0], &p[1], &p[2], &K);
    num[0] = 1;
    int idx[3] = {0, 0, 0};
    for (int i = 1; i < K; ++i) {
        ull nxt = p[0] * num[idx[0]];
        for (int j = 1; j < 3; ++j) {
            ull tmp = p[j] * num[idx[j]];
            nxt = nxt < tmp ? nxt : tmp;
        }
        num[i] = nxt;
        for (int j = 0; j < 3; ++j) {
            if (num[idx[j]] * p[j] == nxt) 
                ++idx[j];
        }
    }
    printf("%llu\n", num[K-1]);
    return 0;
}