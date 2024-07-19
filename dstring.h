/*
	Name:  DString
	Version: 0.1 Alpha
	Date: 19/07/2024
	Author: Diego Moreira
	Licence: MIT
*/

/* Safe alternative to the C standard library "string.h" */

#ifndef DSTRING_H
#define DSTRING_H
#include <stdio.h>
#include "dtypes.h"

// Calculates the size of an array regardless of type
#define size(arr) (sizeof(arr) / sizeof(arr[0]))

// Flags return 
static const i32
	// string_length
	STRING_LENGTH_NULL_OR_VOID = 0,
	// string_length_total
	STRING_LENGTH_TOTAL_NULL = 0,
	
	// string_compare
	STRING_COMPARE_ALL_NULL = 0,
	STRING_COMPARE_ALL_VOID = 0,
	
	STRING_COMPARE_STR1_NULL = -1,
	STRING_COMPARE_STR2_NULL = -2,
	STRING_COMPARE_STR1_VOID = -3,
	STRING_COMPARE_STR2_VOID = -4,
	STRING_COMPARE_STR1_BIGGER = -5,
	STRING_COMPARE_STR2_BIGGER = -6,
	
	// string_interval_compare
	STRING_INTERVAL_COMPARE_ALL_NULL = -1,
	STRING_INTERVAL_COMPARE_STR1_NULL = -2,
	STRING_INTERVAL_COMPARE_STR2_NULL = -3,
	STRING_INTERVAL_COMPARE_ALL_VOID = -4,	
	STRING_INTERVAL_COMPARE_BEGIN_INVALID = -5,
	
	// string_fill
	STRING_FILL_STR_NULL = 1,
	
	// string_copy
	STRING_COPY_ALL_NULL = 1,
	STRING_COPY_STR2_BIGGER = 2,
	
	// string_reatribution
	STRING_REATRIBUTION_ALL_NULL = 1,
	STRING_REATRIBUTION_STR2_BIGGER = 2;

// Prototypes
static u64 string_length(u8 *string);
static u64 string_total_length(u8 *string, size_t size_bytes);
static i64 string_compare(u8 *string1, u8 *string2);
static i64 string_interval_compare(u8 *string1, u8 *string2, u64 begin, u64 end);
static u32 string_fill(u8 *string, u8 character, size_t size_arr);
static u32 string_copy(u8 *string1, size_t size_arr, u8 *string2, i1 copy);
static u32 string_reatribution(u8 *string1, size_t size_arr, u8 *string2, i1 copy);

// Implementation of the standard "strlen" function.
// Calculate the length of a string until finding the null character.
static u64 string_length(u8 *string) {
	if (string == NULL || string[0] == 0) {
		return STRING_LENGTH_NULL_OR_VOID;
	}
	
	u64 length = 0;
	while (1) {
		if (string[length] == 0) {
			break;
		} else {
			++length;
		}
	}
	return length;
}

// Implementation of the standard "strlen" function with other logic.
// Calculate how many non-null bytes are in a string.
static u64 string_total_length(u8 *string, size_t size_arr) {
	if (string == NULL) {
		return STRING_LENGTH_TOTAL_NULL;
	}
	
	u64 length = 0;
	size_t x = 0;
	
	while (x < size_arr) {
		if (string[x] != 0) {
			++length;
		}
		++x;
	}
	return length;
}

// Implementation of the standard "strcmp" function.
// Compare two strings check for errors and return how many bytes are different.
static i64 string_compare(u8 *string1, u8 *string2) {
	
	if (string1 == NULL && string2 == NULL) {
		return STRING_COMPARE_ALL_NULL;
		
	} else if (string1 == NULL) {
		return STRING_COMPARE_STR1_NULL;
		
	} else if (string2 == NULL) {
		return STRING_COMPARE_STR2_NULL;
	}
	
	u64 x = 0, differences = 0;
	u64 len1 = string_length(string1);
	u64 len2 = string_length(string2);
	
	if (len1 == 0 && len2 == 0) {
		return STRING_COMPARE_ALL_VOID;
		
	} else if (len1 == 0) {
		return STRING_COMPARE_STR1_VOID;
		
	} else if (len2 == 0) {
		return STRING_COMPARE_STR2_VOID;
		
	} else if (len1 > len2) {
		return STRING_COMPARE_STR1_BIGGER;
		
	} else if (len2 > len1) {
		return STRING_COMPARE_STR2_BIGGER;
		
	}
	
	while (!(x == len1)) {
		if (string1[x] != string2[x]) {
			++differences;
		}
		++x;
	}
	return differences;
}

// Implementation of the standard "strncmp" function.
static i64 string_interval_compare(u8 *string1, u8 *string2, u64 begin, u64 end) {
	
	if (string1 == NULL && string2 == NULL) {
		return STRING_INTERVAL_COMPARE_ALL_NULL;
		
	} else if (string1 == NULL) {
		return STRING_INTERVAL_COMPARE_STR1_NULL;
		
	} else if (string2 == NULL) {
		return STRING_INTERVAL_COMPARE_STR2_NULL;
	}
	
	u64 len1 = string_length(string1);
	u64 len2 = string_length(string2);
	
	if (len1 == 0 && len2 == 0) {
		return STRING_INTERVAL_COMPARE_ALL_VOID;
		
	} else if (begin >= len1 || begin >= len2) {
        return STRING_INTERVAL_COMPARE_BEGIN_INVALID;
        
	} else if (end > len1) {
		end = len1;
	} else if (end > len2) {
		end = len2;
	}
	
	u64 x = begin, differences = 0;
	
	while (x < end) {
        if (string1[x] != string2[x]) {
            ++differences;
        }
        ++x;
    }
	return differences;
}

// Function that fills a string with a specific byte. Useful for string initialization.
static u32 string_fill(u8 *string, u8 character, size_t size_arr) {
	if (string == NULL) {
		return STRING_FILL_STR_NULL;
	} else {
		for (size_t i = 0; i < size_arr; i++) {
			string[i] = character;
		}
	}
	return 0;
}

// Implementation of the standard "strcpy" function.
static u32 string_copy(u8 *string1, size_t size_arr, u8 *string2, i1 copy) {
	if (string1 == NULL || string2 == NULL) {
		return STRING_COPY_ALL_NULL;
	}
	u64 len = string_length(string2);
	if (len > size_arr - 1) {
		if (!copy) {
			return STRING_COPY_STR2_BIGGER;
		}
		len = size_arr -1;
	}
	
	for (u64 i = 0; i < len; i++) {
		string1[i] = string2[i];
	}
	string1[len] = 0;
	
	return 0;
}

// Implementation of the standard "strcpy" function with other logic.
// Function that resets the first string before copying.
static u32 string_reatribution(u8 *string1, size_t size_arr, u8 *string2, i1 copy) {
	if (string1 == NULL || string2 == NULL) {
		return STRING_REATRIBUTION_ALL_NULL;
	}
	u64 len = string_length(string2);
	if (len > size_arr) {
		if (!copy) {
			return STRING_REATRIBUTION_STR2_BIGGER;
		}
		len = size_arr -1;
	}
	
	string_fill(string1, 0, size_arr);
	
	for (u64 i = 0; i < len; i++) {
		string1[i] = string2[i];
	}
	string1[size_arr -1] = 0;
	
	return 0;
}

struct {
	u64 (*len)(u8 *);
	u64 (*tlen)(u8 *, size_t);
	i64 (*cmp)(u8 *, u8 *);
	i64 (*icmp)(u8 *, u8 *, u64, u64);
	u32 (*fill)(u8 *, u8, size_t);
	u32 (*copy)(u8 *, size_t, u8 *, i1);
	u32 (*set)(u8 *, size_t, u8 *, i1);
} str;

// Initialization of functions
void init_dstring_h() {
	str.len = string_length;
	str.tlen = string_total_length;
	str.cmp = string_compare;
	str.icmp = string_interval_compare;
	str.fill = string_fill;
	str.copy = string_copy;
	str.set = string_reatribution;	
}

#endif