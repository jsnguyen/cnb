#ifndef CONFIG_H_
#define CONFIG_H_

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

#define NPARAMS 10
#define BUFFSIZE 255

typedef struct{
    char  *fn;
    int    n_thread;
    int    niter;
    int    nb;
    double td;
    double mass_low;
    double mass_up;
    double vel_low;
    double vel_up;
    double cubelen;
} config;

config* config_create();
void config_destroy(config *conf);
void config_read(config *conf, const char* infile);
void config_print(config *conf);

char *ltrim(char *s);
char *rtrim(char *s);
char *trim(char *s);
#endif
