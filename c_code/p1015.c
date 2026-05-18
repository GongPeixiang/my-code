#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXLEN 100

int N;
char num[MAXLEN + 1], rev[MAXLEN + 1];

bool check() 
{
    int len = strlen(num);
    for (int i = 0; i < len / 2; ++i) {
        if (num[i] != num[len - i - 1]) 
            return false;
    }
    return true;
}

void get_rev() 
{
    int len = strlen(num);
    for (int i = 0; i < len; ++i) 
        rev[i] = num[len - 1 - i];
    rev[len] = '\0';
}

void add() 
{
    int len = strlen(num), carry = 0;
    for (int i = len - 1; i >= 0; --i) {
        int x = isdigit(num[i]) ? num[i] - '0' : num[i] - 'A' + 10;
        int y = isdigit(rev[i]) ? rev[i] - '0' : rev[i] - 'A' + 10;
        int tmp = x + y + carry;
        int res = tmp % N;
        carry = tmp / N;
        num[i] = res < 10 ? res + '0' : res - 10 + 'A';
    }
    if (carry) {
        num[len + 1] = '\0';
        for (int i = len; i >= 1; --i) 
            num[i] = num[i - 1];
        num[0] = '1';
    }
}

int solve() 
{
    int steps = 0;
    while (!check()) {
        if (steps >= 30) return -1;
        get_rev();
        add();
        ++steps;
    }
    return steps;
}

int main() 
{
    scanf("%d %s", &N, num);
    int ans = solve();
    if (ans == -1) 
        printf("Impossible!\n");
    else
        printf("STEP=%d\n", ans);
    return 0;
}