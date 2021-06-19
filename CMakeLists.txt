cmake_minimum_required(VERSION 3.0)
project(usercall_hpp LANGUAGES CXX)

option(USERCALL_HPP_USE_SHORT_NAMES        "Use shortened macro names"                             OFF)
option(USERCALL_HPP_USE_HEXRAYS_DEFS       "Define the types and macros used by hex-ray's IDA Pro" OFF)
option(USERCALL_HPP_CHECK_RETURN           "Prevent use of return keyword when reasonable"         OFF)
option(USERCALL_HPP_USE_REALLY_SHORT_NAMES "Use extra shortened macro names"                       OFF)

add_library(usercall_hpp INTERFACE include/usercall_hpp/usercall.hpp)
target_include_directories(usercall_hpp INTERFACE include)

if(USERCALL_HPP_USE_SHORT_NAMES)
	target_compile_definitions(usercall_hpp INTERFACE USERCALL_HPP_USE_SHORT_NAMES)
endif()

if(USERCALL_HPP_USE_HEXRAYS_DEFS)
	target_compile_definitions(usercall_hpp INTERFACE USERCALL_HPP_USE_HEXRAYS_DEFS)
endif()

if(USERCALL_HPP_CHECK_RETURN)
	target_compile_definitions(usercall_hpp INTERFACE USERCALL_HPP_CHECK_RETURN)
endif()

if(USERCALL_HPP_USE_REALLY_SHORT_NAMES)
	target_compile_definitions(usercall_hpp INTERFACE USERCALL_HPP_USE_REALLY_SHORT_NAMES)
endif()
