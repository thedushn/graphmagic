//
// Created by dushn on 4.8.17..
//

#include <inttypes.h>
#include "cpu_usage.h"


static struct DataItem *hash_cpu_user = NULL;
static struct DataItem *hash_cpu_system = NULL;


//void cpu_number (){
int cpu_number() {

    int c = 1; //cpu number must be at least zero
    FILE *file;
    char *filename = "/proc/cpuinfo";
    char buffer[1024];
    char *buffer2 = "processor";

    if ((file = fopen(filename, "r")) == NULL || fgets(buffer, 1024, file) == NULL)
        exit(1);
    while (fgets(buffer, 1024, file) != NULL) {
        if (strncmp(buffer2, buffer, strlen(buffer2)) == 0) {
            // sscanf(buffer, "cpu cores\t: %d", &c);
            // break;
            c++;
        }
        //  printf("buffer says %s", buffer);

        // printf("(%d) number of cores \n \n ", c);


    }
    fclose(file);
    printf("(%d) number of cores \n \n ", c);
    //   ncpu = c;

    return c;
}

void cpu_percentage(int cpu_count, Cpu_usage *cpu_usage) {


    float cpu_user[4];
    float cpu_system[4];
    __uint64_t user[4] = {0, 0, 0, 0};
    __uint64_t user_nice[4] = {0, 0, 0, 0};
    __uint64_t idle[4] = {0, 0, 0, 0};
    __uint64_t system[4] = {0, 0, 0, 0};
    float percentage[4] = {0, 0, 0, 0};


    int cpu_number1[4] = {0, 0, 0, 0};
    static __uint64_t jiffies_system[4] = {0, 0, 0, 0}, jiffies_total[4] = {0, 0, 0, 0};
    static __uint64_t jiffies_user[4] = {0, 0, 0, 0};
    static __uint64_t jiffies_user_old[4] = {0, 0, 0, 0}, jiffies_system_old[4] = {0, 0, 0, 0}, jiffies_total_old[4] = {
            0, 0, 0, 0};

    FILE *file;
    char *filename = "/proc/stat";
    char *name_test = "cpu";
    char buffer[1024];
    if ((file = fopen(filename, "r")) == NULL || fgets(buffer, 1024, file) == NULL)

        exit(1);
    // sscanf(buffer,"cpu%4d  %lu %lu %lu %lu",&cpu_number1[5],&user[5] , &user_nice[5], &system[5], &idle[5]);


    static int j = 0;
    //  printf(" CPU buffer before:%s\n",buffer);
    while (fgets(buffer, 1024, file) != NULL) {
        // if (buffer[0] != 'c' && buffer[1] != 'p' && buffer[2] != 'u')
        if (strncmp(buffer, name_test, strlen(name_test)) != 0) {

            break;

        }



        //     printf(" CPU buffer before2:%s\n",buffer);
        //   printf(" j %d\n",j);
        sscanf(buffer, "cpu%4d %" SCNu64 " %" SCNu64 " %" SCNu64 " %" SCNu64 "", &cpu_number1[j], &user[j],
               &user_nice[j], &system[j], &idle[j]);
        //  printf("CPu number for the love of god %d %lu %lu %lu %lu",cpu_number1[j],user[j] , user_nice[j], system[j], idle[j]);
        // printf("CPUN:%d USER:%lu USER_NICE:%lu SYSTEM:%lu IDLE:%lu \n",cpu_number1[j],user[j] , user_nice[j], system[j], idle[j]);
        // printf(" CPU buffer::%s\n",buffer);
        j++;
        if (j == cpu_count) {
            j = 0;
            break;
        }

    }
    fclose(file);
    //  float cpu_percentage[4];

    for (int i = 0; i < cpu_count; i++) {

        //   printf("Numbers do you see them %d %d \n",cpu_number1[i],i);
        jiffies_user_old[i] = jiffies_user[i];
        jiffies_system_old[i] = jiffies_system[i];
        jiffies_total_old[i] = jiffies_total[i];

        jiffies_user[i] = user[i] + user_nice[i];
        jiffies_system[i] = system[i];
        jiffies_total[i] = jiffies_user[i] + jiffies_system[i] + idle[i];


        cpu_user[i] = cpu_system[i] = 0.0;
        if (jiffies_total[i] > jiffies_total_old[i]) {
            jiffies_total_delta[i] = jiffies_total[i] - jiffies_total_old[i];
            //  printf("total deltaprvi%lu\n",  jiffies_total_delta[i]);

            cpu_user[i] = (jiffies_user[i] - jiffies_user_old[i]) * 100 / (float) (jiffies_total_delta[i]);
            cpu_system[i] = (jiffies_system[i] - jiffies_system_old[i]) * 100 / (float) (jiffies_total_delta[i]);
        }

        percentage[i] = cpu_user[i] + cpu_system[i];


    }


    if (sprintf(cpu_usage->percentage0, "%f", percentage[0]) < 0) {

        printf("nije uspelo convertovanje %s \n", cpu_usage->percentage0);
    }
    if (sprintf(cpu_usage->percentage1, "%f", percentage[1]) < 0) {

        printf("nije uspelo convertovanje %s \n", cpu_usage->percentage1);
    }
    if (sprintf(cpu_usage->percentage2, "%f", percentage[2]) < 0) {

        printf("nije uspelo convertovanje %s \n", cpu_usage->percentage2);
    }
    if (sprintf(cpu_usage->percentage3, "%f", percentage[3]) < 0) {

        printf("nije uspelo convertovanje %s \n", cpu_usage->percentage3);
    }


    jiffies_total_delta[4] =
            jiffies_total_delta[0] + jiffies_total_delta[1] + jiffies_total_delta[2] + jiffies_total_delta[3];


}


__uint64_t search(unsigned int key, struct DataItem *hashArray, int hash_size, bool *ima, __uint64_t data) {

    //   printf("enter %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);
    for (int hashIndex = 0; hashIndex < hash_size; hashIndex++) {

        if (hashArray[hashIndex].key == key) {
            *ima = true;
            //    printf("data in search %lu key %i\n", hashArray[hashIndex].data, hashArray[hashIndex].key);
            __uint64_t temp = hashArray[hashIndex].data;
            hashArray[hashIndex].data = data;
            return temp;
//       // printf("data in search %lu key %lu\n",hashArray[hashIndex]->data,hashArray[hashIndex]->key);
        }


    }
    //  printf("exit %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);
    // *ima=false;
    return 0;
}


void
get_cpu_percent(unsigned int pid, __uint64_t jiffies_user, float *cpu_user, __uint64_t jiffies_system,
                float *cpu_system) {
    //   printf("enter %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);
    __uint64_t jiffies_user_old = 0, jiffies_system_old = 0;
    static int hash_size = 0;

    bool ima = false;
    if (hash_cpu_user == NULL) {
        hash_cpu_user = (struct DataItem *) malloc(sizeof(struct DataItem));
        hash_cpu_system = (struct DataItem *) malloc(sizeof(struct DataItem));
        hash_size++;
    }
    //  printf("search\n");
    jiffies_user_old = search(pid, hash_cpu_user, hash_size, &ima, jiffies_user);
    jiffies_system_old = search(pid, hash_cpu_system, hash_size, &ima, jiffies_system);


    if (ima == false) {
        //     printf(">>>1\n");

        struct DataItem *temp = realloc(hash_cpu_user, ( /**j*/ hash_size + 1) * sizeof(struct DataItem));
        struct DataItem *temp1 = realloc(hash_cpu_system, ( /**j*/ hash_size + 1) * sizeof(struct DataItem));
        //     printf(">>>2\n");
        hash_size++;
        if (temp != NULL) {
            hash_cpu_user = temp;
        } else {
            free(hash_cpu_user);

        }
        if (temp1 != NULL) {
            hash_cpu_system = temp1;


        } else {
            free(hash_cpu_system);
        }
        //  printf(">>>3\n");
        //postavljamo novi hash na nulu
        if (hash_cpu_user[hash_size - 1].data != 0 || hash_cpu_system[hash_size - 1].data != 0 ||
            hash_cpu_user[hash_size - 1].key != 0 || hash_cpu_system[hash_size - 1].key != 0) {

            hash_cpu_user[hash_size - 1].data = 0;
            hash_cpu_system[hash_size - 1].data = 0;
            hash_cpu_user[hash_size - 1].key = 0;
            hash_cpu_system[hash_size - 1].key = 0;
            //     printf(">>>4\n");
        }
        //      printf(">>>5\n");
        hash_cpu_user[hash_size - 1].data = jiffies_user;
        hash_cpu_system[hash_size - 1].data = jiffies_system;
        hash_cpu_user[hash_size - 1].key = pid;
        hash_cpu_system[hash_size - 1].key = pid;
        //   printf(">>>6\n");
    }





    //  printf(">>>7\n");
    if (jiffies_user < jiffies_user_old || jiffies_system < jiffies_system_old) {
        //     printf("leave %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);
        return;
    }
    // if (_cpu_count > 0 && jiffies_total_delta > 0)
    if (jiffies_total_delta[4] > 0) {
        //     printf(">>>8  cpu_user=%p  cpu_system=%p\n",cpu_user,cpu_system);
        // float f1,f2;
        // f1=((float)((float)jiffies_user - (float)jiffies_user_old) * 100.) / ((float)(jiffies_total_delta[4]));
        *cpu_user = (float) (((((float) jiffies_user) - ((float) jiffies_user_old)) * 100.) /
                             ((float) (jiffies_total_delta[4])));
        *cpu_system = ((jiffies_system - jiffies_system_old) * 100) / (float) jiffies_total_delta[4];
        //    printf (">>>> f1=%f f2=%f\n",f1,f2);
        // *cpu_user =f1;
        // *cpu_system =f2;
        //*cpu_user=(float) (((((float)jiffies_user) - ((float)jiffies_user_old)) * 100.) / ((float)(jiffies_total_delta[4])));

        //   printf(">>>9\n");
        // printf("total  Delta final %lu user %f system %f \n",jiffies_total_delta[4],*cpu_user,*cpu_system);
    } else {
        //    printf(">>>10\n");
        *cpu_user = *cpu_system = 0;
        //    printf(">>>11\n");
    }
    //  printf("leave %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);
}

void uradi(bool clean) {

    if (clean == true) {

        if (hash_cpu_user != NULL) {
            free(hash_cpu_user);

        }
        if (hash_cpu_system != NULL) {
            free(hash_cpu_system);

        }

    }

}