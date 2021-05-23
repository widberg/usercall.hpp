#include <cstdio>
#include "asm.hpp"

FN(int IN eax, example, (_(int arg IN eax), _(int arg2 IN ebx), _(int arg3 IN ecx)), (
	printf("arg = %d, arg4 = %d\n", arg, arg3);
	arg = arg + arg3;
	printf("arg = %d, arg4 = %d\n", arg, arg3);
	RETURN(arg);
))

FN(example2, (), (
	printf("void function\n");
	RETURN();
))

int main()
{
	int my_a = 1;
	int my_b = 3;
	printf("a = %d, b = %d\n", my_a, my_b);
	example_trampoline(my_a, 0, my_b);
	printf("a = %d, b = %d\n", my_a, my_b);
	example2_trampoline();
	return my_a;
}
