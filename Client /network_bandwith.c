//
// Created by dushn on 16.8.17..
//

#include "network_bandwith.h"

struct  _Network net;
static int broj;
gchar  name_buffer[10];
int interface_name(){

   /* int len;
    int c;*/
    char *v="/sys/class/net/";
    struct dirent *pDirent;
    DIR *pDir;
   // char buffer[10];

    pDir = opendir (v);
    if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", v);
        return 1;
    }

    while ((pDirent = readdir(pDir)) != NULL) {
       // printf ("[%s]\n", pDirent->d_name);
        if(!strcmp(pDirent->d_name, ".") || !strcmp(pDirent->d_name, "..") || !strcmp(pDirent->d_name, "lo")){


        }
        else
        sscanf(pDirent->d_name,"%s" ,name_buffer);

    }

 //   printf("NAME BUFFER : %s \n",name_buffer);


    closedir (pDir);
    return 0;

}

Network received_transfered(){

        Network network_struct;

  static  unsigned  long received_bytes1=0;
  static  unsigned  long transmit_bytes1=0;

   static unsigned  long received_bytes_old=0;
   static unsigned  long transmit_bytes_old=0;

    unsigned  long received_bytes=0;
    unsigned  long received_packets=0;
    unsigned  long received_errors;
    unsigned  long received_drop;
    unsigned  long received_fifo;
    unsigned  long received_frame;
    unsigned  long received_compressed;
    unsigned  long received_multicast;
    unsigned  long transmit_bytes=0;
    unsigned  long transmit_packets=0;
    unsigned  long transmit_errors;
    unsigned  long transmit_drop;
    unsigned  long transmit_fifo;
    unsigned  long transmit_frame;
    unsigned  long transmit_compressed;
    unsigned  long transmit_multicast;
    unsigned  long network=0 ;
    unsigned  long network2=0;
    unsigned  long network_rc =0;
    unsigned  long network_ts = 0;
    FILE *file;
    gchar buffer[1024];
    gchar buffer2[1024];
    gchar buffer3[10];
    gchar *network_size_rc=NULL;
    gchar *network_size_ts=NULL;


    strncpy(buffer3,name_buffer,sizeof(buffer3));


    for(int i= 0;i<sizeof(buffer3);i++ ){

        if (buffer3[i]==0)
        break;
        else
            broj++;
    }
    char *filename = "/proc/net/dev";

   char ch =' ';
    int a=0;

    if ((file = fopen (filename, "r")) == NULL || fgets (buffer, 1024, file) == NULL)
        exit(1);

    while (fgets (buffer, 1024, file) != NULL){


        for(int i=0 ;i<broj;i++){

           if (buffer[i]==buffer3[i])
               a++;
        }
            if (a==broj) {
                broj=0;
                break;
            }





    }


     //   printf("NET buffer :%s",buffer);



   // printf("NET buffer :%s",buffer);

    char *j=strchr(buffer,ch);

   /* sscanf(buffer," %lu %lu",&received_bytes, &received_packets
            , &received_errors,&received_drop, &received_fifo, &received_frame, &received_compressed, &received_multicast,
    &transmit_bytes,
    &transmit_packets,
    &transmit_errors,
    &transmit_drop,
    &transmit_fifo,
    &transmit_frame,
    &transmit_compressed,
   &transmit_multicast);*/
   strncpy ( buffer2, j, sizeof(buffer2) );
   // printf("buffer2 %s",buffer2);

    sscanf(buffer2," %lu %lu  %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu",&received_bytes, &received_packets,
    &received_errors,&received_drop, &received_fifo,
    &received_frame, &received_compressed,
    &received_multicast,
           &transmit_bytes,
           &transmit_packets,
           &transmit_errors,
           &transmit_drop,
           &transmit_fifo,
           &transmit_frame,
           &transmit_compressed,
           &transmit_multicast);

    fclose(file);
    received_bytes_old= received_bytes1;
    transmit_bytes_old= transmit_bytes1;

    received_bytes1=received_bytes;
    transmit_bytes1=transmit_bytes;



    transmit_bytes= (transmit_bytes1- transmit_bytes_old);
    received_bytes= (received_bytes1-received_bytes_old);

  //  printf(" %li %li %li %li %li %li\n",transmit_bytes ,received_bytes,received_bytes1,transmit_bytes1,transmit_bytes_old,received_bytes_old);
    network_rc = /*(float)*/received_bytes;
    network_ts = /*(float)*/transmit_bytes;



    static gboolean pocetak=FALSE;
    if (pocetak==FALSE){
        network_rc=0;
        network=0;
    pocetak = TRUE;
    }
    /*else{
        network_rc=network_rc/1000;
    }*/
    //network_rc=network_rc/1024;}
    static gboolean pocetak2=FALSE;
    if (pocetak2==FALSE){
        network_ts=0;
        network2=0;
    pocetak2 = TRUE;}

    network_struct.received_bytes=network_rc;
    network_struct.transmited_bytes=network_ts;

    return network_struct;


    }

