extern double u2f (unsigned long);

double fpwr2 (long x)
{
    unsigned long exp, frac;
    unsigned long u;
    
    if (x < -1074) {
        /* Too small. Return 0.0 */
        exp = 0;
        frac = 0;
    } else if (x < -1022) {
        /* Denormalized result */
        exp = 0;
        frac = 1 << (x + 1074);
    } else if (x < 1024) {
        /* Normalized result */
        exp = x + 1023;
        frac = 0;
    } else {
        /* Too big. Return +oo */
        exp = 2047;
        frac = 0;
    }
    
    /* Pack exp and frac into 64 bits */
    u = exp << 52 | frac;
    /* Return as float */
    return u2f(u);
}
