//
// Created by dushn on 16.8.17..
//

#include "network_bandwith.h"


#include <errno.h>
#include <inttypes.h>


static struct DataItem_net *hash_network_rec = NULL;
static struct DataItem_net *hash_network_trans = NULL;
static int broj;


__uint64_t search_net(char * key, struct DataItem_net  *hashArray,int hash_size ,bool *ima, __uint64_t data
) {
     printf("enter %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);
    int ret=0;
/*    char kljuc[64];
    for(int i=0;i<sizeof(hash_network_rec->key);i++){
        printf(">>>1\n");
        kljuc[i]=key[i];
        printf(">>>1\n");
    }*/
    printf(">>>2\n");
    for(int hashIndex=0;hashIndex<hash_size;hashIndex++){
        printf(">>>2\n");
        printf(">>>3\n");
        if((ret=strcmp(hashArray[hashIndex].key,key))==0){
            printf(">>>3\n");
            *ima=true;
                printf("data in search  %" SCNu64 " key %s\n", hashArray[hashIndex].data, hashArray[hashIndex].key);
            __uint64_t temp =hashArray[hashIndex].data;
            //   uint64_t trans =hashArray[hashIndex].transmitted;
            if(temp>data){
            printf("network reset need to reset hash data\n");

                hashArray[hashIndex].data=data;
                return 0;
            }
            hashArray[hashIndex].data=data;
            printf(">>>3\n");
            //  hashArray[hashIndex].received=received;

            printf("exit %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);
            return temp;
//       // printf("data in search %lu key %lu\n",hashArray[hashIndex]->data,hashArray[hashIndex]->key);
        }
        else{
            printf("Hash in network  ret %d  \n",ret);
        }


    }

    // *ima=false;
    printf("exit %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);
    return 0;
}




void get_rec_trans(char *name, __uint64_t received,__uint64_t *received_struct, __uint64_t transmitted, __uint64_t *transmited_struct) {
    __uint64_t received_bytes_old = 0, transmit_bytes_old = 0;
    static int hash_size = 0;
    bool ima = false;
    printf("enter %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);
    printf(">>>1\n");
    if (hash_network_rec == NULL) {
        printf(">>>1\n");
        hash_network_rec = (struct DataItem_net *) malloc(sizeof(struct DataItem_net));
        hash_network_trans = (struct DataItem_net *) malloc(sizeof(struct DataItem_net));
        memset(hash_network_trans->key,0,sizeof(hash_network_trans->key));
        memset(hash_network_rec->key,0,sizeof(hash_network_rec->key));
        hash_size++;
        printf(">>>1\n");
    }
    //  printf("search\n");
    printf(">>>2\n");
    received_bytes_old = search_net(name, hash_network_rec, hash_size, &ima, received);
    transmit_bytes_old = search_net(name, hash_network_trans, hash_size, &ima, transmitted);
    printf("Got back %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);
    printf("Data old  %" SCNu64 " %" SCNu64 "\n",received_bytes_old,transmit_bytes_old);
    printf("Data   %" SCNu64 " %" SCNu64 "\n",received,transmitted);
    printf(">>>2\n");
    printf(">>>3\n");
    if (ima == false) {

        printf(">>>3\n");
        struct DataItem_net *temp = realloc(hash_network_rec, ( /**j*/ hash_size + 1) * sizeof(struct DataItem_net));
        struct DataItem_net *temp1 = realloc(hash_network_trans, ( /**j*/ hash_size + 1) * sizeof(struct DataItem_net));
        printf(">>>3\n");
        hash_size++;
        printf(">>>4\n");
        if (temp != NULL) {
            printf(">>>4\n");
            hash_network_rec = temp;
            printf(">>>4\n");

        } else {
            printf(">>>5\n");
            free(hash_network_rec);
            free(temp);
            printf("relloc error %d", errno);
            printf(">>>5\n");

        }

        if (temp1 != NULL) {
            hash_network_trans = temp1;


        } else {
            free(hash_network_trans);
            free(temp1);
            printf("relloc error %d", errno);
        }



        printf(">>>6\n");
        //postavljamo novi hash na nulu
        if (hash_network_rec[hash_size - 2].data != 0 || hash_network_trans[hash_size - 2].data != 0 ||
            hash_network_rec[hash_size - 2].key != 0 || hash_network_trans[hash_size - 2].key != 0) {
            printf(">>>6\n");
            hash_network_rec[hash_size - 2].data = 0;
            hash_network_trans[hash_size - 2].data = 0;
            printf(">>>6\n");

        }
        printf(">>>7\n");
        hash_network_rec[hash_size - 2].data = received;
        hash_network_trans[hash_size - 2].data = transmitted;
        printf(">>>7\n");
        for(int i=0 ;i<sizeof(hash_network_rec->key);i++){
            printf(">>>8\n");
            hash_network_rec[hash_size - 2].key[i] = name[i];
            hash_network_trans[hash_size - 2].key[i] = name[i];
            printf(">>>8\n");

        }


    }


    printf(">>>9\n");
    if(received_bytes_old==0 ){
        printf(">>>9\n");
        *received_struct=0;
        printf(">>>9\n");
    }if( transmit_bytes_old==0){
        printf(">>>10\n");

        *transmited_struct=0;
        printf(">>>10\n");
    }else{
        printf(">>>11\n");
printf("Received_struct  %" SCNu64 " Transimeted_struct %" SCNu64 "\n"
        ,*received_struct
        ,*transmited_struct);
        if (received < received_bytes_old || transmitted < transmit_bytes_old)
        {
            //     printf("leave %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);
            *received_struct=0;
            *transmited_struct=0;
        }
        else{

            *received_struct=(received-received_bytes_old);
            *transmited_struct=(transmitted-transmit_bytes_old);
        }


        printf("Received_struct  %" SCNu64 " Transimeted_struct %" SCNu64 " received %" SCNu64 " transimted %" SCNu64 " "
                       "  Data old  recv %" SCNu64 " trans %" SCNu64 "\n"
                ,*received_struct
                ,*transmited_struct
                ,received
                ,transmitted
                ,received_bytes_old
                ,transmit_bytes_old

        );
        printf(">>>11\n");
    }
    printf("exit %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);


   // printf("Name %s rec %ld trans %ld \n",name,*received_struct,*transmited_struct);

/*
    for(int i=0;i<hash_size-1;i++){


        printf("index[%d] name %s received %ld trans %ld\n",i,hash_network_rec[i].key,hash_network_rec[i].data,hash_network_trans[i].data);
    }
*/





}

int interface_name(Network *network1){
    printf("enter %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);

    char *v="/sys/class/net/";
    struct dirent *pDirent;
    DIR *pDir;
    // char buffer[10];
    __uint64_t network_rc =0;
    __uint64_t network_ts = 0;
    char name[64];
    memset(name,0,sizeof(name));
 //   struct stat info;
    pDir = opendir (v);
    printf(">>>1\n");
    if (pDir == NULL) {
        printf(">>>1\n");
        printf ("Cannot open directory '%s'\n", v);
        printf(">>>1\n");
        return 1;

    }
//    int i=0;
   // printf("interface_name \n");
    printf(">>>2\n");
    while ((pDirent = readdir(pDir)) != NULL) {
       // printf ("Names of interfaces [%s]\n", pDirent->d_name);



        // fstat(*pDirent->d_name,&info);
        printf(">>>2\n");
        if(!strcmp(pDirent->d_name, ".") || !strcmp(pDirent->d_name, "..") || !strcmp(pDirent->d_name, "lo")){

      //      printf("not interface %s\n",pDirent->d_name);
        }
        else{
            printf(">>>3\n");
            sscanf(pDirent->d_name,"%s" ,name);
          // printf("NAme %s\n", name);
            __uint64_t received_bytes=0;
            unsigned  long received_packets=0;
            unsigned  long received_errors;
            unsigned  long received_drop;
            unsigned  long received_fifo;
            unsigned  long received_frame;
            unsigned  long received_compressed;
            unsigned  long received_multicast;
            __uint64_t transmit_bytes=0;
            unsigned  long transmit_packets=0;
            unsigned  long transmit_errors;
            unsigned  long transmit_drop;
            unsigned  long transmit_fifo;
            unsigned  long transmit_frame;
            unsigned  long transmit_compressed;
            unsigned  long transmit_multicast;
            __uint64_t network_rc1=0 ;
            __uint64_t network_ts1=0;

            FILE *file;
            char buffer[1024];
            char buffer2[1024];
            char buffer3[64];
            strncpy(buffer3, name, sizeof(buffer3));

           //     printf("Buffer3 %s\n",buffer3);
            printf(">>>3\n");
            for (int  g = 0; g < sizeof(buffer3); g++) {
                printf(">>>4\n");
                if (buffer3[g] == '\0')
                    break;
                else
                    broj++;
            }
        //    printf("broj %d\n", broj);

            char *filename = "/proc/net/dev";

      /*      char ch = ' ';
            int a = 0;*/
            printf(">>>4\n");
            if ((file = fopen(filename, "r")) == NULL || fgets(buffer, 1024, file) == NULL)
                exit(1);

            while (fgets(buffer, 1024, file) != NULL) {

          //  printf("buffer %s \n",buffer);
             /*   for (int  r = 0; r < broj; r++) {

                    if (buffer[r] == buffer3[r])
                        a++;
                }
                if (a == broj) {
                    broj = 0;
                    break;
                }*/
                char *temp=buffer;
                    while (*temp==' '){
                        temp=temp+1;
                    }
           //     printf("Buffer [%s]\nBuffer3 [%s] \n",buffer,buffer3);
                if(strncmp(temp,buffer3,(size_t)broj)==0){
                   //     printf("da li ulazimo u break\n");
                    break;
                }
                else{
                    //     printf("Buffer [%s]buffer3 [%s] \n",buffer,buffer3);
                }


            }


          //  printf("NET buffer :[%s]",buffer);


            char *network_data = strchr(buffer, ':');

            network_data=network_data+1;

            strncpy(buffer2, network_data, sizeof(buffer2));
            //  printf("buffer2 [%s]\n", buffer2);
            printf(">>>5\n");
            sscanf(buffer2, " %" SCNu64 " %lu  %lu %lu %lu %lu %lu %lu %" SCNu64 " %lu %lu %lu %lu %lu %lu %lu", &received_bytes,
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

          //     printf("received bytes beofre %" SCNu64" \n",received_bytes);

         //   printf("usli\n");
            printf(">>>5\n");
            network_rc1=0;
            network_ts1=0;

            get_rec_trans(name,received_bytes,&network_rc1,transmit_bytes,&network_ts1);
              printf("name %s received_bytes    %" SCNu64 " transmit_bytes %" SCNu64 "\n",name,received_bytes,transmit_bytes);
            printf("name %s rec_rc1 %" SCNu64 " trans_ts1  %" SCNu64 " \n",name,network_rc1,network_ts1);
          //  printf("izasli\n");
            printf(">>>6\n");
            network_rc+=network_rc1;
            network_ts+=network_ts1;
            printf("received_rc    %" SCNu64 " transimted_ts %" SCNu64 "\n",network_rc,network_ts);
            // i++;
            printf(">>>6\n");
            memset(name,0,sizeof(name));
            memset(buffer,0,sizeof(buffer));
            memset(buffer2,0,sizeof(buffer2));
            memset(buffer3,0,sizeof(buffer3));
            broj=0;
            printf(">>>6\n");
            fclose(file);
        }



    }

    printf(">>>7\n");
    printf("received_rc    %" SCNu64 " transimted_ts %" SCNu64 "\n",network_rc,network_ts);
    network1->received_bytes=network_rc;
    network1->transmited_bytes=network_ts;
    printf(" Received  [%" SCNu64 "] Transmitted [ %" SCNu64 "] \n",network1->received_bytes,network1->transmited_bytes);
    printf(">>>7\n");
    broj=0;
    closedir (pDir);
    printf("exit %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);
    return 0;

}
void clean(){

    free(hash_network_trans);
    free(hash_network_rec);
}
