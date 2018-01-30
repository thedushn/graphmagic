//
// Created by dushn on 25.9.17..
//

#include "devices.h"

#include <errno.h>


void  testing_files2( Devices *devices){






struct statvfs info;

statvfs(devices->directory,&info);


devices->fid=info.f_flag;
//    printf("///////\n");
//    printf("devices %lu , name %s \n",info.f_flag,devices.name);
//    printf("///////\n");


devices->total=(__uint64_t)info.f_blocks*(__uint64_t)info.f_bsize;
devices->used=(((__uint64_t)info.f_blocks-(__uint64_t)info.f_bfree))* (__uint64_t)info.f_bsize;
devices->avail=(__uint64_t)(info.f_bavail*info.f_bsize);
devices->free=(__uint64_t)(info.f_bfree*info.f_bsize);
/*
        printf("memory_total %lu\n" ,devices.total/1024);
        printf("memory_used   %lu\n" ,devices.used/1024);
        printf("memory_avail   %lu\n" ,devices.avail/1024);
        printf("memory_free   %lu\n" ,devices.free/1024);*/




}






void device2(Devices * * array,bool show,__int32_t *niz2){

    Devices * devices;
    __int32_t niz=0;

    mountlist3(&devices,show,&niz);
  // printf("Niz u devices%d\n",niz);

  /*  for(int r=0;r<niz;r++){

        printf("Devices %lu, %lu,%lu,%lu %lu, %s %s %s\n",
               devices[r].used,devices[r].avail,
               devices[r].fid,devices[r].free,devices[r].total,
               devices[r].name,devices[r].directory,devices[r].type);

    }*/

    *niz2=niz;
    *array=devices;

}

void mountlist3(Devices **array,bool mount,__int32_t *fake){


    Devices *devices2, *temp;
    devices2=malloc(sizeof(Devices));
    int niz=0;
    char *filename="/proc/mounts";

    char buffer[1024];
/*    char name_test[256];
    char mounted[256];
    char type[256];*/
    FILE *file;


    file= fopen(filename,"r");
    if (file == NULL) {
        printf("open failed, errno = %d\n", errno);
    }
    fseek(file, 0, SEEK_SET);
  //  int g=0;
    if(mount==true){
        while( fgets (buffer, 1024, file) != NULL) {


            sscanf(buffer, "%63s %255s %63s", devices2[niz].name, devices2[niz].directory, devices2[niz].type);
        //    sscanf(buffer, "%63s %255s %63s", name_test, mounted, type);


         /*   for (int h = 0; h < 64; h++) {
                if (name_test[h] != '\0') {
                    devices2[niz].name[h] = name_test[h];
                } else {
                    devices2[niz].name[h] = name_test[h];

                    break;
                }
            }
            for (int h = 0; h < 256; h++) {
                if (mounted[h] != '\0') {
                    devices2[niz].directory[h] = mounted[h];
                } else {
                    devices2[niz].directory[h] = mounted[h];

                    break;
                }
            }
            for (int r = 0; r < 64; r++) {
                if (type[r] != '\0') {
                    devices2[niz].type[r] = type[r];
                } else {
                    devices2[niz].type[r] = type[r];

                    break;
                }
            }*/
           // devices2[niz] = testing_files(devices2[niz]);//statf    pa saljemo
            testing_files2(&devices2[niz]);
            niz++;
            temp=realloc(devices2,( /**j*/ niz+1)*sizeof(Devices));

            if ( temp != NULL ) {
                devices2=temp;
            } else {
                free(devices2);
            }

        }
    }
    else{
        while( fgets (buffer, 1024, file) != NULL){
            //upisujemo podatke
            sscanf(buffer, "%s %s %s", devices2[niz].name, devices2[niz].directory, devices2[niz].type);
            //  sscanf(buffer,"%63s %255s %63s",devices2[niz].name,devices2[niz].directory,devices2[niz].type);


            struct stat filestat;

            memset(&filestat, 0, sizeof(filestat));
            lstat (devices2[niz].name, &filestat);

            switch (filestat.st_mode & S_IFMT)
            {

                case  S_IFBLK:
                {


                   /* for (int h = 0; h < 64; h++) {
                        if (name_test[h] != '\0') {
                            devices2[niz].name[h] = name_test[h];
                        } else {
                            devices2[niz].name[h] = name_test[h];

                            break;
                        }
                    }
                    for (int h = 0; h < 256; h++) {
                        if (mounted[h] != '\0') {
                            devices2[niz].directory[h] = mounted[h];
                        } else {
                            devices2[niz].directory[h] = mounted[h];

                            break;
                        }
                    }
                    for (int r = 0; r < 64; r++) {
                        if (type[r] != '\0') {
                            devices2[niz].type[r] = type[r];
                        } else {
                            devices2[niz].type[r] = type[r];

                            break;
                        }
                    }*/
                   // devices2[niz] = testing_files(devices2[niz]);//statf    pa saljemo
                    testing_files2(&devices2[niz]);
                    niz++;
                    temp=realloc(devices2,( /**j*/ niz+1)*sizeof(Devices));

                    if ( temp != NULL ) {
                        devices2=temp;
                    } else {
                        free(devices2);
                        free(temp);
                    }


                    break;

                }
                default:
                    memset(devices2[niz].name,0,sizeof(devices2[niz].name));
                    memset(devices2[niz].directory,0,sizeof(devices2[niz].directory));
                    memset(devices2[niz].type,0,sizeof(devices2[niz].type));
                    break;
            }



        }
    }

    fclose(file);
  //  printf("NIZ %d\n",niz);
  /*  for(int r=0;r<niz;r++){

        printf("Mount :%lu, %lu,%lu,%lu %lu, %s %s %s\n",
               devices2[r].used,devices2[r].avail,
               devices2[r].fid,devices2[r].free,devices2[r].total,
               devices2[r].name,devices2[r].directory,devices2[r].type);

    }*/
    *array=devices2;
    *fake=(__int32_t)niz;
   // printf("Mountlist *pointer %d\n",*fake);


}


