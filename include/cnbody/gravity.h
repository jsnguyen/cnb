#ifndef GRAVITY_H_
#define GRAVITY_H_

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "cnbody/body.h"

typedef struct{
    double pos[3];
    double vel[3];
} posvel;

void vecfgrav(double *vec, double m1, double m2, double *pa, double *pb);

posvel apply_velverl(body *b, body *bs, int nb, double td);
#endif
