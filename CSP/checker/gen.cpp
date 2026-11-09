#include <bits/stdc++.h>
using namespace std;

using distro = uniform_int_distribution<int>;

int main(int argc, char* argv[]) {
    // chrono::system_clock::now().time_since_epoch().count();
    unsigned seed = stoul(argv[1]);
    mt19937 rng(seed);
    int n = distro(1,100)(rng), m = distro(1,100)(rng), k = distro(1,100)(rng), r = distro(1,108)(rng);
    printf("%d %d %d %d\n", n, m, k, r);
    for (int i = 0; i < n+m; i++) {
        int x = distro(1,108)(rng), y = distro(1,108)(rng);
        printf("%d %d\n", x, y);
    }
    return 0;
}