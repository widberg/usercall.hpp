#include <cstdio>
#define USERCALL_HPP_USE_HEXRAYS_DEFS
#define USERCALL_HPP_CHECK_RETURN
#define USERCALL_HPP_USE_REALLY_SHORT_NAMES
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
