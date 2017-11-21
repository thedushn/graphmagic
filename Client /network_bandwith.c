//
// Created by dushn on 16.8.17..
//

#include "network_bandwith.h"

#include <sys/statvfs.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <errno.h>



static struct DataItem *hash_network_rec = NULL;
static struct DataItem *hash_network_trans = NULL;
static int broj;
struct DataItem {
    uint64_t data;

    char key[64];
};

uint64_t search_net(char * key, struct DataItem  *hashArray,int hash_size ,bool *ima, uint64_t data
) {

    int ret=0;
    char kljuc[64];
    for(int i=0;i<sizeof(hash_network_rec->key);i++){

        kljuc[i]=key[i];
    }
    for(int hashIndex=0;hashIndex<hash_size;hashIndex++){


        if((ret=strcmp(hashArray[hashIndex].key,kljuc))==0){
            *ima=true;
            //    printf("data in search %lu key %i\n", hashArray[hashIndex].data, hashArray[hashIndex].key);
            uint64_t temp =hashArray[hashIndex].data;
            //   uint64_t trans =hashArray[hashIndex].transmitted;
            hashArray[hashIndex].data=data;
            //  hashArray[hashIndex].received=received;
            return temp;
//       // printf("data in search %lu key %lu\n",hashArray[hashIndex]->data,hashArray[hashIndex]->key);
        }


    }

    // *ima=false;
    return 0;
}




void get_rec_trans(char *name, uint64_t received, uint64_t *received_struct, uint64_t transmitted, uint64_t *transmited_struct) {
    uint64_t received_bytes_old = 0, transmit_bytes_old = 0;
    static int hash_size = 0;
    bool ima = false;
    if (hash_network_rec == NULL) {
        hash_network_rec = (struct DataItem *) malloc(sizeof(struct DataItem));
        hash_network_trans = (struct DataItem *) malloc(sizeof(struct DataItem));
        memset(hash_network_trans->key,0,sizeof(hash_network_trans->key));
        memset(hash_network_rec->key,0,sizeof(hash_network_rec->key));
        hash_size++;
    }
    //  printf("search\n");
    received_bytes_old = search_net(name, hash_network_rec, hash_size, &ima, received);
    transmit_bytes_old = search_net(name, hash_network_trans, hash_size, &ima, transmitted);


    if (ima == false) {


        struct DataItem *temp = realloc(hash_network_rec, ( /**j*/ hash_size + 1) * sizeof(struct DataItem));
        struct DataItem *temp1 = realloc(hash_network_trans, ( /**j*/ hash_size + 1) * sizeof(struct DataItem));
        hash_size++;
        if (temp != NULL) {
            hash_network_rec = temp;
        } else {
            free(hash_network_rec);
            printf("relloc error %d", errno);

        }
        if (temp1 != NULL) {
            hash_network_trans = temp1;


        } else {
            free(hash_network_trans);
            printf("relloc error %d", errno);
        }




        //postavljamo novi hash na nulu
        if (hash_network_rec[hash_size - 2].data != 0 || hash_network_trans[hash_size - 2].data != 0 ||
            hash_network_rec[hash_size - 2].key != 0 || hash_network_trans[hash_size - 2].key != 0) {

            hash_network_rec[hash_size - 2].data = 0;
            hash_network_trans[hash_size - 2].data = 0;

        }
        hash_network_rec[hash_size - 2].data = received;
        hash_network_trans[hash_size - 2].data = transmitted;
        for(int i=0 ;i<sizeof(hash_network_rec->key);i++){
            hash_network_rec[hash_size - 2].key[i] = name[i];
            hash_network_trans[hash_size - 2].key[i] = name[i];

        }


    }



    if(received_bytes_old==0 ){

        *received_struct=0;

    }if( transmit_bytes_old==0){


        *transmited_struct=0;
    }else{

        *received_struct=(received-received_bytes_old);
        *transmited_struct=(transmitted-transmit_bytes_old);
    }


    printf("Name %s rec %ld trans %ld \n",name,*received_struct,*transmited_struct);

    for(int i=0;i<hash_size-1;i++){


        printf("index[%d] name %s received %ld trans %ld\n",i,hash_network_rec[i].key,hash_network_rec[i].data,hash_network_trans[i].data);
    }





}

int interface_name(Network *network1){

    /* int len;
     int c;*/
    char *v="/sys/class/net/";
    struct dirent *pDirent;
    DIR *pDir;
    // char buffer[10];
    unsigned  long network_rc =0;
    unsigned  long network_ts = 0;
    char name[64];
    memset(name,0,64);
    struct stat info;
    pDir = opendir (v);

    if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", v);
        return 1;
    }
    int i=0;
    printf("interface_name \n");
    while ((pDirent = readdir(pDir)) != NULL) {
        printf ("Names of interfaces [%s]\n", pDirent->d_name);



        // fstat(*pDirent->d_name,&info);

        if(!strcmp(pDirent->d_name, ".") || !strcmp(pDirent->d_name, "..") || !strcmp(pDirent->d_name, "lo")){


        }
        else{

            sscanf(pDirent->d_name,"%s" ,name);
            // Network network1;
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
            unsigned  long network_rc1=0 ;
            unsigned  long network_ts1=0;

            FILE *file;
            char buffer[1024];
            char buffer2[1024];
            char buffer3[64];
            strncpy(buffer3, name, sizeof(buffer3));


            for (int  g = 0; g < sizeof(buffer3); g++) {

                if (buffer3[g] == 0)
                    break;
                else
                    broj++;
            }

            char *filename = "/proc/net/dev";

            char ch = ' ';
            int a = 0;

            if ((file = fopen(filename, "r")) == NULL || fgets(buffer, 1024, file) == NULL)
                exit(1);

            while (fgets(buffer, 1024, file) != NULL) {


                for (int  r = 0; r < broj; r++) {

                    if (buffer[r] == buffer3[r])
                        a++;
                }
                if (a == broj) {
                    broj = 0;
                    break;
                }


            }


            printf("NET buffer :[%s]",buffer);


            char *network_data = strchr(buffer, ch);


            strncpy(buffer2, network_data, sizeof(buffer2));
            //  printf("buffer2 [%s]\n", buffer2);

            sscanf(buffer2, " %lu %lu  %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu", &received_bytes,
                   &received_packets,
                   &received_errors, &received_drop, &received_fifo,
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

            //   printf("received bytes beofre %ld \n",received_bytes);

            printf("usli\n");
            get_rec_trans(name,received_bytes,&network_rc1,transmit_bytes,&network_ts1);
            //  printf("name %s rec %ld trans %ld\n",name,network1->received_bytes,network1->transmited_bytes);
            printf("name %s rec %ld trans %ld\n",name,network_rc1,network_ts1);
            printf("izasli\n");

            network_rc+=network_rc1;
            network_ts+=network_ts1;
            // i++;
            fclose(file);
        }



    }


    network1->received_bytes=network_rc;
    network1->transmited_bytes=network_ts;
    broj=0;
    closedir (pDir);
    return 0;

}
void clean(){

    free(hash_network_trans);
    free(hash_network_rec);
}
/*
static int broj;

char  name_buffer[10][64];
int interface_name(){

    */
/* int len;
     int c;*//*

    char *v="/sys/class/net/";
    struct dirent *pDirent;
    DIR *pDir;
    // char buffer[10];


    struct stat info;
    pDir = opendir (v);
    if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", v);
        return 1;
    }
    int i=0;
    // malloc()
    while ((pDirent = readdir(pDir)) != NULL) {
        printf ("[%s]\n", pDirent->d_name);



        fstat(*pDirent->d_name,&info);

        if(!strcmp(pDirent->d_name, ".") || !strcmp(pDirent->d_name, "..") || !strcmp(pDirent->d_name, "lo")){


        }
        else{

            sscanf(pDirent->d_name,"%s" ,name_buffer[i]);
            i++;
        }


    }
    for(int j=0;j<i;j++){

        printf("index %d NAME BUFFER : %s \n",j,name_buffer[j]);
    }




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
    char buffer[1024];
    char buffer2[1024];
    char buffer3[10];
    char *network_size_rc=NULL;
    char *network_size_ts=NULL;


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

   */
/* sscanf(buffer," %lu %lu",&received_bytes, &received_packets
            , &received_errors,&received_drop, &received_fifo, &received_frame, &received_compressed, &received_multicast,
    &transmit_bytes,
    &transmit_packets,
    &transmit_errors,
    &transmit_drop,
    &transmit_fifo,
    &transmit_frame,
    &transmit_compressed,
   &transmit_multicast);*//*

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
    network_rc = */
/*(float)*//*
received_bytes;
    network_ts = */
/*(float)*//*
transmit_bytes;



    static bool pocetak=false;
    if (pocetak==false){
        network_rc=0;
        network=0;
    pocetak = true;
    }
    */
/*else{
        network_rc=network_rc/1000;
    }*//*

    //network_rc=network_rc/1024;}
    static bool pocetak2=false;
    if (pocetak2==false){
        network_ts=0;
        network2=0;
    pocetak2 = true;}

    network_struct.received_bytes=network_rc;
    network_struct.transmited_bytes=network_ts;

    return network_struct;


    }



void received_transfered2(Network *network_st){



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
    char buffer[1024];
    char buffer2[1024];
    char buffer3[10];



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

    */
/* sscanf(buffer," %lu %lu",&received_bytes, &received_packets
             , &received_errors,&received_drop, &received_fifo, &received_frame, &received_compressed, &received_multicast,
     &transmit_bytes,
     &transmit_packets,
     &transmit_errors,
     &transmit_drop,
     &transmit_fifo,
     &transmit_frame,
     &transmit_compressed,
    &transmit_multicast);*//*

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
    network_rc = */
/*(float)*//*
received_bytes;
    network_ts = */
/*(float)*//*
transmit_bytes;



    static bool pocetak=false;
    if (pocetak==false){
        network_rc=0;
        network=0;
        pocetak = true;
    }
    */
/*else{
        network_rc=network_rc/1000;
    }*//*

    //network_rc=network_rc/1024;}
    static bool pocetak2=false;
    if (pocetak2==false){
        network_ts=0;
        network2=0;
        pocetak2 = true;}

    network_st->received_bytes=network_rc;
   network_st->transmited_bytes=network_ts;




}


void received_transfered3(Network *network_st){



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
    char buffer[1024];
    char buffer2[1024];
    char buffer3[10];



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

    */
/* sscanf(buffer," %lu %lu",&received_bytes, &received_packets
             , &received_errors,&received_drop, &received_fifo, &received_frame, &received_compressed, &received_multicast,
     &transmit_bytes,
     &transmit_packets,
     &transmit_errors,
     &transmit_drop,
     &transmit_fifo,
     &transmit_frame,
     &transmit_compressed,
    &transmit_multicast);*//*

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
    network_rc = */
/*(float)*//*
received_bytes;
    network_ts = */
/*(float)*//*
transmit_bytes;



    static bool pocetak=false;
    if (pocetak==false){
        network_rc=0;
        network=0;
        pocetak = true;
    }
    */
/*else{
        network_rc=network_rc/1000;
    }*//*

    //network_rc=network_rc/1024;}
    static bool pocetak2=false;
    if (pocetak2==false){
        network_ts=0;
        network2=0;
        pocetak2 = true;}

    network_st->received_bytes=network_rc;
    network_st->transmited_bytes=network_ts;




}
*/
