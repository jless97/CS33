//2.64

int any_odd_one(unsigned x)
{
    return ((x & 0xAAAAAAAA) != 0);
}
