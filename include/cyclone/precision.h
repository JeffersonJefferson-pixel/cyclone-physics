#ifndef CYCLONE_PRECISION_H
#define CYCLONE_PRECISION_H

#include <float.h>

namespace cyclone 
{
#define SINGLE_PRECISION
    typedef float real;
    #define REAL_MAX FLT_MAX
    #define real_sqrt sqrtf
    #define real_pow powf
    #define real_abs fabsf
    #define real_sin sinf
    #define real_cos cosf
    #define real_exp expf
}

#endif