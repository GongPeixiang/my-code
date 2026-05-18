#include <stdio.h>
#include <string.h>

#define MAXLEN 5000

char a[MAXLEN + 1], b[MAXLEN + 1], result[MAXLEN + 5];
int res[MAXLEN + 5];

void add() 
{
    memset(res, 0, sizeof(res));
    int la = strlen(a), lb = strlen(b);
    int len = (la > lb ? la : lb);
    int i = la - 1, j = lb - 1, k = len - 1;
    int carry = 0;
    while (k >= 0) {
        int x = i >= 0 ? a[i] - '0' : 0;
        int y = j >= 0 ? b[j] - '0' : 0;
        int tmp = x + y + carry;
        res[k] = tmp % 10;
        carry = tmp / 10;
        --k, --i, --j;
    }
    int cnt = 0;
    if (carry) 
        result[cnt++] = '1';
    for (int i = 0; i < len; ++i) 
        result[cnt++] = (char)(res[i] + '0');
    result[cnt] = '\0';
} 

int main() 
{
    scanf(" %s %s", a, b);
    add();
    printf("%s\n", result);
    return 0;
}