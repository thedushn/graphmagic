//
// Created by dushn on 23.10.17..
//

#ifndef GTKWORLD_INTERRUPTS_S_H
#define GTKWORLD_INTERRUPTS_S_H


typedef struct _Interrupts Interrupts;
struct _Interrupts{

    gchar name[4];
    signed long CPU0;
    signed long CPU1;
    signed long CPU2;
    signed long CPU3;
    gchar ime1[256];
    gchar ime2[256];
    gchar ime3[256];
    gchar ime4[256];

};
#endif //GTKWORLD_INTERRUPTS_S_H
