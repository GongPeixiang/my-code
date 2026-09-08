#include <bits/stdc++.h>
using namespace std;

int main()
{
    string line;
    getline(cin, line);
    
    array<int, 26> abc_cnt = {0};
    array<int, 5> linker_cnt = {0};

    for (int i = 0; i < line.size(); i++) {
        if (line[i] >= 'a' && line[i] <= 'z') {
            int idx = line[i] - 'a';
            abc_cnt[idx]++;
        } else {
            switch(line[i]) {
                case '!': linker_cnt[0]++; break;
                case '&': linker_cnt[1]++; break;
                case '|': linker_cnt[2]++; break;
                case '>': linker_cnt[3]++; break;
                case '-': linker_cnt[4]++; break;
                default: break;
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        if (abc_cnt[i]) {
            char tmp = i + 'a';
            cout << abc_cnt[i] << tmp << ' ';
        }
    }
    cout << '\n';

    if (linker_cnt[0]) 
        cout << linker_cnt[0] << '!' << ' ';
    if (linker_cnt[1]) 
        cout << linker_cnt[1] << '&' << ' ';
    if (linker_cnt[2])
        cout << linker_cnt[2] << '|' << ' ';
    if (linker_cnt[3])
        cout << linker_cnt[3] << '>' << ' ';
    if (linker_cnt[4]) 
        cout << linker_cnt[4] << '-' << ' ';
    cout << '\n'; 
}