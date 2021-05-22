#include <cstdio>

#include "asm.hpp"
#define RETURN_LOCATION eax
FUNCTION(int, example, (ARGUMENT(int, arg, eax), ARGUMENT(int, arg2, ebx), ARGUMENT(int, arg3, ebx), ARGUMENT(int, arg4, ebx)), {
	printf("hey %d\n", arg);
	arg = arg + 1;
	printf("hey %d\n", arg);
	RETURN(arg);
})
#undef RETURN_LOCATION

int main()
{
	int a = 0;
	printf("hey %d\n", a);
	CALL(a, eax, example, (VALUE(a, eax)));
	printf("hey %d\n", a);
	return a;
}
