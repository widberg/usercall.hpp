#include <cstdio>
#include "asm.hpp"

FN(int, eax, example, (ARG(int, arg, eax), ARG(int, arg2, ebx), ARG(int, arg3, ecx), ARG_STACK(int, arg4, 8)), (
	printf("arg = %d, arg4 = %d\n", arg, arg4);
	arg = arg + arg4;
	printf("hey %d\n", arg);
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
	my_a = example_trampoline(my_a, 0, 0, my_b);
	printf("a = %d, b = %d\n", my_a, my_b);
	example2_trampoline();
	return my_a;
}
