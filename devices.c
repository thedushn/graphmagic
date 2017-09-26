//
// Created by dushn on 25.9.17..
//

#include "devices.h"

#include <fcntl.h>
#include <sys/statvfs.h>
#include <stdio.h>
#include <glibtop.h>
#include "glibtop/mountlist.h"


#include <errno.h>
uint64_t totalFilesSize=0;
uint64_t totalFilesSize1=0;
unsigned long sectorSize=0;
void get_names(){

    char *filename="/dev";
    static int i=0;
    GDir *dir;
    const gchar *name;


   readDir(filename);





}
void readDir(char *path) {
    DIR *directory;
    struct dirent *d_file;  // a file in *directory

    directory = opendir (path);
    Devices devices = { 0 };
    int filesd;
    struct statvfs info;

    while ((d_file = readdir (directory)) != 0)
    {
        struct stat filestat;
        char *abPath=malloc(1024);
        memset(abPath, 0, 1024);
        strcpy(abPath, path);
        strcat(abPath, "/");
        strcat(abPath, d_file->d_name);

        lstat (abPath, &filestat);
        //  printf("%s\n",d_file->d_name);
        switch (filestat.st_mode & S_IFMT)
        {
            /*  case S_IFDIR:
              {
                  if (strcmp (".", d_file->d_name) && strcmp ("..", d_file->d_name))
                  {
                      printf("File: %s\nSize: %d\n\n", abPath, filestat.st_size);

                      //Add slack space to the final sum
                   //  int slack=sectorSize-(filestat.st_size%sectorSize);

                      totalFilesSize+=filestat.st_size;//+slack;

                     // readDir(abPath);
                  }
                  break;
              }
              case S_IFREG:
              {
                  printf("File: %s\nSize: %d\n\n", abPath, filestat.st_size);

                  //Add slack space to the final sum
                  int slack=sectorSize-(filestat.st_size%sectorSize);

                  totalFilesSize+=filestat.st_size+slack;

                  break;
              }*/
            case  S_IFBLK:
            {

               // printf("o yeea: %s\nSize: %d\n\n", abPath, filestat.st_size);

                //Add slack space to the final sum





                FILE *file;
                size_t j=strlen(abPath);
                printf("strlen of abPath %zd \n",j);
                printf("%llu\n",(unsigned long long ) filestat.st_size);
                for(int i=0;i<=j;i++){

                    devices.name[i]=*(abPath+i);

                }
                devices.name[j+1]='\0';

              /*  while(i < 256 - 1 && (c = gets(abPath) != EOF)) //Keep space for the final \0
                {
                   devices.name[i++] = c;
                }
                devices.name[i] = '\0';
           */
                filesd = open (devices.name, O_RDWR);
                if (file == NULL) {
                    printf("open failed, errno = %d\n", errno);
                    printf("Device name:%s\n",devices.name);
                }
                else {
                   printf("fopen succeeded\n");
                    printf("Device name:%s\n",devices.name);
                }
               // fstatvfs(file,&info);
                fstatvfs(filesd,&info);

                sectorSize=info.f_bsize;
            //    double slack=sectorSize-(filestat.st_size%sectorSize);

                totalFilesSize+=filestat.st_size;//+slack;
                uint64_t usedBytes=(info.f_blocks-info.f_bfree)*info.f_bsize;
                printf("Total blocks: %d\nFree blocks: %d\nSize of block: %d\n\
Size in bytes: %d\nTotal Files size: %d\n",
                       info.f_blocks, info.f_bfree, info.f_bsize, usedBytes, totalFilesSize);

                printf("///////\n");

                g_array_append_val(names,devices);
            //    printf("Device name:%s\n",devices.name);
            //    printf("%d index \n",names->len);

                break;

            }
        }

        free(abPath);
    }

    for(int i=0;i<names->len;i++){

        Devices *devices1 ;
              devices1  =&g_array_index(names,Devices,i);

     //   printf("all the devices%s\n",devices1->name);

    }
    mountlist(names);

    closedir (directory);

}
void array_devices(){

    names=g_array_new (FALSE, FALSE, sizeof (Devices));

};

void device(){

    char *filename="/dev/sda1";
   /* char *filename="/";*/
    struct statvfs info;
    struct statvfs info1;

    int fileds=0;
    array_devices();// pravimo niz
   // statvfs(filename, &info);
    get_names();
    g_array_free(names,TRUE);
   // char *filename2= readDir(filename);

/*
    for(int i=0; i<names->len;i++){

        char *pointer=g_array_index(names,char,i);
        printf("names %s",pointer);

    }*/
  //  statvfs(filename2, &info);
    //sectorSize=info.f_bsize;
/*    if (-1 == (fileds = open(filename,O_RDONLY)))
        perror("open() error");
    fstatvfs( fileds,&info1);
    uint64_t usedBytes=(info.f_blocks-info.f_bfree)*info.f_bsize;
    uint64_t usedBytes1=(info1.f_blocks-info1.f_bfree)*info1.f_bsize;

        printf("%s\n",filename);

    printf("Total blocks: %d\n\
Free blocks: %d\n\
Size of block: %d\n\
Size in bytes: %d\n"
                   "Total Files size: "
                   "%d free inodes %d \n",
           info.f_blocks
            , info.f_bfree
            , info.f_bsize,
           usedBytes,
           totalFilesSize,
           info.f_files);
    printf("///////\n");



   // file = fopen (filename2, "r ");
  //  fstatvfs( file,&info1);

    printf("Total blocks1: %d\nFree blocks: %d\nSize of block: %d\n\
Size in bytes: %d\nTotal Files size: %d\n",
           info1.f_blocks, info1.f_bfree, info1.f_bsize, usedBytes1, totalFilesSize1);
    printf("///////\n");


    if (-1 == (fileds = open(filename,O_RDONLY)))
        perror("open() error");
    else if (-1 == fstatvfs(fileds, &info1))
        perror("fstatvfs() error");
    else {
        puts("fstatvfs() returned the following information");
        puts("about the Root ('/') file system:");
        printf("  f_bsize    : %u\n", info.f_bsize);
        printf("  f_blocks   : %08X\n",
               *((int *)&info1.f_blocks)
               *//**,((int *)&info1.f_blocks)*//*);
        printf("  f_bfree    : %08X%08X\n",
               *((int *)&info1.f_bfree),
               *((int *)&info1.f_bfree));
        printf("  f_files    : %u\n", info1.f_files);
        printf("  f_ffree    : %u\n", info1.f_ffree);
        printf("  f_fsid     : %u\n", info1.f_fsid);
        printf("  f_flag     : %X\n", info1.f_flag);
        printf("  f_namemax  : %u\n", info1.f_namemax);
        *//*printf("  f_pathmax  : %u\n", info1.f_pathmax);
        printf("  f_basetype : %s\n", info1.f_basetype);*//*
    }*/
}



void mountlist(GArray *array){

        Devices *devices={0};






    char *filename="/proc/mounts";
   char buffer[1024];
    FILE *file;

    file= fopen(filename,"r");
    if (file == NULL) {
        printf("open failed, errno = %d\n", errno);
    }

    for(int i=0;i<names->len;i++){
        devices=&g_array_index(names,Devices,i);
        while( fgets (buffer, 1024, file) != NULL){


        //    printf("%s\n",buffer);

        }
    }



}
