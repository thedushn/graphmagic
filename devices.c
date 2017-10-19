//
// Created by dushn on 25.9.17..
//

#include "devices.h"





#include <errno.h>


//void upis_dev(GArray *array){
//
////    char name_test[256];
////    char mounted[256];
////    char type[256];
//    Devices devices;
//    Devices *devices1;
//    for (int r = 0; r < array->len; r++) {
//
//            printf(" upis%d\n",array->len);
//        devices1 = &g_array_index(array, Devices, r);
//
//        for (int h = 0; h < 256; h++) {
//            if (devices1->name[h] != '\0') {
//                devices.name[h] = devices1->name[h];
//            } else {
//                devices.name[h] = devices1->name[h];
//
//                break;
//            }
//        }
//        for (int h = 0; h < 256; h++) {
//            if (devices1->directory[h] != '\0') {
//                devices.directory[h] = devices1->directory[h];
//            } else {
//                devices.directory[h] =devices1->directory[h];
//
//                break;
//            }
//        }
//        for (int j = 0; j < 256; j++) {
//            if (devices1->type[j] != '\0') {
//                devices.type[j] =devices1->type[j];
//            } else {
//                devices.type[j] =devices1->type[j];
//
//                break;
//            }
//        }
//
//        printf(" upispre2 %d\n",names_temp->len);
//       g_array_append_val(names_temp,devices);
//
//
//    }
//
//
//};
//void poredjenje_dev(GArray *array){
//
//
//    Devices *devices2;
//    Devices *devices1;
////
//    if(array->len!=names_temp->len){
//
//        printf("koristimo array %d temp %d\n",array->len,names_temp->len);
//    }
//    for (int r = 0; r < array->len; r++) {
//        devices1=&g_array_index(array,Devices,r);
//        devices2=&g_array_index(names_temp,Devices,r);
//           printf("Array%s\n",devices1->name);
//           printf("Array2%s\n",devices2->name);
//        printf(" Temp_niz %d\n",names_temp->len);
//        printf("novi niz %d\n",array->len);
//        int g= strcmp(devices1->name,devices2->name);
//        if(strcmp(devices1->name,devices2->name)!=0
//           || devices1->used - devices2->used!=0
//           || devices1->total - devices2->total!=0
//           || devices1->free - devices2->free!=0
//           ||devices1->avail - devices2->avail!=0){
//
//
//            //koristi novi niz
//            printf("comparing %d\n",g);
//            printf("use another array");
//        }
//        printf("comparing worked  %d\n",g);
//
//
//
//
//
//    }
//
//
//
//
//}
//void printanje_dev(GArray *array){
//    Devices *devices;
//
//    devices = &g_array_index(names_temp,Devices,0);
//    if(devices==NULL){
//        upis_dev(array);
//
//    }
//    poredjenje_dev(array);
//
//
//   // g_array_free(names,TRUE);
////    g_array_free(ginterrupts_main,TRUE);
////    ginterrupts_main=g_array_new(FALSE,TRUE,sizeof(Interrupts));
// //   names=g_array_new(FALSE,TRUE,sizeof(Devices));
//
//};
Devices testing_files( Devices devices){






    struct statvfs info;

    statvfs(devices.directory,&info);

    //uint64_t usedBytes=(info.f_blocks-info.f_bfree)*info.f_bsize;
   // printf("Total blocks_test: %d\nFree blocks: %d\nSize of block: %d\n\
Size in bytes: %d\nTotal Files size: %lu\n",
//           (int)info.f_blocks, (int)info.f_bfree, (int)info.f_bsize,(int) usedBytes, (long)info.f_blocks*(long)info.f_bsize);
   devices.fid=info.f_flag;
//    printf("///////\n");
//    printf("devices %lu , name %s \n",info.f_flag,devices.name);
//    printf("///////\n");


       devices.total=(long)info.f_blocks*(long)info.f_bsize;
       devices.used=(((long)info.f_blocks-(long)info.f_bfree))* (long)info.f_bsize;
        devices.avail=info.f_bavail*info.f_bsize;
        devices.free=info.f_bfree*info.f_bsize;
/*
        printf("memory_total %lu\n" ,devices.total/1024);
        printf("memory_used   %lu\n" ,devices.used/1024);
        printf("memory_avail   %lu\n" ,devices.avail/1024);
        printf("memory_free   %lu\n" ,devices.free/1024);*/


    return devices;

}

void readDir(char *path) {
    DIR *directory;
    struct dirent *d_file;  // a file in *directory
    directory = opendir (path);

    while ((d_file = readdir (directory)) != 0)
    {
        struct stat filestat;
        char *abPath=malloc(1024);
        memset(abPath, 0, 1024);
        strcpy(abPath, path);
        strcat(abPath, "/");
        strcat(abPath, d_file->d_name);

        lstat (abPath, &filestat);

        switch (filestat.st_mode & S_IFMT)
        {

            case  S_IFBLK:
            {

                size_t j=strlen(abPath);// duzina imena

                mountlist(abPath,j,FALSE); //ako su block type proveravamo da li pripadaju u mount list

                break;

            }
            default:
                break;
        }

        free(abPath);
    }


    closedir (directory);

}
//void array_devices(){
//
//
//    names=g_array_new (FALSE, FALSE, sizeof (Devices));
//
//
//};

GArray *device(gboolean show){

   char *filename="/dev";
//GArray *names;
  names=g_array_new (FALSE, FALSE, sizeof (Devices));
    if(show==TRUE){

        mountlist("",0,TRUE);
    }
    else{
        readDir(filename);
    }

    //printf("pre slanja u beli svet  %d\n",names->len);
    //printanje_dev(names);
return names;

}



void mountlist(char *path,size_t j,gboolean mount){

        Devices devices={0};
    char *filename="/proc/mounts";
   char buffer[1024];
    char name_test[256];
    char mounted[256];
    char type[256];
    FILE *file;

    file= fopen(filename,"r");
    if (file == NULL) {
        printf("open failed, errno = %d\n", errno);
    }
    fseek(file, 0, SEEK_SET);
int g=0;
        if(mount==TRUE){
            while( fgets (buffer, 1024, file) != NULL) {


                sscanf(buffer, "%255s %255s %255s", name_test, mounted, type);


                for (int h = 0; h < 256; h++) {
                    if (name_test[h] != '\0') {
                        devices.name[h] = name_test[h];
                    } else {
                        devices.name[h] = name_test[h];

                        break;
                    }
                }
                for (int h = 0; h < 256; h++) {
                    if (mounted[h] != '\0') {
                        devices.directory[h] = mounted[h];
                    } else {
                        devices.directory[h] = mounted[h];

                        break;
                    }
                }
                for (int r = 0; r < 256; r++) {
                    if (type[r] != '\0') {
                        devices.type[r] = type[r];
                    } else {
                        devices.type[r] = type[r];

                        break;
                    }
                }
                devices = testing_files(devices);
                g_array_prepend_val(names, devices);
            }
        }
        else{
            while( fgets (buffer, 1024, file) != NULL){

                sscanf(buffer,"%255s %255s %255s",name_test,mounted,type);

                for(int i=0 ;i<j;i++){

                    if( path[i]==name_test[i]){

                        g++;
                        if(g==j){
                            if(name_test[g]=='\0'){

                                //   printf("path1 %s name_test %s g %d j %d \n",path,name_test,g,(int)j);
                                for(int t= 0;t<=j;t++){

                                    devices.name[t]=name_test[t];
                                }

                                for(int h=0;h<256;h++){
                                    if(mounted[h]!='\0') {
                                        devices.directory[h] = mounted[h];
                                    }
                                    else{
                                        devices.directory[h] = mounted[h];

                                        break;
                                    }
                                }
                                for(int r=0;r<256;r++){
                                    if(type[r]!='\0') {
                                        devices.type[r] = type[r];
                                    }
                                    else{
                                        devices.type[r] = type[r];

                                        break;
                                    }
                                }
                                //   printf(" type %s\n",type);
                                devices=testing_files(devices);
                                g_array_prepend_val(names,devices);
                            }

                        }

                    }
                    else{

                        g=0;
                        break;
                    }

                }

            }
        }
    fclose(file);

}
