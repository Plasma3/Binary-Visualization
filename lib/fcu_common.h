// Copyright 2025 Fredrik Ahlberg <fcu.ahlberg@gmail.com>
//
// SPDX-License-Identifier: Unlicense OR EUPL-1.2 OR CC0-1.0 OR 0BSD OR MIT OR MIT-0
// File description can be found at the end of this file (to avoid a wall of text here)

// Version: 0.1.7
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

#define fcu_ALL // TODO: remove this later, (makes vscode color the code as normal)
#define fcu_CAPI static

// The other modules need fcu_core to function
#if (defined(fcu_STRING) || defined(fcu_DEBUG) || defined(fcu_NUMBERS) || defined(fcu_TIME)) && !defined(fcu_CORE)
	#define fcu_CORE
#endif

// ========================================
// fcu_core
// ========================================
#if defined(fcu_ALL) || defined(fcu_CORE)
#pragma region fcu_core
// ----------------------------------------
// Typedefs
// ----------------------------------------
typedef 	  void* 		   ptr_t;	//!< Void pointer
typedef  	  void* const 	  cptr_t;	//!< Constant void pointer
typedef const void* const 	sc_ptr_t;	//!< Static constant void pointer
typedef const void* 		 s_ptr_t; 	//!< Pointer to constant void

typedef 	  char* 		 a_ptr_t; 	//!< Aritmetic pointer
// typedef 	  char* const 	ac_ptr_t; 	//!< Aritmetic constant pointer
typedef const char* 		sa_ptr_t;	//!< Static aritmetic pointer
// typedef const char* const  sac_ptr_t;	//!< Static aritmetic constant pointer

typedef signed 		int		 s_int;		//!< Signed integer
typedef unsigned	int		 u_int;		//!< Unsigned integer
typedef const 		s_int	sc_int;		//!< Signed constant integer
typedef const 		u_int	uc_int;		//!< Unsigned constant integer

typedef signed 		char	 s_char;	//!< Signed byte (char)
typedef unsigned 	char	 u_char;	//!< Unsigned byte (char)
typedef const 		u_char 	uc_char;	//!< Signed constant byte (char)
typedef const 		s_char 	sc_char;	//!< Unsigned constant byte (char)

typedef 	  char*	   		   str_t;	//!< String (pointer to char)
typedef 	  char* const 	 s_str_t; 	//!< Static string (constant pointer to char)
typedef const char* 	     c_str_t; 	//!< Constant string (pointer to constant char array)
typedef const char* const 	sc_str_t; 	//!< Static constant string (constant pointer to constant char array)

typedef const char cchar;

#pragma region Rust-style typedefs
	typedef uint8_t 	u8;
	typedef  int8_t 	i8;
	typedef const u8 	u8c;
	typedef const i8 	i8c;

	typedef uint16_t 	u16;
	typedef  int16_t 	i16;
	typedef const u16 	u16c;
	typedef const i16 	i16c;

	typedef uint32_t 	u32;
	typedef  int32_t 	i32;
	typedef const u32 	u32c;
	typedef const i32 	i32c;

	typedef uint64_t 	u64;
	typedef  int64_t 	i64;
	typedef const u64 	u64c;
	typedef const i64 	i64c;

	typedef float 		f32;
	typedef double 		f64;
	typedef const f32 	f32c;
	typedef const f64 	f64c;
#pragma endregion

// ----------------------------------------
// Constants
// ----------------------------------------
#define kiloByte 1024U						//!< The number of bytes in a kiloByte (kB)
#define MegaByte (kiloByte * kiloByte)		//!< The number of bytes in a MegaByte (MB)
#define GigaByte (MegaByte * kiloByte)		//!< The number of bytes in a GigaByte (GB)


// ----------------------------------------
// Macros
// ----------------------------------------
// === For loops ===
#define f_FOR(START_VALUE, END_VALUE, ITERATOR, TYPE) 	for (TYPE ITERATOR = START_VALUE; ITERATOR < END_VALUE; ITERATOR++)

#define f_FOR_0(TIMES, ITERATOR, TYPE) 				f_FOR(0, TIMES, ITERATOR, TYPE)						//!< Typical generic for-loop with startvalue 0
#define f_FOR_1(TIMES, ITERATOR, TYPE) 				f_FOR(1, TIMES + 1, ITERATOR, TYPE)						//!< Typical generic for-loop with startvalue 1

#define f_FOR_int(TIMES, ITERATOR) 					f_FOR_0(TIMES, ITERATOR, int)						//!< Typical for-loop with iterator of type int 	with startvalue 0
#define f_FOR_uint(TIMES, ITERATOR) 				f_FOR_0(TIMES, ITERATOR, u_int)						//!< Typical for-loop with iterator of type u_int 	with startvalue 0
#define f_FOR_u32(TIMES, ITERATOR) 					f_FOR_0(TIMES, ITERATOR, u32)						//!< Typical for-loop with iterator of type u_int 	with startvalue 0
#define f_FOR_sint(TIMES, ITERATOR) 				f_FOR_0(TIMES, ITERATOR, s_int)						//!< Typical for-loop with iterator of type u_int 	with startvalue 0
#define f_FOR_sizet(TIMES, ITERATOR) 				f_FOR_0(TIMES, ITERATOR, size_t)					//!< Typical for-loop with iterator of type size_t 	with startvalue 0

#define f_FOR_int_1(TIMES, ITERATOR) 				f_FOR_1(TIMES, ITERATOR, int)						//!< Typical for-loop with iterator of type int 	with startvalue 1
#define f_FOR_uint_1(TIMES, ITERATOR) 				f_FOR_1(TIMES, ITERATOR, u_int)						//!< Typical for-loop with iterator of type u_int 	with startvalue 1
#define f_FOR_u32_1(TIMES, ITERATOR) 				f_FOR_1(TIMES, ITERATOR, u32)						//!< Typical for-loop with iterator of type u_int 	with startvalue 1
#define f_FOR_sint_1(TIMES, ITERATOR) 				f_FOR_1(TIMES, ITERATOR, s_int)						//!< Typical for-loop with iterator of type u_int 	with startvalue 1
#define f_FOR_sizet_1(TIMES, ITERATOR) 				f_FOR_1(TIMES, ITERATOR, size_t)					//!< Typical for-loop with iterator of type size_t  with startvalue 1

#define f_FOR_int_i(TIMES) 							f_FOR_int(TIMES, i)									//!< Typical for-loop with iterator (i) of type int 	with startvalue 0
#define f_FOR_uint_i(TIMES) 						f_FOR_uint(TIMES, i)								//!< Typical for-loop with iterator (i) of type u_int 	with startvalue 0
#define f_FOR_u32_i(TIMES) 							f_FOR_uint(TIMES, i)								//!< Typical for-loop with iterator (i) of type u_int 	with startvalue 0
#define f_FOR_sint_i(TIMES) 						f_FOR_sint(TIMES, i)								//!< Typical for-loop with iterator (i) of type u_int 	with startvalue 0
#define f_FOR_sizet_i(TIMES) 						f_FOR_sizet(TIMES, i)								//!< Typical for-loop with iterator (i) of type size_t 	with startvalue 0

#define f_FOR_int_i_1(TIMES) 						f_FOR_int_1(TIMES, i)								//!< Typical for-loop with iterator (i) of type int 	with startvalue 1
#define f_FOR_uint_i_1(TIMES) 						f_FOR_uint_1(TIMES, i)								//!< Typical for-loop with iterator (i) of type u_int 	with startvalue 1
#define f_FOR_u32_i_1(TIMES) 						f_FOR_u32_1(TIMES, i)								//!< Typical for-loop with iterator (i) of type u_int 	with startvalue 1
#define f_FOR_sint_i_1(TIMES) 						f_FOR_sint_1(TIMES, i)								//!< Typical for-loop with iterator (i) of type u_int 	with startvalue 1
#define f_FOR_sizet_i_1(TIMES) 						f_FOR_sizet_1(TIMES, i)								//!< Typical for-loop with iterator (i) of type size_t 	with startvalue 1

#define f_FOR_uint_2D(TIMES_1, ITERATOR_1, TIMES_2, ITERATOR_2) 	f_FOR_uint(TIMES_1, ITERATOR_1) f_FOR_uint(TIMES_2, ITERATOR_2)
#define f_FOR_uint_ij_2D(TIMES_i, TIMES_j) 							f_FOR_uint_2D(TIMES_i, i, TIMES_j, j)

// === Helpers ===
#define ONCE(THING) 				do { THING } while (0)					//!< Execute code once without the need of a trailing semicolon (;)

// === Lists ===
// #define LENGHT_OF(LIST)		(sizeof(LIST) / sizeof(*LIST))					//!< The lenght of an array or pointer (DEPRECATED)
#define LENGTH(list) _countof(list) //!< The length of an array

// === Print ===
#define PRINT_I32(N) 				printf(#N ": %d\n", N)						//!< Prints a I32 (%d) followed by a \n
#define PRINT_U32(N) 				printf(#N ": %u\n", N)						//!< Prints a I32 (%u) followed by a \n
#define PRINT_I64(N) 				printf(#N ": %lld\n", N)					//!< Prints a I64 (%lld) followed by a \n
#define PRINT_U64(N) 				printf(#N ": %llu\n", N)					//!< Prints a U64 (%llu) followed by a \n
#define PRINT_F32(N) 				printf(#N ": %f\n", N)						//!< Prints a F32 (%f) followed by a \n
#define PRINT_F64(N) 				printf(#N ": %f\n", N)						//!< Prints a F64 (%f) followed by a \n

#define PRINT_INT(N)  				printf(#N ": %d\n", N)						//!< Prints an signed int   (or any other type that can be printed with %d) followed by a \n
#define PRINT_UINT(N) 				printf(#N ": %u\n", N)						//!< Prints an unsigned int (or any other type that can be printed with %u) followed by a \n
#define PRINT_STR(N)  				printf(#N ": %s\n", N)						//!< Prints an char pointer (or any other type that can be printed with %s) followed by a \n
#define PRINT_BOOL(N) 				printf(#N ": %s\n", N ? "True" : "False")
#define PRINT_POINTER(N) 			printf(#N ": %p\n", (void*) N)
#define f_PRINT_SIZEOF(N) 			printf("Size of " #N ": %llu bytes\n", sizeof(N))
#define f_PRINT_FLOAT(N)			printf(#N ": %f\n", N)
#define PRINT(N)					printf(N "\n")							//!< Prints a string litteral and adds a newline afterward

// === Pointers ===
/**
 * Macro that adds a static check that this is a list with at least one element (aka not null) 
 * 
 * @details
 * Adds [static 1] after obj, i.e. "int _ptr(foo)" becomes int "foo[static 1]", which means that foo
 * is an array (i.e. a pointer) that contatins/points to at least one element. This means that the
 * pointer foo is never null.
 * 
 * Only works on function parameters, example: "void myFunc(int _ptr(foo)) {}", here foo has the type "int*"
 */
#define _ptr(parameter) 	parameter[static 1]
/**
 * Macro to declare a constant parameter pointer to a object, with nullchecking by the compiler
 * 
 * This is just _ptr(...) but the pointer (not what the pointer is pointing at) is const
*/
#define _cptr(parameter) 	parameter[const static 1]

// === Allocation ===
#define f_CALLOC(pointer, amount) pointer = calloc(amount, sizeof(*pointer))
#define f_FREE(pointer) free(pointer); pointer = nullptr

// === Assert ===
/**
 * @brief Crashes the program here immediatly 
 * @param[in] MESSAGE Message to be printed alongside the crash to give context
 * @details A report with file and line information will be provided in \c stderr and an optional \p MESSAGE can be printed alongside it
 * 
 * Can be used inside an \c if statement to create essentialy an \c assert
 * Like <tt> if (cond) CRASH_HERE("LOL!") </tt> not <tt> if (CRASH_HERE("LOL!")) </tt>
 */
#define CRASH_HERE(MESSAGE) \
	ONCE( \
		fprintf(stderr, "> Crash in %s:%d\n> Message: %s\n", \
		__FILE__, __LINE__, \
		MESSAGE); \
		*(int*)0 = 0xDEAD; \
	)

// Ways to crash and make the debugger detect it
// - abort()
// - raise(SIGSEGV) // requires signal.h
// - *(int*)0 = 0xDEAD // works!
// - assert() // works!


// Prob move these to fcu_debug
#define ASSERT_BASE(CONDITION, MESSAGE) ONCE( if (!(CONDITION)) { CRASH_HERE(MESSAGE); } )
#define ASSERT_M(CONDITION, MESSAGE)	ASSERT_BASE(CONDITION, "Assert failed: " #CONDITION "\n" "> Assert Message: " MESSAGE)
#define ASSERT(CONDITION) 				ASSERT_M(CONDITION, "")
#define ASSERT_NULLCHECK(THING) 		ASSERT_M(THING != nullptr, "Null check failed!")

#define ASSERT_THAT_IF_M(THIS_IS_TRUE, THEN, MESSAGE) \
	ASSERT_BASE( !(THIS_IS_TRUE) || ((THIS_IS_TRUE) && (THEN)), \
	"Assert failed: If (" #THIS_IS_TRUE ") then (" #THEN ")" "\n" \
	"> Assert Message: " MESSAGE)
	
#define ASSERT_THAT_IF(THIS_IS_TRUE, THEN) \
	ASSERT_THAT_IF_M(THIS_IS_TRUE, THEN,  "None")


// ----------------------------------------
// Asserts
// ----------------------------------------
// static inline void assert_nonnull(sc_ptr_t pointer) { assert(pointer != nullptr); }
#define assert_nonnull(pointer) assert(pointer != nullptr)
#define assert_allFileClosed()  assert( _fcloseall() == 0 )



// === Misc ===
#define attr_UNUSED __attribute__ ((unused))

#if 0
#define _byteswap(value) \
	_Generic((value), 					\
		int: _byteswap_ulong(value), 	\
		u16: _byteswap_ushort(value), 	\
		u32: _byteswap_ulong(value), 	\
		u64: _byteswap_uint64(value) 	\
	)
#endif

#define f_byteswap16(value) _byteswap_ulong(value)
#define f_byteswap32(value) _byteswap_ulong(value)
#define f_byteswap64(value) _byteswap_uint64(value)

#pragma endregion fcu_core
#endif

// ========================================
// fcu_strings
// ========================================
#if defined(fcu_ALL) || defined(fcu_STRINGS)
#pragma region fcu_strings
// Returns 1 if true, otherwise zero
#define f_char_is_lowercase(character)			( character >= 'a' && character <= 'z' )
#define f_char_is_uppercase(character)			( character >= 'A' && character <= 'Z' )
#define f_char_is_number(character)				( character >= '0' && character <= '9' )
#define f_char_is_letter(character)				( f_char_is_lowercase(character) || f_char_is_uppercase(character) )
#define f_char_is_in_alphabet(character)		( f_char_is_letter(character) )
#define f_char_is_alpha_numercial(character) 	( f_char_is_letter(character) || f_char_is_number(character) )

#define f_char_is_blank(character) 				( character == '\t' || character == ' ')

#define f_char_toggle_uppercase(character) 		( character ^ 0x20 )
#define f_char_toggle_lowercase(character) 		( character ^ 0x20 )

// Compares two strings, returns true if they match
// Stolen from <string.h>, rewritten to be easier to understand
// If both pointers are null, true is returned
// If only one of the pointers are null, false is retuned
fcu_CAPI int f_streql(const char* l, const char* r) {
	// If both strings are null
	if (l == nullptr && r == nullptr) return 1; else

	// If one of them are null
	if (l == nullptr || r == nullptr) return 0;
	
	// for (; *l==*r && *l; l++, r++);
	while (*l == *r && *l != '\0')
	{
		l++; r++;
	}

	// Reached the end of both strings
	if (*r == '\0' && *l == '\0') 
		return 1;

	return 0;
}

// Compares two strings first n characters, returns true if they match
// f_streql but with a max lenght of n
// If both strings terminate before n characters are reached, true is returned
fcu_CAPI int f_streql_n(const char* l, const char* r, u_int n) {
	// If both strings are null
	if (l == nullptr && r == nullptr) return 1; else

	// If one of them are null
	if (l == nullptr || r == nullptr) return 0;

	// for (; n && *l == *r && *l ; l++, r++, n--);
	while (
		n > 0 
	&& *l == *r 
	&& *l != '\0'
	) {
		l++; r++;
		n--;
	}

	// They matched the whole way through
	if (n == 0) return 1;
	
	// Both strings terminate before n characters
	if (*l == '\0' && *r == '\0') return 1;
	
	return 0;
}

// Compares two strings first n characters, returns true if thier letters match
// Is case insensitive, i.e. allows A == a
// f_streql but case insensitive and with a max lenght of n
// If both strings terminate before n characters are reached, true is returned
fcu_CAPI int f_streql_nic(const char* l, const char* r, u_int n) {
	// If both strings are null
	if (l == nullptr && r == nullptr) return 1; else

	// If one of them are null
	if (l == nullptr || r == nullptr) return 0;

	while (
		n > 0 
	// Checks if the characters match, if not and one of them is a letter, check if it's uppercase version match
	&& ( *l == *r || ( f_char_is_letter(*r) ? *l == f_char_toggle_uppercase(*r) : false ) ) 
	&& *l != '\0')
	{
		l++; r++;
		n--;
	}

	// They matched the whole way through
	if (n == 0) 
		return 1;
	
	// Both strings terminate before n characters
	if (*l == '\0' && *r == '\0') 
		return 1;
	
	return 0;
}

// Returns lenght of the string (excluding the null terminator)
// Stolen from <string.h> or stackoverflow (can't remember), but rewritten to be easier to understand (by me)
// Also returns a 32 bit unsigned instead of a 64 bit unsigned
fcu_CAPI u_int f_strlen(c_str_t s) {
	u_int l = 0;
	for (; s && *s; s++, l++);
	return l;
}

/**
 * Returns true if the entire string is composed of digits [0-9]
 * Returns false if s is a nullptr or is an empty string
 */
fcu_CAPI int f_str_is_number(const char* s) 
{
	if (s == nullptr || *s == '\0') return 0;

	for (; *s; s++) {
		if ( !f_char_is_number(*s) ) return 0;
	}

	return 1;
}

/**
 * Returns true if the entire string is composed of digits (-)[0-9]
 * Exactly the same as f_str_is_number but allows an optional plus/minus sign at the begining, aka accepts a negative number
 */
fcu_CAPI int f_str_is_number2(const char* s) 
{
	if ( s == nullptr) return 0; else

	if (*s == '-' || *s == '+') s++;
	
	return f_str_is_number(s);
}

/**
 * Prints an amount of bytes as either Gigabyte, Megabyte or kilobyte (formatted)
 */
fcu_CAPI void f_print_byteAmount(u64c bytes)
{
	if (bytes >= GigaByte) {
		if (bytes % GigaByte == 0) 	printf_s("%llu GB", (bytes / GigaByte));
		else 						printf_s("%.2f GB", (f64) bytes / GigaByte);
	} else
	if (bytes >= MegaByte) {
		if (bytes % MegaByte == 0) 	printf_s("%llu MB", (bytes / MegaByte));
		else 						printf_s("%.2f MB", (f64) bytes / MegaByte);
	} else
	if (bytes >= kiloByte) {
		if (bytes % kiloByte == 0) 	printf_s("%llu kB", (bytes / kiloByte));
		else 						printf_s("%.2f kB", (f64) bytes / kiloByte);
	} else {
		printf_s("%llu B", bytes);
	}
}

// Removes \n if it's the last character in the string
#define f_str_remove_trailing_newline(string) (string)[strcspn((string), "\n")] = 0

/**
 * Trims off a number from a string
 * Returns number of read/trimmed characters
 * example: cursor += f_str_trim_number(string, cursor);
 */ 
fcu_CAPI u32 f_str_trim_number(cchar _cptr(string), u32c offset)
{
	u32 i = 0;
	while ( f_char_is_number(string[offset + i]) ) i++;
	return i;
}

/**
 * Trims off whitespaces from a string
 * Returns number of read/trimmed characters
 * example: cursor += f_str_trim_whitespaces(string, cursor);
 */ fcu_CAPI u32 f_str_trim_whitespaces(cchar _cptr(string), u32c offset)
{
	u32 i = 0;
	while ( f_char_is_blank(string[offset + i]) ) i++;
	return i;
}

/**
 * Parses a u32 from a string
 * Returns number of read characters, use third parameter to get the read value (can be set as null)
 * example: cursor += f_str_parse_u32(string, cursor, &value);
 */
fcu_CAPI u32 f_str_parse_u32(cchar _cptr(string), u32 cursor, u32* read_value_into)
{
	// Calculate number of characters to parse
	u32 digits = f_str_trim_number(&string[cursor], 0);
	assert(digits < 16); // todo

	// Parse the value and return
	if (read_value_into != nullptr)
		*read_value_into = strtoul(&string[cursor], nullptr, 10);
	return digits;
}


// Translate å, ä and ö to windows ascii representation (for use when accessing files with åäö in thier names via fopen, not needed for printf)
fcu_CAPI str_t f_strmap_swedish2ascii(cchar _cptr(string), u32 stringSize)
{
	// Create a buffer and a cursor for the new string
	u32 cursor = 0;
	str_t f_CALLOC(buffer, stringSize);

	f_FOR_u32_i(stringSize)
	{
		u8 specialChar = 0;

		// On 195, check for special character (i.e. ååö and ÅÄÖ)
		if ((u8) string[i] == 195)
		{
			if ((u8) string[i + 1] == 165) specialChar = 229; else 	// å
			if ((u8) string[i + 1] == 164) specialChar = 228; else 	// ä
			if ((u8) string[i + 1] == 182) specialChar = 246; else 	// ö
			if ((u8) string[i + 1] == 133) specialChar = 197; else 	// Å
			if ((u8) string[i + 1] == 132) specialChar = 196; else 	// Ä
			if ((u8) string[i + 1] == 150) specialChar = 214; 		// Ö



			if (specialChar != 0) {
				i++; // Skip over the next character
				buffer[cursor] = (char) specialChar;
			}
		}

		else {
			buffer[cursor] = string[i];
		}

		cursor++;
	}

	return buffer;
}


#pragma endregion fcu_strings
#endif

// ========================================
// fcu_numbers
// ========================================
#if defined(fcu_ALL) || defined(fcu_NUMBERS)
#pragma region fcu_numbers

#define f_PI 3.1415926535897932384

#define f_DEG2RAD (f_PI/180.0)
#define f_RAD2DEG (180.0/f_PI)

// // Clamps an int between two values
// fcu_CAPI int f_clamp_int(int value, int min, int max) {
// 	const int minimum = value < min ? min : value;
// 	return minimum > max ? max : minimum;
// }

// // Clamps an unsigned int between two values
// fcu_CAPI u_int f_clamp_uint(u_int value, u_int min, u_int max) {
// 	const u_int minimum = value < min ? min : value;
// 	return minimum > max ? max : minimum;
// }


// // Returns the bigger unsigned int
// fcu_CAPI u_int f_max_uint(u_int a, u_int b) {
// 	return a > b ? a : b;
// }

// // Returns the smaller unsigned int
// fcu_CAPI u_int f_min_uint(u_int a, u_int b) {
// 	return a < b ? a : b;
// }


// Returns the bigger value
// Warning: does not cache the arguments
#define f_max(a, b) \
	(a > b ? a : b)

// Returns the smaller value
// Warning: does not cache the arguments
#define f_min(a, b) \
	(a < b ? a : b)

// Clamps a value between a minimum and a maximum
// Warning: does not cache the arguments
#define f_clamp(value, min, max) \
	(f_min(max, f_max(min, value) ))

/**
 * Retuns the biggest of 3 values
 * Warning: does not cache the arguments
 */
#define f_max3(a, b, c) \
	f_max(a, f_max(b, c))

/**
 * Retuns the smallest of 3 values
 * Warning: does not cache the arguments
 */
#define f_min3(a, b, c) \
	f_min(a, f_min(b, c))

// #if ( sizeof (unsigned int) ) != sizeof(u32))
// #error 
// #endif

// Doesn't seem to work atm
#define f_abs(value) ( ((value) >= 0) ? (value) : (value) * (-1) )

// u32 f_abs(int value) {
// 	return (u32) _f_abs(value);
// }

fcu_CAPI u32 f_abs_i32(i32 value) {
	return (u32) f_abs(value);
}


// Returns a random float between 0.0 and 1.0
fcu_CAPI float f_randf() {
	return (float) rand() / (float) RAND_MAX;
}

// Returns a random double between 0.0 and 1.0
fcu_CAPI double f_rand() {
	return (double) rand() / (double) RAND_MAX;
}

// Returns a value linearly between lower and upper where t=0.0 
// is equal to lower and t=1.0 is equal to upper.
// @note lower_bound <= upper_bound (useally)
#define f_lerp_between(lower, upper, t) \
	( ( (upper) - (lower) ) * (t) + (lower) )

// Should do the opposite of f_lerp_between(..)
// A return value between 0.0 and 1.0 means that value lies
// between lower and upper
#define f_unlerp_between(lower, upper, value) \
	( ( (value) - (lower) ) / ( (upper) - (lower) ) )

// Returns a random value between lower and upper
//
// (lower and upper are included)
// @note lower <= upper (useally)
#define f_rand_between(lower, upper) \
	f_lerp_between(lower, upper, f_rand())
	// ( ((upper) - (lower)) * f_rand() + (lower) )

#pragma endregion fcu_numbers
#endif

// ========================================
// fcu_time
// ========================================
#if defined(fcu_ALL) || defined(fcu_TIME)
#pragma region fcu_time

/** 
 * Calculates how much "ahead" time_1 is time_0
 * returns time_1 - time_0
 * 
 * Attribution: https://stackoverflow.com/a/68804612
 * Remixed to match the style of the other fcu-functions
 * See also: https://linux.die.net/man/3/clock_gettime
 */
fcu_CAPI struct timespec f_clock_getdiff(const struct timespec _ptr(time_1), const struct timespec _ptr(time_0)) {
	struct timespec diff = {
		.tv_sec  = time_1->tv_sec  - time_0->tv_sec,
		.tv_nsec = time_1->tv_nsec - time_0->tv_nsec,
	};
	if (diff.tv_nsec < 0) {
		diff.tv_nsec += 1000000000;
		diff.tv_nsec--;
	}
	return diff;
}

/** 
 * Calculates how much "ahead" time_1 is time_0
 * returns time_1 - time_0 as a double
 * 
 * Attribution: https://stackoverflow.com/a/68804612
 * Remixed to match the style of the other fcu-functions
 * See also: https://linux.die.net/man/3/clock_gettime
 */
fcu_CAPI double f_clock_diffrence(const struct timespec _ptr(time_1), const struct timespec _ptr(time_0)) {
	return ((double) (time_1->tv_sec  - time_0->tv_sec ))
	+  ((double) (time_1->tv_nsec - time_0->tv_nsec)) / 1e9;
}

typedef struct timespec f_time;

fcu_CAPI f_time f_time_getDiff(const f_time _cptr(time_1), const f_time _cptr(time_2)) {
	return f_clock_getdiff(time_1, time_2);
}

fcu_CAPI f64 f_time_getDiffD(const f_time time_1, const f_time time_2) {
	return f_clock_diffrence(&time_1, &time_2);
}

fcu_CAPI f_time f_time_getTime() {
	f_time time = {0};
	assert( 0 == clock_gettime(CLOCK_MONOTONIC, &time) );
	
	return time;
}

#pragma endregion fcu_time
#endif

// ========================================
// fcu_debug
// ========================================
#if defined(fcu_ALL) || defined(fcu_DEBUG)
#pragma region fcu_debug

/** Usage:
 * 	\param desc:    if non-NULL, printed as a description before hex dump.
 * 	\param addr:    the address to start dumping from.
 * 	\param len:     the number of bytes to dump.
 * 	\param perLine: number of bytes on each output line.
 * Attribution: https://stackoverflow.com/a/7776146
 * Remixed to match the style of the other fcu-functions
*/ 
fcu_CAPI void f_hex_dump (const str_t desc, const void* addr, const u_int len, u_int perLine) {
	// Silently ignore silly per-line values.
	if (perLine < 4 || perLine > 64) perLine = 16;

	u_int i;
	char buff[perLine+1];
	const char* pc = (const char*) addr;
	
	// Output description if given.
	if (desc != NULL) printf ("%s:\n", desc);

	// Length checks.
	if (len == 0) {
		printf("  ZERO LENGTH\n");
		return;
	}
	// if (len < 0) {
	//     printf("  NEGATIVE LENGTH: %d\n", len);
	//     return;
	// }

	// Process every byte in the data.
	for (i = 0; i < len; i++) {
		// Multiple of perLine means new or first line (with line offset).
		if ((i % perLine) == 0) {
			// Only print previous-line ASCII buffer for lines beyond first.
			if (i != 0) printf ("  %s\n", buff);

			// Output the offset of current line.
			printf ("  %04x ", i);
		}

		// Now the hex code for the specific character.
		printf (" %02x", pc[i]);

		// And buffer a printable ASCII character for later.
		if ((pc[i] < 0x20) || (pc[i] > 0x7e)) // isprint() may be better.
			buff[i % perLine] = '.';
		else
			buff[i % perLine] = pc[i];
		buff[(i % perLine) + 1] = '\0';
	}

	// Pad out last line if not exactly perLine characters.
	while ((i % perLine) != 0) {
		printf ("   ");
		i++;
	}

	// And print the final ASCII buffer.
	printf ("  %s\n", buff);
}

fcu_CAPI void f_printBitsInByte(u8 byte)
{
	printf("0b");
	int size = sizeof(u8) * 8;
    f_FOR_int_i(size) {
		printf("%i", (byte >> (size - i - 1)) & 1);
	}
}

// Check if this one still works
fcu_CAPI void f_printf_bits(char* bytes, u_int size) {
	f_FOR_uint_i(size) {
		i = size - i - 1; // Iterate in reverse, i.e. [size, size-1, size-2, ..., 1, 0]
		char byte = bytes[i];
		if (i != 0) printf(" ");

		printf("0b");
		f_FOR_uint(8, j) {
			j = 8 - j - 1; // Iterate in reverse, i.e. [7, 6, 5, 4, 3, 2, 1, 0]
			printf("%d", byte >> (8 - j - 1) & 1);
		}
	}
	printf("\n");
}

// ----------------------------------------
// ANSI Control codes
// ----------------------------------------
#define f_ANSI_ESC 			"\x1b"
#define f_ANSI_START 		f_ANSI_ESC"["
#define f_ANSI_END 			"m"
#define f_ANSI_RESET 		"\x1b[0m"

// Color Foreground ___
#define f_ANSI_CF_BLACK 	"\x1b[30m"
#define f_ANSI_CF_RED 		"\x1b[31m"
#define f_ANSI_CF_GREEN 	"\x1b[32m"
#define f_ANSI_CF_YELLOW 	"\x1b[33m"
#define f_ANSI_CF_BLUE 		"\x1b[34m"
#define f_ANSI_CF_MAGENTA 	"\x1b[35m"
#define f_ANSI_CF_CYAN 		"\x1b[36m"
#define f_ANSI_CF_WHITE 	"\x1b[37m"
#define f_ANSI_CF_DEFAULT 	"\x1b[39m"

// Color Dim Foreground ___
#define f_ANSI_CDF_BLACK 	"\x1b[2;30m"
#define f_ANSI_CDF_RED 		"\x1b[2;31m"
#define f_ANSI_CDF_GREEN 	"\x1b[2;32m"
#define f_ANSI_CDF_YELLOW 	"\x1b[2;33m"
#define f_ANSI_CDF_BLUE 	"\x1b[2;34m"
#define f_ANSI_CDF_MAGENTA 	"\x1b[2;35m"
#define f_ANSI_CDF_CYAN 	"\x1b[2;36m"
#define f_ANSI_CDF_WHITE 	"\x1b[2;37m"
#define f_ANSI_CDF_DEFAULT 	"\x1b[2;39m"


#define f_DEBUG_FUNC_START() printf(f_ANSI_CDF_YELLOW " -> Starting function " "%s" f_ANSI_RESET "\n", __func__); const f_time f_START_TIME = f_time_getTime()
#define f_DEBUG_FUNC_END()   printf(f_ANSI_CDF_YELLOW " -> Ending function " "%s" " (%.6f s)" f_ANSI_RESET "\n", __func__, f_time_getDiffD(f_time_getTime(), f_START_TIME))

#pragma endregion fcu_debug
#endif

#if defined(fcu_ALL) || defined(fcu_COLOR)
#pragma region fcu_color
	


	// Attribution: https://stackoverflow.com/a/4382138/9953215
	static u32c f_COLOR_LIST_BOYNTON_RGBA[] = {
		0x0000FFff, // Blue		(  0,   0, 255),
		0xFF0000ff, // Red		(255,   0,   0),
		0x00FF00ff, // Green	(  0, 255,   0),
		0xFFFF00ff, // Yellow	(255, 255,   0),
		0xFF00FFff, // Magenta	(255,   0, 255),
		0xFFF0F0ff, // Pink		(255, 128, 128),
		0xF0F0F0ff, // Gray		(128, 128, 128),
		0xF00000ff, // Brown	(128,   0,   0),
		0xFFF000ff, // Orange	(255, 128,   0),
		
		// Black and White can also be added if needed
	};

	// Attribution: https://stackoverflow.com/a/4382138/9953215
	static u32c f_COLOR_LIST_KELLY_RGBA[] = {
		0xFFB300ff, // Vivid Yellow
		0x803E75ff, // Strong Purple
		0xFF6800ff, // Vivid Orange
		0xA6BDD7ff, // Very Light Blue
		0xC10020ff, // Vivid Red
		0xCEA262ff, // Grayish Yellow
		0x817066ff, // Medium Gray

		// The following don't work well for people with defective color vision
		0x007D34ff, // Vivid Green
		0xF6768Eff, // Strong Purplish Pink
		0x00538Aff, // Strong Blue
		0xFF7A5Cff, // Strong Yellowish Pink
		0x53377Aff, // Strong Violet
		0xFF8E00ff, // Vivid Orange Yellow
		0xB32851ff, // Strong Purplish Red
		0xF4C800ff, // Vivid Greenish Yellow
		0x7F180Dff, // Strong Reddish Brown
		0x93AA00ff, // Vivid Yellowish Green
		0x593315ff, // Deep Yellowish Brown
		0xF13A13ff, // Vivid Reddish Orange
		0x232C16ff, // Dark Olive Green

		// Black and White can also be added if needed
	};

	// Extracts the red channel from a 32-bit rgba color (little endian, expects bytes to be swapped)
	#define f_color_RGBA2R(RGBA) ((RGBA) >>  0 | 0xff)
	// Extracts the red channel from a 32-bit rgba color (little endian, expects bytes to be swapped)
	#define f_color_RGBA2G(RGBA) ((RGBA) >>  8 | 0xff)
	// Extracts the red channel from a 32-bit rgba color (little endian, expects bytes to be swapped)
	#define f_color_RGBA2B(RGBA) ((RGBA) >> 16 | 0xff)
	// Extracts the red channel from a 32-bit rgba color (little endian, expects bytes to be swapped)
	#define f_color_RGBA2A(RGBA) ((RGBA) >> 24 | 0xff)
	

	#pragma region    RGB to HSV
	#if 0
		#include <math.h>
		
		/**
		 * Converts rgb to hsv
		 * Arguments should be in the range 0..1
		 * Resulting Hue will be in radian, Saturation and Value will be in the ranges 0..1
		 * Attribution: https://www.rapidtables.com/convert/color/rgb-to-hsv.html
		 */
		fcu_CAPI void f_color_RGB2HSV(f64c R_prim, f64c G_prim, f64c B_prim, 
			f64 _cptr(Hue), f64 _cptr(Saturation), f64 _cptr(Value)
		) {
			f64 C_max = f_max3(R_prim, G_prim, B_prim);
			f64 C_min = f_min3(R_prim, G_prim, B_prim);
			f64 delta = C_max - C_min;

			// Hue
			if (delta == 0.0) 
				*Hue = 0.0; 
			else
			if (C_max == R_prim) {
				*Hue = 60.0 * f_DEG2RAD * fmod((G_prim - B_prim) / delta, 6.0);
			} else
			if (C_max == G_prim) {
				*Hue = 60.0 * f_DEG2RAD * ((B_prim - R_prim) / delta + 2.0);
			} else
			if (C_max == B_prim) {
				*Hue = 60.0 * f_DEG2RAD * ((R_prim - G_prim) / delta + 4.0);
			} else
				unreachable();

			*Saturation = (C_max == 0.0) ? 0.0 : delta / C_max;
			*Value      =  C_max;
		}

		/**
		 * Converts a 32-bit rgba color (little endian, expects bytes to be swapped) to HSVa
		 * Resulting Hue will be in radian, Saturation, Value and Alpha will be in the ranges 0..1
		 */
		fcu_CAPI void f_color_RGBA2HSVA(u32c RGBA, 
			f64 _cptr(Hue), f64 _cptr(Saturation), f64 _cptr(Value), f64 _cptr(Alpha)
		) {
			f64c R_prim = (f64) f_color_RGBA2R(RGBA) / (f64) UINT8_MAX;
			f64c G_prim = (f64) f_color_RGBA2G(RGBA) / (f64) UINT8_MAX;
			f64c B_prim = (f64) f_color_RGBA2B(RGBA) / (f64) UINT8_MAX;
			f64c A_prim = (f64) f_color_RGBA2A(RGBA) / (f64) UINT8_MAX;

			f_color_RGB2HSV(R_prim, G_prim, B_prim, Hue, Saturation, Value);
			*Alpha = A_prim;
		}

	#endif
	#pragma endregion



#pragma endregion
#endif


#if defined(fcu_ALL) || defined(fcu_WINDOWS)
#pragma region fcu_windows

void f_FixWindowsTerminal();

#ifdef FCU_WINDOWS_IMPLEMENTATION

	#include "Windows.h"
	#include <assert.h>
	// #include <stdio.h>

	void f_FixWindowsTerminal() {
		// Get the handle for stdout
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		assert(hOut != INVALID_HANDLE_VALUE);

		// Get the mode
		DWORD dwMode = 0;
		assert(GetConsoleMode(hOut, &dwMode));

		// Add virtual terminal processing
		dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		assert(SetConsoleMode(hOut, dwMode));
		
		// Add utf-8
		SetConsoleOutputCP(CP_UTF8);
	}

#endif

#pragma endregion
#endif


#pragma GCC diagnostic pop

/**
 * @file   fcu_common.h
 * @author Fredrik Ahlberg (fcu.ahlberg\@gmail.com)
 * @brief  Commonly used types and macros
 * 
 * Contains typedef for diffrent types of signed/unsigned
 * integers and bytes, a "string" pointer, macros for diffrent
 * commonly used for-loops to reduce typing, helper "functions"
 * and some constants.
 * 
 * Usage:
 * \code #define  fcu_CORE
 * \code #include fcu_common.h
 * 
 * Include Options:
 * - \code fcu_ALL
 * - \code fcu_CORE
 * - \code fcu_STRINGS
 * - \code fcu_DEBUG
 * - \code fcu_NUMBERS
 */
