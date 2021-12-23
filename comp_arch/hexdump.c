// @ Task:
// Implement a simple hex-dump function
// void hexdump(char *restrict out, unsigned char *restrict in, size_t n);
// For n bytes of input data in, place 4n bytes of hexadecimal representation into out. For each input symbol, emit \xNM, where NM is its ASCII code.
// 
// Example:
// hexdump(out, "Hello World", 12) should place into the output array the 
// string:
// "\x48\x65\x6c\x6c\x6f\x20\x57\x6f\x72\x6c\x64\x00"
#include <stdio.h>
#include <string.h>

void hexdump(char *restrict out, unsigned char *restrict in, size_t n);

int main(int argc, char const *argv[])
{
    char a[40] = { '\0' };  

    hexdump(a, "Hello World", 14);

    printf("hex out: %s\n", a);

    return 0;
}

// WARNING: it assumes that out has enough space and therefore doesn't check
// for buffer overflow
void hexdump(char *restrict out, unsigned char *restrict in, size_t n)
{
    char hex_arr[n][4];
    int  a = 0;
    int  l = 0;

    for (size_t i = 0; i < n; i++)
    {
        // Check that n doesn't exceed length of 'in'
        if (in[i] == '\0') 
        {
            out[l++] = '\\';
            out[l++] = 'x';
            out[l++] = '0';
            return;
        }

        int quotient = (in[i] >= '0' && in[i] <= '9') ? in[i] - '0' : in[i];

        if (quotient == 0) 
        {
            hex_arr[i][++a] = 0 + 48; 
        }

        while (quotient != 0)
        {
            int remainder = quotient % 16;

            if (remainder < 10) remainder = remainder + 48;
            else                remainder = remainder + 55;

            hex_arr[i][++a] = remainder;
            quotient        = quotient / 16;
        } 

        out[l++] = '\\';
        out[l++] = 'x';
        for (int j = a; j > 0; j--)
        {
            out[l++] = hex_arr[i][j];
        }

        a = 0;
    }

    return; 
}