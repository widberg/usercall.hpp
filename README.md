# asm.hpp
C++ Macros for custom calling conventions on functions

```cpp
#include <cstdio>
#include "asm.hpp"

FUNCTION(int, eax, example, (ARGUMENT(int, arg, eax), ARGUMENT(int, arg2, ebx), ARGUMENT(int, arg3, ecx), ARGUMENT(int, arg4, edx)), {
	printf("hey %d\n", arg);
	arg = arg + 1;
	printf("hey %d\n", arg);
	RETURN(arg);
})

int main()
{
	int a = 0;
	printf("hey %d\n", a);
	CALL(a, eax, example, (VALUE(a, eax), VALUE(0, ebx), VALUE(0, ecx), VALUE(0, edx)));
	printf("hey %d\n", a);
	return a;
}
```
