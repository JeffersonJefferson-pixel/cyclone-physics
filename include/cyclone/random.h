#ifndef CYCLONE_RANDOM_H
#define CYCLONE_RANDOM_H

#include "core.h"

namespace cyclone
{
    class Random
    {
    public:
        Random();

        void Random::seed(unsigned s);
        
        unsigned Random::rotl(unsigned n, unsigned r);

        unsigned Random::rotr(unsigned n, unsigned r);

        unsigned Random::randomBits();

        real randomReal();

        real randomReal(real min, real max);

        unsigned randomInt(unsigned max);

        Vector3 randomVector(const Vector3 &min, const Vector3 &max);

    private:
        int p1, p2;
        unsigned buffer[17];
    };
};

#endif