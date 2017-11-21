//
// Created by dushn on 25.9.17..
//

#include "devices.h"

#include <errno.h>



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





void device2(Devices * * array,bool show,int *niz2){

    Devices * devices;
    int niz=0;

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

void mountlist3(Devices **array,bool mount,int *fake){


    Devices *devices2, *temp;
    devices2=malloc(sizeof(Devices));
    int niz=0;
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
  //  int g=0;
    if(mount==true){
        while( fgets (buffer, 1024, file) != NULL) {


            sscanf(buffer, "%255s %255s %255s", name_test, mounted, type);


            for (int h = 0; h < 256; h++) {
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
            for (int r = 0; r < 256; r++) {
                if (type[r] != '\0') {
                    devices2[niz].type[r] = type[r];
                } else {
                    devices2[niz].type[r] = type[r];

                    break;
                }
            }
            devices2[niz] = testing_files(devices2[niz]);//statf    pa saljemo
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

            sscanf(buffer,"%255s %255s %255s",name_test,mounted,type);


            struct stat filestat;
            char *abPath=malloc(1024);
            memset(abPath, 0, 1024);

            strcat(abPath, name_test);

            memset(&filestat, 0, sizeof(filestat));
            lstat (abPath, &filestat);
            switch (filestat.st_mode & S_IFMT)
            {

                case  S_IFBLK:
                {


                    for (int h = 0; h < 256; h++) {
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
                    for (int r = 0; r < 256; r++) {
                        if (type[r] != '\0') {
                            devices2[niz].type[r] = type[r];
                        } else {
                            devices2[niz].type[r] = type[r];

                            break;
                        }
                    }
                    devices2[niz] = testing_files(devices2[niz]);//statf    pa saljemo
                    niz++;
                    temp=realloc(devices2,( /**j*/ niz+1)*sizeof(Devices));

                    if ( temp != NULL ) {
                        devices2=temp;
                    } else {
                        free(devices2);
                    }

                    //  closedir(directory);
                    break;

                }
                default:
                    //  closedir(directory);
                    break;
            }

            free(abPath);

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
    *fake=niz;
   // printf("Mountlist *pointer %d\n",*fake);


}


