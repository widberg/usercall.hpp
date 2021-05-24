# usercall.hpp

MSVC Visual C++ Macros for custom calling conventions on functions

## Why?

I originally had this idea while using [microsoft/Detours](https://github.com/microsoft/Detours) to inject a DLL into a running program and hook some functions. The problem with using the standard [Argument Passing and Naming Conventions](https://docs.microsoft.com/en-us/cpp/cpp/argument-passing-and-naming-conventions?view=msvc-160), i.e. __cdecl, __fastcall, __stdcall, etc., is that not every function in the exe used one of these predefined standards. After some research I discovered that this was due to the MSVC Visual C++ compiler optimizing register allocations to prevent stack thrashing. Long story short, I got fed up with writing a custom prolog and epilog for every function so here we are `usercall.hpp`.

## TODO

- [ ] __userpurge
- [ ] stack arguments

## Example

```cpp
// main.cpp

#include <cstdio>
#include "usercall.hpp"

F(int IN eax __usercall example, (int arg IN eax, int arg2 IN ebx, int arg3 IN ecx), (
	printf("arg = %d, arg4 = %d\n", arg, arg3);
	arg = arg + arg3;
	printf("arg = %d, arg4 = %d\n", arg, arg3);
	RETURN(arg);
))

F(void __usercall example2, (), (
	printf("void function\n");
	RETURN;
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
```
