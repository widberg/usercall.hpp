#include <cstdio>
#include "asm.hpp"

FUNCTION(int, eax, example, (ARGUMENT(int, arg, eax), ARGUMENT(int, arg2, ebx), ARGUMENT(int, arg3, ecx), ARGUMENT(int, arg4, edx), ARGUMENT_STACK(int, arg5, 8)),
{
	printf("arg = %d, arg5 = %d\n", arg, arg5);
	arg = arg + arg5;
	printf("hey %d\n", arg);
	RETURN(arg);
})

FUNCTION(example2, (),
{
	printf("void function\n");
	RETURN();
})

int main()
{
	int a = 1;
	int b = 2;
	printf("hey %d\n", a);
	CALL(a, eax, example, (VALUE(a, eax), VALUE(0, ebx), VALUE(0, ecx), VALUE(0, edx), VALUE_STACK(b)));
	printf("hey %d\n", a);
	CALL(example2, ());
	return a;
}
