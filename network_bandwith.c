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
    if (pocetak==FALSE)
        network_rc=0;
    pocetak = TRUE;
    network_rc=network_rc/1024;
    static gboolean pocetak2=FALSE;
    if (pocetak2==FALSE)
        network_ts=0;
    pocetak2 = TRUE;
    network_ts=network_ts/1024;

    printf("NET %lu %lu\n",received_bytes,transmit_bytes);
    net.received_bytes=network;
    net.transmited_bytes=network2;

    net.network_size_rc=network_size_rc;
    net.network_size_ts=network_size_ts;

    net.received_kb=network_rc;
    net.transmited_kb=network_ts;



    }
