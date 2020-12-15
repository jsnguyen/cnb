#include "cnbody/gravity.h"

/* ADDS TO VEC not overwrite */
void vecfgrav(double *vec, double m1, double m2, double *pa, double *pb){
    const double G=6.67408e-11;
    double dir[3];
    for(int i=0;i<3;i++){
        dir[i]=pb[i]-pa[i];
    }
    double mag = sqrt(dir[0]*dir[0]+dir[1]*dir[1]+dir[2]*dir[2]);
    if(mag<1e14){
        mag=mag*10;
    }
    double f = G*m1*m2/(mag*mag);
    for(int i=0;i<3;i++){
        vec[i] += dir[i]/mag*f;
    }
}

posvel apply_velverl(body *b, body *bs, int nb, double td){
    double fgrav_init[]={0,0,0};
    double fgrav_fina[]={0,0,0};
    posvel nprop;
    for(int i=0;i<nb;i++){
        if(body_get_id(*b) != body_get_id(bs[i])){
            vecfgrav(fgrav_init, body_get_mass(*b), body_get_mass(bs[i]), body_get_pos(*b), body_get_pos(bs[i]));
        }
    }
    nprop.pos[0]=body_get_pos(*b)[0]+body_get_vel(*b)[0]*td+0.5*fgrav_init[0]/body_get_mass(*b)*td*td;
    nprop.pos[1]=body_get_pos(*b)[1]+body_get_vel(*b)[1]*td+0.5*fgrav_init[1]/body_get_mass(*b)*td*td;
    nprop.pos[2]=body_get_pos(*b)[2]+body_get_vel(*b)[2]*td+0.5*fgrav_init[2]/body_get_mass(*b)*td*td;

    for(int i=0;i<nb;i++){
        if(body_get_id(*b) != body_get_id(bs[i])){
            vecfgrav(fgrav_fina, body_get_mass(*b), body_get_mass(bs[i]), nprop.pos       , body_get_pos(bs[i]));
        }
    }
    nprop.vel[0]=body_get_vel(*b)[0]+0.5*(fgrav_init[0]/body_get_mass(*b)+fgrav_fina[0]/body_get_mass(*b))*td;
    nprop.vel[1]=body_get_vel(*b)[1]+0.5*(fgrav_init[1]/body_get_mass(*b)+fgrav_fina[1]/body_get_mass(*b))*td;
    nprop.vel[2]=body_get_vel(*b)[2]+0.5*(fgrav_init[2]/body_get_mass(*b)+fgrav_fina[2]/body_get_mass(*b))*td;

    return nprop;
}
