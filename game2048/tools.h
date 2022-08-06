#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
    #define debug(...) printf(__VA_ARGS__)                                               
#else
    #define debug(...)
#endif

void rand_two(void);
void show_view(void);
int is_die(void);
static int is_full(void);

#endif//TOOLS_H
