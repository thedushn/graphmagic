//
// Created by dushn on 31.8.17..
//

#include "interrupts.h"









gint sortiranje(gconstpointer a,gconstpointer b){
    Interrupts *interrupts1= (Interrupts *)a;
    Interrupts *interrupts2=(Interrupts *)b;

     long CPU0a = 0;
     long CPU1a = 0;
     long CPU2a = 0;
     long CPU3a = 0;
     long CPU0b = 0;
     long CPU1b = 0;
     long CPU2b = 0;
     long CPU3b = 0;
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


//   for (int r = 0; r <= ginterrupts->len; r++) {//// staviti samo manje
   for (int r = 0; r < array->len; r++) {
        //Interrupts interrupts3={0};
        Interrupts interrupts3={0};
        Interrupts *interrupts1;
    //    interrupts1 = &g_array_index(array, Interrupts, r);
        interrupts1 = &g_array_index(array, Interrupts, r);
        //  printf("%lu %lu %lu %lu   ime: %s\n", interrupts1->CPU0, interrupts1->CPU1, interrupts1->CPU2, interrupts1->CPU3,interrupts1->name);
        interrupts3.name[0]=interrupts1->name[0];
        interrupts3.name[1]=interrupts1->name[1];
        interrupts3.name[2]=interrupts1->name[2];
        interrupts3.name[3]=interrupts1->name[3];

        interrupts3.CPU0=interrupts1->CPU0;
        interrupts3.CPU1=interrupts1->CPU1;
        interrupts3.CPU2=interrupts1->CPU2;
        interrupts3.CPU3=interrupts1->CPU3;

       upis_imena( interrupts1 , &interrupts3);

        g_array_insert_val(array2,r,interrupts3);
       // g_array_append_val(array2,interrupts3);
     //  printf("lenght %d\n ",array2->len);
//       if (array2->len > 1)
//           g_array_remove_index (array2, array2->len - 1);
    }
   // printf("lenght %d\n ",array2->len);

};
void poredjenje(GArray *array,GArray *array2,GArray *array3){//array novi array2 stari



    for (int r = 0; r < array->len; r++) {
        Interrupts interrupts3={0};
        Interrupts *interrupts1=&g_array_index(array,Interrupts,r);

        Interrupts *interrupts2=&g_array_index(array2,Interrupts,r);

       interrupts3.CPU0=interrupts1->CPU0 - interrupts2->CPU0;
        interrupts3.CPU1=interrupts1->CPU1 - interrupts2->CPU1;
        interrupts3.CPU2=interrupts1->CPU2 - interrupts2->CPU2;
        interrupts3.CPU3=interrupts1->CPU3 - interrupts2->CPU3;

            interrupts3.name[0] = interrupts1->name[0];
            interrupts3.name[1] = interrupts1->name[1];
            interrupts3.name[2] = interrupts1->name[2];
            interrupts3.name[3] = interrupts1->name[3];



         upis_imena(interrupts1,&interrupts3);

        g_array_append_val(array3,interrupts3);


    }
    printf("%d\n",array3->len);
    for(int i=0 ;i<array3->len;i++){
        Interrupts *interrupts5;
        interrupts5=&g_array_index(array3,Interrupts,i);
        printf("name[%s] CPU0[%lu] CPU1[%lu] CPU2[%lu] CPU3[%lu] ime1[%s],ime2 [%s] ime3 [%s] ime4[%s]\n",interrupts5->name,interrupts5->CPU0,interrupts5->CPU1,interrupts5->CPU2,interrupts5->CPU3,interrupts5->ime1,interrupts5->ime2,interrupts5->ime3,interrupts5->ime4);
    }

    g_array_sort(array3,(GCompareFunc)sortiranje);



           while (array3->len > 10) {
                g_array_remove_index(array3, array3->len - 11);

            }


};
/*void poredjenje(){
    Interrupts *interrupts2;
    Interrupts *interrupts1;
    Interrupts interrupts3={0};
    signed long CPU0 = 0;
    signed long CPU1 = 0;
    signed long CPU2 = 0;
    signed long CPU3 = 0;
//    for (int r = 0; r < array->len; r++) {
//        interrupts1=&g_array_index(array,Interrupts,r);
        for (int r = 0; r < ginterrupts->len; r++) {
            interrupts1=&g_array_index(ginterrupts,Interrupts,r);
        interrupts2=&g_array_index(ginterrupts_temp,Interrupts,r);
     //   printf("%lu\n",interrupts1->CPU0);
        CPU0=interrupts1->CPU0 - interrupts2->CPU0;
        CPU1=interrupts1->CPU1 - interrupts2->CPU1;
        CPU2=interrupts1->CPU2 - interrupts2->CPU2;
        CPU3=interrupts1->CPU3 - interrupts2->CPU3;
       // printf("%lu\n",CPU0);
        if(interrupts1->name[0]==interrupts2->name[0] && interrupts1->name[1]==interrupts2->name[1] && interrupts1->name[2]==interrupts2->name[2] ) {
            interrupts3.name[0] = interrupts1->name[0];
            interrupts3.name[1] = interrupts1->name[1];
            interrupts3.name[2] = interrupts1->name[2];
            interrupts3.name[3] = interrupts1->name[3];
        }
        interrupts3.CPU0=CPU0;
        interrupts3.CPU1=CPU1;
        interrupts3.CPU2=CPU2;
        interrupts3.CPU3=CPU3;

      interrupts3 = upis_imena(interrupts1,interrupts3);

        g_array_append_val(ginterrupts_main,interrupts3);


    }


    g_array_sort(ginterrupts_main,(GCompareFunc)sortiranje);


   // for (int r = 0; r < array->len; r++) {
    for (int r = 0; r < ginterrupts->len; r++) {

        interrupts1=&g_array_index(ginterrupts_main,Interrupts,r);
        if(r>=ginterrupts->len-10 && r<ginterrupts->len){
     //   if(r>=array->len-10 && r<array->len){
            Interrupts interrupts4={0};

            interrupts4.CPU0=interrupts1->CPU0;
            interrupts4.CPU1=interrupts1->CPU1;
            interrupts4.CPU2=interrupts1->CPU2;
            interrupts4.CPU3=interrupts1->CPU3;
            interrupts4.name[0]=interrupts1->name[0];
            interrupts4.name[1]=interrupts1->name[1];
            interrupts4.name[2]=interrupts1->name[2];
            interrupts4.name[3]=interrupts1->name[3];

                  interrupts4 = upis_imena(interrupts1,interrupts4);


            g_array_append_val(ginterrupts_final,interrupts4);
          //  printf("size before %d\n",ginterrupts_final->len);
            if (ginterrupts_final->len > 10) {
                g_array_remove_index(ginterrupts_final, ginterrupts_final->len - 11);
               // printf("size after %d\n",ginterrupts_final->len);
            }
        }
    }


//    for(int i=0 ;i<ginterrupts_final->len;i++){
//        Interrupts *interrupts5;
//        interrupts5=&g_array_index(ginterrupts_final,Interrupts,i);
//    //    printf("name[%s] CPU0[%lu] CPU1[%lu] CPU2[%lu] CPU3[%lu] ime1[%s],ime2 [%s] ime3 [%s] ime4[%s]\n",interrupts5->name,interrupts5->CPU0,interrupts5->CPU1,interrupts5->CPU2,interrupts5->CPU3,interrupts5->ime1,interrupts5->ime2,interrupts5->ime3,interrupts5->ime4);
//    }
    g_array_free(ginterrupts_temp,TRUE);
    ginterrupts_temp=g_array_new(FALSE,TRUE,sizeof(Interrupts));
    //upis();
  //  upis(array);





};*/
//void printanje() {
////void printanje(GArray *array) {
//
//
//    int i=0;
//
//       Interrupts *interrupts2 = &g_array_index(ginterrupts_temp,Interrupts,i);//uzmemo vrednost
//
//        if(interrupts2==NULL){
//          //  upis(array);
//       //     upis(ginterrupts);
//
//        }
//       // poredjenje(array);
//   //     poredjenje(ginterrupts);
//
//
//    g_array_free(ginterrupts,TRUE);
//    g_array_free(ginterrupts_main,TRUE);
//    ginterrupts_main=g_array_new(FALSE,FALSE,sizeof(Interrupts));
//    ginterrupts=g_array_new(FALSE,FALSE,sizeof(Interrupts));
//}
GArray * interrupt_usage() {


        FILE *file;
        gchar *filename = "/proc/interrupts";
        gchar buffer[1024];


  GArray * ginterrupts=g_array_new(FALSE,FALSE,sizeof(Interrupts));

        if ((file = fopen(filename, "r")) == NULL || fgets(buffer, 1024, file) == NULL)
            exit(1);


        while (fgets(buffer, 1024, file) != NULL) {
            guint i = 0;
            Interrupts interrupts={0};


            sscanf(buffer, "%s %li %li %li %li %255s %255s %255s %255s",interrupts.name, &interrupts.CPU0, &interrupts.CPU1,
                   &interrupts.CPU2,
                   &interrupts.CPU3,
                   interrupts.ime1,
                   interrupts.ime2,
                   interrupts.ime3,
                   interrupts.ime4 );


            while(interrupts.name[i] != ':'){


                i++;

            }
            interrupts.name[i]='\0';













            g_array_append_val(ginterrupts,interrupts);



        }
        fclose(file);


       // g_array_sort(ginterrupts,(GCompareFunc)sortiranje);

//    while (ginterrupts->len > 10) {
//        g_array_remove_index(ginterrupts, ginterrupts->len - 11);
//        // printf("size after %d\n",ginterrupts_final->len);
//    }

       // printanje();
     //   printanje(ginterrupts);



return ginterrupts;
}




