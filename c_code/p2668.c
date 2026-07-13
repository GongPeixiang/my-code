#include <stdio.h>
#include <string.h>

int card[15], ans;

#define min(a, b) ((a) < (b) ? (a) : (b))

void dfs(int step) 
{
    if (step >= ans) return;
    int k = 0; // 单顺子
    for (int i = 0; i < 12; ++i) {
        if (card[i] == 0) k = 0;
        else {
            if (++k >= 5) {
                for (int j = i; j >= i - k + 1; --j) --card[j];
                dfs(step + 1);
                for (int j = i; j >= i - k + 1; --j) ++card[j];
            }
        }
    }
    k = 0;  // 双顺子
    for (int i = 0; i < 12; ++i) {
        if (card[i] <= 1) k = 0;
        else {
            if (++k >= 3) {
                for (int j = i; j >= i - k + 1; --j) card[j] -= 2;
                dfs(step + 1);
                for (int j = i; j >= i - k + 1; --j) card[j] += 2;
            }
        }
    }
    k = 0;  // 三顺子
    for (int i = 0; i < 12; ++i) {
        if (card[i] <= 2) k = 0;
        else {
            if (++k >= 2) {
                for (int j = i; j >= i - k + 1; --j) card[j] -= 3;
                dfs(step + 1);
                for (int j = i; j >= i - k + 1; --j) card[j] += 3;
            }
        }
    }
    // 带牌
    for (int i = 0; i < 13; ++i) {
        if (card[i] <= 2) continue;
        if (card[i] >= 3) { // 三带
            card[i] -= 3;
            for (int j = 0; j < 14; ++j) { // 带单张
                if (card[j] == 0 || j == i) continue;
                --card[j];
                dfs(step + 1);
                ++card[j];
            }
            for (int j = 0; j < 13; ++j) {
                if (card[j] <= 1 || j == i) continue;
                card[j] -= 2;
                dfs(step + 1);
                card[j] += 2;
            }
            card[i] += 3;
        }
        if (card[i] == 4) { // 四带
            card[i] -= 4;
            for (int j = 0; j < 14; ++j) {
                if (card[j] == 0 || j == i) continue;
                --card[j];
                for (int k = 0; k < 14; ++k) {
                    if (card[k] == 0 || k == i || k == j) continue;
                    --card[k];
                    dfs(step + 1);
                    ++card[k];
                }
                ++card[j];
            }
            for (int j = 0; j < 13; ++j) {
                if (card[j] <= 1 || j == i) continue;
                card[j] -= 2;
                for (int k = 0; k < 13; ++j) {
                    if (card[k] <= 1 || k == j || k == i) continue;
                    card[k] -= 2;
                    dfs(step + 1);
                    card[k] += 2;
                }
                card[j] += 2;
            }
            card[i] += 4;
        }
    }
    // 单或对或三或四，不带
    for (int i = 0; i < 14; ++i) if (card[i]) ++step;
    ans = min(ans, step);
}

int main() 
{
    int T, n;
    scanf("%d %d", &T, &n);
    while (T--) {
        ans = n;
        memset(card, 0, sizeof(card));
        int c, val;
        for (int i = 0; i < n; ++i) {
            scanf("%d %d", &val, &c);
            if (3 <= val && val <= 13) ++card[val-3];
            else if (val == 1) ++card[11];
            else if (val == 2) ++card[12];
            else if (val == 0) ++card[13];            
        }
        dfs(0);
        printf("%d\n", ans);
    }
    return 0;
}