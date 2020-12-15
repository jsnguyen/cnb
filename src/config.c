#include "cnbody/config.h"

config* config_create(){
    config *conf;
    conf = malloc(sizeof(config));
    conf->fn = malloc(BUFFSIZE*sizeof(char));
    return conf;
}

void config_destroy(config *conf){
    if(conf){
        free(conf);
    }
    if(conf->fn){
        free(conf->fn);
    }
}

void config_read(config *conf, const char* infile){
    FILE *fp;
    fp = fopen(infile,"r");

    char line[BUFFSIZE];
    char *num;
    for(int i=0;i<NPARAMS;i++){
        if(fgets(line,BUFFSIZE,fp)){
            num = strchr(line,'=')+1;
            switch(i){
                case 0:
                    strcpy(conf->fn,trim(num));
                    break;
                case 1:
                    conf->n_thread = (int) atof(num);
                    break;
                case 2:
                    conf->niter = (int) atof(num);
                    break;
                case 3:
                    conf->nb = (int) atof(num);
                    break;
                case 4:
                    conf->td = atof(num);
                    break;
                case 5:
                    conf->mass_low = atof(num);
                    break;
                case 6:
                    conf->mass_up = atof(num);
                    break;
                case 7:
                    conf->vel_low = atof(num);
                    break;
                case 8:
                    conf->vel_up = atof(num);
                    break;
                case 9:
                    conf->cubelen = atof(num);
                    break;
            }
        }
    }
    fclose(fp);
}
void config_print(config* conf){
    printf("** Parameters **\n");
    printf("fn       = %s\n",conf->fn);
    printf("n_thread = %i\n",conf->n_thread);
    printf("niter    = %i\n",conf->niter);
    printf("nb       = %i\n",conf->nb);
    printf("td       = %f\n",conf->td);
    printf("mass_low = %f\n",conf->mass_low);
    printf("mass_up  = %f\n",conf->mass_up);
    printf("vel_low  = %f\n",conf->vel_low);
    printf("vel_up   = %f\n",conf->vel_up);
    printf("cubelen  = %f\n",conf->cubelen);
}

char *ltrim(char *s){
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s){
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s){
    return rtrim(ltrim(s)); 
}
