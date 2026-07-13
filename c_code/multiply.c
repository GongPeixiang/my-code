#include <stdio.h>
#include <string.h>

#define MAXLEN 5005

char a[MAXLEN], b[MAXLEN], result[MAXLEN*2];
int res[MAXLEN*2];
char zero[2] = {'0', '\0'};

void multiply(void) 
{
    memset(res, 0, sizeof(res));
    if (strcmp(a, zero) == 0 || strcmp(b, zero) == 0) {
        strcpy(result, zero);
        return;
    }
    int la = strlen(a), lb = strlen(b);
    for (int i = la - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = lb - 1; j >= 0; --j) {
            int x = a[i] - '0', y = b[j] - '0';
            int tmp = x * y + carry + res[i+j+1];
            res[i+j+1] = tmp % 10;
            carry = tmp / 10;
        }
        if (carry) 
            res[i] += carry;
    }
    int i = 0, len = la + lb;
    while (res[i] == 0) 
        ++i;
    int cnt = 0;
    for (; i < len; ++i) 
        result[cnt++] = (char)(res[i] + '0');
    result[cnt] = '\0';
}

int main() 
{
    scanf("%s %s", a, b);
    multiply();
    printf("%s\n", result);
    return 0;
}