#include <bits/stdc++.h>
using namespace std;

int n;
double s, c, l, p0;
vector<double> p, d;

int main() {
    cin >> s >> c >> l >> p0 >> n;
    p.resize(n + 2);
    d.resize(n + 2);
    p[0] = p0, d[0] = 0, p[n+1] = 0, d[n+1] = s;
    for (int i = 1; i <= n; i++) 
        cin >> d[i] >> p[i];

    double cost = 0, oil_left = 0;
    int cur = 0;
    while (cur < n + 1) {
        double limit = c * l + d[cur];
        auto it = upper_bound(d.begin() + cur, d.end(), limit);
        int idx = distance(d.begin(), it);   // 可达的边界（取不到，开区间）

        if (idx == cur + 1) {
            cout << "No Solution" << '\n';
            return 0;
        }
    
        int next_less = -1;
        for (int i = cur + 1; i < idx; i++) {
            if (p[i] < p[cur]) {
                next_less= i;
                break;
            }
        }

        // 可达的地方没有比当前处油价低的
        if (next_less == -1) {
            int pos = cur + 1;
            for (int i = cur + 1; i < idx; i++) {
                if (p[i] < p[pos]) 
                    pos = i;
            }
            double oil_add = c - oil_left;
            double cost_add = oil_add * p[cur];
            cost += cost_add;
            oil_left = c - (d[pos] - d[cur]) / l;
            cur = pos;
        }
        else {
            double oil_add = (d[next_less] - d[cur]) / l > oil_left ?  
                (d[next_less] - d[cur]) / l - oil_left : 0;
            double cost_add = oil_add * p[cur];
            cost += cost_add;
            oil_left = oil_left + oil_add - (d[next_less] - d[cur]) / l;
            cur = next_less;
        }
    } 

    cout << fixed << setprecision(2) << cost << '\n';
}