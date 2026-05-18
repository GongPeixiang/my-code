#include<bits/stdc++.h>
using namespace std;

struct Student {
    long long num;
    vector <int> score;
};

int main() {
    int n = 0, m = 0, k = 0;
    cin >> n >> m >> k;
    vector <Student> students(n);
    for (int i = 0; i < n; i++) {
        cin >> students[i].num;
        students[i].score.resize(m);
        for (int j = 0; j < m; j++) {
            cin >> students[i].score[j];
        }
    }

    float ave = 0, sum = 0;
    for (int i = 0; i < n; i++) {
        sum += students[i].score[k-1];
    }
    ave = sum / n;

    sort(students.begin(), students.end(), [k](const Student &a, const Student &b) {
        if (a.score[k-1] != b.score[k-1]) 
            return a.score[k-1] > b.score[k-1];
        return a.num < b.num;
    });

    int c = (n + 1) / 2;
    int midscore = students[c-1].score[k-1];

    printf("%.1f %d\n",ave,midscore);

    for (int i = 0; i < n; i++) {
        if (students[i].score[k-1] == midscore) {
            cout << students[i].num << " ";
            for (int j = 0; j < m; j++) {
                cout << students[i].score[j] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}