#include <bits/stdc++.h>
using namespace std;

struct State {
    char m, b;
    bool h;
};
char g;

inline bool judge(State s) {
    return s.m == g && s.b == g && s.h;
}

int main() {
    State state;
    cin >> state.m >> state.b >> g >> state.h;
    while (!judge(state)) {
        if (state.m != state.b && !state.h) {
            cout << "Monkey go to " << state.b << '\n';
            state.m = state.b;
        }
        else if (state.m != state.b && state.h) {
            cout << "Monkey climb down from the box" << '\n';
            state.h = false;
        }
        else {
            // state.m在此分支必然等于state.b
            if (state.b != g && state.h) {
                cout << "Monkey climb down from the box" << '\n';
                state.h = false;
            }
            else if (state.b != g && !state.h) {
                cout << "Monkey push the box to " << g << '\n';
                state.b = state.m = g;
            }
            else {
                cout << "Monkey climb onto the box" << '\n';
                state.h = true;
            }
        }
    }
    cout << "Monkey reach the banana" << '\n';
}