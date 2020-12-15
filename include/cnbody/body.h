#ifndef BODY_H_
#define BODY_H_

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct{
    int id;
    double mass;
    double diam;
    double *pos;
    double *vel;

    /* these point to data but don't actually malloc data */
    double *px,*py,*pz;
    double *vx,*vy,*vz;
    double angmom;
} body;


void body_init(body *b);
body* body_create();

void body_delete(body *b);
void body_destroy(body *b);

void body_set(body *b, int i, double m, double d, double p[3], double v[3], double a);
void body_set_id(body *b, int i);
void body_set_mass(body *b, double m);
void body_set_diam(body *b, double d);
void body_set_pos(body *b, double p[3]);
void body_set_pos_x(body *b, double p);
void body_set_pos_y(body *b, double p);
void body_set_pos_z(body *b, double p);
void body_set_vel(body *b, double v[3]);
void body_set_vel_x(body *b, double v);
void body_set_vel_y(body *b, double v);
void body_set_vel_z(body *b, double v);
void body_set_angmom(body *b, double a);

double body_get_id(body b);
double body_get_mass(body b);
double body_get_diam(body b);
double* body_get_pos(body b);
double* body_get_vel(body b);
double body_get_angmom(body b);

void body_print(body b);

void body_write(body b, const char* fn);

#endif
