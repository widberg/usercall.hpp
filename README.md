# usercall.hpp

MSVC Visual C++ Preprocessor macros for custom calling conventions on functions

## Why?

I originally had this idea while using [microsoft/Detours](https://github.com/microsoft/Detours) to inject a DLL into a running program and hook some functions. The problem with using the standard [Argument Passing and Naming Conventions](https://docs.microsoft.com/en-us/cpp/cpp/argument-passing-and-naming-conventions?view=msvc-160), i.e. __cdecl, __fastcall, __stdcall, etc., is that not every function in the exe used one of these predefined standards. After some research I discovered that this was due to the MSVC Visual C++ compiler optimizing register allocations to prevent stack thrashing. Long story short, I got fed up with writing a custom prologue and epilogue for every function so here we are `usercall.hpp`.

## Features

- [X] `__usercall`
- [X] `__userpurge`
- [X] Register arguments
- [X] Auto-generated trampoline functions to call `__usercall/__userpurge` functions from a `__cdecl` interface
- [X] Value functions with explicit return location
- [X] `void` functions
- [X] Prototypes
- [X] Syntax that closely mirrors standard MSVC Visual C++ function syntax
- [X] Terminology consistent with IDA Pro
- [X] Source code that demonstrates several undocumented tricks available in the [new MSVC preprocessor](https://docs.microsoft.com/en-us/cpp/preprocessor/preprocessor-experimental-overview?view=msvc-160)
- [ ] Stack arguments
- [X] Annoying line number shenanigans (kind of expected with this level of abuse of the preprocessor)

## Install

```sh
curl https://raw.githubusercontent.com/widberg/usercall.hpp/master/usercall.hpp
```

## Example

```cpp
// main.cpp

#include <cstdio>
#include "usercall.hpp"

P(int IN eax __usercall(4) example, (int arg IN eax, int arg2 IN ebx, int arg3 IN ecx));
P(void __usercall example2, ());

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

F(int IN eax __usercall(4) example, (int arg IN eax, int arg2 IN ebx, int arg3 IN ecx),
(
    printf("arg = %d, arg4 = %d\n", arg, arg3);
    arg = arg + arg3;
    printf("arg = %d, arg4 = %d\n", arg, arg3);
    return (arg);
))

F(void __usercall example2, (),
(
    printf("void function\n");
    return;
))
```

Becomes

```cpp
// main.cpp

#include <cstdio>

int example(int arg, int arg2, int arg3);
int example_trampoline(int arg, int arg2, int arg3);

void example2();
void example2_trampoline();

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

int example(int arg, int arg2, int arg3);
int example_trampoline(int arg, int arg2, int arg3)
{
    int __asm_hpp_out;
    __asm { mov eax, arg }
    __asm { mov ebx, arg2 }
    __asm { mov ecx, arg3 }
    __asm { sub ESP, 4 }
    __asm { call example }
    __asm { add ESP, 0 }
    __asm { mov __asm_hpp_out, eax }
    return __asm_hpp_out;
}

__declspec(naked) int example(int arg, int arg2, int arg3)
{
    __asm { push EBP }
    __asm { mov EBP, ESP }
    __asm { sub ESP, __LOCAL_SIZE }
    __asm { push EAX }
    __asm { push EBX }
    __asm { push ECX }
    __asm { push EDI }
    __asm { push EDX }
    __asm { push ESI }
    __asm { mov arg, eax }
    __asm { mov arg2, ebx }
    __asm { mov arg3, ecx }
    printf("arg = %d, arg4 = %d\n", arg, arg3);
    arg = arg + arg3;
    printf("arg = %d, arg4 = %d\n", arg, arg3);
    __asm { mov eax, arg }
    __asm { jmp example_return }
example_return:
    __asm { pop ESI }
    __asm { pop EDX }
    __asm { pop EDI }
    __asm { pop ECX }
    __asm { pop EBX }
    __asm { pop EAX }
    __asm { mov ESP, EBP }
    __asm { pop EBP }
    __asm { ret 4 }
}

void example2();
void example2_trampoline()
{
    __asm { sub ESP, 0 }
    __asm { call example2 }
    __asm { add ESP, 0 }
}

__declspec(naked) void example2()
{
    __asm { push EBP }
    __asm { mov EBP, ESP }
    __asm { sub ESP, __LOCAL_SIZE }
    __asm { push EAX }
    __asm { push EBX }
    __asm { push ECX }
    __asm { push EDI }
    __asm { push EDX }
    __asm { push ESI }
    printf("void function\n");
    __asm { jmp example2_return }
example2_return:
    __asm { pop ESI }
    __asm { pop EDX }
    __asm { pop EDI }
    __asm { pop ECX }
    __asm { pop EBX }
    __asm { pop EAX }
    __asm { mov ESP, EBP }
    __asm { pop EBP }
    __asm { ret 0 }
}
```

## Documentation

## FAQ

### Wouldn't It Have Been Easier to Use Python/AWK/Perl?

Yes.

### Is It Possible to Write a C Compiler in the new MSVC Preprocessor

Probably.
