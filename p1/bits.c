/* 
 * CS:APP Data Lab 
 * 
 * Jason Less/ 404640158
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
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
    //Because shifts are done arithmetically, it needs to make sure to properly shift the byte pattern
    //to take into account a negative number (i.e. msb is 1)
    x = (x >> 16) | x;
    x = (x >> 8) | x;
    x = (x >> 4) | x;
    x = (x >> 2) | x;
    x = (x >> 1) | x;
    
    //If it is a negative number, then every bit must be converted to a 1, and then not of that to produce 0
    return ~x & 1;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    //First mask is used to count the number of bits in each byte separately
    //This is done by looking at the 0 and 4 bits of each of the four bytes
    //and then shifting to the right three times to look at all bits
    int mask1 = 0x11 | (0x11 << 8) | (0x11 << 16) | (0x11 << 24);
    
    //Second mask is used to carry the proper number of one bits over to right-most bytes (zero and one byte)
    int mask2 = 0xF | (0xF << 8);
    
    
    //Using the first mask, and using three right shifts (doesn't matter if logical or arithmetic), all bits of each byte
    //can be examined
    x = (x & mask1) + ((x >> 1) & mask1) + ((x >> 2) & mask1) + ((x >> 3) & mask1);
    
    //Instead of looking at all four bytes, this will carry the amount of one bits to the right-most bytes
    x = x + (x >> 16);
    
    //The second mask helps to move over the one bits to the bits 0-3 and 8-11 (which will be used to align the rows
    //properly for the final addition
    x = (x & mask2) + ((x >> 4) & mask2);
    x = x + (x >> 8);
    
    //0x3F is the correct and because, the only positions where a 1 bit can be possible is in bit positions 0-15
    //This is because the largest possible return value is 32, which is 0010 0000 in binary
    return x & 0x3F;
}
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
    //Taking not x and not y and then anding them will in effect produce the opposite of x or y
    //Taking a not again will produce the x or y result
    return ~(~x & ~y);
}
/*
 * bitRepeat - repeat x's low-order n bits until word is full.
 *   Can assume that 1 <= n <= 32.
 *   Examples: bitRepeat(1, 1) = -1
 *             bitRepeat(7, 4) = 0x77777777
 *             bitRepeat(0x13f, 8) = 0x3f3f3f3f
 *             bitRepeat(0xfffe02, 9) = 0x10080402
 *             bitRepeat(-559038737, 31) = -559038737
 *             bitRepeat(-559038737, 32) = -559038737
 *   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
 *             (This is more general than the usual integer coding rules.)
 *   Max ops: 40
 *   Rating: 4
 */
int bitRepeat(int x, int n) {
    
    //I wasn't able to figure this one out :(
  return 2;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
    //Check to see if x will still represent the same value after truncating the full byte representation
    //By shifting by 32 - n, it can check to see if the value is the same
    int shiftValue = 32 + (~n+1);
    int shiftXLeft = x << shiftValue;
    
    //Shifting to the right will sign extend the bits back to the original position
    int shiftXRight = shiftXLeft >> shiftValue;
    
    int canFitsBits = x ^ shiftXRight;
    return !canFitsBits;
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
    //Goal is to extract full bytes, so it wants multiples of eight bits
    //The statement below in effect is n * 2^3
    int shiftMultipleOfEight = n << 3;
    
    //After shifting the proper amount, mask the 0 byte (the byte to extract), zeroing the remaining bits
    return (x >> shiftMultipleOfEight) & 0xFF;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    //Check the most signficant bit (msb) or the sign bit of x and y
    //To see whether either number is positive (msb = 0) or negative (msb = 1)
    int checkSignBitX = (x >> 31) & 1;
    int checkSignBitY = (y >> 31) & 1;
    
    //Check if x and y are the same number
    //If they are the same number, then the exclusive-or returns 0
    //So not the result because it should return 1
    int checkEquality = !(x ^ y);
    
    //Check to see if x is a negative number and y is a postive number
    //This would show right away if x is less than y
    int checkXNegYPos = (checkSignBitX ^ checkSignBitY) & checkSignBitX;
    
    //Check the difference of x - y to see if the result is a negative number
    //Will be used in next checks to test the msb
    int checkDifference = x + ~y + 1;
    
    //If the msb is a 1, then x is less than y
    //If the msb is a 0, then x is greater than y
    //Must check for overflow (i.e. if both x and y are the same sign, but the result is a different sign)
    int isLessThan = (checkDifference >> 31) & 1;
    int checkOverflow = !(checkSignBitX ^ checkSignBitY);
    int isLessThanNoOverflow = isLessThan & checkOverflow;
    
    return checkEquality | checkXNegYPos | isLessThanNoOverflow;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
    //Shift the value 1 over to the most significant bit (msb) position to check it with x
    int checkSignBit = 1 << 31;
    
    //Check the msb of x to see if it is a positive or negative number
    int checkXNeg = x & checkSignBit;
    
    //Check to see if x is zero
    int checkXZero = !x;
    
    return !(checkXNeg | checkXZero);
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
    //Do a logical shift on x as the mask will correct the sign extension later
    int logicalShiftX = x >> n;
    
    //Create a mask to correct the arithmetic right shift
    int initialMask = (((1 << 31) >> n) << 1);
    
    //Take the not of the initial mask to correct the arithmetic right shift
    int finalMask = ~initialMask;
    
    return logicalShiftX & finalMask;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    //Smallest two's complement integer [10...0]
    return 1 << 31;
}
