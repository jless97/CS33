//2.73

#include <stdio.h>
#include <limits.h>

int saturating_add (int x, int y)
{
    int sum = x + y;
    int shiftValue = ((sizeof(int) << 3) - 1);
    
    int isXNeg = x >> shiftValue;
    int isYNeg = y >> shiftValue;
    int isSumNeg = sum >> shiftValue;
    
    int sumPosOverflow = ~isXNeg & ~isYNeg & isSumNeg;
    int sumNegOverflow = isXNeg & isYNeg & ~isSumNeg;
    int sumNotOverflow = ~(sumPosOverflow | sumNegOverflow);
    
    int overflowResult = ((sumPosOverflow & INT_MAX) | (sumNegOverflow & INT_MIN) | (sumNotOverflow & sum));
    
    return overflowResult;
}

