#include <iostream>

template <typename... Args>
void print(const Args&... args) 
{
    (..., (std::cout << args << ' '));
    std::cout << '\n';
}

int main() 
{
    print("hello", 123, 3.14);
    return 0;
}