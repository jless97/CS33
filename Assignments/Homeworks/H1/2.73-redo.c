//2.73

#include <stdio.h>
#include <limits.h>

int saturating_add (int x, int y)
{
    int sum = x + y;
    int shiftValue = ((sizeof(int) << 3) - 1);
    
    int isXNeg = x >> shiftValue;
    int isYNeg = y >> shiftValue;
    int randomValue;
    
    int isOverflow = __builtin_add_overflow (x, y, &randomValue);
    
    isOverflow = isOverflow >> shiftValue;
    int notOverflow = ~isOverflow;
    
    int posOverflow = ~isXNeg & ~isYNeg & isOverflow;
    int negOverflow = isXNeg & isYNeg & isOverflow;
    
    posOverflow = posOverflow >> shiftValue;
    negOverflow = negOverflow >> shiftValue;
    
    int overflowResult = ((posOverflow & INT_MAX) | (negOverflow & INT_MIN) | (notOverflow & sum));
    
    return overflowResult;
}
