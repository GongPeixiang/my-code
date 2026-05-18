#include <stdio.h> 
#include "stack.h"

DECLARE_STACK(int);

int main() 
{
	Stack_int s;
	stack_init_int(&s, 5);

	for (size_t i = 0; i < 10; i++) 
		stack_push_int(&s, i);

	size_t size = stack_size_int(&s);

	for (int i = 0; i < size; i++) {
		int ret = stack_pop_int(&s);
		printf("%d ", ret);
	}

	stack_clear_int(&s);

	return 0;
}