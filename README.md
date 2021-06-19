# usercall.hpp

MSVC Visual C++ Preprocessor macros for custom calling conventions on functions

## Why?

I originally had this idea while using [microsoft/Detours](https://github.com/microsoft/Detours) to inject a DLL into a running program and hook some functions. The problem with using the standard [Argument Passing and Naming Conventions](https://docs.microsoft.com/en-us/cpp/cpp/argument-passing-and-naming-conventions?view=msvc-160), i.e. __cdecl, __fastcall, __stdcall, etc., is that not every function in the exe used one of these predefined standards. After some research I discovered that this was due to the MSVC Visual C++ compiler optimizing register allocations to prevent stack thrashing. Long story short, I got fed up with writing a custom prologue and epilogue for every function so here we are `usercall.hpp`.

## Features

- [X] `__usercall`
- [X] `__userpurge`
- [X] Register arguments
- [X] Stack arguments
- [X] Register return values
- [X] Auto-generated trampoline functions to call `__usercall/__userpurge` functions from a `__cdecl` interface
- [X] Value functions with explicit return location
- [X] `void` functions
- [X] Prototypes
- [X] Pointer-to-function
- [X] Syntax that closely mirrors standard MSVC Visual C++ function syntax
- [X] IDA Pro types and macros
- [X] Terminology consistent with IDA Pro
- [X] Source code that demonstrates several undocumented tricks available in the [new MSVC preprocessor](https://docs.microsoft.com/en-us/cpp/preprocessor/preprocessor-experimental-overview?view=msvc-160)
- [ ] Stack return values
- [ ] Variadic functions
- [ ] Argument type decorations (get around this with the `using` or `typedef` keywords)
- [X] Annoying line number shenanigans (kind of expected with this level of abuse of the preprocessor)

I add features when I need them; there is no development plan.

## Install

```sh
curl https://raw.githubusercontent.com/widberg/usercall.hpp/master/usercall.hpp
```

## Example

```cpp
#include <cstdio>
#include "usercall.hpp"

AP(int __usercall example AT eax)(int arg AT eax, int arg2 AT ebx, int arg3 AT ecx);
AP(void __usercall example2)();

int main()
{
    int my_a = 1;
    int my_b = 3;
    printf("a = %d, b = %d\n", my_a, my_b);
    my_a = example_trampoline(my_a, 0, my_b);
    printf("a = %d, b = %d\n", my_a, my_b);
    example2_trampoline();
    return my_a;
}

AF(int __usercall example AT eax)(int arg AT eax, int arg2 AT ebx, int arg3 AT ecx)
(
    printf("arg = %d, arg4 = %d\n", arg, arg3);
    arg = arg + arg3;
    printf("arg = %d, arg4 = %d\n", arg, arg3);
    RETURN(arg);
)

AF(void __usercall example2)()
(
    printf("void function\n");
    RETURN;
)
```

## Documentation

### Notes

---

**NEVER** call a `__usercall/__userpurge` function with the standard C++ function call syntax. You **MUST** use a trampoline or an inline assembly block to call these functions from C++ if you don't want a mess of runtime corruption errors. `__usercall/__userpurge` function can safely be passed to detours. You only need to generate a trampoline for `__usercall/__userpurge` functions that you intend to call from C++.

One annoying bug is if an arguments type is not exactly an identifier then `usercall.hpp` trips over itself until the preprocessor puts it out of its misery. A work around to this is to use the `using` or `typedef` keywords to make a single identifier type. Ex. `unsigned int arg` does not work but `using arg_type_t = unsigned int;` and `arg_type_t arg` works. This issue extends to pointer types. I am working to find a solution to this.

This library will destroy the line number accuracy in error messages. This is due to a combination of bugs in MSVC and I cannot fix this. To minimize the effect of this "feature" I recommend testing your `__usercall/__userpurge` functions in their own individual files before merging them all into one file to minimize the guesswork of which function is causing the error.

### Api

---

```cpp
// Define a function
USERCALL_FUNCTION(return_type __usercall/__userpurge name AT reg)(type name AT reg, ..., type name, ...)
(
    body
)

// Declare a function
USERCALL_FUNCTION_PROTOTYPE(return_type __usercall/__userpurge name AT reg)(type name AT reg, ..., type name, ...);

// Define a trampoline, <name>_trampoline, for name
USERCALL_TRAMPOLINE(return_type __usercall/__userpurge name AT reg)(type name AT reg, ..., type name, ...);

// Declare a trampoline,  <name>_trampoline
USERCALL_TRAMPOLINE_PROTOTYPE(return_type __usercall/__userpurge name AT reg)(type name AT reg, ..., type name, ...);

// Define a function and its trampoline
USERCALL_FUNCTION_AND_TRAMPOLINE(return_type __usercall/__userpurge name AT reg)(type name AT reg, ..., type name, ...)
(
    body
)

// Define a pointer to a function
USERCALL_POINTER_TO_FUNCTION(return_type __usercall/__userpurge name AT reg)(type name AT reg, ..., type name, ...)
    (expression);

// Declare a pointer to a function
USERCALL_POINTER_TO_FUNCTION_PROTOTYPE(return_type __usercall/__userpurge name AT reg)(type name AT reg, ..., type name, ...);

// Return value (Only available in non-void __usercall/__userpurge functions)
RETURN(expression);

// Return void (Only available in void __usercall/__userpurge functions)
RETURN;

// The name component of the current __usercall/__userpurge function signature (as an identifier) (Only available in __usercall/__userpurge functions)
USERCALL__FUNCTION__
```

### Options

---

Enable an option by defining it somewhere before including `usercall.hpp` or uncomment it in the "CONFIGURATION OPTIONS" section of your copy of the header. All options are disabled by default.

#### USERCALL_HPP_USE_SHORT_NAMES

---

This option provides shortened aliases for the Api macros. Each one matches the pattern `UC[FTAP][FP]`.

```cpp
#ifdef USERCALL_HPP_USE_SHORT_NAMES
#    define UCFF USERCALL_FUNCTION // Function Function
#    define UCFP USERCALL_FUNCTION_PROTOTYPE // Function Prototype
#    define UCTF USERCALL_TRAMPOLINE // Trampoline Function
#    define UCTP USERCALL_TRAMPOLINE_PROTOTYPE // Trampoline Prototype
#    define UCAF USERCALL_FUNCTION_AND_TRAMPOLINE // And Function
#    define UCAP USERCALL_FUNCTION_AND_TRAMPOLINE_PROTOTYPE // And Prototype
#    define UCPF USERCALL_POINTER_TO_FUNCTION // Pointer Function
#    define UCPP USERCALL_POINTER_TO_FUNCTION_PROTOTYPE // Pointer Prototype
#endif
```

#### USERCALL_HPP_CHECK_RETURN

---

This option will cause a compiler error to occur when you use the `return` keyword instead of the `RETURN` macro in a `__usercall/__userpurge` function. This is disabled by default because defining a macro with the same identifier as a C++ keyword is evil but this is a good check to have for your sanity and it has no effect outside of `__usercall/__userpurge` functions.

#### USERCALL_HPP_USE_HEXRAYS_DEFS

---

This option will make `usercall.hpp` define the types and macros used by hex-ray's IDA Pro. Copied with attribution from the `defs.h` file in the IDA SDK.

#### USERCALL_HPP_USE_REALLY_SHORT_NAMES

---

This option does the same thing as `USERCALL_HPP_USE_SHORT_NAMES` except without the `UC` prefix. I do not recommend using this option because it may cause name collisions that are hard to debug.

## FAQ

### Wouldn't It Have Been Easier to Use Python/AWK/Perl?

Yes.

### Is It Possible to Write a C Compiler in the new MSVC Preprocessor

Probably.
