/* 
 * CS:APP Data Lab 
 * 
 * <Sujita Shah (Shahx220@umn.edu)
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
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

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2014 Free Software Foundation, Inc.
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
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */

 /*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
// If x is maximum, x + 1 = ~x. So -(x+1)+x+1 should be 0, 
//x+1 also shouldn't be 0.
int isTmax(int x) {
	int add = x + 1;
	int c = add + x + 1;
	return (!!(x+1))&(!c);
}
/* 
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
 //Using demorgan's law, ~(x|y) = ~x & ~y
int bitNor(int x, int y) {
  x=~x;
  y=~y;
  return (x&y);
}
/* 
 * upperBits - pads n upper bits with 1's
 *  You may assume 0 <= n <= 32
 *  Example: upperBits(4) = 0xF0000000
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 1
 */
 //if n ==0, !!n will be 0. otherwise !!n = 1.
 //Then left shift 31 bits and then right shift n-1 bits
int upperBits(int n) {
	int x = ( !!n ) << 31;
	x = x >> (n + ~1 + 1) ;
	return  x;
	//( ~0 & ( !n + ( ~1 + 1 ) ) ) << ( 32 + ( ~n + 1 ) )
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
 //right shift x 31 bits is used for see the sign of the number
 //and then right shift x, to see whether there is still number
 //in bit higher than 16 bits.
int fitsShort(int x) {
  int mk=x>>31;
  x=x>>15;
  x=mk^x;
  return !x;
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
 //Detailed comment inside this function
int divpwr2(int x, int n) {
	int mk = ~0;
	mk = mk << n;
	mk = ~mk;					//mk is 000001111..(n ones) after this statement.
	int round = x & mk;			//*check whether the lower bits is 0 or not.
	int sign = x >> 31;				//*sign = 0 if x >= 0 otherwise, all ones.
	x = x >> n;						// Do the division
	x = x + (!!(round)&!!(sign));	// If x is negative and the round is not 0, x should plus one
	
    return x ;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
 //creat the mask 0xAAAAAAAA first, and then use mask & x see wether 
 //all the odd bits in the number is 1.
int allOddBits(int x) {
	int a = 0xAA;
	a = ( a << 8 ) | a;
	a = ( a << 16 ) | a;
	int v = a & x;
  return !(v + ( ~ a + 1 )) ;
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
 //simply do left shift 31 bits and right shift 31 bits
int copyLSB(int x) {
	x=x<<31;
	x=x>>31;
    return x;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
 //if x is positive or 0, right shift 31 bits x will be 0.
 //otherwise all 1. on the last line, !!x deal with if x is 0. 
int isPositive(int x) {
	int n = x >> 31;
    return !n & !!x ;
}
/* 
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
 //create a mask, use the mask to
 //copy the first n bits of x, shift it to the right.
 //another mask copy the last 31-n bit,
 //combine two mask get the right answer
int rotateLeft(int x, int n) {
	int mk = !!n;
	mk = mk << 31;
	int a10=mk;
	int n_minus_1 = n + ( ~ 1 + 1 );
	mk= mk >> n_minus_1;
	mk = mk & x;
	mk = mk >> 1;
	int a10_flip = ~a10;
	mk = a10_flip & mk;
	int neg_n = ~n + 1;
	mk = mk >> ( 31 + neg_n );
	int mk2 = a10_flip >> n_minus_1;
	mk2 = x & mk2;
	x= mk2 << n;
	x = x | mk;
    return x;
}
/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
 //create a mask contain the right amount length of 1111
 //shift it to left to the right position
 //For the case which has to shift to left for 32 bits
 //simply shift 31 bits first and then shift 1 more bit
int bitMask(int highbit, int lowbit) {
	int len = highbit + ~lowbit + 1;
	int len_check = len >> 31;
	int mask = ~0;
	int neg_len_check = ~(len_check);
	mask = mask << (len & neg_len_check);
	mask = mask << (1 & neg_len_check);
	mask = ~mask;
	mask = mask << lowbit;
    return mask;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
//Divide the total x in half and use the first half | with the second half
//Do this step until x's lenth is 1
//if no 1 in x, x should be 0, otherwise 1.
int bang(int x) {
	int y=x>>16;
	y=y|x;
	x=y;
	y=y>>8;
	y=y|x;
	x=y;
	y=y>>4;
	y=y|x;
	x=y;
	y=y>>2;
	y=y|x;
	x=y;
	y=y>>1;
	y=y|x;
  return (~y&1);
}
/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int trueThreeFourths(int x)
{
	int mk = 3;											//create a mask with the value 3 (10 base), 011(2 base)
	mk = mk & x;
	int sign = x >> 31;									//*sign = 0 if x >= 0 otherwise, all ones.
	int x_origin = x;
	x = x >> 2;											// division arithmetic
	int result = x_origin + (~x + 1);
	int round_truth = !!mk;
	result = result + ~((!sign) & (round_truth)) + 1; 	// deal with round off if x is positive
														//int neg_round=(!!sign) & (round_truth);
														//do nothing if x is negative
    return result;
}
