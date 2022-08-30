#if 0
INTEGER CODING RULES:

	Complete the body of each function with one
	or more lines of C code that implements the function. Your code
	must consist of a sequence of variable declarations, followed by
	a sequence of assignment statements, followed by a return statement.

	The general style is as follows:

	int funct(...) {
		/* brief description of how your implementation works */
		int var1 = expr1;
		...
		int varM = exprM;

		varJ = exprJ;
		...
		varN = exprN;

		return exprR;
	}

	Each "expr" is an expression using ONLY the following:
	1. Integer constants 0 through 255 (0xFF), inclusive. You are
	   not allowed to use big constants such as 0xFFFFFFFF.
	2. Function arguments and local variables (no global variables).
	3. Unary integer operations ! ~
	4. Binary integer operations & ^ | + << >>

	Some of the problems restrict the set of allowed operators even further.
	Each "expr" may consist of multiple operators. You are not restricted to
	one operator per line.

	You are expressly forbidden to:
	1. Use any control constructs such as if, do, while, for, switch, etc.
	2. Define or use any macros.
	3. Define any additional functions in this file.
	4. Call any functions.
	5. Use any other operations, such as &&, ||, -, or ?:
	6. Use any form of casting.
	7. Use any data type other than int.  This implies that you
	   cannot use arrays, structs, or unions.


	You may assume that your machine:
	1. Uses 2s complement, 32-bit representations of integers.
	2. Performs right shifts arithmetically.
	3. Has unpredictable behavior when shifting an integer by more
	   than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
	/*
	 * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
	 */
	int pow2plus1(int x) {
		/* exploit ability of shifts to compute powers of 2 */
		return (1 << x) + 1;
	}

	/*
	 * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
	 */
	int pow2plus4(int x) {
		/* exploit ability of shifts to compute powers of 2 */
		int result = (1 << x);
		result += 4;
		return result;
	}
#endif
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 9.0.0.  Version 9.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, fourth edition, plus
   Amd. 1  and Amd. 2 and 273 characters from forthcoming  10646, fifth edition.
   (Amd. 2 was published 2016-05-01,
   see https://www.iso.org/obp/ui/#iso:std:iso-iec:10646:ed-4:v1:amd:2:v1:en) */
/* We do not support C11 <threads.h>.  */


/*
 * bit_and - Compute x&y using only ~ and |
 *   Examples: bit_and(6, 5) = 4
 *             bit_and(3, 12) = 0
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bit_and(int x, int y) {
	// DeMorgan's Law moment
	return ~(~x | ~y);
}


/*
 * negate - Return -x
 *   Examples: negate(1) = -1
 *             negate(0) = 0
 *             negate(-33) = 33
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	// Slides moment
	return ~x + 1;
}


/*
 * is_equal - Return 1 if x == y, else return 0
 *   Examples: is_equal(5, 5) = 1
 *             is_equal(4, 5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int is_equal(int x, int y) {
	// x ^ y returns all 0's if x == y, and some nonzero number otherwise
	// We can convert that to 1 using bang
	return !(x ^ y);
}


/*
 * div_pwr_2 - Compute x/(2^n), for 0 <= n <= 30
 *   Round toward zero
 *   Examples: div_pwr_2(15, 1) = 7
 *             div_pwr_2(-33, 4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int div_pwr_2(int x, int n) {
	// First we extract the sign
	// Leads 0 if positive, 1 if negative
	int sign = x & (1 << 31);

	int neg_one = ~1 + 1;
	int pos_div = x >> n;
	int neg_div =  (x + (1 << n) + neg_one) >> n;

	int mask = sign >> 31;
	return (pos_div & ~mask) + (neg_div & mask);

}


/*
 * leastBitPos - Return a mask that marks the position of the
 *   least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 4
 */
int leastBitPos(int x) {
	// When you negate a number, you flip all the bits
	// 0010
	// 1101
	// If you add 1 to the negation, you end up with the actual negation
	// 1110
	// You can actually & this with the original number to get the last bit (it's the 1 bit where the carrying stops)

	return x & (~x + 1);
}


/*
 * conditional - Compute the result of x ? y : z
 *   Examples: conditional(2, 4, 5) = 4
 *             conditional(0, 1, 2) = 2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	// Mask converts x to either -1 or 0
	int mask = ~(!x) + 1;
	// then we can mask appropriately depending on case
	return (~mask & y) + (mask & z);

	// TODO: Add test case for overflow between adding y and -z
}


/*
 * add_ok - Return 0 if x+y will overflow, 1 otherwise
 *   Examples: add_ok(0x80000000, 0x80000000) = 0
 *             add_ok(0x80000000, 0x70000000) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int add_ok(int x, int y) {
	// Leads with 1 if signs are same, 0 otherwise
	int same_sign = ~(x ^ y);

	int result = x + y;
	// Leads with 0 if the signs are same, 1 otherwise
	int result_sign = (x ^ result);

	return !((same_sign & result_sign) >> 31);
}


/*
 * abs_val - Return the absolute value of x
 *   Examples: abs_val(-1) = 1
 *             abs_val(33) = 33
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 5
 */
int abs_val(int x) {
	int sign = x >> 31;
	int neg = ~x + 1;
	int signed_neg = sign & neg;
	return x + signed_neg + signed_neg;
}


/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 5
 */
int bang(int x) {
	// Leverages the property that 0 is the only number whose negation and itself has leading bit 0
	// This means 0 or'd with -0 will have leading bit 0... that's important because we can shift it!

	return ((x | (~x + 1)) >> 31) + 1;

}

// NOTE: Issues with compilation -- make sure GCC is installed for multi-library (must support 32 bit architechure)