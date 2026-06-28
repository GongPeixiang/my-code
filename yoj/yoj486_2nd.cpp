#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    string standard;
    cin >> n >> standard;
    vector<string> Seq(n);
    for (int i = 0; i < n; i++) 
        cin >> Seq[i];
    auto cmp = [standard] (const string &a, const string &b) {
        if (a != b) {
            for (int i = 0; i < a.size(); i++) {
                int pos_1 = standard.find(a[i]), pos_2 = standard.find(b[i]);
                if (pos_1 != pos_2)
                    return pos_1 < pos_2;
            }
        }
        return false;
    };
    sort(Seq.begin(), Seq.end(), cmp);
    for (string str : Seq) 
        cout << str << '\n';
}