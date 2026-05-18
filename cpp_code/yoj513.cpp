#include <bits/stdc++.h>
using namespace std;

string str;
int m;
long long ans = -1e18;

// 避免多次调用str.size()，减小开销
void dfs(long long sum, int plus_cnt, int start, const int len) 
{
    if (plus_cnt == m) {
        sum += stoll(str.substr(start));
        ans = max(ans, sum);
        return;
    }
    int right_limit = len - 1 - (m - plus_cnt);
    for (int pos = start; pos <= right_limit; pos++) {
        long long add = stoll(str.substr(start, pos - start + 1));
        dfs(sum + add, plus_cnt + 1, pos + 1, len);
    }
}

int main() 
{
    cin >> m >> str;
    dfs(0, 0, 0, str.size());
    cout << ans << '\n';
    return 0;
}