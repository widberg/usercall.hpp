// Copyright (c) 2021 widberg
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef USERCALL_HPP
#define USERCALL_HPP

/////////////////////////////////////////////////
//                                             //
//            CONFIGURATION OPTIONS            //
//                                             //
/////////////////////////////////////////////////

// Unimplemented: #define USERCALL_HPP_USE_SHORT_NAMES

/////////////////////////////////////////////////
//                                             //
//             PREPROCESSOR CHECK              //
//                                             //
/////////////////////////////////////////////////

#if !defined(_MSVC_TRADITIONAL) || !_MSVC_TRADITIONAL
#    error Unable to use usercall.hpp with a standard conforming preprocessor
#endif

/////////////////////////////////////////////////
//                                             //
//                  UTILITY                    //
//                                             //
/////////////////////////////////////////////////

#define COMMA() ,

#define EMPTY(...)
#define DEFER(id) id EMPTY()
#define OBSTRUCT(...) __VA_ARGS__ DEFER(EMPTY)()
#define EXPAND(...) __VA_ARGS__

#define TUPLE_GET_FIRST(a, b, ...) a
#define TUPLE_GET_SECOND(a, b, ...) b

#define PAREN_TWO(a, b) \
(a, b \
NEW_LINE() \
)

#define SPACE_DELIM_SECOND_OUT_DEFINE(out_define, input) \
	DEF(input, /HASH()HASH()/) \
	DEFER(DEF)PAREN_TWO(out_define, input) \
	__pragma(warning(push)) \
	__pragma(warning(disable:4067)) \
	UNDEF(input) \
	__pragma(warning(pop))

#define SPLIT(out, input, spliter) \
	DEF(spliter, COMMA()) \
	DEFER(DEF)(out, (input)) \
	UNDEF(spliter)

#define SPLIT_SIZE(out, string, splitter) \
	SPLIT(SPLIT_SIZE_INTERNAL_OUT, string, splitter) \
	DEFER(DEF)(out, EXPAND(DEFER(GET_ARG_COUNT)SPLIT_SIZE_INTERNAL_OUT)) \
	UNDEF(SPLIT_SIZE_INTERNAL_OUT)

#define HASH() #
#define COMMENT /##/
#define NEW_LINE_INTERNAL() HASH()define DUMMY R"dummy(
/*)dummy"
#define NEW_LINE() COMMENT NEW_LINE_INTERNAL() */

#define DEF(a, b) \
	NEW_LINE() \
	HASH()define a b \
	NEW_LINE()

#define UNDEF(a) \
	NEW_LINE() \
	HASH()undef a \
	NEW_LINE()

#define GET_ARG_COUNT_TUPLE_INTERNAL(...) GET_ARG_COUNT##__VA_ARGS__
#define GET_ARG_COUNT_TUPLE(...) EXPAND(DEFER(GET_ARG_COUNT)__VA_ARGS__)
#define GET_ARG_COUNT(...)  INTERNAL_EXPAND_ARGS_PRIVATE(INTERNAL_ARGS_AUGMENTER(__VA_ARGS__))
#define INTERNAL_ARGS_AUGMENTER(...) unused, __VA_ARGS__
#define INTERNAL_EXPAND_ARGS_PRIVATE(...) EXPAND(INTERNAL_GET_ARG_COUNT_PRIVATE(__VA_ARGS__, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define INTERNAL_GET_ARG_COUNT_PRIVATE(_1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _10_, _11_, _12_, _13_, _14_, _15_, _16_, _17_, _18_, _19_, _20_, _21_, _22_, _23_, _24_, _25_, _26_, _27_, _28_, _29_, _30_, _31_, _32_, _33_, _34_, _35_, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, count, ...) count

#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define USERCALL_PREPROCESSOR_ASSERT_DEFINED(macro, message) \
	NEW_LINE() \
	HASH()ifndef macro \
	NEW_LINE() \
	HASH()error message \
	NEW_LINE() \
	HASH()endif \
	NEW_LINE()

/////////////////////////////////////////////////
//                                             //
//               USERCALL PUBLIC               //
//                                             //
/////////////////////////////////////////////////



/////////////////////////////////////////////////
//                                             //
//              USERCALL INTERNAL              //
//                                             //
/////////////////////////////////////////////////

#define __usercall_INTERNAL(callee_clean) \
	COMMA() \
	(callee_clean, 0, callee_clean)

#define __userpurge_INTERNAL(caller_clean) \
	COMMA() \
	(0, caller_clean, caller_clean)

#define __usercall(a) __usercall_INTERNAL(a)
#define __userpurge(a) __userpurge_INTERNAL(a)

// Function

#define MARTIAL_FN_INTERNAL_(...) FUNCTION(CAT(EXPAND, __VA_ARGS__))

#define MARTIAL_FN_INTERNAL_INTERNAL(a, ...) \
	SPLIT(OUT, a, IN) \
	DEFER(MARTIAL_FN_INTERNAL_)(OUT, __VA_ARGS__) \
	UNDEF(OUT)


#define MARTIAL_FN_INTERNAL(a, ...) \
	__pragma(push_macro("__usercall")) \
	UNDEF(__usercall) \
	DEF(__usercall, COMMA() (0, 0, 0)) \
	MARTIAL_FN_INTERNAL_INTERNAL(a, __VA_ARGS__) \
	__pragma(pop_macro("__usercall"))

#define F(...) DEFER(MARTIAL_FN_INTERNAL)(__VA_ARGS__)

// Prototype

#define PROTOTYPE(return_type, function_name, arguments) \
return_type function_name(DEFER(ARGUMENT_LIST)(CAT(EXPAND, arguments))); \
return_type function_name##_trampoline(DEFER(ARGUMENT_LIST)(CAT(EXPAND, arguments)));

#define MARTIAL_P_INTERNAL_(a, args) \
	SPLIT(OUT, a, IN) \
	PROTOTYPE(DEFER(CAT)(TUPLE_GET_FIRST, OUT), DEFER(TUPLE_GET_SECOND)(a), args) \
	UNDEF(OUT)

#define MARTIAL_P_INTERNAL(a, args) \
	__pragma(push_macro("__usercall")) \
	UNDEF(__usercall) \
	DEF(__usercall, __usercall_INTERNAL(0)) \
	MARTIAL_P_INTERNAL_(a, args) \
	__pragma(pop_macro("__usercall"))

#define P(...) DEFER(MARTIAL_P_INTERNAL)(__VA_ARGS__)

// ARGUMENTS

#define ARGUMENT(argument_type_argument_name, argument_expression) \
	(argument_type_argument_name, \
	ARGUMENT_NAME, \
	(__asm { mov ARGUMENT_NAME, argument_expression }), \
	(__asm { mov argument_expression, ARGUMENT_NAME }))

#define ARGUMENT_STACK(argument_type_argument_name, argument_offset) \
	(argument_type_argument_name, \
	ARGUMENT_NAME, \
	(__asm { push EAX }; __asm { mov EAX, [EBP + argument_offset] } __asm { mov ARGUMENT_NAME, EAX } __asm { pop EAX }), \
	(__asm { push ARGUMENT_NAME }))

// ARGUMENT_LIST

#define ARGUMENT_LIST_1_INTERNAL(argument_type_argument_name, ...) argument_type_argument_name

#define ARGUMENT_LIST_0()
#define ARGUMENT_LIST_1(argument) \
	ARGUMENT_TUPLE_FROM_STRING(ARGUMENT_TUPLE, argument) \
	DEFER(CAT)(ARGUMENT_LIST_1_INTERNAL, ARGUMENT_TUPLE) \
	UNDEF(ARGUMENT_TUPLE)
#define ARGUMENT_LIST_2(argument, ...) \
	ARGUMENT_LIST_1(argument), EXPAND(ARGUMENT_LIST_1(__VA_ARGS__))
#define ARGUMENT_LIST_3(argument, ...) \
	ARGUMENT_LIST_1(argument), EXPAND(ARGUMENT_LIST_2(__VA_ARGS__))
#define ARGUMENT_LIST_4(argument, ...) \
	ARGUMENT_LIST_1(argument), EXPAND(ARGUMENT_LIST_3(__VA_ARGS__))
#define ARGUMENT_LIST_5(argument, ...) \
	ARGUMENT_LIST_1(argument), EXPAND(ARGUMENT_LIST_4(__VA_ARGS__))
#define ARGUMENT_LIST_6(argument, ...) \
	ARGUMENT_LIST_1(argument), EXPAND(ARGUMENT_LIST_5(__VA_ARGS__))
#define ARGUMENT_LIST_7(argument, ...) \
	ARGUMENT_LIST_1(argument), EXPAND(ARGUMENT_LIST_6(__VA_ARGS__))
#define ARGUMENT_LIST_8(argument, ...) \
	ARGUMENT_LIST_1(argument), EXPAND(ARGUMENT_LIST_7(__VA_ARGS__))
#define ARGUMENT_LIST_9(argument, ...) \
	ARGUMENT_LIST_1(argument), EXPAND(ARGUMENT_LIST_8(__VA_ARGS__))
#define ARGUMENT_LIST_10(argument, ...) \
	ARGUMENT_LIST_1(argument), EXPAND(ARGUMENT_LIST_9(__VA_ARGS__))
#define ARGUMENT_LIST_11(argument, ...) \
	ARGUMENT_LIST_1(argument), EXPAND(ARGUMENT_LIST_10(__VA_ARGS__))
#define ARGUMENT_LIST_12(argument, ...) \
	ARGUMENT_LIST_1(argument), EXPAND(ARGUMENT_LIST_11(__VA_ARGS__))
#define ARGUMENT_LIST_13(argument, ...) \
	ARGUMENT_LIST_1(argument), EXPAND(ARGUMENT_LIST_12(__VA_ARGS__))
#define ARGUMENT_LIST_14(argument, ...) \
	ARGUMENT_LIST_1(argument), EXPAND(ARGUMENT_LIST_13(__VA_ARGS__))
#define ARGUMENT_LIST_15(argument, ...) \
	ARGUMENT_LIST_1(argument), EXPAND(ARGUMENT_LIST_14(__VA_ARGS__))
#define ARGUMENT_LIST_16(argument, ...) \
	ARGUMENT_LIST_1(argument), EXPAND(ARGUMENT_LIST_15(__VA_ARGS__))
#define ARGUMENT_LIST(...)  EXPAND(DEFER(CAT)(ARGUMENT_LIST_, GET_ARG_COUNT(__VA_ARGS__))(__VA_ARGS__))

// ARGUMENT_LOAD

#define ARGUMENT_TUPLE_FROM_STRING(out, string) \
	SPLIT(ARGUMENT_TWO_TUPLE, string, IN) \
	DEFER(DEF)(out, EXPAND(DEFER(ARGUMENT)ARGUMENT_TWO_TUPLE)) \
	UNDEF(ARGUMENT_TWO_TUPLE)

#define ARGUMENT_LOAD_1_INTERNAL(argument_type_argument_name, argument_name, argument_expression, ...) \
	SPACE_DELIM_SECOND_OUT_DEFINE(ARGUMENT_NAME, argument_type_argument_name) \
	EXPAND##argument_expression \
	UNDEF(ARGUMENT_NAME)

#define ARGUMENT_LOAD_0()
#define ARGUMENT_LOAD_1(argument) \
	ARGUMENT_TUPLE_FROM_STRING(ARGUMENT_TUPLE, argument) \
	DEFER(CAT)(ARGUMENT_LOAD_1_INTERNAL, ARGUMENT_TUPLE) \
	UNDEF(ARGUMENT_TUPLE)
#define ARGUMENT_LOAD_2(argument, ...) \
	ARGUMENT_LOAD_1(argument) EXPAND(ARGUMENT_LOAD_1(__VA_ARGS__))
#define ARGUMENT_LOAD_3(argument, ...) \
	ARGUMENT_LOAD_1(argument) EXPAND(ARGUMENT_LOAD_2(__VA_ARGS__))
#define ARGUMENT_LOAD_4(argument, ...) \
	ARGUMENT_LOAD_1(argument) EXPAND(ARGUMENT_LOAD_3(__VA_ARGS__))
#define ARGUMENT_LOAD_5(argument, ...) \
	ARGUMENT_LOAD_1(argument) EXPAND(ARGUMENT_LOAD_4(__VA_ARGS__))
#define ARGUMENT_LOAD_6(argument, ...) \
	ARGUMENT_LOAD_1(argument) EXPAND(ARGUMENT_LOAD_5(__VA_ARGS__))
#define ARGUMENT_LOAD_7(argument, ...) \
	ARGUMENT_LOAD_1(argument) EXPAND(ARGUMENT_LOAD_6(__VA_ARGS__))
#define ARGUMENT_LOAD_8(argument, ...) \
	ARGUMENT_LOAD_1(argument) EXPAND(ARGUMENT_LOAD_7(__VA_ARGS__))
#define ARGUMENT_LOAD_9(argument, ...) \
	ARGUMENT_LOAD_1(argument) EXPAND(ARGUMENT_LOAD_8(__VA_ARGS__))
#define ARGUMENT_LOAD_10(argument, ...) \
	ARGUMENT_LOAD_1(argument) EXPAND(ARGUMENT_LOAD_9(__VA_ARGS__))
#define ARGUMENT_LOAD_11(argument, ...) \
	ARGUMENT_LOAD_1(argument) EXPAND(ARGUMENT_LOAD_10(__VA_ARGS__))
#define ARGUMENT_LOAD_12(argument, ...) \
	ARGUMENT_LOAD_1(argument) EXPAND(ARGUMENT_LOAD_11(__VA_ARGS__))
#define ARGUMENT_LOAD_13(argument, ...) \
	ARGUMENT_LOAD_1(argument) EXPAND(ARGUMENT_LOAD_12(__VA_ARGS__))
#define ARGUMENT_LOAD_14(argument, ...) \
	ARGUMENT_LOAD_1(argument) EXPAND(ARGUMENT_LOAD_13(__VA_ARGS__))
#define ARGUMENT_LOAD_15(argument, ...) \
	ARGUMENT_LOAD_1(argument) EXPAND(ARGUMENT_LOAD_14(__VA_ARGS__))
#define ARGUMENT_LOAD_16(argument, ...) \
	ARGUMENT_LOAD_1(argument) EXPAND(ARGUMENT_LOAD_15(__VA_ARGS__))
#define ARGUMENT_LOAD(...)  EXPAND(DEFER(CAT)(ARGUMENT_LOAD_, GET_ARG_COUNT(__VA_ARGS__))(__VA_ARGS__))

// BEGIN_FUNCTION

#define BEGIN_FUNCTION(return_type, return_expression, function_name, ...) \
	DEF(USERCALL__FUNCTION__, function_name) \
	DEF(RETURN_LOCATION, return_expression) \
	__declspec(naked) return_type function_name(ARGUMENT_LIST(__VA_ARGS__)) { \
	__asm { push EBP } \
	__asm { mov EBP, ESP } \
	__asm { sub ESP, __LOCAL_SIZE } \
	__asm { push EAX } \
	__asm { push EBX } \
	__asm { push ECX } \
	__asm { push EDI } \
	__asm { push EDX } \
	__asm { push ESI } \
	ARGUMENT_LOAD(__VA_ARGS__)

// RETURN

#define RETURN_VALUE(return_expression) \
	__asm { mov RETURN_LOCATION, return_expression } \
	__asm { jmp DEFER(CAT)(USERCALL__FUNCTION__, _return) }

#define RETURN_VOID \
	__asm { jmp DEFER(CAT)(USERCALL__FUNCTION__, _return) }

// END_FUNCTION

#define END_FUNCTION() \
DEFER(CAT)(USERCALL__FUNCTION__, _return): \
UNDEF(USERCALL__FUNCTION__) \
	__asm { pop ESI } \
	__asm { pop EDX } \
	__asm { pop EDI } \
	__asm { pop ECX } \
	__asm { pop EBX } \
	__asm { pop EAX } \
	__asm { mov ESP, EBP } \
	__asm { pop EBP } \
	__asm { ret CALLEE_CLEAN } \
	} \
	UNDEF(RETURN_LOCATION)

// TRAMPOLINE_LOAD

#define TRAMPOLINE_LOAD_1_INTERNAL(argument_type_argument_name, argument_name, argument_expression, trampoline_expression) \
	SPACE_DELIM_SECOND_OUT_DEFINE(ARGUMENT_NAME, argument_type_argument_name) \
	EXPAND##trampoline_expression \
	UNDEF(ARGUMENT_NAME)

#define TRAMPOLINE_LOAD_0()
#define TRAMPOLINE_LOAD_1(argument) \
	ARGUMENT_TUPLE_FROM_STRING(ARGUMENT_TUPLE, argument) \
	DEFER(CAT)(TRAMPOLINE_LOAD_1_INTERNAL, ARGUMENT_TUPLE) \
	UNDEF(ARGUMENT_TUPLE)
#define TRAMPOLINE_LOAD_2(argument, ...) \
	TRAMPOLINE_LOAD_1(argument) EXPAND(TRAMPOLINE_LOAD_1(__VA_ARGS__))
#define TRAMPOLINE_LOAD_3(argument, ...) \
	TRAMPOLINE_LOAD_1(argument) EXPAND(TRAMPOLINE_LOAD_2(__VA_ARGS__))
#define TRAMPOLINE_LOAD_4(argument, ...) \
	TRAMPOLINE_LOAD_1(argument) EXPAND(TRAMPOLINE_LOAD_3(__VA_ARGS__))
#define TRAMPOLINE_LOAD_5(argument, ...) \
	TRAMPOLINE_LOAD_1(argument) EXPAND(TRAMPOLINE_LOAD_4(__VA_ARGS__))
#define TRAMPOLINE_LOAD_6(argument, ...) \
	TRAMPOLINE_LOAD_1(argument) EXPAND(TRAMPOLINE_LOAD_5(__VA_ARGS__))
#define TRAMPOLINE_LOAD_7(argument, ...) \
	TRAMPOLINE_LOAD_1(argument) EXPAND(TRAMPOLINE_LOAD_6(__VA_ARGS__))
#define TRAMPOLINE_LOAD_8(argument, ...) \
	TRAMPOLINE_LOAD_1(argument) EXPAND(TRAMPOLINE_LOAD_7(__VA_ARGS__))
#define TRAMPOLINE_LOAD_9(argument, ...) \
	TRAMPOLINE_LOAD_1(argument) EXPAND(TRAMPOLINE_LOAD_8(__VA_ARGS__))
#define TRAMPOLINE_LOAD_10(argument, ...) \
	TRAMPOLINE_LOAD_1(argument) EXPAND(TRAMPOLINE_LOAD_9(__VA_ARGS__))
#define TRAMPOLINE_LOAD_11(argument, ...) \
	TRAMPOLINE_LOAD_1(argument) EXPAND(TRAMPOLINE_LOAD_10(__VA_ARGS__))
#define TRAMPOLINE_LOAD_12(argument, ...) \
	TRAMPOLINE_LOAD_1(argument) EXPAND(TRAMPOLINE_LOAD_11(__VA_ARGS__))
#define TRAMPOLINE_LOAD_13(argument, ...) \
	TRAMPOLINE_LOAD_1(argument) EXPAND(TRAMPOLINE_LOAD_12(__VA_ARGS__))
#define TRAMPOLINE_LOAD_14(argument, ...) \
	TRAMPOLINE_LOAD_1(argument) EXPAND(TRAMPOLINE_LOAD_13(__VA_ARGS__))
#define TRAMPOLINE_LOAD_15(argument, ...) \
	TRAMPOLINE_LOAD_1(argument) EXPAND(TRAMPOLINE_LOAD_14(__VA_ARGS__))
#define TRAMPOLINE_LOAD_16(argument, ...) \
	TRAMPOLINE_LOAD_1(argument) EXPAND(TRAMPOLINE_LOAD_15(__VA_ARGS__))
#define TRAMPOLINE_LOAD(...)  EXPAND(DEFER(CAT)(TRAMPOLINE_LOAD_, GET_ARG_COUNT(__VA_ARGS__))(__VA_ARGS__))

// FUNCTION

#define DEFINE_CLEAN(callee, caller, args) \
DEF(CALLEE_CLEAN, callee) \
DEF(CALLER_CLEAN, caller) \
DEF(ARGS_SIZE, args)

#define FUNCTION_5(return_type, return_expression, function_name, arguments, body) \
	PROTOTYPE(return_type, EMPTY##function_name, arguments) \
	return_type DEFINE_CLEAN##function_name##_trampoline(ARGUMENT_LIST(EXPAND##arguments)) { return_type __asm_hpp_out; TRAMPOLINE_LOAD(EXPAND##arguments) __asm { sub ESP, ARGS_SIZE } __asm { call EMPTY##function_name } __asm { add ESP, CALLER_CLEAN } __asm { mov __asm_hpp_out, return_expression } return __asm_hpp_out; } \
	BEGIN_FUNCTION(return_type, return_expression, EMPTY##function_name, EXPAND##arguments) \
	DEF(return, RETURN_VALUE) \
		EXPAND##body \
	END_FUNCTION() \
	UNDEF(return) \
	UNDEF(CALLEE_CLEAN) \
	UNDEF(CALLER_CLEAN) \
	UNDEF(ARGS_SIZE)

#define USERCALL_void USERCALL_void

#define FUNCTION_4(return_type, function_name, arguments, body) \
	USERCALL_PREPROCESSOR_ASSERT_DEFINED(USERCALL_##return_type, "Expected void. Maybe you forgot the return location.") \
	PROTOTYPE(void, EMPTY##function_name, arguments) \
	void DEFINE_CLEAN##function_name##_trampoline(ARGUMENT_LIST(EXPAND##arguments)) { TRAMPOLINE_LOAD(EXPAND##arguments) __asm { sub ESP, ARGS_SIZE } __asm { call EMPTY##function_name } __asm { add ESP, CALLER_CLEAN } } \
	BEGIN_FUNCTION(void,, EMPTY##function_name, EXPAND##arguments) \
	DEF(return, RETURN_VOID) \
		EXPAND##body \
	END_FUNCTION() \
	UNDEF(return) \
	UNDEF(CALLEE_CLEAN) \
	UNDEF(CALLER_CLEAN) \
	UNDEF(ARGS_SIZE)

#define FUNCTION(...)  EXPAND(DEFER(CAT)(FUNCTION_, GET_ARG_COUNT(__VA_ARGS__))(__VA_ARGS__))

#define PUSH_ARGUMENT(argument) __asm { push argument }

#define POP_ARGUMENT(argument) __asm { pop argument }

#endif // USERCALL_HPP
