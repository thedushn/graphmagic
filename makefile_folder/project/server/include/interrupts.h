//
// Created by dushn on 31.8.17..
//

#ifndef GTKWORLD_INTERRUPTS_H
#define GTKWORLD_INTERRUPTS_H


#include <math.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>


#include <stdlib.h>
#include "common.h"


void interrupt_usage(int info);

void interrupt_usage2(Interrupts **array, __int32_t *j);


void upis_imena(Interrupts *interrupts1, Interrupts *interrupts3);


#endif //GTKWORLD_INTERRUPTS_H
