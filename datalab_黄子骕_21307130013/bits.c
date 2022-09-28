/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 黄子骕  21307130013
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
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
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* We do not support C11 <threads.h>.  */
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  //用(x & y)去找出x,y中那些都为1的位，用(~x & ~y)找出x，y中那些都为0的位，由于最后结果我们是要这些位为0，
  //而在x，y中一个1一个0的位为1，因此~(x & y) & ~(~x & ~y)即可有此效果
  return ~(x & y) & ~(~x & ~y);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  //因为 1 的二进制表示为 000....1,所以我们令它左移31位就可得到 100...0，即为补码表示最小整数
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  //首先，补码表示的最大整数为 01111...1，即除了最高位为0，其他位均为1.我们可以用(~x ^ (x + 1)) 
  //来验证是否处最高位外均为1，因为只有均为1， 在+1后不断进位，(~x ^ (x + 1))的值才能为0.
  //同时，由于-1（11111...1）除最高位外也都为1，因此需要额外排除它的干扰，只有当x不为-1时，
  //!(~x)的值为0，因此!(((~x ^ (x + 1))) | !(~x))即可保证x为 0111...1时候返回1，
  //其他时候返回0
  return !(((~x ^ (x + 1))) | !(~x));
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  //前两行代码可以构建一个二进制表示为 101010...10的数
  //进一步利用这个数与x进行&运算，提取出x的奇数位
  //最后将上一步结果与 101010....10作^运算来比较x奇数位是否均为1
  //并对结果做！运算，此时x若奇数位均为1，结果返回1
  int bits_low16_test = 0xAA + (0xAA << 8);
  int bits_all32_test = (bits_low16_test << 16) + bits_low16_test;
  return !((bits_all32_test & x) ^ bits_all32_test);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  //使用公式: ~x + 1 = -x
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  //首先使用is_less和is_larger来保存x与上下限的差值
  //之后仅需判断差值的符号位是否均为0即可（由于在此题的条件中,若出现溢出时，is_less和is_larger的
  //符号位不可能同时为0，因此可以这样判断）
  int is_less, is_larger;
  is_less = 0x39 + (~x + 1);
  is_larger = x + (~0x30 + 1);
  return !((is_less >> 31) | (is_larger >> 31));
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  //当x为0时，test为000...0，当x不为0时，test为111...1
  //此时，test与~test之间必定会有一个为000...0，为000...0的那一侧便不输出
  //因此用(test & y) | (~test & z)， 利用test是否为000...0来做判断输出y还是z
  int test, change;
  change = !!x;
  test = ~change + 1;
  return (test & y) | (~test & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  //当x，y符号位相同，且x <= y时， y-x 的符号位一定为0
  //当x，y符号位不同时候，仅需确认x的符号位为1即可
  //最后一行分别表示上述两种情况，只要有一种情况成立（即&的一侧为0000..0）则返回1
  int difference, neg_x, sign_x, sign_y, is_same;
  neg_x = ~x + 1;
  difference = y + neg_x;
  sign_x = x >> 31;
  sign_y = y >> 31;
  is_same = sign_x ^ sign_y;
  return !((is_same | (difference >> 31)) & ~(is_same & sign_x));
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  //在这里我考虑x 与 -x符号位相同时，x为0或INT_MIN
  //因此只需验证x与-x的符号位是否相同，并排除INT_MIN干扰即可（即保证符号位为0而不为1）
  //当同号且x不为INT_MIN时，((sign_x ^ sign_neg_x) | sign_x)结果为000...0，其他时候为111...1
  int neg_x, sign_x, sign_neg_x;
  neg_x = ~x + 1;
  sign_x = x >> 31;
  sign_neg_x = neg_x >> 31;
  return ((sign_x ^ sign_neg_x) | sign_x) + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  //首先将正负数都统一成统一情况（若负数则取反），即找最高位的1并+1（符号位）得到表示x的最小位数
  //先检查最高的16位，若含1，则表明要表示x需要16位以上，因此使test_16保存为16，同时将x右移16位以此
  //使得最高的16位都变为0，进而可以无影响的研究剩余位；若不含1，则表明要表示x需要 小于等于16位，此
  //时test_16为0，同时在这情况下最高的16位同样为0，可以直接继续研究剩余位
  //重复上述步骤
  //将所有测试结果相加并+1（符号位）得到结果
  int sign, test_16, test_8, test_4, test_2, test_1, test_last;
  sign = x >> 31;
  x = (~sign & x) | (sign & ~x);//统一情况
  test_16 = !!(x >> 16) << 4;
  x = x >> test_16;
  test_8 = !!(x >> 8) << 3;
  x = x >> test_8;
  test_4 = !!(x >> 4) << 2;
  x = x >> test_4;
  test_2 = !!(x >> 2) << 1;
  x = x >> test_2;
  test_1 = !!(x >> 1);
  x = x >> test_1;
  test_last = x;//只剩一位无法再分
  return test_16 + test_8 + test_4 + test_2 + test_1 + test_last + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  //首先用sign，exp，frac分别保存符号位，阶码以及尾数
  //若exp为special状态，直接返回uf
  //若exp为denormalized状态，此时有几种可能性
  //1 - 尾数的最高位为0，此时其他不变将尾数左移1位即可
  //2 - 尾数的最高位为1，此时尾数左移1位同时exp+1（因为exp+1后变为normalized状态，M的整数位变为1）
  //3 - 尾数为0，则直接返回uf（0乘一切都0）
  //若exp为normalized状态，先令exp+1，若变为special状态则直接返回同符号的无穷
  //若仍为normalized状态则其他部分不变，返回exp部分+1后的结果
  unsigned sign, exp, frac, exp2, frac2;
  sign = uf >> 31;
  exp = uf << 1 >> 24;
  frac = uf << 9 >> 9;
  if(exp == 0xff){//special状态
    return uf;
  }
  if(exp == 0 && frac == 0){//为0
    return uf;
  }
  if(exp == 0){//denormalized状态
    frac2 = frac << 1;//此处对于思路中的可能性1与2，此操作均有效
    return (sign << 31) + frac2;
  }
  else{//normalized状态
    exp2 = exp + 1;
    if(exp2 == 0xff){//normalized状态变为了special状态
      return ((sign << 8) + exp2) << 23;
    }
    frac2 = frac;
  }
  return  ((((sign << 8)+ exp2) << 23) + frac2);
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf){
  //首先记录uf的符号位，阶码，尾数
  //若为denormalized状态，则直接返回0，其他情况则计算出E
  //若E>31,则超出int表示范围，返回0x80000000
  //若E<0，则直接返回0
  //若E>=0且E<=31，此时将尾数适当左移或右移，使得小数点在适当的位置（即只保存整数部分）
  //此时有几种情况
  //1 - uf为正，同时移动后未覆盖符号位，此时直接返回
  //2 - uf为正，移动后覆盖了符号位，此时E一定为31，此时一定超过int表示范围，返回0x80000000
  //3 - uf为负，移动后未覆盖符号位，此时返回相反数
  //4 - uf为负，移动后覆盖了符号位，此时E一定为31，此时当结果不为100...0时，超出负数表示最小值
  //返回0x8000000，若结果为100...0，同样返回0x80000000
  unsigned sign, exp, frac;
  int E,result;
  sign = uf >> 31;
  exp = uf << 1 >> 24;
  if(exp != 0){
    E = exp - 127;
  }else{
    return 0;
  }
  frac = uf << 9 >> 9;
  //根据E大小判断处理方法
  if(E > 31){
    return 0x80000000;
  }
  if(E < 0){
    return 0;
  }
  frac = frac | 0x00800000;//使得第24位为1，即模拟出M的整数位
  if(E > 23){
    result = frac << (E - 23);
  }else{
    result = frac >> (23 - E);
  }
  if(sign == 1 && E != 31){//思路中的情况3
    return ~result + 1;
  }else if(E == 31 && ((sign == 0) || (result << 1 != 0))){//思路中情况2，4
    return 0x80000000;
  }else{//思路中情况1以及情况4中结果为100...0的情况（100...0即0x80000000）
    return result;
  }
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  //将x取值范围划分为四个部分
  //1 - x>127时,超出表示范围，返回正无穷
  //2 - x<-149时，无法表示，返回0
  //3 - -126<=x<=127时，用normalized状态表示，frac为0，exp为x+Bias
  //4 - -149<=x<-126时，用denormalized状态表示，exp为0，frac根据x大小通过移位操作确定
  unsigned exp, frac, result;
  if(x > 127){
    return 0x7f800000;
  }
  if(x < -149){
    return 0;
  }
  if(x >= -126 && x <= 127){
    exp = x + 127;
    frac = 0;
  }
  if(x < -126 && x >= -149){
    exp = 0;
    frac = 1 << (23 - ((-126) - x));
  }
  result = (exp << 23) + frac;
  return result; 
}
