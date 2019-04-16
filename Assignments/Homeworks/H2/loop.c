//3.60
//loop.c

long loop(long x, long n)
{
    long result = 0;
    long mask;
    for(mask = 1; mask != 0; mask = mask << n)
    {
        result |= (x & mask);
    }
    return result;
}

/*3.60 Answers A-F
    A. x is in %rdi, and later %r8 also holds x, n is in %esi, and later %ecx also holds n, mask is stored in %rdx, and result is stored in %rax
    B. result = 0, and mask = 1
    C. mask != 0
    D. It is left shifted by n after each iteration of the loop
    E. It is Or'd with the And of x and mask (i.e. result |= (x & mask))
    F. See code above

*/
