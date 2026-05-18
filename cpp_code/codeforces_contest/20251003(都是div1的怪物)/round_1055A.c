#include <stdio.h>

int main() 
{
    int t;
    scanf("%d", &t);
    while (t--) 
    {
        int n;
        scanf("%d", &n);
        int a[105];
        int has_zero = 0;
        int freq[105] = {0};
        for (int i = 0; i < n; i++) 
        {
            scanf("%d", &a[i]);
            if (a[i] == 0) has_zero = 1;
            freq[a[i]]++;
        }
        
        if (has_zero) 
        {
            int distinct_nonzero = 0;
            for (int v = 1; v <= 100; v++) 
            {
                if (freq[v] > 0) distinct_nonzero++;
            }
            printf("%d\n", distinct_nonzero + 1);
        } 
        else 
        {
            int distinct = 0;
            for (int v = 1; v <= 100; v++) 
            {
                if (freq[v] > 0) distinct++;
            }
            printf("%d\n", distinct);
        }
    }
    return 0;
}