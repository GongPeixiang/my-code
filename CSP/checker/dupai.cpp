#include <bits/stdc++.h>
using namespace std;

#ifdef _WIN32
    #define COMPARE "fc aout.txt bout.txt > nul"
    #define NULL_IS_NUL 1
#else 
    #define COMPARE "diff -q aout.txt bout.txt > /dev/null"
#endif

char cmd[256];

int main() {
    for (int i = 1; i <= 100000; i++) {
        sprintf(cmd, "gen.exe %d > in.txt", i);
        system(cmd);
        if (system("a < in.txt > aout.txt")) {
            printf("[test %d]: RE\n");
            return 1;
        }
        system("b < in.txt > bout.txt");
        if (system(COMPARE)) {
            printf("[test %d]: WA\n", i);
            printf("INPUT:\n");
            system("type in.txt");
            printf("EXPECTED:\n");
            system("type bout.txt");
            printf("YOUR ANSWER:\n");
            system("type aout.txt");
            system("copy in.txt fail_in.txt > nul");
            return 1;
        }
        if (i%100 == 0) printf("PASSED %d tests\n", i);
    }
    printf("ALL PASSED\n");
    return 0;
}