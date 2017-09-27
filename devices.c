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
//void testing_files( Devices devices){
Devices testing_files( Devices devices){
//void testing_files(char * mounted){

    FILE *file;
    struct stat filestat;



   // lstat ("/", &filestat);
    lstat (devices.directory, &filestat);
    //lstat (mounted, &filestat);
   // Devices devices = { 0 };
    int filesd;
    struct statvfs info;

    filesd = open (devices.directory, O_RDWR);
    //filesd = open (mounted, O_RDWR);
    //filesd = open (devices.name, O_RDWR);
    if (file == NULL) {
        printf("open failed, errno = %d\n", errno);
    //    printf("Device name:%s\n",mounted);
    }
    else {
        printf("fopen succeeded\n");
      //  printf("Device name:%s\n",mounted);
    }
    // fstatvfs(file,&info);
    statvfs(devices.directory,&info);
//    statvfs(mounted,&info);

    sectorSize=info.f_bsize;




  uint64_t   totalFilesSize1=filestat.st_size;
    uint64_t usedBytes=(info.f_blocks-info.f_bfree)*info.f_bsize;
    printf("Total blocks_test: %d\nFree blocks: %d\nSize of block: %d\n\
Size in bytes: %d\nTotal Files size: %d\n",
           info.f_blocks, info.f_bfree, info.f_bsize, usedBytes, totalFilesSize1);

    printf("///////\n");

    g_array_append_val(names,devices);
    //    printf("Device name:%s\n",devices.name);
    //    printf("%d index \n",names->len);


       devices.total=(long)info.f_blocks*(long)info.f_bsize;
       devices.used=(((long)info.f_blocks-(long)info.f_bfree))* (long)info.f_bsize;
        devices.avail=info.f_bavail*info.f_bsize;
        devices.free=info.f_bfree*info.f_bsize;
       //memory.available=((long)info.f_blocks*(long)info.f_bsize-(long)info.f_blocks*(long)info.f_bavail)/1024;
        printf("memory_total %lu\n" ,devices.total/1024);
        printf("memory_used   %lu\n" ,devices.used/1024);
        printf("memory_avail   %lu\n" ,devices.avail/1024);
        printf("memory_free   %lu\n" ,devices.free/1024);


    return devices;

}
void get_names(){

    char *filename="/";
   // char *filename="/dev";
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

            case  S_IFBLK:
            {


                FILE *file;
                size_t j=strlen(abPath);
              //  printf("strlen of abPath %zd \n",j);
                printf("%llu\n",(unsigned long long ) filestat.st_size);
//                for(int i=0;i<=j;i++){
//
//                    devices.name[i]=*(abPath+i);
//
//                }
//                devices.name[j+1]='\0';

              /*  while(i < 256 - 1 && (c = gets(abPath) != EOF)) //Keep space for the final \0
                {
                   devices.name[i++] = c;
                }
                devices.name[i] = '\0';
           */
                filesd = open (devices.name, O_RDWR);
                if (file == NULL) {
                    printf("open failed, errno = %d\n", errno);
              //      printf("Device name:%s\n",devices.name);
                }
//                else {
//             //      printf("fopen succeeded\n");
//             //       printf("Device name:%s\n",devices.name);
//                }

        /*        fstatvfs(filesd,&info);
//
                totalFilesSize+=filestat.st_size;
                uint64_t usedBytes=(info.f_blocks-info.f_bfree)*info.f_bsize;
                printf("Total blocks: %d\nFree blocks: %d\nSize of block: %d\n\
Size in bytes: %d\nTotal Files size: %d\n",
                       info.f_blocks, info.f_bfree, info.f_bsize, usedBytes, totalFilesSize);*/

                printf("///////\n");
                mountlist(abPath,j);
        //        g_array_append_val(names,devices);
             //   printf("Device name:%s\n",devices.name);
            //    printf("%d index \n",names->len);

                break;

            }
        }

        free(abPath);
    }

 /*   for(int i=0;i<names->len;i++){

        Devices *devices1 ;
              devices1  =&g_array_index(names,Devices,i);

     //   printf("all the devices%s\n",devices1->name);

    }*/


    closedir (directory);

}
void array_devices(){

    names=g_array_new (FALSE, FALSE, sizeof (Devices));

};

void device(){

   char *filename="/dev";

    array_devices();
    readDir(filename);

printf("Duzina niza %d\n",names->len);

    struct statvfs info;


    int fileds=0;
 //   array_devices();// pravimo niz
  // statvfs("/", &info);
  //  get_names();
  //  testing_files();
    g_array_free(names,TRUE);
   // char *filename2= readDir(filename);

/*
    for(int i=0; i<names->len;i++){

        char *pointer=g_array_index(names,char,i);
        printf("names %s",pointer);

    }*/
  //  statvfs(filename2, &info);
    //sectorSize=info.f_bsize;
//    if (-1 == (fileds = open(filename,O_RDONLY)))
//        perror("open() error");
  //  fstatvfs( fileds,&info1);
    uint64_t usedBytes=(info.f_blocks-info.f_bfree)*info.f_bsize;
 //   uint64_t usedBytes1=(info1.f_blocks-info1.f_bfree)*info1.f_bsize;

        printf("%s\n",filename);

    printf("Total blocks_main: %d\n\
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




}



void mountlist(char *path,size_t j){

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
  /*  for(int i=0;i<names->len;i++){
       devices=&g_array_index(array,Devices,i);*/
        while( fgets (buffer, 1024, file) != NULL){


            sscanf(buffer,"%255s %255s %255s",name_test,mounted,type);



            for(int i=0 ;i<j;i++){

                if( path[i]==name_test[i]){

                    g++;
                    if(g==j){
                        if(name_test[g]=='\0'){

                            printf("path1 %s name_test %s g %d j %d \n",path,name_test,g,j);
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
                            printf(" type %s\n",type);
                            devices=testing_files(devices);
                            // testing_files(mounted);
                            g_array_append_val(names,devices);
                        }

                    }

                }
                else{

                    g=0;
                    break;
                }


            }



        }
    // }
    printf(" Final Directory: %s Device: %s used %lu total %lu free %lu type %s available %lu\n",
           devices.directory,
           devices.name,
           devices.used,
           devices.total,
           devices.free,
           devices.type,
           devices.avail);


}
