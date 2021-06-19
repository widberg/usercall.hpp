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

// #include <intrin.h> // MSVC Visual C++ compiler intrinsics

/////////////////////////////////////////////////
//                                             //
//            CONFIGURATION OPTIONS            //
//                                             //
/////////////////////////////////////////////////

// #define USERCALL_HPP_USE_SHORT_NAMES
// #define USERCALL_HPP_USE_HEXRAYS_DEFS
// #define USERCALL_HPP_CHECK_RETURN
// #define USERCALL_HPP_USE_REALLY_SHORT_NAMES

/////////////////////////////////////////////////
//                                             //
//               USERCALL PUBLIC               //
//                                             //
/////////////////////////////////////////////////

#ifdef USERCALL_HPP_USE_SHORT_NAMES
#    define UCFF USERCALL_FUNCTION
#    define UCFP USERCALL_FUNCTION_PROTOTYPE
#    define UCTF USERCALL_TRAMPOLINE
#    define UCTP USERCALL_TRAMPOLINE_PROTOTYPE
#    define UCAF USERCALL_FUNCTION_AND_TRAMPOLINE
#    define UCAP USERCALL_FUNCTION_AND_TRAMPOLINE_PROTOTYPE
#    define UCPF USERCALL_POINTER_TO_FUNCTION
#    define UCPP USERCALL_POINTER_TO_FUNCTION_PROTOTYPE
#endif

#ifdef USERCALL_HPP_USE_REALLY_SHORT_NAMES
#    define FF USERCALL_FUNCTION
#    define FP USERCALL_FUNCTION_PROTOTYPE
#    define TF USERCALL_TRAMPOLINE
#    define TP USERCALL_TRAMPOLINE_PROTOTYPE
#    define AF USERCALL_FUNCTION_AND_TRAMPOLINE
#    define AP USERCALL_FUNCTION_AND_TRAMPOLINE_PROTOTYPE
#    define PF USERCALL_POINTER_TO_FUNCTION
#    define PP USERCALL_POINTER_TO_FUNCTION_PROTOTYPE
#endif

/////////////////////////////////////////////////
//                                             //
//             PREPROCESSOR CHECK              //
//                                             //
/////////////////////////////////////////////////

#if !defined(_MSVC_TRADITIONAL) || !_MSVC_TRADITIONAL
#    error "Unable to use usercall.hpp with a preprocessor other than the new MSVC preprocessor"
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

#define TUPLE_GET_FIRST(a, ...) a
#define TUPLE_GET_SECOND(a, b, ...) b
#define TUPLE_GET_THIRD(a, b, c, ...) c
#define TUPLE_GET_FOURTH(a, b, c, d, ...) d

#define TUPLE_POP_FRONT(a, ...) __VA_ARGS__

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

#define HASH() #
#define COMMENT /##/
#define NEW_LINE_INTERNAL() HASH()define DUMMY R"dummy(
/*)dummy"
#define NEW_LINE() COMMENT NEW_LINE_INTERNAL() */

#define DEF(a, b) \
	NEW_LINE() \
	HASH()define a b \
	NEW_LINE()

#define UNDEF(...) \
	NEW_LINE() \
	HASH()undef __VA_ARGS__ \
	NEW_LINE()

#define IF(...) \
	NEW_LINE() \
	HASH()if __VA_ARGS__ \
	NEW_LINE()

#define ELSE(...) \
	NEW_LINE() \
	HASH()else __VA_ARGS__ \
	NEW_LINE()

#define ENDIF() \
	NEW_LINE() \
	HASH()endif \
	NEW_LINE()

#define SELECT(switch, a, ...) \
	IF(switch) \
		a \
	ELSE() \
		__VA_ARGS__ \
	ENDIF()

#define GET_ARG_COUNT_TUPLE_INTERNAL(...) GET_ARG_COUNT##__VA_ARGS__
#define GET_ARG_COUNT_TUPLE(...) EXPAND(DEFER(GET_ARG_COUNT)__VA_ARGS__)
#define GET_ARG_COUNT(...)  INTERNAL_EXPAND_ARGS_PRIVATE(INTERNAL_ARGS_AUGMENTER(__VA_ARGS__))
#define INTERNAL_ARGS_AUGMENTER(...) unused, __VA_ARGS__
#define INTERNAL_EXPAND_ARGS_PRIVATE(...) EXPAND(INTERNAL_GET_ARG_COUNT_PRIVATE(__VA_ARGS__, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define INTERNAL_GET_ARG_COUNT_PRIVATE(_1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _10_, _11_, _12_, _13_, _14_, _15_, _16_, _17_, _18_, _19_, _20_, _21_, _22_, _23_, _24_, _25_, _26_, _27_, _28_, _29_, _30_, _31_, _32_, _33_, _34_, _35_, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, count, ...) count

#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define USERCALL_FOR_EACH_LR_0(op, ...)
#define USERCALL_FOR_EACH_LR_1(op, argument) \
	op(argument)
#define USERCALL_FOR_EACH_LR_2(op, argument, ...) \
	USERCALL_FOR_EACH_LR_1(op, argument) EXPAND(USERCALL_FOR_EACH_LR_1(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_3(op, argument, ...) \
	USERCALL_FOR_EACH_LR_1(op, argument) EXPAND(USERCALL_FOR_EACH_LR_2(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_4(op, argument, ...) \
	USERCALL_FOR_EACH_LR_1(op, argument) EXPAND(USERCALL_FOR_EACH_LR_3(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_5(op, argument, ...) \
	USERCALL_FOR_EACH_LR_1(op, argument) EXPAND(USERCALL_FOR_EACH_LR_4(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_6(op, argument, ...) \
	USERCALL_FOR_EACH_LR_1(op, argument) EXPAND(USERCALL_FOR_EACH_LR_5(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_7(op, argument, ...) \
	USERCALL_FOR_EACH_LR_1(op, argument) EXPAND(USERCALL_FOR_EACH_LR_6(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_8(op, argument, ...) \
	USERCALL_FOR_EACH_LR_1(op, argument) EXPAND(USERCALL_FOR_EACH_LR_7(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_9(op, argument, ...) \
	USERCALL_FOR_EACH_LR_1(op, argument) EXPAND(USERCALL_FOR_EACH_LR_8(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_10(op, argument, ...) \
	USERCALL_FOR_EACH_LR_1(op, argument) EXPAND(USERCALL_FOR_EACH_LR_9(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_11(op, argument, ...) \
	USERCALL_FOR_EACH_LR_1(op, argument) EXPAND(USERCALL_FOR_EACH_LR_10(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_12(op, argument, ...) \
	USERCALL_FOR_EACH_LR_1(op, argument) EXPAND(USERCALL_FOR_EACH_LR_11(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_13(op, argument, ...) \
	USERCALL_FOR_EACH_LR_1(op, argument) EXPAND(USERCALL_FOR_EACH_LR_12(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_14(op, argument, ...) \
	USERCALL_FOR_EACH_LR_1(op, argument) EXPAND(USERCALL_FOR_EACH_LR_13(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_15(op, argument, ...) \
	USERCALL_FOR_EACH_LR_1(op, argument) EXPAND(USERCALL_FOR_EACH_LR_14(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_16(op, argument, ...) \
	USERCALL_FOR_EACH_LR_1(op, argument) EXPAND(USERCALL_FOR_EACH_LR_15(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR(op, ...)  EXPAND(DEFER(CAT)(USERCALL_FOR_EACH_LR_, GET_ARG_COUNT(__VA_ARGS__))(op, __VA_ARGS__))

#define USERCALL_FOR_EACH_LR_COMMAS_0(op, ...)
#define USERCALL_FOR_EACH_LR_COMMAS_1(op, argument) \
	op(argument)
#define USERCALL_FOR_EACH_LR_COMMAS_2(op, argument, ...) \
	USERCALL_FOR_EACH_LR_COMMAS_1(op, argument), EXPAND(USERCALL_FOR_EACH_LR_COMMAS_1(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_COMMAS_3(op, argument, ...) \
	USERCALL_FOR_EACH_LR_COMMAS_1(op, argument), EXPAND(USERCALL_FOR_EACH_LR_COMMAS_2(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_COMMAS_4(op, argument, ...) \
	USERCALL_FOR_EACH_LR_COMMAS_1(op, argument), EXPAND(USERCALL_FOR_EACH_LR_COMMAS_3(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_COMMAS_5(op, argument, ...) \
	USERCALL_FOR_EACH_LR_COMMAS_1(op, argument), EXPAND(USERCALL_FOR_EACH_LR_COMMAS_4(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_COMMAS_6(op, argument, ...) \
	USERCALL_FOR_EACH_LR_COMMAS_1(op, argument), EXPAND(USERCALL_FOR_EACH_LR_COMMAS_5(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_COMMAS_7(op, argument, ...) \
	USERCALL_FOR_EACH_LR_COMMAS_1(op, argument), EXPAND(USERCALL_FOR_EACH_LR_COMMAS_6(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_COMMAS_8(op, argument, ...) \
	USERCALL_FOR_EACH_LR_COMMAS_1(op, argument), EXPAND(USERCALL_FOR_EACH_LR_COMMAS_7(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_COMMAS_9(op, argument, ...) \
	USERCALL_FOR_EACH_LR_COMMAS_1(op, argument), EXPAND(USERCALL_FOR_EACH_LR_COMMAS_8(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_COMMAS_10(op, argument, ...) \
	USERCALL_FOR_EACH_LR_COMMAS_1(op, argument), EXPAND(USERCALL_FOR_EACH_LR_COMMAS_9(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_COMMAS_11(op, argument, ...) \
	USERCALL_FOR_EACH_LR_COMMAS_1(op, argument), EXPAND(USERCALL_FOR_EACH_LR_COMMAS_10(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_COMMAS_12(op, argument, ...) \
	USERCALL_FOR_EACH_LR_COMMAS_1(op, argument), EXPAND(USERCALL_FOR_EACH_LR_COMMAS_11(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_COMMAS_13(op, argument, ...) \
	USERCALL_FOR_EACH_LR_COMMAS_1(op, argument), EXPAND(USERCALL_FOR_EACH_LR_COMMAS_12(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_COMMAS_14(op, argument, ...) \
	USERCALL_FOR_EACH_LR_COMMAS_1(op, argument), EXPAND(USERCALL_FOR_EACH_LR_COMMAS_13(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_COMMAS_15(op, argument, ...) \
	USERCALL_FOR_EACH_LR_COMMAS_1(op, argument), EXPAND(USERCALL_FOR_EACH_LR_COMMAS_14(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_COMMAS_16(op, argument, ...) \
	USERCALL_FOR_EACH_LR_COMMAS_1(op, argument), EXPAND(USERCALL_FOR_EACH_LR_COMMAS_15(op, __VA_ARGS__))
#define USERCALL_FOR_EACH_LR_COMMAS(op, ...)  EXPAND(DEFER(CAT)(USERCALL_FOR_EACH_LR_COMMAS_, GET_ARG_COUNT(__VA_ARGS__))(op, __VA_ARGS__))

/////////////////////////////////////////////////
//                                             //
//              USERCALL INTERNAL              //
//                                             //
/////////////////////////////////////////////////

#ifdef _WIN64
#    define USERCALL_BP RBP
#    define USERCALL_SP RSP
#    define USERCALL_AX RAX
#    define USERCALL_BX RBX
#    define USERCALL_CX RCX
#    define USERCALL_DI RDI
#    define USERCALL_DX RDX
#    define USERCALL_SI RSI
#    define USERCALL_REGISTER_SIZE 8
#elif _WIN32
#    define USERCALL_BP EBP
#    define USERCALL_SP ESP
#    define USERCALL_AX EAX
#    define USERCALL_BX EBX
#    define USERCALL_CX ECX
#    define USERCALL_DI EDI
#    define USERCALL_DX EDX
#    define USERCALL_SI ESI
#    define USERCALL_REGISTER_SIZE 4
#else
#    error "usercall: unrecognized architecture."
#endif // _WIN64

#ifndef USERCALL_BACKUP_REGISTER
#    define USERCALL_BACKUP_REGISTER USERCALL_AX
#endif // USERCALL_BACKUP_REGISTER

#ifdef USERCALL_HPP_CHECK_RETURN

#define USERCALL_CHECK_RETURN_INIT() \
	__pragma(push_macro("return")) \
	DEF(return, return _usercall_internal_return_detected_in_usercall_userpurge_function_try_using_the_RETURN_macro_instead)

#define USERCALL_CHECK_RETURN_DEINIT() \
	UNDEF(return) \
	__pragma(pop_macro("return")) \

#define _USERCALL_INTERNAL_RETURN() \
	DEF(_usercall_internal_return_detected_in_usercall_userpurge_function_try_using_the_RETURN_macro_instead, ) \
	return \
	UNDEF(_usercall_internal_return_detected_in_usercall_userpurge_function_try_using_the_RETURN_macro_instead)

#else

#define USERCALL_CHECK_RETURN_INIT()
#define USERCALL_CHECK_RETURN_DEINIT()
#define _USERCALL_INTERNAL_RETURN() return

#endif // USERCALL_HPP_CHECK_RETURN

/////////////////////////
// Pointer to Function //
/////////////////////////

#define USERCALL_POINTER_TO_FUNCTION_PROTOTYPE(configuration) \
	__pragma(push_macro("USERCALL_FUNCTION_CONFIGURATION")) \
	USERCALL_PARSE_FUNCTION_CONFIGURATION(configuration) \
	POINTER_TO_FUNCTION_PROTOTYPE_CONSUME_ARGUMENTS

#define POINTER_TO_FUNCTION_PROTOTYPE_CONSUME_ARGUMENTS(...) \
	CAT(POINTER_TO_FUNCTION_CONFIGURATION_BUILDER, USERCALL_FUNCTION_CONFIGURATION) \
	(FUNCTION_ARGUMENT_LIST_BUILDER(__VA_ARGS__)) \
	__pragma(pop_macro("USERCALL_FUNCTION_CONFIGURATION"))

#define USERCALL_POINTER_TO_FUNCTION(configuration) \
	__pragma(push_macro("USERCALL_FUNCTION_CONFIGURATION")) \
	USERCALL_PARSE_FUNCTION_CONFIGURATION(configuration) \
	POINTER_TO_FUNCTION_CONSUME_ARGUMENTS

#define POINTER_TO_FUNCTION_CONSUME_ARGUMENTS(...) \
	__pragma(push_macro("USERCALL_FUNCTION_ARGUMENTS")) \
	DEF(USERCALL_FUNCTION_ARGUMENTS, __VA_ARGS__) \
	POINTER_TO_FUNCTION_CONSUME_EXPRESSION

#define POINTER_TO_FUNCTION_CONSUME_EXPRESSION(...) \
	DEFER(POINTER_TO_FUNCTION_BUILDER)(USERCALL_FUNCTION_CONFIGURATION, (USERCALL_FUNCTION_ARGUMENTS), (__VA_ARGS__)) \
	__pragma(pop_macro("USERCALL_FUNCTION_CONFIGURATION")) \
	__pragma(pop_macro("USERCALL_FUNCTION_ARGUMENTS"))

#define POINTER_TO_FUNCTION_CONFIGURATION_BUILDER(return_type, calling_convention, name, ...) \
	return_type (calling_convention name)

#define POINTER_TO_FUNCTION_CONFIGURATION_BUILDER_NO_NAME(return_type, calling_convention, name, ...) \
	return_type (calling_convention *)

#define POINTER_TO_FUNCTION_BUILDER(configuration, arguments, expression) \
	CAT(POINTER_TO_FUNCTION_CONFIGURATION_BUILDER, configuration) \
	(CAT(FUNCTION_ARGUMENT_LIST_BUILDER, arguments)) \
	= reinterpret_cast< \
		CAT(POINTER_TO_FUNCTION_CONFIGURATION_BUILDER_NO_NAME, configuration) \
		(CAT(FUNCTION_ARGUMENT_LIST_BUILDER, arguments)) \
	>(expression)

/////////////////////////////
// Function and Trampoline //
/////////////////////////////

#define USERCALL_FUNCTION_AND_TRAMPOLINE(configuration) \
	__pragma(push_macro("USERCALL_FUNCTION_CONFIGURATION")) \
	USERCALL_PARSE_FUNCTION_CONFIGURATION(configuration) \
	USERCALL_FUNCTION_AND_TRAMPOLINE_CONSUME_ARGUMENTS

#define USERCALL_FUNCTION_AND_TRAMPOLINE_CONSUME_ARGUMENTS(...) \
	__pragma(push_macro("USERCALL_FUNCTION_ARGUMENTS")) \
	DEF(USERCALL_FUNCTION_ARGUMENTS, __VA_ARGS__) \
	USERCALL_FUNCTION_AND_TRAMPOLINE_CONSUME_BODY

#define USERCALL_FUNCTION_AND_TRAMPOLINE_CONSUME_BODY(...) \
	 DEFER(FUNCTION_BUILDER)(USERCALL_FUNCTION_CONFIGURATION, (USERCALL_FUNCTION_ARGUMENTS), (__VA_ARGS__)) \
	 DEFER(TRAMPOLINE_BUILDER)(USERCALL_FUNCTION_CONFIGURATION, (USERCALL_FUNCTION_ARGUMENTS)) \
	__pragma(pop_macro("USERCALL_FUNCTION_CONFIGURATION")) \
	__pragma(pop_macro("USERCALL_FUNCTION_ARGUMENTS"))

#define USERCALL_FUNCTION_AND_TRAMPOLINE_PROTOTYPE(configuration) \
	__pragma(push_macro("USERCALL_FUNCTION_CONFIGURATION")) \
	USERCALL_PARSE_FUNCTION_CONFIGURATION(configuration) \
	USERCALL_FUNCTION_AND_TRAMPOLINE_PROTOTYPE_CONSUME_ARGUMENTS

#define USERCALL_FUNCTION_AND_TRAMPOLINE_PROTOTYPE_CONSUME_ARGUMENTS(...) \
	DEFER(FUNCTION_SIGNATURE_BUILDER)(USERCALL_FUNCTION_CONFIGURATION, (__VA_ARGS__)); \
	DEFER(TRAMPOLINE_SIGNATURE_BUILDER)(USERCALL_FUNCTION_CONFIGURATION, (__VA_ARGS__)) \
	__pragma(pop_macro("USERCALL_FUNCTION_CONFIGURATION"))

////////////////////////
// Trampoline Builder //
////////////////////////

// Trampoline Prototype

#define USERCALL_TRAMPOLINE_PROTOTYPE(configuration) \
	__pragma(push_macro("USERCALL_FUNCTION_CONFIGURATION")) \
	USERCALL_PARSE_FUNCTION_CONFIGURATION(configuration) \
	TRAMPOLINE_PROTOTYPE_CONSUME_ARGUMENTS

#define TRAMPOLINE_PROTOTYPE_CONSUME_ARGUMENTS(...) \
	DEFER(TRAMPOLINE_SIGNATURE_BUILDER)(USERCALL_FUNCTION_CONFIGURATION, (__VA_ARGS__)) \
	__pragma(pop_macro("USERCALL_FUNCTION_CONFIGURATION"))

#define TRAMPOLINE_SIGNATURE_BUILDER(configuration, arguments) \
	DEFER(CAT)(TRAMPOLINE_CONFIGURATION_BUILDER, configuration) \
	(CAT(TRAMPOLINE_ARGUMENT_LIST_BUILDER, arguments))

#define TRAMPOLINE_CONFIGURATION_BUILDER(return_type, calling_convention, function_name, ...) \
	return_type __cdecl function_name##_trampoline

#define TRAMPOLINE_ARGUMENT_LIST(declaration, name, ...) \
	declaration

#define TRAMPOLINE_ARGUMENT_LIST_OP(arg) \
	FUNCTION_PARSE_ARGUMENT(_USERCALL_INTERNAL_TEMP, arg) \
	DEFER(CAT)(TRAMPOLINE_ARGUMENT_LIST, _USERCALL_INTERNAL_TEMP) \
	UNDEF(_USERCALL_INTERNAL_TEMP)

#define TRAMPOLINE_ARGUMENT_LIST_BUILDER(...) \
	DEFER(USERCALL_FOR_EACH_LR_COMMAS)(TRAMPOLINE_ARGUMENT_LIST_OP, __VA_ARGS__)

// Trampoline

#define USERCALL_TRAMPOLINE(configuration) \
	__pragma(push_macro("USERCALL_FUNCTION_CONFIGURATION")) \
	USERCALL_PARSE_FUNCTION_CONFIGURATION(configuration) \
	TRAMPOLINE_CONSUME_ARGUMENTS

// Argument Load

#define TRAMPOLINE_ARGUMENT_LOAD(declaration, name, reg) \
	__asm { mov reg, name }

#define TRAMPOLINE_ARGUMENT_LOAD_OP(arg) \
	FUNCTION_PARSE_ARGUMENT(_USERCALL_INTERNAL_TEMP, arg) \
	DEFER(SELECT)(DEFER(CAT)(GET_ARG_COUNT, _USERCALL_INTERNAL_TEMP) == 3, \
		DEFER(CAT)(TRAMPOLINE_ARGUMENT_LOAD, _USERCALL_INTERNAL_TEMP)) \
	UNDEF(_USERCALL_INTERNAL_TEMP)

#define TRAMPOLINE_ARGUMENT_LOAD_BUILDER(...) \
	DEFER(USERCALL_FOR_EACH_LR)(TRAMPOLINE_ARGUMENT_LOAD_OP, __VA_ARGS__)

#define TRAMPOLINE_CALL_ARGUMENTS_OP(arg) \
	FUNCTION_PARSE_ARGUMENT(_USERCALL_INTERNAL_TEMP, arg) \
	DEFER(SELECT)(DEFER(CAT)(GET_ARG_COUNT, _USERCALL_INTERNAL_TEMP) == 2, \
		DEFER(SELECT)(defined(_USERCALL_IS_NOT_FIRST), DEFER(COMMA)(), DEF(_USERCALL_IS_NOT_FIRST(), true)) DEFER(CAT)(TUPLE_GET_SECOND, _USERCALL_INTERNAL_TEMP)) \
	UNDEF(_USERCALL_INTERNAL_TEMP)

#define _USERCALL_IS_NOT_FIRST()

#define TRAMPOLINE_CALL_ARGUMENTS_BUILDER(...) \
	__pragma(push_macro("_USERCALL_IS_NOT_FIRST")) \
	UNDEF(_USERCALL_IS_NOT_FIRST) \
	DEFER(USERCALL_FOR_EACH_LR)(TRAMPOLINE_CALL_ARGUMENTS_OP, __VA_ARGS__) \
	__pragma(pop_macro("_USERCALL_IS_NOT_FIRST"))

#define TRAMPOLINE_CALL_BUILDER(configuration, arguments) \
	CAT(TUPLE_GET_THIRD, configuration) \
	(CAT(TRAMPOLINE_CALL_ARGUMENTS_BUILDER, arguments))

#define TRAMPOLINE_RETURN_BUILDER(return_type, calling_convention, name, return_location) \
	return_type _usercall_internal_return_; \
	__asm { mov _usercall_internal_return_, return_location } \
	return _usercall_internal_return_;

#define TRAMPOLINE_CONSUME_ARGUMENTS(...) \
	DEFER(TRAMPOLINE_BUILDER)(USERCALL_FUNCTION_CONFIGURATION, (__VA_ARGS__)); \
	__pragma(pop_macro("USERCALL_FUNCTION_CONFIGURATION"))

#define TRAMPOLINE_BUILDER(configuration, arguments) \
	DEFER(TRAMPOLINE_SIGNATURE_BUILDER)(configuration, arguments) \
	{ \
	CAT(TRAMPOLINE_ARGUMENT_LOAD_BUILDER, arguments) \
	TRAMPOLINE_CALL_BUILDER(configuration, arguments); \
	DEFER(USERCALL_IS_VOID_FUNCTION)(USERCALL_IS_VOID_OUT, configuration) \
	SELECT(!USERCALL_IS_VOID_OUT, \
		CAT(TRAMPOLINE_RETURN_BUILDER, configuration)) \
	UNDEF(USERCALL_IS_VOID_OUT) \
	}

//////////////////////
// Function Builder //
//////////////////////

#define USERCALL_FUNCTION_PROTOTYPE(configuration) \
	__pragma(push_macro("USERCALL_FUNCTION_CONFIGURATION")) \
	USERCALL_PARSE_FUNCTION_CONFIGURATION(configuration) \
	PROTOTYPE_CONSUME_ARGUMENTS

#define PROTOTYPE_CONSUME_ARGUMENTS(...) \
	DEFER(FUNCTION_SIGNATURE_BUILDER)(USERCALL_FUNCTION_CONFIGURATION, (__VA_ARGS__)) \
	__pragma(pop_macro("USERCALL_FUNCTION_CONFIGURATION"))

#define FUNCTION_SIGNATURE_BUILDER(configuration, arguments) \
	DEFER(CAT)(FUNCTION_CONFIGURATION_BUILDER, configuration) \
	(CAT(FUNCTION_ARGUMENT_LIST_BUILDER, arguments))

// Function Configuration

#define FUNCTION_CONFIGURATION_BUILDER(return_type, calling_convention, function_name, ...) \
	void calling_convention function_name

// Argument List

#define FUNCTION_ARGUMENT_LIST(declaration, name) \
	declaration

#define FUNCTION_ARGUMENT_LIST_OP(arg) \
	FUNCTION_PARSE_ARGUMENT(_USERCALL_INTERNAL_TEMP, arg) \
	DEFER(SELECT)(DEFER(CAT)(GET_ARG_COUNT, _USERCALL_INTERNAL_TEMP) == 2, \
		DEFER(SELECT)(defined(_USERCALL_IS_NOT_FIRST), DEFER(COMMA)(), DEF(_USERCALL_IS_NOT_FIRST(), true)) DEFER(CAT)(FUNCTION_ARGUMENT_LIST, _USERCALL_INTERNAL_TEMP)) \
	UNDEF(_USERCALL_INTERNAL_TEMP)

#define FUNCTION_ARGUMENT_LIST_BUILDER(...) \
	__pragma(push_macro("_USERCALL_IS_NOT_FIRST")) \
	UNDEF(_USERCALL_IS_NOT_FIRST) \
	DEFER(USERCALL_FOR_EACH_LR)(FUNCTION_ARGUMENT_LIST_OP, __VA_ARGS__) \
	__pragma(pop_macro("_USERCALL_IS_NOT_FIRST"))

// Argument Load

#define FUNCTION_ARGUMENT_LOAD(declaration, name, reg) \
	declaration; \
	__asm { mov name, reg }

#define FUNCTION_ARGUMENT_LOAD_OP(arg) \
	FUNCTION_PARSE_ARGUMENT(_USERCALL_INTERNAL_TEMP, arg) \
	DEFER(SELECT)(DEFER(CAT)(GET_ARG_COUNT, _USERCALL_INTERNAL_TEMP) == 3, \
		DEFER(CAT)(FUNCTION_ARGUMENT_LOAD, _USERCALL_INTERNAL_TEMP)) \
	UNDEF(_USERCALL_INTERNAL_TEMP)

#define FUNCTION_ARGUMENT_LOAD_BUILDER(...) \
	DEFER(USERCALL_FOR_EACH_LR)(FUNCTION_ARGUMENT_LOAD_OP, __VA_ARGS__)

// Function Template

#define FUNCTION_BUILDER(configuration, arguments, body) \
	DEFER(USERCALL_IS_VOID_FUNCTION)(USERCALL_IS_VOID_OUT, configuration) \
	SELECT(USERCALL_IS_VOID_OUT, \
		DEF(RETURN, DEFER(_USERCALL_INTERNAL_RETURN_VOID)()) DEF(_USERCALL_INTERNAL_RETURN_LOCATION, ) DEF(_USERCALL_INTERNAL_RETURN_TYPE, ), \
		DEF(RETURN, USERCALL_RETURN_VALUE) DEF(_USERCALL_INTERNAL_RETURN_LOCATION, DEFER(CAT)(TUPLE_GET_FOURTH, configuration)) DEF(_USERCALL_INTERNAL_RETURN_TYPE, DEFER(CAT)(TUPLE_GET_FIRST, configuration))) \
	UNDEF(USERCALL_IS_VOID_OUT) \
	USERCALL_CHECK_RETURN_INIT() \
	DEFER(DEF)(USERCALL__FUNCTION__, DEFER(CAT)(TUPLE_GET_THIRD, configuration)) \
	FUNCTION_SIGNATURE_BUILDER(configuration, arguments) \
	{ \
	__asm { push USERCALL_AX } \
	__asm { push USERCALL_BX } \
	__asm { push USERCALL_CX } \
	__asm { push USERCALL_DI } \
	__asm { push USERCALL_DX } \
	__asm { push USERCALL_SI } \
	CAT(FUNCTION_ARGUMENT_LOAD_BUILDER, arguments) \
	CAT(EXPAND, body) \
	} \
	UNDEF(USERCALL__FUNCTION__) \
	USERCALL_CHECK_RETURN_DEINIT() \
	UNDEF(_USERCALL_INTERNAL_RETURN_LOCATION) \
	UNDEF(_USERCALL_INTERNAL_RETURN_TYPE) \
	UNDEF(RETURN)

////////////////////
// Function Parse //
////////////////////

// Function Body

#define USERCALL_RETURN_VALUE(return_expression) \
	__asm { pop USERCALL_SI } \
	__asm { pop USERCALL_DX } \
	__asm { pop USERCALL_DI } \
	__asm { pop USERCALL_CX } \
	__asm { pop USERCALL_BX } \
	__asm { pop USERCALL_AX } \
	_USERCALL_INTERNAL_RETURN_TYPE _usercall_internal_return_ = return_expression; \
	__asm { mov _USERCALL_INTERNAL_RETURN_LOCATION, _usercall_internal_return_ } \
	_USERCALL_INTERNAL_RETURN()

#define _USERCALL_INTERNAL_RETURN_VOID() \
	__asm { pop USERCALL_SI } \
	__asm { pop USERCALL_DX } \
	__asm { pop USERCALL_DI } \
	__asm { pop USERCALL_CX } \
	__asm { pop USERCALL_BX } \
	__asm { pop USERCALL_AX } \
	_USERCALL_INTERNAL_RETURN()

#define USERCALL_IS_VOID_FUNCTION(out, configuration) \
	__pragma(push_macro("void")) \
	DEF(void,) \
	DEFER(SELECT)(DEFER(GET_ARG_COUNT)(DEFER(CAT)(TUPLE_GET_FIRST, USERCALL_FUNCTION_CONFIGURATION)), DEF(out, false), DEF(out, true)) \
	UNDEF(void) \
	__pragma(pop_macro("void"))

#define FUNCTION_CONSUME_BODY(...) \
	DEFER(FUNCTION_BUILDER)( \
		USERCALL_FUNCTION_CONFIGURATION, \
		(USERCALL_FUNCTION_ARGUMENTS), \
		(__VA_ARGS__)) \
	__pragma(pop_macro("USERCALL_FUNCTION_CONFIGURATION")) \
	__pragma(pop_macro("USERCALL_FUNCTION_ARGUMENTS"))

// Function Arguments

#define FUNCTION_PARSE_ARGUMENT(out, argument) \
	SPLIT(USERCALL_ARGUMENT_SPLIT, argument, AT) \
	DEFER(SPACE_DELIM_SECOND_OUT_DEFINE)(USERCALL_ARGUMENT_NAME, DEFER(CAT)(TUPLE_GET_FIRST, USERCALL_ARGUMENT_SPLIT)) \
	DEFER(SELECT)(DEFER(CAT)(GET_ARG_COUNT, USERCALL_ARGUMENT_SPLIT) == 2, \
		DEF(out, ( \
			DEFER(CAT)(TUPLE_GET_FIRST, USERCALL_ARGUMENT_SPLIT), \
			USERCALL_ARGUMENT_NAME, \
			DEFER(CAT)(TUPLE_GET_SECOND, USERCALL_ARGUMENT_SPLIT) \
		)), \
		DEF(out, ( \
			DEFER(CAT)(TUPLE_GET_FIRST, USERCALL_ARGUMENT_SPLIT), \
			USERCALL_ARGUMENT_NAME \
		))) \
	UNDEF(USERCALL_ARGUMENT_SPLIT) \
	UNDEF(USERCALL_ARGUMENT_NAME)

#define FUNCTION_PARSE_ARGUMENT_OP(arg) \
	FUNCTION_PARSE_ARGUMENT(_USERCALL_INTERNAL_TEMP, arg) \
	_USERCALL_INTERNAL_TEMP \
	UNDEF(_USERCALL_INTERNAL_TEMP)

#define FUNCTION_CONSUME_ARGUMENTS(...) \
	__pragma(push_macro("USERCALL_FUNCTION_ARGUMENTS")) \
	DEF(USERCALL_FUNCTION_ARGUMENTS, __VA_ARGS__) \
	FUNCTION_CONSUME_BODY

// Function Configuration

#define USERCALL_PARSE_FUNCTION_CONFIGURATION(configuration) \
	DEF(__usercall, COMMA() __stdcall COMMA()) \
	DEF(__userpurge, COMMA() __cdecl COMMA()) \
	DEFER(SPLIT)(USERCALL_FUNCTION_CONFIGURATION, configuration, AT) \
	UNDEF(__usercall) \
	UNDEF(__userpurge)

#define USERCALL_FUNCTION(configuration) \
	__pragma(push_macro("USERCALL_FUNCTION_CONFIGURATION")) \
	USERCALL_PARSE_FUNCTION_CONFIGURATION(configuration) \
	FUNCTION_CONSUME_ARGUMENTS

/////////////////////////////////////////////////
//                                             //
//             HEXRAYS DEFS PUBLIC             //
//                                             //
/////////////////////////////////////////////////

#ifdef USERCALL_HPP_USE_HEXRAYS_DEFS
/*

   This file contains definitions used in the Hex-Rays decompiler output.
   It has type definitions and convenience macros to make the
   output more readable.

   Copyright (c) 2007-2020 Hex-Rays

*/

typedef          __int64 ll;
typedef unsigned __int64 ull;
#define MAKELL(num) num ## i64
#define FMT_64 "I64"
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

typedef          char   int8;
typedef   signed char   sint8;
typedef unsigned char   uint8;
typedef          short  int16;
typedef   signed short  sint16;
typedef unsigned short  uint16;
typedef          int    int32;
typedef   signed int    sint32;
typedef unsigned int    uint32;
typedef ll              int64;
typedef ll              sint64;
typedef ull             uint64;

#define _BYTE  uint8
#define _WORD  uint16
#define _DWORD uint32
#define _QWORD uint64

typedef int8 _BOOL1;
typedef int16 _BOOL2;
typedef int32 _BOOL4;
typedef int64 _BOOL8;

#ifndef _WINDOWS_
typedef int8 BYTE;
typedef int16 WORD;
typedef int32 DWORD;
typedef int32 LONG;
typedef int BOOL;
#endif
typedef int64 QWORD;
#ifndef __cplusplus
typedef int bool;
#endif

#define __pure
#define __noreturn  __declspec(noreturn)

#ifndef NULL
#define NULL 0
#endif

#define LAST_IND(x,part_type)    (sizeof(x)/sizeof(part_type) - 1)
#if defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN
#  define LOW_IND(x,part_type)   LAST_IND(x,part_type)
#  define HIGH_IND(x,part_type)  0
#else
#  define HIGH_IND(x,part_type)  LAST_IND(x,part_type)
#  define LOW_IND(x,part_type)   0
#endif

#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
#define WORDn(x, n)   (*((_WORD*)&(x)+n))
#define DWORDn(x, n)  (*((_DWORD*)&(x)+n))

#define LOBYTE(x)  BYTEn(x,LOW_IND(x,_BYTE))
#define LOWORD(x)  WORDn(x,LOW_IND(x,_WORD))
#define LODWORD(x) DWORDn(x,LOW_IND(x,_DWORD))
#define HIBYTE(x)  BYTEn(x,HIGH_IND(x,_BYTE))
#define HIWORD(x)  WORDn(x,HIGH_IND(x,_WORD))
#define HIDWORD(x) DWORDn(x,HIGH_IND(x,_DWORD))
#define BYTE1(x)   BYTEn(x,  1)
#define BYTE2(x)   BYTEn(x,  2)
#define BYTE3(x)   BYTEn(x,  3)
#define BYTE4(x)   BYTEn(x,  4)
#define BYTE5(x)   BYTEn(x,  5)
#define BYTE6(x)   BYTEn(x,  6)
#define BYTE7(x)   BYTEn(x,  7)
#define BYTE8(x)   BYTEn(x,  8)
#define BYTE9(x)   BYTEn(x,  9)
#define BYTE10(x)  BYTEn(x, 10)
#define BYTE11(x)  BYTEn(x, 11)
#define BYTE12(x)  BYTEn(x, 12)
#define BYTE13(x)  BYTEn(x, 13)
#define BYTE14(x)  BYTEn(x, 14)
#define BYTE15(x)  BYTEn(x, 15)
#define WORD1(x)   WORDn(x,  1)
#define WORD2(x)   WORDn(x,  2)
#define WORD3(x)   WORDn(x,  3)
#define WORD4(x)   WORDn(x,  4)
#define WORD5(x)   WORDn(x,  5)
#define WORD6(x)   WORDn(x,  6)
#define WORD7(x)   WORDn(x,  7)

#define SBYTEn(x, n)   (*((int8*)&(x)+n))
#define SWORDn(x, n)   (*((int16*)&(x)+n))
#define SDWORDn(x, n)  (*((int32*)&(x)+n))

#define SLOBYTE(x)  SBYTEn(x,LOW_IND(x,int8))
#define SLOWORD(x)  SWORDn(x,LOW_IND(x,int16))
#define SLODWORD(x) SDWORDn(x,LOW_IND(x,int32))
#define SHIBYTE(x)  SBYTEn(x,HIGH_IND(x,int8))
#define SHIWORD(x)  SWORDn(x,HIGH_IND(x,int16))
#define SHIDWORD(x) SDWORDn(x,HIGH_IND(x,int32))
#define SBYTE1(x)   SBYTEn(x,  1)
#define SBYTE2(x)   SBYTEn(x,  2)
#define SBYTE3(x)   SBYTEn(x,  3)
#define SBYTE4(x)   SBYTEn(x,  4)
#define SBYTE5(x)   SBYTEn(x,  5)
#define SBYTE6(x)   SBYTEn(x,  6)
#define SBYTE7(x)   SBYTEn(x,  7)
#define SBYTE8(x)   SBYTEn(x,  8)
#define SBYTE9(x)   SBYTEn(x,  9)
#define SBYTE10(x)  SBYTEn(x, 10)
#define SBYTE11(x)  SBYTEn(x, 11)
#define SBYTE12(x)  SBYTEn(x, 12)
#define SBYTE13(x)  SBYTEn(x, 13)
#define SBYTE14(x)  SBYTEn(x, 14)
#define SBYTE15(x)  SBYTEn(x, 15)
#define SWORD1(x)   SWORDn(x,  1)
#define SWORD2(x)   SWORDn(x,  2)
#define SWORD3(x)   SWORDn(x,  3)
#define SWORD4(x)   SWORDn(x,  4)
#define SWORD5(x)   SWORDn(x,  5)
#define SWORD6(x)   SWORDn(x,  6)
#define SWORD7(x)   SWORDn(x,  7)

#define __SPAIR16__(high, low)  (((int16)  (high) <<  8) | (uint8) (low))
#define __SPAIR32__(high, low)  (((int32)  (high) << 16) | (uint16)(low))
#define __SPAIR64__(high, low)  (((int64)  (high) << 32) | (uint32)(low))
#define __SPAIR128__(high, low) (((int128) (high) << 64) | (uint64)(low))
#define __PAIR16__(high, low)   (((uint16) (high) <<  8) | (uint8) (low))
#define __PAIR32__(high, low)   (((uint32) (high) << 16) | (uint16)(low))
#define __PAIR64__(high, low)   (((uint64) (high) << 32) | (uint32)(low))
#define __PAIR128__(high, low)  (((uint128)(high) << 64) | (uint64)(low))

#ifdef __cplusplus

#define __CASSERT_N0__(l) COMPILE_TIME_ASSERT_ ## l
#define __CASSERT_N1__(l) __CASSERT_N0__(l)
#define CASSERT(cnd) typedef char __CASSERT_N1__(__LINE__) [(cnd) ? 1 : -1]

template<class T> bool is_mul_ok(T count, T elsize)
{
  CASSERT(T(-1) > 0); // make sure T is unsigned
  if ( elsize == 0 || count == 0 )
    return true;
  return count <= T(-1) / elsize;
}

template<class T> bool saturated_mul(T count, T elsize)
{
  return is_mul_ok(count, elsize) ? count * elsize : T(-1);
}

#include <stddef.h>

inline void *qmemcpy(void *dst, const void *src, size_t cnt)
{
  char *out = (char *)dst;
  const char *in = (const char *)src;
  while ( cnt > 0 )
  {
    *out++ = *in++;
    --cnt;
  }
  return dst;
}

template<class T> T __ROL__(T value, int count)
{
  const uint nbits = sizeof(T) * 8;

  if ( count > 0 )
  {
    count %= nbits;
    T high = value >> (nbits - count);
    if ( T(-1) < 0 )
      high &= ~((T(-1) << count));
    value <<= count;
    value |= high;
  }
  else
  {
    count = -count % nbits;
    T low = value << (nbits - count);
    value >>= count;
    value |= low;
  }
  return value;
}

inline uint8  __ROL1__(uint8  value, int count) { return __ROL__((uint8)value, count); }
inline uint16 __ROL2__(uint16 value, int count) { return __ROL__((uint16)value, count); }
inline uint32 __ROL4__(uint32 value, int count) { return __ROL__((uint32)value, count); }
inline uint64 __ROL8__(uint64 value, int count) { return __ROL__((uint64)value, count); }
inline uint8  __ROR1__(uint8  value, int count) { return __ROL__((uint8)value, -count); }
inline uint16 __ROR2__(uint16 value, int count) { return __ROL__((uint16)value, -count); }
inline uint32 __ROR4__(uint32 value, int count) { return __ROL__((uint32)value, -count); }
inline uint64 __ROR8__(uint64 value, int count) { return __ROL__((uint64)value, -count); }

template<class T> int8 __MKCSHL__(T value, uint count)
{
  const uint nbits = sizeof(T) * 8;
  count %= nbits;

  return (value >> (nbits-count)) & 1;
}

template<class T> int8 __MKCSHR__(T value, uint count)
{
  return (value >> (count-1)) & 1;
}

template<class T> int8 __SETS__(T x)
{
  if ( sizeof(T) == 1 )
    return int8(x) < 0;
  if ( sizeof(T) == 2 )
    return int16(x) < 0;
  if ( sizeof(T) == 4 )
    return int32(x) < 0;
  return int64(x) < 0;
}

template<class T, class U> int8 __OFSUB__(T x, U y)
{
  if ( sizeof(T) < sizeof(U) )
  {
    U x2 = x;
    int8 sx = __SETS__(x2);
    return (sx ^ __SETS__(y)) & (sx ^ __SETS__(U(x2-y)));
  }
  else
  {
    T y2 = y;
    int8 sx = __SETS__(x);
    return (sx ^ __SETS__(y2)) & (sx ^ __SETS__(T(x-y2)));
  }
}

template<class T, class U> int8 __OFADD__(T x, U y)
{
  if ( sizeof(T) < sizeof(U) )
  {
    U x2 = x;
    int8 sx = __SETS__(x2);
    return ((1 ^ sx) ^ __SETS__(y)) & (sx ^ __SETS__(U(x2+y)));
  }
  else
  {
    T y2 = y;
    int8 sx = __SETS__(x);
    return ((1 ^ sx) ^ __SETS__(y2)) & (sx ^ __SETS__(T(x+y2)));
  }
}

template<class T, class U> int8 __CFSUB__(T x, U y)
{
  int size = sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U);
  bool res;
  if ( size == 1 )
    res = uint8(x) < uint8(y);
  else if ( size == 2 )
    res = uint16(x) < uint16(y);
  else if ( size == 4 )
    res = uint32(x) < uint32(y);
  else
    res = uint64(x) < uint64(y);
  return res;
}

template<class T, class U> int8 __CFADD__(T x, U y)
{
  int size = sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U);
  if ( size == 1 )
    return uint8(x) > uint8(x+y);
  if ( size == 2 )
    return uint16(x) > uint16(x+y);
  if ( size == 4 )
    return uint32(x) > uint32(x+y);
  return uint64(x) > uint64(x+y);
}

template<class T, class U> int8 __CFSUB__(T x, U y, int8 cf)
{
  return __CFADD__(y, cf) ^ __CFSUB(x, y + cf);
}

template<class T, class U> int8 __OFSUB__(T x, U y, int8 cf)
{
  return __OFADD__(y, cf) ^ __OFSUB(x, y + cf);
}

inline uint8   abs8(int8     x) { return x >= 0 ? x : -x; }
inline uint16  abs16(int16   x) { return x >= 0 ? x : -x; }
inline uint32  abs32(int32   x) { return x >= 0 ? x : -x; }
inline uint64  abs64(int64   x) { return x >= 0 ? x : -x; }

#include <string.h>
#include <type_traits>

template <typename T, typename F>
inline typename std::enable_if<sizeof(T) <= sizeof(F), T>::type __coerce(F f)
{
  T t;
  memcpy(&t, &f, sizeof(T));
  return t;
}
#define COERCE_FLOAT(v) __coerce<float>(v)
#define COERCE_DOUBLE(v) __coerce<double>(v)
#define COERCE_LONG_DOUBLE(v) __coerce<long double>(v)
#define COERCE_UNSIGNED_INT(v) __coerce<unsigned int>(v)
#define COERCE_UNSIGNED_INT64(v) __coerce<uint64>(v)

#else // C++

#define __ROL__(x, y) __rotl__(x, y)
#define __ROR__(x, y) __rotr__(x, y)
#define __CFSHL__(x, y) invalid_operation
#define __CFSHR__(x, y) invalid_operation
#define __CFADD__(x, y) invalid_operation
#define __CFSUB__(x, y) invalid_operation
#define __OFADD__(x, y) invalid_operation
#define __OFSUB__(x, y) invalid_operation

#define abs8(x)   (int8)  ((int8)  (x) >= 0 ? (x) : -(x))
#define abs16(x)  (int16) ((int16) (x) >= 0 ? (x) : -(x))
#define abs32(x)  (int32) ((int32) (x) >= 0 ? (x) : -(x))
#define abs64(x)  (int64) ((int64) (x) >= 0 ? (x) : -(x))
#define abs128(x) (int128)((int128)(x) >= 0 ? (x) : -(x))

#endif // C++

#define __RCL__(x, y)    invalid_operation
#define __RCR__(x, y)    invalid_operation
#define __MKCRCL__(x, y) invalid_operation
#define __MKCRCR__(x, y) invalid_operation
#define __SETP__(x, y)   invalid_operation

#define _UNKNOWN char

#define snprintf _snprintf
#define vsnprintf _vsnprintf

#define ADJ(p) (__parentof(p) *)(p-__deltaof(p))
#endif // USERCALL_HPP_USE_HEXRAYS_DEFS

#endif // USERCALL_HPP
