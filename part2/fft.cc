#include <iostream>
#include <cmath>
#include "fft.h"

void fft(Complex *input, int length)
{
    int rev, logLength;
    logLength = static_cast<int>(std::log2(length));

    // bit reverse every element and swap
    for (unsigned int i = 0; i < length; ++i)
    {
        rev = reverse_bit(i, logLength);
        if (rev > i)
            std::swap(input[rev], input[i]);
    }

    // start of fft calculation
    // s: fft tree level, m: butterfly size,
    // k: ind of butterfly, j: each element of butterfly
    int s, m = 1, k, j;
    Complex i(0.0f, 1.0f);

    // w: 1, wm: roots of unity
    for (s = 1; s < logLength; ++s)
    {
        m <<= s;
        
        Complex wm(std::cos(2 * PI / m), -1 * std::sin(2 * PI / m));


        Complex w(1.0f, 0.0f);
        for (j = 0; j < (m >> 1); ++j)
        {
            for (k = j; k < length; k += m) 
            {
                Complex t = w * input[k + (m >> 1)];
                Complex u = input[k];
                input[k] = u + t;
                input[k + (m >> 1)] = u - t;
            }
            w = w * wm;
        }

        // for (k = 0; k < length; k += m)
        // {
        //     Complex w(1.0f, 0.0f);
        //     for (j = 0; j < (m >> 1); ++j)
        //     {
        //         Complex t = w * input[k + j + (m /2)];
        //         Complex u = input[k + j];
        //         input[k + j] = u + t;
        //         input[k + j + (m /2)] = u - t;
        //         w = w * wm;
        //     }
        // }
    }
}

unsigned int reverse_bit(unsigned int in, int logLength)
{
    unsigned int rev = 0;
    for (int i = 0; i < logLength; ++i)
    {
        rev <<= 1;
        rev |= in & 1;
        in >>= 1;
    }
    return rev;
}