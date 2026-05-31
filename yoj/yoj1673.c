#include <stdio.h>
#include <string.h>

#define MAXN 1005
#define MAXL 50

int n, m;
struct NAT {
    char LAN[MAXL], WAN[MAXL];
} nat_tab[MAXN];
char IN[5] = "IN", OUT[5] = "OUT";

int main() 
{
    scanf(" %d %d", &n, &m);
    for (int i = 0; i < n; ++i) 
        scanf(" %s %s", nat_tab[i].LAN, nat_tab[i].WAN);
    char mode[5], src[MAXL], dst[MAXL];
    while (m--) {
        scanf(" %s %s %s", mode, src, dst);
        //printf(" %s %s %s\n", mode, src, dst);
        if (strcmp(mode, IN) == 0) {
            int k = -1;
            for (int i = 0; i < n; ++i) {
                if (strcmp(nat_tab[i].WAN, dst) == 0) {
                    k = i;
                    break;
                }
            }
            if (k != -1) 
                printf("%s %s\n", src, nat_tab[k].LAN);
            else 
                printf("DROP\n");
        } else if (strcmp(mode, OUT) == 0) {
            int k = -1;
            for (int i = 0; i < n; ++i) {
                if (strcmp(nat_tab[i].LAN, src) == 0) {
                    k = i;
                    break;
                }
            }
            if (k != -1) 
                printf("%s %s\n", nat_tab[k].WAN, dst);
            else 
                printf("DROP\n");
        } else 
            continue;
    }
    return 0;
}