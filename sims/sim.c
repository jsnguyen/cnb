#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "time.h"
#include "cnbody/body.h"
#include "cnbody/gravity.h"
#define SOL_MASS 1.989e30
#define EAR_MASS 5.972e24
#define AU 1.396e11
#define PARSEC 3.0857e16

static inline double get_rand_between(double a, double b) {
    assert(a<b);
    return a+((double)rand() / (double)RAND_MAX)*(b-a);
}

static inline void random_bodies(body *bs, int nb, double mass_low, double mass_up, double vel_low, double vel_up, double cubelen){
    for(int i=0;i<nb;i++){
        body_set_id(&bs[i],i);
        body_set_mass(&bs[i],get_rand_between(mass_low,mass_up));
        double pos[3];
        double vel[]={0,0,0};
        for(int j=0;j<2;j++){
            pos[j]=get_rand_between(-cubelen/2.0,cubelen/2.0);
            vel[j]=get_rand_between(vel_low,vel_up);
        }
        pos[2]=0;
        vel[2]=0;
        body_set_pos(&bs[i],pos);
        body_set_vel(&bs[i],vel);
    }
}

static inline void write_params(const char* fn, const int niter, const int nb, const double td, const double mass_low, const double mass_up, const double vel_low, const double vel_up, const double cubelen){
    FILE *f;
    f = fopen(fn,"w");
    fprintf(f,"%i\n",niter);
    fprintf(f,"%i\n",nb);
    fprintf(f,"%f\n",td);
    fprintf(f,"%f\n",mass_low);
    fprintf(f,"%f\n",mass_up);
    fprintf(f,"%f\n",vel_low);
    fprintf(f,"%f\n",vel_up);
    fprintf(f,"%f\n",cubelen);
    fclose(f);
}

int main(int argc, char* argv[]){

    srand((unsigned)time(NULL));
    /* rand is weird */
    rand(); rand(); rand();

    const char*  fn       = "out.txt"; 
    const int    niter    = 10000;
    const int    nb       = 100;
    const double td       = 1e6;
    const double mass_low = 1e16*SOL_MASS;
    const double mass_up  = 2e16*SOL_MASS;
    const double vel_low  = -1e16;
    const double vel_up   = 1e16;
    const double cubelen  = 1e9*PARSEC;

    body bs[nb];
    for(int i=0;i<nb;i++){
        body_init(&bs[i]);
    }
    printf("Initialized random bodies.\n");

    random_bodies(bs,nb,mass_low,mass_up,vel_low,vel_up,cubelen);
    printf("Generated random bodies.\n");

    /*
    for(int i=0;i<nb;i++){
        body_print(bs[i]);
    }
    */

    write_params(fn,niter,nb,td,mass_low,mass_up,vel_low,vel_up,cubelen);
    printf("Parameters written to %s.\n",fn);

    printf("Beginning main simulation loop.\n");
    posvel nprop[nb];

    clock_t start_t = clock();
    clock_t elaps_t;
    clock_t begin_loop_t;
    double cpu_t, loop_t;
    double loop_ravg=0;
    for(int i=0;i<niter;i++){
        begin_loop_t = clock();

        for(int j=0;j<nb;j++){
            body_write(bs[j],fn);
        }

        for(int j=0;j<nb;j++){
            nprop[j] = apply_velverl(&bs[j], bs, nb, td);
            body_set_pos(&bs[j],nprop[j].pos);
            body_set_vel(&bs[j],nprop[j].vel);
            for(int k=0;k<3;k++){
                double curr_pos=body_get_pos(bs[j])[k];
                if(curr_pos < -cubelen/2.0){
                    switch (k){
                        case 0:
                            body_set_pos_x(&bs[j],curr_pos+cubelen);
                            break;
                        case 1:
                            body_set_pos_y(&bs[j],curr_pos+cubelen);
                            break;
                        case 2:
                            body_set_pos_z(&bs[j],curr_pos+cubelen);
                            break;
                    }
                }
                else if(curr_pos > cubelen/2.0){
                    switch (k){
                        case 0:
                            body_set_pos_x(&bs[j],curr_pos-cubelen);
                            break;
                        case 1:
                            body_set_pos_y(&bs[j],curr_pos-cubelen);
                            break;
                        case 2:
                            body_set_pos_z(&bs[j],curr_pos-cubelen);
                            break;
                    }
                }
            }
        }
        elaps_t = clock();
        cpu_t = (double) (elaps_t - start_t) / CLOCKS_PER_SEC;
        loop_t = (double) (elaps_t - begin_loop_t)/ CLOCKS_PER_SEC;
        loop_ravg = (loop_t+i*loop_ravg)/(i+1);

        printf("\r[%.2f%%] || elapsed: %.3fs ||  est time comp: %.3fs || avg loop time: %.3fs ||",(double) 100*(i+1)/niter,cpu_t,loop_ravg*(niter-1-i),loop_ravg);
        fflush(stdout);
    }
    printf("\n");
    
    for(int i=0;i<nb;i++){
        body_delete(&bs[i]);
    }
    printf("Bodies deleted.\n");

    printf("Success!\n");
    return 0;
}
