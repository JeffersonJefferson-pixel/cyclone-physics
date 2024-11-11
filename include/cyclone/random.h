#ifndef CYCLONE_RANDOM_H
#define CYCLONE_RANDOM_H

#include "core.h"

namespace cyclone
{
    class Random
    {
    public:
        Random();

        void seed(unsigned s);
        
        unsigned rotl(unsigned n, unsigned r);

        unsigned rotr(unsigned n, unsigned r);

        unsigned randomBits();

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