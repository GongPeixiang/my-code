#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAXLEN 50

char A[MAXLEN + 5], B[MAXLEN + 5];
bool vals[3];

typedef struct stack {
    char arr[MAXLEN];
    int tp; // tail pointer
} Stack;

// 一种判断方法:适合写成函数式宏一般适合内联,循环、多分支和相对复杂的返回不适合
static inline void push(Stack *s, char ch) { s->arr[s->tp++] = ch; }

static inline char pop(Stack *s) { return s->arr[--s->tp]; }

static inline char peek(Stack *s) { return s->arr[s->tp - 1]; }

static inline bool is_empty(Stack *s) { return s->tp == 0; }

bool cal(char op, bool a, bool b) 
{
    switch (op) {
        case '|': return a || b;
        case '&': return a && b;
        case '>': return !a || b;
        case '=': return a == b;
    }
    return false;
}

int get_order(char op) 
{
    switch (op) {
        case '!': return 5;
        case '&': return 4;
        case '|': return 3;
        case '>': return 2;
        case '-': return 1;
        default: return -1;
    }
}

Stack nums, ops;

bool eval(char str[MAXLEN + 5]) 
{
    memset(&nums, 0, sizeof(Stack));
    memset(&ops, 0, sizeof(Stack));
    nums.tp = ops.tp = 0;
    int n = strlen(str);
    char ch, tmp;
    for (int i = 0; i < n; ++i) {
        ch = str[i];
        if (isalpha(ch)) {
            tmp = vals[ch - 'p'] ? '1' : '0';
            push(&nums, tmp);
        } else {
            if (ch == '(') 
                push(&ops, ch);
            else if (ch == ')') {
                while (!is_empty(&ops) && peek(&ops) != '(') {
                    char op = pop(&ops);
                    if (op == '!') {
                        bool a = pop(&nums) - '0';
                        a = !a;
                        tmp = a ? '1' : '0';
                    } else {
                        // 注意弹出顺序
                        bool b = pop(&nums) - '0' , a = pop(&nums) - '0';
                        bool res = cal(op, a, b);
                        tmp = res ? '1' : '0';
                    }
                    push(&nums, tmp);
                }
                if (!is_empty(&ops)) 
                    pop(&ops);
            } else {
                while (!is_empty(&ops) && peek(&ops) != '(' 
                && get_order(peek(&ops)) >= get_order(ch)) {
                    char op = pop(&ops);
                    if (op == '!') {
                        bool a = pop(&nums) - '0';
                        a = !a;
                        tmp = a ? '1' : '0';
                    } else {
                        bool b = pop(&nums) - '0' , a = pop(&nums) - '0';
                        bool res = cal(op, a, b);
                        tmp = res ? '1' : '0';
                    }
                    push(&nums, tmp);
                }
                push(&ops, ch);
            }
        }
    }
    while (!is_empty(&ops)) {
        char op = pop(&ops);
        if (op == '!') {
            bool a = pop(&nums) - '0';
            a = !a;
            tmp = a ? '1' : '0';
        } else {
            bool b = pop(&nums) - '0' , a = pop(&nums) - '0';
            bool res = cal(op, a, b);
            tmp = res ? '1' : '0';
        }
        push(&nums, tmp);
    }
    return peek(&nums) - '0';
}

int main() 
{
    scanf(" %s %s", A, B);
    
    int cnt = 0;
    for (int k = 0; k < (1 << 3); ++k) {
        for (int i = 0; i < 3; ++i) 
            vals[i] = (k >> (2 - i)) & 1;
        bool res1 = eval(A), res2 = eval(B);
        printf("p=%d q=%d r=%d ", vals[0], vals[1], vals[2]);
        printf("A=%d B=%d A>B=%d", res1, res2, res1 <= res2);
        if (res1 <= res2) 
            ++cnt;
        printf("\n");
    }
    if (cnt == (1 << 3)) 
        printf("yes\n");
    else 
        printf("no\n");

    return 0;
}