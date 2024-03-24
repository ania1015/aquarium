#ifndef REGULATOR_H
#define REGULATOR_H



void przeliczNastawy(float Ti, float  h, float kp, float *k1, float* k2);
float RegulatorPIsprzet(float y, float  w, float k1, float k2);

#endif
