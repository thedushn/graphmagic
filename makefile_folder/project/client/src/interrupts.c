//
// Created by dushn on 31.8.17..
//

#include "interrupts.h"



gint sortiranje(gconstpointer a,gconstpointer b){
    Interrupts *interrupts1= (Interrupts *)a;
    Interrupts *interrupts2=(Interrupts *)b;

    __uint64_t CPU0a = 0;
    __uint64_t  CPU1a = 0;
    __uint64_t  CPU2a = 0;
    __uint64_t  CPU3a = 0;
    __uint64_t CPU0b = 0;
    __uint64_t  CPU1b = 0;
    __uint64_t  CPU2b = 0;
    __uint64_t  CPU3b = 0;
     int CPUa= 0;
     int CPUb= 0;

    CPU0a=interrupts1->CPU0;
    CPU1a=interrupts1->CPU1;
    CPU2a=interrupts1->CPU2;
    CPU3a=interrupts1->CPU3;

    CPU0b=interrupts2->CPU0;
    CPU1b=interrupts2->CPU1;
    CPU2b=interrupts2->CPU2;
    CPU3b=interrupts2->CPU3;
    CPUa=(int)(CPU0a+CPU1a+CPU2a+CPU3a);
    CPUb=(int)(CPU0b+CPU1b+CPU2b+CPU3b);

    /*printf(" PRVi %lu %lu %lu %lu   ime: %s\n", interrupts1->CPU0, interrupts1->CPU1, interrupts1->CPU2, interrupts1->CPU3,interrupts1->name);
    printf(" DRUGI %lu %lu %lu %lu   ime: %s\n", interrupts2->CPU0, interrupts1->CPU1, interrupts1->CPU2, interrupts1->CPU3,interrupts1->name);*/

    return CPUa - CPUb;



};

void upis_imena(Interrupts *interrupts1,Interrupts *interrupts3){

    size_t j=strlen(interrupts1->ime1);
    for (int t = 0; t <= j; t++) {

        interrupts3->ime1[t] = interrupts1->ime1[t];


    }
    j=strlen(interrupts1->ime2);
    for (int t = 0; t <= j; t++) {

        interrupts3->ime2[t] = interrupts1->ime2[t];


    }
    j=strlen(interrupts1->ime3);
    for (int t = 0; t <= j; t++) {

        interrupts3->ime3[t] = interrupts1->ime3[t];


    }
    j=strlen(interrupts1->ime4);
    for (int t = 0; t <= j; t++) {

        interrupts3->ime4[t] = interrupts1->ime4[t];


    }


//    return interrupts3;
};

void upis(GArray *array,GArray *array2){


    while (array2->len > 0) {

        g_array_remove_index(array2, 0);
    }
//   for (int r = 0; r <= ginterrupts->len; r++) {//// staviti samo manje
   for (guint r = 0; r < array->len; r++) {

        Interrupts interrupts3;


       // interrupts1 = &g_array_index(array, Interrupts, r);
        interrupts3 = g_array_index(array, Interrupts, r);




        //g_array_insert_val(array2,r,interrupts3);

        g_array_insert_val(array2,r,interrupts3);

       while (array2->len > 10) {
           g_array_remove_index(array2, array2->len - 11);

       }

    }
    //  printf("lenght %d\n ",array2->len);

};
//GArray * poredjenje(GArray *array,GArray *array2){//array novi array2 stari
void poredjenje(GArray *array,GArray *array2,GArray *array3){//array novi array2 stari
//
    int i=0;
    Interrupts *interruptstest = &g_array_index(array2,Interrupts,i);//uzmemo vrednost

    if(interruptstest==NULL){
        //upis(array,array2);
        array2=array;

    }
//    if(array2->len<1){
//
//        upis(array,array2);
//    }
    while(array3->len>0){

        g_array_remove_index(array3, 0);
    }
 /*   if(array3->len>0){

        g_array_free(array3,TRUE);
        array3=g_array_new(FALSE,FALSE,sizeof(Interrupts));
    }*/
    for (int r = 0; r < array->len; r++) {
      //  Interrupts *interrupts3;
       // interrupts3  = (Interrupts*) malloc(sizeof(Interrupts));
        Interrupts interrupts3={0};
        memset(&interrupts3, 0, sizeof(Interrupts));
        Interrupts *interrupts1=&g_array_index(array,Interrupts,r);

        Interrupts *interrupts2=&g_array_index(array2,Interrupts,r);


/*
        interrupts3->CPU0=interrupts1->CPU0 - interrupts2->CPU0;
        interrupts3->CPU1=interrupts1->CPU1 - interrupts2->CPU1;
        interrupts3->CPU2=interrupts1->CPU2 - interrupts2->CPU2;
        interrupts3->CPU3=interrupts1->CPU3 - interrupts2->CPU3;*/

        //  for(int j=0; j<sizeof(interrupts1->name);j++) {

        strcpy(interrupts3.name, interrupts1->name);
        //interrupts3.name[j] = interrupts1->name[j];
        //  }

        __uint64_t temp=interrupts1->CPU0 - interrupts2->CPU0;
       interrupts3.CPU0=temp;
        temp=interrupts1->CPU1 - interrupts2->CPU1;
        interrupts3.CPU1=temp;
        temp=interrupts1->CPU2 - interrupts2->CPU2;
        interrupts3.CPU2=temp;
        temp=interrupts1->CPU3 - interrupts2->CPU3;
        interrupts3.CPU3=temp;




        // upis_imena(interrupts1,&interrupts3);
        strcpy(interrupts3.ime1, interrupts1->ime1);
        strcpy(interrupts3.ime2, interrupts1->ime2);
        strcpy(interrupts3.ime3, interrupts1->ime3);
        strcpy(interrupts3.ime4, interrupts1->ime4);


        g_array_append_val(array3,interrupts3);

        //free(interrupts3);
    }
   // printf("Before sorting %d\n",array3->len);
//    for(int i=0 ;i<array3->len;i++){
//        Interrupts *interrupts5;
//        interrupts5=&g_array_index(array3,Interrupts,i);
//        printf("name[%s] CPU0[%lu] CPU1[%lu] CPU2[%lu] CPU3[%lu] ime1[%s],ime2 [%s] ime3 [%s] ime4[%s]\n",interrupts5->name,interrupts5->CPU0,interrupts5->CPU1,interrupts5->CPU2,interrupts5->CPU3,interrupts5->ime1,interrupts5->ime2,interrupts5->ime3,interrupts5->ime4);
//    }

    g_array_sort(array3,(GCompareFunc)sortiranje);



           while (array3->len > 10) {
                g_array_remove_index(array3, array3->len - 11);

            }



//return array3;

};

