//
// Created by dushn on 4.8.17..
//

#include "cpu_usage.h"








//void cpu_number (){
int cpu_number (){

    int c=0;
    FILE *file;
    char *filename = "/proc/cpuinfo";
    char buffer[1024];
    if ((file = fopen (filename, "r")) == NULL || fgets (buffer, 1024, file) == NULL)
        exit(1);
    while (fgets (buffer, 1024, file) != NULL) {
        if (buffer[0] == 'c' && buffer[1] == 'p' && buffer[2] == 'u' && buffer[3] == ' ' && buffer[4] == 'c' &&
            buffer[5] == 'o' && buffer[6] == 'r')
        {
            sscanf(buffer, "cpu cores\t: %d", &c);
            break;
        }
     //   printf("buffer says %s", buffer);

       // printf("(%d) number of cores \n \n ", c);


    }
    fclose(file);
  //  printf("(%d) number of cores \n \n ", c);
 //   ncpu = c;

    return c;
}
void cpu_percentage(int cpu_count,Cpu_usage *cpu_usage){



    float cpu_user[4];
    float cpu_system[4];
    unsigned  long user[4]={0,0,0,0};
    unsigned  long user_nice[4]={0,0,0,0};
    unsigned  long idle[4]={0,0,0,0};
    unsigned  long system[4]={0,0,0,0};
    float percentage[4]={0,0,0,0};


    int cpu_number1[4]={0,0,0,0};
    static unsigned long jiffies_system [4]={0,0,0,0}, jiffies_total [4]={0,0,0,0};
    static unsigned long jiffies_user[4]={0,0,0,0};
    static unsigned long jiffies_user_old [4]={0,0,0,0}, jiffies_system_old [4]={0,0,0,0}, jiffies_total_old [4]={0,0,0,0};;
     unsigned long test=0;
    FILE *file;
    char *filename = "/proc/stat";
    char buffer[1024];
    if ((file = fopen (filename, "r")) == NULL || fgets (buffer, 1024, file) == NULL)

        exit(1);
   // sscanf(buffer,"cpu%4d  %lu %lu %lu %lu",&cpu_number1[5],&user[5] , &user_nice[5], &system[5], &idle[5]);


    static int j=0;
  //  printf(" CPU buffer before:%s\n",buffer);
    while (fgets(buffer, 1024, file) != NULL) {
        if (buffer[0] != 'c' && buffer[1] != 'p' && buffer[2] != 'u')
            break;


   //     printf(" CPU buffer before2:%s\n",buffer);
     //   printf(" j %d\n",j);
        sscanf(buffer,"cpu%4d %lu %lu %lu %lu",&cpu_number1[j],&user[j] , &user_nice[j], &system[j], &idle[j]);
      //  printf("CPu number for the love of god %d %lu %lu %lu %lu",cpu_number1[j],user[j] , user_nice[j], system[j], idle[j]);
       // printf("CPUN:%d USER:%lu USER_NICE:%lu SYSTEM:%lu IDLE:%lu \n",cpu_number1[j],user[j] , user_nice[j], system[j], idle[j]);
       // printf(" CPU buffer::%s\n",buffer);
        j++;
        if (j==cpu_count){
            j=0;
            break;
        }

    }
    fclose (file);
  //  float cpu_percentage[4];

    for(int i=0 ; i< cpu_count;i++) {

     //   printf("Numbers do you see them %d %d \n",cpu_number1[i],i);
        jiffies_user_old[i] = jiffies_user[i];
        jiffies_system_old[i] = jiffies_system[i];
        jiffies_total_old[i] = jiffies_total[i];

        jiffies_user[i] = user[i] + user_nice[i];
        jiffies_system[i] = system[i];
        jiffies_total[i] = jiffies_user[i] + jiffies_system[i] + idle[i];


        cpu_user[i]= cpu_system[i]= 0.0;
        if (jiffies_total[i] > jiffies_total_old[i]) {
            jiffies_total_delta[i] = jiffies_total[i] - jiffies_total_old[i];
          //  printf("total deltaprvi%lu\n",  jiffies_total_delta[i]);
            test+=jiffies_total_delta[i];
            cpu_user[i] = (jiffies_user[i] - jiffies_user_old[i]) * 100 / (float) (jiffies_total_delta[i]);
           cpu_system[i] = (jiffies_system[i] - jiffies_system_old[i]) * 100 / (float) (jiffies_total_delta[i]);
        }

        percentage[i] =cpu_user[i] + cpu_system[i];









    }
    cpu_usage->percentage0 =percentage[0];
        cpu_usage->percentage1 =percentage[1];
        cpu_usage->percentage2 =percentage[2];
        cpu_usage->percentage3 =percentage[3];


    jiffies_total_delta[4]= jiffies_total_delta[0]+jiffies_total_delta[1]+jiffies_total_delta[2]+jiffies_total_delta[3];




}
#define SIZE 20

struct DataItem {
    unsigned  long data;
    unsigned int key;
};



int hashCode(int key) {
    return key % SIZE;
}

unsigned long search(unsigned int key,struct DataItem  *hashArray,int hash_size ,bool *ima, unsigned long data) {


    for(int hashIndex=0;hashIndex<hash_size;hashIndex++){

        if(hashArray[hashIndex].key==key){
            *ima=TRUE;
            printf("data in search %lu key %i\n", hashArray[hashIndex].data, hashArray[hashIndex].key);
            unsigned long temp =hashArray[hashIndex].data;
            hashArray[hashIndex].data=data;
            return temp;
//       // printf("data in search %lu key %lu\n",hashArray[hashIndex]->data,hashArray[hashIndex]->key);
        }


    }

    *ima=FALSE;
    return 0;
}

void insert(int key,unsigned long data,struct DataItem * * hashArray,int *hash_size) {

    struct DataItem *temp ;
 //   item->data = data;
  //  item->key = key;

    //get the hash
  //  int hashIndex = hashCode(key);
    int g=0;
    //move in array until an empty or deleted cell
    int hashIndex=0;
/*    for(  hashIndex;hashIndex<*hash_size;hashIndex++){
        if(hashArray[hashIndex]->key==key){

            hashArray[hashIndex]->data=data;
            printf("nadjen kljuc %d\n",key);
            break;
        }
        g++;

    }*/
    while(hashIndex<*hash_size){
        if(hashArray[hashIndex]->key==key){

            hashArray[hashIndex]->data=data;
            printf("nadjen kljuc %d\n",key);
            break;
        }
        hashIndex++;


    }
    if(hashIndex==*hash_size){
        temp=realloc(*hashArray,( /**j*/ *hash_size+2)*sizeof(struct DataItem));
        if ( temp != NULL ) {
            *hashArray=temp;
        } else {
            free(hashArray);
        }
          hashArray[hashIndex]->data = data;
   hashArray[hashIndex]->key = key;
        *hash_size=hashIndex+1;
    }



  /*  hashArray[hashIndex]->data = data;
    hashArray[hashIndex]->key = key;*/
}
/*
struct DataItem* delete(struct DataItem* item) {
    int key = item->key;

    //get the hash
    int hashIndex = hashCode(key);

    //move in array until an empty
    while(hashArray[hashIndex] != NULL) {

        if(hashArray[hashIndex]->key == key) {
            struct DataItem* temp = hashArray[hashIndex];

            //assign a dummy item at deleted position
            hashArray[hashIndex] = dummyItem;
            return temp;
        }

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }

    return NULL;
}*/
/*
void display() {
    int i = 0;

    for(i = 0; i<SIZE; i++) {

        if(hashArray[i] != NULL)
            printf(" (%d,%d)",hashArray[i]->key,hashArray[i]->data);
        else
            printf(" ~~ ");
    }

    printf("\n");
}*/

/*int main() {
    dummyItem = (struct DataItem*) malloc(sizeof(struct DataItem));
    dummyItem->data = -1;
    dummyItem->key = -1;

    insert(1, 20);
    insert(2, 70);
    insert(42, 80);
    insert(4, 25);
    insert(12, 44);
    insert(14, 32);
    insert(17, 11);
    insert(13, 78);
    insert(37, 97);

  //  display();
 //   item = search(37);

    if(item != NULL) {
        printf("Element found: %d\n", item->data);
    } else {
        printf("Element not found\n");
    }

    delete(item);
  //  item = search(37);

    if(item != NULL) {
        printf("Element found: %d\n", item->data);
    } else {
        printf("Element not found\n");
    }
}*/

void
get_cpu_percent (unsigned int pid, unsigned long jiffies_user, float *cpu_user, unsigned long jiffies_system, float *cpu_system)
{
    static struct DataItem *hash_cpu_user = NULL;
    static struct DataItem *hash_cpu_system = NULL;
    unsigned  long jiffies_user_old=0, jiffies_system_old=0;
    static int hash_size=0;
    static int fluffy=1;
    bool ima= FALSE;
    if (hash_cpu_user == NULL)
    {
        hash_cpu_user  = (struct DataItem*) malloc(sizeof(struct DataItem));
        hash_cpu_system = (struct DataItem*) malloc(sizeof(struct DataItem));
        hash_size++;
    }
    printf("search\n");
       jiffies_user_old =search(pid,hash_cpu_user,hash_size,&ima,jiffies_user);
    jiffies_system_old = search(pid,hash_cpu_system,hash_size,&ima,jiffies_system);



        if(ima==FALSE){

            hash_size++;
            struct DataItem * temp=realloc(hash_cpu_user,( /**j*/ hash_size+1)*sizeof(struct DataItem));
            struct DataItem * temp1=realloc(hash_cpu_system,( /**j*/ hash_size+1)*sizeof(struct DataItem));

            if ( temp != NULL && temp1!=NULL ) {
                hash_cpu_user=temp;
                hash_cpu_system=temp1;
                printf("povecali smo niz\n");

            } else {
                free(hash_cpu_user);
                free(hash_cpu_system);
            }

            //postavljamo novi hash na nulu
            if(hash_cpu_user[hash_size-1].data!=0 ||hash_cpu_system[hash_size-1].data!=0||hash_cpu_user[hash_size-1].key!=0|| hash_cpu_system[hash_size-1].key!=0 ){

                hash_cpu_user[hash_size-1].data = 0;
                hash_cpu_system[hash_size-1].data =0;
                hash_cpu_user[hash_size-1].key = 0;
                hash_cpu_system[hash_size-1].key = 0;
            }
            hash_cpu_user[hash_size-1].data = jiffies_user;
            hash_cpu_system[hash_size-1].data = jiffies_system;
            hash_cpu_user[hash_size-1].key = pid;
            hash_cpu_system[hash_size-1].key = pid;

        }





    //insert(pid,jiffies_user,&hash_cpu_user,&hash_size);


  //  g_hash_table_insert (hash_cpu_user, GUINT_TO_POINTER (pid), GUINT_TO_POINTER (jiffies_user));
  //  g_hash_table_insert (hash_cpu_system, GUINT_TO_POINTER (pid), GUINT_TO_POINTER (jiffies_system));

    if (jiffies_user < jiffies_user_old || jiffies_system < jiffies_system_old)
        return;

    // if (_cpu_count > 0 && jiffies_total_delta > 0)
    if (jiffies_total_delta[4] > 0)
    {

        *cpu_user = (jiffies_user - jiffies_user_old) * 100 / (float)jiffies_total_delta[4];
        *cpu_system = (jiffies_system - jiffies_system_old) * 100 / (float)jiffies_total_delta[4];
        // printf("total  Delta final %lu user %f system %f \n",jiffies_total_delta[4],*cpu_user,*cpu_system);
    }
    else
    {
        *cpu_user = *cpu_system = 0;
    }

}