// Copyright 2025 Fredrik Ahlberg <fcu.ahlberg@gmail.com>
//
// SPDX-License-Identifier: Unlicense OR MIT
// File description can be found at the end of this file (to avoid a wall of text here)

// Version: 0.1.0

#pragma once
#include "fcu_common.h"
#include <string.h>

// #define f_LIST_EXPANSION_FACTOR 1.5f
// #define f_LIST_PRINT_ON_REALLOC

#ifndef f_LIST_EXPANSION_FACTOR
	/**
	 * @note Expansion factor of 2 is the best choice if you have multiple "active" lists.
	 * But for only one list then 1.5 is better (but when the fuck do you only have one big 
	 * list that needs additional memory efficency).
	 */
	#define f_LIST_EXPANSION_FACTOR 2.0f
#endif
#define f_LIST_EXPAND_CAPACITY(capacity) capacity = (u32) ((f32) capacity * f_LIST_EXPANSION_FACTOR)

#pragma region    Reallocations
	
	#ifdef f_LIST_PRINT_ON_REALLOC
		#define _f_LIST_REALLOC(list, new_size, getter) \
			printf("Reallocating the list %-20s (from %s) to ", #list, __FILE__); \
			f_print_byteAmount(new_size); PRINT(); \
			list.getter = realloc(list.getter, new_size)
	#else
		#define _f_LIST_REALLOC(list, new_size, getter) \
			list.getter = realloc(list.getter, new_size)
	#endif

	#define f_LIST_REALLOC(list, new_size) _f_LIST_REALLOC(list, new_size, get)

#pragma endregion


#define _f_LIST_ADD(name, type, accessName) \
	struct { \
		type* accessName; 	/* Pointer to first element */ \
		u32   capacity; 	/* Total size allocated to list */ \
		u32   count; 		/* Amount of elements */ \
	} name

#define f_LIST_ADD(name, type) _f_LIST_ADD(name, type, get)
	
#define f_LIST_OF_STRINGS_ADD(name) \
	struct { \
		u32 cursor; \
		_f_LIST_ADD(buffer, char, start) \
;		 f_LIST_ADD(indicies, u32); \
	} name



// ========================================
// Methods
// ========================================
typedef f_LIST_ADD(f_ListTemplate, void);
typedef f_LIST_OF_STRINGS_ADD(f_ListOfStringsTemplate);

#pragma region    Initialization
	
	#define _f_List_init(list, initial_capacity, getter) ONCE( \
		list.count = 0; \
		list.capacity = initial_capacity; \
		f_CALLOC( list.getter, initial_capacity); \
		assert_nonnull( list.getter ); \
	)
	#define f_List_init(list, initial_capacity) _f_List_init(list, initial_capacity, get)

	#define f_List_ofStrings_init(list, initial_capacity, initial_char_buffer_capacity) ONCE( \
		list.cursor = 0; \
		_f_List_init(list.buffer, initial_char_buffer_capacity, start); \
;		 f_List_init(list.indicies, initial_capacity); \
	)

#pragma endregion

#pragma region    Get size
	
	#define _f_List_calcAllocSize(list, getter) \
		((list).capacity * sizeof( *(list).getter ))

	#define  f_List_calcAllocSize(list) _f_List_calcAllocSize(list, get)
	#define  f_List_ofStrings_calcAllocSize(list) \
		( _f_List_calcAllocSize(list.buffer, start) + f_List_calcAllocSize(list.indicies) )



	#define _f_LList_calcAllocSize(list, getter) _f_List_calcAllocSize(*(list), getter)



#pragma endregion

#pragma region    Free
	
	#define _f_List_free(list, getter) ONCE( f_FREE(list.getter); )
	#define  f_List_free(list) _f_List_free(list, get)
	#define  f_List_ofStrings_free(list) ONCE( \
		_f_List_free(list.buffer, start); \
;		 f_List_free(list.indicies); \
	)

	#define _f_LList_free(list, getter) _f_List_free(list, getter)

#pragma endregion

#pragma region    Appends

	#define _f_List_Append(list, appende, getter) ONCE( \
		if (list.count == list.capacity) { \
			f_LIST_EXPAND_CAPACITY(list.capacity); \
			_f_LIST_REALLOC(list, _f_List_calcAllocSize(list, getter), getter); \
		} \
		assert(list.count < list.capacity); \
		list.getter[ list.count ] = appende; \
		list.count++; \
	)
	#define  f_List_Append(list, appende) _f_List_Append(list, appende, get)
	
	#define  f_List_ofStrings_Append(list, string, string_size) \
	ONCE( \
		f_List_Append(list.indicies, list.cursor); \
		\
		if ( (u64) list.buffer.count + (u64) (string_size + 1) > list.buffer.capacity ) \
		{ \
			f_LIST_EXPAND_CAPACITY(list.buffer.capacity); \
			_f_LIST_REALLOC(list.buffer, _f_List_calcAllocSize(list.buffer, start), start); \
		} \
		\
		assert( (u64) list.buffer.count + (u64) (string_size + 1) <= list.buffer.capacity); \
		assert(0 == strncpy_s( \
			&list.buffer.start[list.cursor], \
			list.buffer.capacity - list.cursor, \
			string, string_size \
		)); \
		\
		list.cursor += (string_size + 1); \
		list.buffer.count = list.cursor; \
		assert(list.cursor <= list.buffer.capacity); \
	)
	
#pragma endregion

#pragma region    Getter
	
	// #define f_List_get(list, i) list.get[i]

	#define f_List_ofStrings_getString(list, i) \
		&list.buffer.start[ list.indicies.get[i] ]

	#define _f_List_getLast(list, getter) \
		list.getter[ list.count - 1 ]

	#define f_List_getLast(list) _f_List_getLast(list, get)
	#define f_List_ofString_getLast(list) f_List_ofStrings_getString(list, list.indicies.count - 1)

#pragma endregion

#pragma region    Default lists types
// 	// typedef f_LIST_ADD(f_List_default_u32, u32);
	typedef f_LIST_ADD(f_list_i32_t, i32);
	typedef f_LIST_ADD(f_list_u32_t, u32);
#pragma endregion


#pragma region    Prints



#pragma endregion


// ========================================
// Linked List
// ========================================

/**
 * A Linked List with specified type
 * Naming convention: f_ L(inked) L(ist) <type>
 */
#define _f_LLIST_ADD(name, type, accessName) \
	struct name { \
		struct { \
			type value; \
			u32 next; /* Index of next entry, -1 is null, -2 means this entry is deleted */ \
		}* accessName; \
		u32 head; \
		u32 tail; \
		u32 capacity; \
		u32 count; \
		u32 memCursor; /* For memory management purpose */ \
	} name

#define _f_LList_init(list, initial_capacity, getter) ONCE( \
		list.count 		= 0; \
		list.capacity 	= initial_capacity; \
		list.head  		= (u32) -1; \
		list.tail 		= (u32) -1; \
		list.memCursor 	= 0; \
		f_CALLOC( list.getter, list.capacity ); \
		assert_nonnull(list.getter); \
	)


// #pragma region    Getters

	
	
// #pragma endregion





