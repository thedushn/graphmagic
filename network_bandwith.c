//
// Created by dushn on 16.8.17..
//

#include "network_bandwith.h"

struct  Network net;
static int broj;
gchar  name_buffer[10];
int interface_name(){

    int len;
    int c;
    char *v="/sys/class/net/";
    struct dirent *pDirent;
    DIR *pDir;
    char buffer[10];

    pDir = opendir (v);
    if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", v);
        return 1;
    }

    while ((pDirent = readdir(pDir)) != NULL) {
        printf ("[%s]\n", pDirent->d_name);
        if(!strcmp(pDirent->d_name, ".") || !strcmp(pDirent->d_name, "..") || !strcmp(pDirent->d_name, "lo")){


        }
        else
        sscanf(pDirent->d_name,"%s" ,name_buffer);

    }

    printf("NAME BUFFER : %s \n",name_buffer);

    closedir (pDir);
    return 0;

}

void received_transfered(){


  static  unsigned  long received_bytes1=0;
  static  unsigned  long transmit_bytes1=0;

   static unsigned  long received_bytes_old=0;
   static unsigned  long transmit_bytes_old=0;

    unsigned  long received_bytes;
    unsigned  long received_packets;
    unsigned  long received_errors;
    unsigned  long received_drop;
    unsigned  long received_fifo;
    unsigned  long received_frame;
    unsigned  long received_compressed;
    unsigned  long received_multicast;
    unsigned  long transmit_bytes;
    unsigned  long transmit_packets;
    unsigned  long transmit_errors;
    unsigned  long transmit_drop;
    unsigned  long transmit_fifo;
    unsigned  long transmit_frame;
    unsigned  long transmit_compressed;
    unsigned  long transmit_multicast;
    FILE *file;
    gchar buffer[1024];
    gchar buffer2[1024];
    gchar buffer3[10];

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
    printf("buffer2 %s",buffer2);

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
    char *network_size_rc;
    char *network_size_ts;

    float network_rc = (float)received_bytes;
    float network_ts = (float)transmit_bytes;

    float network ;
    float network2;

    if(network_rc >=1048576){

        network=network_rc/1024/1024;
        network_size_rc="mb/s";

    }
    if(network_rc >= 1024 && network_rc <1048576){

        network = network_rc/1024;
        network_size_rc ="kb/s";

    }
    if(network_rc<1024){
        network=network_rc;
        network_size_rc="bytes/s";

    }

    if(network_ts >=1048576){

        network2=network_ts/1024/1024;
        network_size_ts="mb/s";

    }
    if(network_ts >= 1024 && network_ts <1048576){

        network2 = network_ts/1024;
        network_size_ts="kb/s";

    }
    if(network_rc<1024){
        network2=network_ts;
        network_size_ts="bytes/s";

    }


    static gboolean pocetak=FALSE;
    if (pocetak==FALSE){
        network_rc=0;
        network=0;
    pocetak = TRUE;
    }
    else{
    network_rc=network_rc/1024;}
    static gboolean pocetak2=FALSE;
    if (pocetak2==FALSE){
        network_ts=0;
        network2=0;
    pocetak2 = TRUE;}
    else{
    network_ts=network_ts/1024;
    }
    printf("NET %lu %lu\n",received_bytes,transmit_bytes);
    net.received_bytes=network;
    net.transmited_bytes=network2;

    net.network_size_rc=network_size_rc;
    net.network_size_ts=network_size_ts;

    net.received_kb=network_rc;
    net.transmited_kb=network_ts;
    printf("network_rc %f network_ts %f",network_rc,network_ts);



    }
