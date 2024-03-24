#include "regulator.h"


void przeliczNastawy(float Ti, float  h, float kp, float *k1, float* k2)
{
        float x = h /(2 *  Ti);
        *k1 = kp * (x + 1);
        *k2 = kp * (x - 1);
}
float RegulatorPIsprzet(float y, float  w, float k1, float k2)
{
    static float u_prev = 0;
    static float  e_prev = 0;
    float e = w - y;
    float u = 0;

    u = u_prev + k1 * e + k2 * e_prev;
    if(u > 1)
        u = 1;
    else if (u < 0)
        u = 0;
     u_prev = u;
     e_prev = e;

    return u;
}

