#include <bits/stdc++.h>
using namespace std;

constexpr double PI = 3.1415926535;

void solve_t1() 
{
    double init = 5.0;
    for (int i = 0; i < 3; i++) {
        double tmp = 1 / init;
        init = 1 + tmp;
    }
    cout << fixed << setprecision(3) << init << '\n';
}

void solve_t2() 
{
    double ans = sqrt(4.0 * 4.0 + 3.0 * 3.0);
    cout << fixed << setprecision(3) << ans << '\n';
}

void solve_t3() 
{
    double ans = sqrt((1.0 - cos(PI / 3)) * 0.5);
    cout << fixed << setprecision(3) << ans << '\n';
}

void solve_t4() 
{
    double a = sin(PI /4), b = cos(PI / 4);
    double ans = 2 * pow(a, 2) + a * b - pow(b, 2);
    cout << fixed << setprecision(3) << ans << '\n';
}

void solve_t5() 
{
    double ans = 2 * sqrt(5) * (sqrt(6) + sqrt(3)) / 9.0;
    cout << fixed << setprecision(3) << ans << '\n';
}

void solve_t6() 
{
    double ans = (log(5) * log(3) - log(2)) / sin(PI /3);
    cout << fixed << setprecision(3) << ans << '\n';
}

int main() 
{
    solve_t1();
    solve_t2();
    solve_t3();
    solve_t4();
    solve_t5();
    solve_t6();
    return 0;
}