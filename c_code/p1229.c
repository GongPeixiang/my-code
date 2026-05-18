#include <stdio.h>
#include <string.h>

#define MAXLEN 300

char a[MAXLEN], b[MAXLEN], tmp[MAXLEN];

void get_substr(char str[], int src, int l) 
{
    char *p = str + src;
    int cnt = 0;
    while (cnt < l) 
        tmp[cnt++] = *(p++);
    tmp[cnt++] = '\0';
}

void rev() 
{
    int l = strlen(tmp);
    char c;
    for (int i = 0; i < l / 2; ++i) {
        c = tmp[i];
        tmp[i] = tmp[l - i - 1];
        tmp[l - i - 1] = c;
    }
}

int main() 
{
    scanf(" %s %s", a, b);
    int len = strlen(a);
    long long ans = 1;
    for (int i = 0; i < len - 1; ++i) {
        get_substr(a, i, 2);
        rev();
        if (strstr(b, tmp)) 
            ans *= 2;
    }
    printf("%lld\n", ans);
    return 0;
}