#include "fft.h"
#include <cstring>

void fft(Complex* input, Complex* output, int length)
{
    std::memcpy(output, input, sizeof(output[0]) * length);
}

void bit_reverse()
{

}