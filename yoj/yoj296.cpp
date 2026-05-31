#include<bits/stdc++.h>
using namespace std;

struct Student {
    string code;
    int p;
    vector<float> times;
};

struct TimeCount {
    float time;
    int cnt;
};

int main() {
    int n = 0, k = 0;
    cin >> n >> k;

    vector<Student> student;
    student.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> student[i].code >> student[i].p;
        student[i].times.resize(student[i].p);
        for (int j = 0; j < student[i].p; j++) {
            cin >> student[i].times[j];
        }
    }

    vector<TimeCount> timecnt;
    
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            float a = (float)j + 1 + 0.1 * ((float)i + 1);
            int cnt = 0;
            for (int l = 0; l < n; l++) {
                for (int m = 0; m < student[l].times.size(); m++) {
                    if (student[l].times[m] == a) {
                        cnt++;
                        break;
                    }
                }
            }
            timecnt.push_back(TimeCount{a,cnt});
        }
    }

    auto compare = [] (const TimeCount &a, const TimeCount &b) {
        if (a.cnt != b.cnt) 
            return a.cnt < b.cnt;
        return a.time < b.time;
    };
    
    sort(timecnt.begin(),timecnt.end(),compare);
    for (int i = 0; i < k; i++) {
        cout << timecnt[i].time << ' ' << timecnt[i].cnt << endl;
    }

    return 0;
}