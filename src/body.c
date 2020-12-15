#include "cnbody/body.h"

body* body_create(){
    body *nb = malloc(sizeof(body));
    nb->pos = malloc(3*sizeof(double));
    nb->vel = malloc(3*sizeof(double));

    nb->id = -1;

    nb->px = &nb->pos[0];
    nb->py = &nb->pos[1];
    nb->pz = &nb->pos[2];

    nb->vx = &nb->vel[0];
    nb->vy = &nb->vel[1];
    nb->vz = &nb->vel[2];

    nb->mass=0;
    nb->diam=0;
    for(int i=0;i<3;i++){
        nb->pos[i] = 0;
        nb->vel[i] = 0;
    }
    nb->angmom=0;
    
    return nb;
}

void body_init(body *b){
    b->pos = malloc(3*sizeof(double));
    b->vel = malloc(3*sizeof(double));

    b->id = -1;

    b->px = &b->pos[0];
    b->py = &b->pos[1];
    b->pz = &b->pos[2];

    b->vx = &b->vel[0];
    b->vy = &b->vel[1];
    b->vz = &b->vel[2];

    b->mass=0;
    b->diam=0;
    for(int i=0;i<3;i++){
        b->pos[i] = 0;
        b->vel[i] = 0;
    }
    b->angmom=0;
}

void body_delete(body *b){
    if(b->pos){
        free(b->pos);
    }
    if(b->vel){
        free(b->vel);
    }
}

void body_destroy(body *b){
    if(b->pos){
        free(b->pos);
    }
    if(b->vel){
        free(b->vel);
    }
    if(b){
        free(b);
    }
}

void body_set(body *b, int i, double m, double d, double p[3], double v[3], double a){
    b->id = i;
    b->mass = m;
    b->diam = d;
    memcpy(b->pos,p,3*sizeof(double));
    memcpy(b->vel,v,3*sizeof(double));
    b->angmom = a;
}
void body_set_id(body *b, int i){b->id=i;}
void body_set_mass(body *b, double m){b->mass=m;}
void body_set_diam(body *b, double d){b->diam=d;}

void body_set_pos(body *b, double p[3]){
    body_set_pos_x(b,p[0]);
    body_set_pos_y(b,p[1]);
    body_set_pos_z(b,p[2]);
}

void body_set_pos_x(body *b, double p){*b->px=p;}
void body_set_pos_y(body *b, double p){*b->py=p;}
void body_set_pos_z(body *b, double p){*b->pz=p;}

void body_set_vel(body *b, double v[3]){
    body_set_vel_x(b,v[0]);
    body_set_vel_y(b,v[1]);
    body_set_vel_z(b,v[2]);
}

void body_set_vel_x(body *b, double v){*b->vx=v;}
void body_set_vel_y(body *b, double v){*b->vy=v;}
void body_set_vel_z(body *b, double v){*b->vz=v;}
void body_set_angmom(body *b, double a){b->angmom=a;}

double body_get_id(body b){return b.id;}
double body_get_mass(body b){return b.mass;}
double body_get_diam(body b){return b.diam;}
double* body_get_pos(body b){return b.pos;}
double* body_get_vel(body b){return b.vel;}
double body_get_angmom(body b){return b.angmom;}

void body_print(body b){
    printf("id     = %i\n",b.id);
    printf("mass   = %f\n",b.mass);
    printf("diam   = %f\n",b.diam);
    printf("pos    = %f,%f,%f\n",b.pos[0],b.pos[1],b.pos[2]);
    printf("vel    = %f,%f,%f\n",b.vel[0],b.vel[1],b.vel[2]);
    printf("angmom = %f\n",b.angmom);
}

void body_write(body b, const char* fn){
    FILE *f;
    f=fopen(fn,"a");
    fprintf(f,"%f %f %f\n",b.pos[0],b.pos[1],b.pos[2]);
    fclose(f);
}
