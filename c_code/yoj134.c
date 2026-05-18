#include <stdio.h>
#include <stdbool.h>

#define MAXN 10

int N, res, cnt = 0;
struct Guess {
    int a, b, c;
} guess[MAXN];

bool check(const int num) 
{
    int d[4], cpy = num;
    for (int i = 3; i >= 0; --i) {
        d[i] = cpy % 10;
        cpy /= 10;
    }
    int e[4];
    for (int k = 0; k < N; ++k) {
        int ak = guess[k].a, bk = guess[k].b, ck = guess[k].c;
        for (int i = 3; i >= 0; --i) {
            e[i] = ak % 10;
            ak /= 10;
        }
        int curb = 0, curc = 0;
        for (int i = 0; i < 4; ++i) {
            if (d[i] == e[i]) 
                ++curc;
        }
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (e[j] == d[i]) {
                    ++curb;
                    e[j] = -1; 
                    break;
                }
            }
        }
        if (curc != ck || curb != bk) 
            return false;
    }
    return true;
}

int main() 
{
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) 
        scanf("%d %d %d", &guess[i].a, &guess[i].b, &guess[i].c);
    for (int num = 1000; num <= 9999; ++num) {
        if (check(num)) {
            res = num;
            ++cnt;
        }
    }
    if (cnt == 1) 
        printf("%d\n", res);
    else    
        printf("Not sure\n");
    return 0;
}