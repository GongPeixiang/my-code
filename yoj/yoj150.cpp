#include <bits/stdc++.h>
using namespace std;

struct Student {
    string id;
    int score;
    int rank;
};

int main() {
    int n;
    cin >> n;
    vector<Student> students(n);
    for (int i = 0; i < n; i++) {
        cin >> students[i].id >> students[i].score;
    }
    sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
        if (a.score != b.score) 
            return a.score > b.score;
        return a.id < b.id;
    });
    students[0].rank = 1;
    int idx = 1;
    for (int i = 1; i < n; i++) {
        if (students[i].score < students[i - 1].score) 
            idx = i + 1;
        students[i].rank = idx;
    }
    for (Student s : students) {
        cout << s.rank << ' ' << s.id << ' ' << s.score << '\n';
    }
    return 0;
}