#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 返回值为void类型的函数本质上是 void (*)() 类型的指针(函数指针)
void func1() { printf("func1\n"); }
void func2() { printf("func2\n"); }
void func3() { printf("func3\n"); }

// 函数指针数组
void (*arr[3])();

int main() 
{
    arr[0] = func1;
    arr[1] = func2;
    arr[2] = func3;
    for (int i = 0; i < 3; ++i) 
        arr[i](); // ()是函数调用运算符, 也可写做 (*arr[i])()
    return 0;
}