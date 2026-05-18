#include <stdio.h>
#include <stdbool.h>

#define MAXN 10

int N, cnt = 0, res;
struct Guess {
    int a, b, c;
} guess[MAXN];

bool check(const int num) 
{
    printf("=== checking %d ===\n", num);  // 调试输出
    
    int d[4], cpy = num;
    for (int i = 3; i >= 0; --i) {
        d[i] = cpy % 10;
        cpy /= 10;
    }
    
    for (int k = 0; k < N; ++k) {
        printf("  guess[%d]: a=%d b=%d c=%d\n", k, guess[k].a, guess[k].b, guess[k].c);
        
        int e[4];
        int ak = guess[k].a;
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
        
        printf("    curb=%d curc=%d (expected b=%d c=%d)\n", curb, curc, guess[k].b, guess[k].c);
        
        if (curc == guess[k].c && curb == guess[k].b) 
            return false;
    }
    return true;
}

int main() 
{
    printf("Start\n");
    scanf("%d", &N);
    printf("N=%d\n", N);
    
    for (int i = 0; i < N; ++i) {
        scanf("%d %d %d", &guess[i].a, &guess[i].b, &guess[i].c);
        printf("guess[%d]: %d %d %d\n", i, guess[i].a, guess[i].b, guess[i].c);
    }
    
    for (int num = 1000; num <= 9999; ++num) {
        if (check(num)) {
            printf(">>> num %d is valid\n", num);
            res = num;
            ++cnt;
        }
        if (cnt > 1) {
            printf(">>> cnt > 1, breaking\n");
            break;
        }
    }
    
    printf("cnt=%d\n", cnt);
    if (cnt == 1) 
        printf("%d\n", res);
    else    
        printf("Not sure\n");
    return 0;
}
