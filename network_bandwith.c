//
// Created by dushn on 16.8.17..
//

#include "network_bandwith.h"

struct  Network net;

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
    char *filename = "/proc/net/dev";
    char ch = ' ';

    if ((file = fopen (filename, "r")) == NULL || fgets (buffer, 1024, file) == NULL)
        exit(1);
     //   printf("NET buffer :%s",buffer);
    fgets (buffer, 1024, file);
    fgets (buffer, 1024, file);

   // printf("NET buffer :%s",buffer);
   char *j =  strchr(buffer, ch);
    sscanf(buffer," %lu %lu",&received_bytes, &received_packets/*, &received_errors,&received_drop, &received_fifo, &received_frame, &received_compressed, &received_multicast,
    &transmit_bytes,
    &transmit_packets,
    &transmit_errors,
    &transmit_drop,
    &transmit_fifo,
    &transmit_frame,
    &transmit_compressed,
   &transmit_multicast*/);
   strncpy ( buffer2, j, sizeof(buffer2) );
    printf("buffer2 %s",buffer2);
    sscanf(buffer2," %lu %lu  %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu",&received_bytes, &received_packets, &received_errors,&received_drop, &received_fifo, &received_frame, &received_compressed, &received_multicast,
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
    char *network_size;
    float network1 = (float)received_bytes;
    float network ;

    if(network1 >=1048576){

        network=network1/1024/1024;
        network_size="mb/s";

    }
    if(network1 >= 1024 && network1 <1048576){

        network = network/1024;
        network_size ="kb/s";

    }
    if(network1<1024){
        network=network1;
        network_size="bytes/s";

    }
    network1=network1/1024;

    printf("NET %lu %lu\n",received_bytes,transmit_bytes);
    net.received_bytes=network;
    net.transfered_bytes=transmit_bytes;
    net.network_size=network_size;
    net.received_kb=network1;


    }
