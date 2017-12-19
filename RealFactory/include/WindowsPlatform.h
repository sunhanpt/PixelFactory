#pragma once
/**
* Windows specific types
**/

struct FWindowsPlatformTypes : public FGenericPlatformTypes
{
#ifdef _WIN64
	typedef unsigned __int64	SIZE_T;
	typedef signed __int64		SSIZE_T;
#else
	typedef unsigned long		SIZE_T;
	typedef signed long			SSIZE_T;
#endif // _WIN64

};

typedef FWindowsPlatformTypes FPlatformTypes;

// Base defines, must define these for the platform, there are no defaults
#define PLATFORM_DESKTOP					1
#if defined( _WIN64 )
#define PLATFORM_64BITS					1
#else
#define PLATFORM_64BITS					0
#endif

// Function type macros.
#define VARARGS     __cdecl											/* Functions with variable arguments */
#define CDECL	    __cdecl											/* Standard C function */
#define STDCALL		__stdcall										/* Standard calling convention */
#define FORCEINLINE __forceinline									/* Force code to be inline */
#define FORCENOINLINE __declspec(noinline)							/* Force code to NOT be inline */
#define FUNCTION_NO_RETURN_START __declspec(noreturn)				/* Indicate that the function never returns. */
#define FUNCTION_NON_NULL_RETURN_START _Ret_notnull_				/* Indicate that the function never returns nullptr. */

// Hints compiler that expression is true; generally restricted to comparisons against constants
#if !defined(__clang__) || defined(_MSC_VER)	// Clang only supports __assume when using -fms-extensions
#define ASSUME(expr) __assume(expr)
#endif

// Alignment.
#if defined(__clang__)
#define GCC_PACK(n) __attribute__((packed,aligned(n)))
#define GCC_ALIGN(n) __attribute__((aligned(n)))
#if defined(_MSC_VER)
#define MS_ALIGN(n) __declspec(align(n)) // With -fms-extensions, Clang will accept either alignment attribute
#endif
#else
#define MS_ALIGN(n) __declspec(align(n))
#endif

// Pragmas
#define MSVC_PRAGMA(Pragma) __pragma(Pragma)

// Prefetch
#define PLATFORM_CACHE_LINE_SIZE	128

// DLL export and import definitions
#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)

// disable this now as it is annoying for generic platform implementations
#pragma warning(disable : 4100) // unreferenced formal parameter



//! define a break macro for debugging.
#if defined(_DEBUG)
#include "assert.h"
#define _RF_DEBUG_BREAK_IF( _CONDITION_ ) assert( !(_CONDITION_) );
#else
#define _RF_DEBUG_BREAK_IF( _CONDITION_ )
#endif