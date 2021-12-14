#include <stdio.h>

void randomfill(__uint64_t *out, size_t n, __uint64_t x, 
                __uint64_t a, __uint64_t c)
{
    for ( ; n; n--)
    {
        x = x * a + c; 
        *out++ = x;
    }
};

// Var 1: loop fission (distribution): split the loop, create 
// addition array to store the value of x during each iteration. 
// 
// Drawbacks: a new loop-independent dependency of arr[i] from x 
// is introduced and more memory is required; also, it probably has 
// a worse locality (?), but the 2-nd loop can be parallelized now
void randomfill_distr(__uint64_t *out, size_t n, __uint64_t x, 
                      __uint64_t a, __uint64_t c)
{
    __uint64_t arr[n];

    for (size_t i = 0; i < n; i++)
    {
        x *= a;
        x += c;     // dep. on x (35:9), loop-indep.
        arr[i] = x; // dep. on x (36:9), loop-indep.
    }

    for (size_t j = 0; j < n; j++, out++)
    {
        out[j] = arr[j];
    }
};



int main(int argc, char const *argv[])
{
    __uint64_t x = 1;
    __uint64_t *out = &x;
    randomfill(out, 3, 1, 3, 2);

    __uint64_t y = 1;
    __uint64_t *out1 = &y;
    randomfill_distr(out1, 3, 1, 3, 2);

    return 0;
}
