#include <inttypes.h>
#include"stdio.h"
#include"stdlib.h"

#include"sys/socket.h"

#include"pthread.h"


#include "functions.h"
#include "interrupts.h"
#include "cpu_usage.h"

#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
// macros for packing floats and doubles:
#define pack754_16(f) (pack754((f), 16, 5))
#define pack754_32(f) (pack754((f), 32, 8))
#define pack754_64(f) (pack754((f), 64, 11))
#define unpack754_16(i) (unpack754((i), 16, 5))
#define unpack754_32(i) (unpack754((i), 32, 8))
#define unpack754_64(i) (unpack754((i), 64, 11))

/*
** pack754() -- pack a floating point number into IEEE-754 format
*/
unsigned long long int pack754(long double f, unsigned bits, unsigned expbits)
{
    long double fnorm;
    int shift;
    long long sign, exp, significand;
    unsigned significandbits = bits - expbits - 1; // -1 for sign bit

    if (f == 0.0) return 0; // get this special case out of the way

    // check sign and begin normalization
    if (f < 0) { sign = 1; fnorm = -f; }
    else { sign = 0; fnorm = f; }

    // get the normalized form of f and track the exponent
    shift = 0;
    while(fnorm >= 2.0) { fnorm /= 2.0; shift++; }
    while(fnorm < 1.0) { fnorm *= 2.0; shift--; }
    fnorm = fnorm - 1.0;

    // calculate the binary form (non-float) of the significand data
    significand = fnorm * ((1LL<<significandbits) + 0.5f);

    // get the biased exponent
    exp = shift + ((1<<(expbits-1)) - 1); // shift + bias

    // return the final answer
    return (sign<<(bits-1)) | (exp<<(bits-expbits-1)) | significand;
}

/*
** unpack754() -- unpack a floating point number from IEEE-754 format
*/
long double unpack754(unsigned long long int i, unsigned bits, unsigned expbits)
{
    long double result;
    long long shift;
    unsigned bias;
    unsigned significandbits = bits - expbits - 1; // -1 for sign bit

    if (i == 0) return 0.0;

    // pull the significand
    result = (i&((1LL<<significandbits)-1)); // mask
    result /= (1LL<<significandbits); // convert back to float
    result += 1.0f; // add the one back on

    // deal with the exponent
    bias = (1<<(expbits-1)) - 1;
    shift = ((i>>significandbits)&((1LL<<expbits)-1)) - bias;
    while(shift > 0) { result *= 2.0; shift--; }
    while(shift < 0) { result /= 2.0; shift++; }

    // sign it
    result *= (i>>(bits-1))&1? -1.0: 1.0;

    return result;
}

/*
** packi16() -- store a 16-bit int into a char buffer (like htons())
*/
void packi16(unsigned char *buf, unsigned int i)
{
    *buf++ = i>>8; *buf++ = i;
}

/*
** packi32() -- store a 32-bit int into a char buffer (like htonl())
*/
void packi32(unsigned char *buf, unsigned long int i)
{
    *buf++ = i>>24; *buf++ = i>>16;
    *buf++ = i>>8;  *buf++ = i;
}

/*
** packi64() -- store a 64-bit int into a char buffer (like htonl())
*/
void packi64(unsigned char *buf, unsigned long long int i)
{
    *buf++ = i>>56; *buf++ = i>>48;
    *buf++ = i>>40; *buf++ = i>>32;
    *buf++ = i>>24; *buf++ = i>>16;
    *buf++ = i>>8;  *buf++ = i;
}

/*
** unpacki16() -- unpack a 16-bit int from a char buffer (like ntohs())
*/
int unpacki16(unsigned char *buf)
{
    unsigned int i2 = ((unsigned int)buf[0]<<8) | buf[1];
    int i;

    // change unsigned numbers to signed
    if (i2 <= 0x7fffu) { i = i2; }
    else { i = -1 - (unsigned int)(0xffffu - i2); }

    return i;
}

/*
** unpacku16() -- unpack a 16-bit unsigned from a char buffer (like ntohs())
*/
unsigned int unpacku16(unsigned char *buf)
{
    return ((unsigned int)buf[0]<<8) | buf[1];
}

/*
** unpacki32() -- unpack a 32-bit int from a char buffer (like ntohl())
*/
long int unpacki32(unsigned char *buf)
{
    unsigned long int i2 = ((unsigned long int)buf[0]<<24) |
                           ((unsigned long int)buf[1]<<16) |
                           ((unsigned long int)buf[2]<<8)  |
                           buf[3];
    long int i;

    // change unsigned numbers to signed
    if (i2 <= 0x7fffffffu) { i = i2; }
    else { i = -1 - (long int)(0xffffffffu - i2); }

    return i;
}

/*
** unpacku32() -- unpack a 32-bit unsigned from a char buffer (like ntohl())
*/
unsigned long int unpacku32(unsigned char *buf)
{
    return ((unsigned long int)buf[0]<<24) |
           ((unsigned long int)buf[1]<<16) |
           ((unsigned long int)buf[2]<<8)  |
           buf[3];
}

/*
** unpacki64() -- unpack a 64-bit int from a char buffer (like ntohl())
*/
long long int unpacki64(unsigned char *buf)
{
    unsigned long long int i2 = ((unsigned long long int)buf[0]<<56) |
                                ((unsigned long long int)buf[1]<<48) |
                                ((unsigned long long int)buf[2]<<40) |
                                ((unsigned long long int)buf[3]<<32) |
                                ((unsigned long long int)buf[4]<<24) |
                                ((unsigned long long int)buf[5]<<16) |
                                ((unsigned long long int)buf[6]<<8)  |
                                buf[7];
    long long int i;

    // change unsigned numbers to signed
    if (i2 <= 0x7fffffffffffffffu) { i = i2; }
    else { i = -1 -(long long int)(0xffffffffffffffffu - i2); }

    return i;
}

/*
** unpacku64() -- unpack a 64-bit unsigned from a char buffer (like ntohl())
*/
unsigned long long int unpacku64(unsigned char *buf)
{
    return ((unsigned long long int)buf[0]<<56) |
           ((unsigned long long int)buf[1]<<48) |
           ((unsigned long long int)buf[2]<<40) |
           ((unsigned long long int)buf[3]<<32) |
           ((unsigned long long int)buf[4]<<24) |
           ((unsigned long long int)buf[5]<<16) |
           ((unsigned long long int)buf[6]<<8)  |
           buf[7];
}

/*
** pack() -- store data dictated by the format string in the buffer
**
**   bits |signed   unsigned   float   string
**   -----+----------------------------------
**      8 |   c        C
**     16 |   h        H         f
**     32 |   l        L         d
**     64 |   q        Q         g
**      - |                               s
**
**  (16-bit unsigned length is automatically prepended to strings)
*/

unsigned int pack(unsigned char *buf, char *format, ...)
{
    va_list ap;

    signed char c;              // 8-bit
    unsigned char C;

    int h;                      // 16-bit
    unsigned int H;

    long int l;                 // 32-bit
    unsigned long int L;

    long long int q;            // 64-bit
    unsigned long long int Q;

    float f;                    // floats
    double d;
    long double g;
    unsigned long long int fhold;

    char *s;                    // strings
    unsigned int len;

    unsigned int size = 0;

    va_start(ap, format);

    for(; *format != '\0'; format++) {
        switch(*format) {
            case 'c': // 8-bit
                size += 1;
                c = (signed char)va_arg(ap, int); // promoted
                *buf++ = c;
                break;

            case 'C': // 8-bit unsigned
                size += 1;
                C = (unsigned char)va_arg(ap, unsigned int); // promoted
                *buf++ = C;
                break;

            case 'h': // 16-bit
                size += 2;
                h = va_arg(ap, int);
                packi16(buf, h);
                buf += 2;
                break;

            case 'H': // 16-bit unsigned
                size += 2;
                H = va_arg(ap, unsigned int);
                packi16(buf, H);
                buf += 2;
                break;

            case 'l': // 32-bit
                size += 4;
                l = va_arg(ap, long int);
                packi32(buf, l);
                buf += 4;
                break;

            case 'L': // 32-bit unsigned
                size += 4;
                L = va_arg(ap, unsigned long int);
                packi32(buf, L);
                buf += 4;
                break;

            case 'q': // 64-bit
                size += 8;
                q = va_arg(ap, long long int);
                packi64(buf, q);
                buf += 8;
                break;

            case 'Q': // 64-bit unsigned
                size += 8;
                Q = va_arg(ap, unsigned long long int);
                packi64(buf, Q);
                buf += 8;
                break;

            case 'f': // float-16
                size += 2;
                f = (float)va_arg(ap, double); // promoted
                fhold = pack754_16(f); // convert to IEEE 754
                packi16(buf, fhold);
                buf += 2;
                break;

            case 'd': // float-32
                size += 4;
                d = va_arg(ap, double);
                fhold = pack754_32(d); // convert to IEEE 754
                packi32(buf, fhold);
                buf += 4;
                break;

            case 'g': // float-64
                size += 8;
                g = va_arg(ap, long double);
                fhold = pack754_64(g); // convert to IEEE 754
                packi64(buf, fhold);
                buf += 8;
                break;

            case 's': // string
                s = va_arg(ap, char*);
                len = strlen(s);
                size += len + 2;
                packi16(buf, len);
                buf += 2;
                memcpy(buf, s, len);
                buf += len;
                break;
        }
    }

    va_end(ap);

    return size;
}

/*
** unpack() -- unpack data dictated by the format string into the buffer
**
**   bits |signed   unsigned   float   string
**   -----+----------------------------------
**      8 |   c        C
**     16 |   h        H         f
**     32 |   l        L         d
**     64 |   q        Q         g
**      - |                               s
**
**  (string is extracted based on its stored length, but 's' can be
**  prepended with a max length)
*/
void unpack(unsigned char *buf, char *format, ...)
{
    va_list ap;

    signed char *c;              // 8-bit
    unsigned char *C;

    int *h;                      // 16-bit
    unsigned int *H;

    long int *l;                 // 32-bit
    unsigned long int *L;

    long long int *q;            // 64-bit
    unsigned long long int *Q;

    float *f;                    // floats
    double *d;
    long double *g;
    unsigned long long int fhold;

    char *s;
    unsigned int len, maxstrlen=0, count;

    va_start(ap, format);

    for(; *format != '\0'; format++) {
        switch(*format) {
            case 'c': // 8-bit
                c = va_arg(ap, signed char*);
                if (*buf <= 0x7f) { *c = *buf;} // re-sign
                else { *c = -1 - (unsigned char)(0xffu - *buf); }
                buf++;
                break;

            case 'C': // 8-bit unsigned
                C = va_arg(ap, unsigned char*);
                *C = *buf++;
                break;

            case 'h': // 16-bit
                h = va_arg(ap, int*);
                *h = unpacki16(buf);
                buf += 2;
                break;

            case 'H': // 16-bit unsigned
                H = va_arg(ap, unsigned int*);
                *H = unpacku16(buf);
                buf += 2;
                break;

            case 'l': // 32-bit
                l = va_arg(ap, long int*);
                *l = unpacki32(buf);
                buf += 4;
                break;

            case 'L': // 32-bit unsigned
                L = va_arg(ap, unsigned long int*);
                *L = unpacku32(buf);
                buf += 4;
                break;

            case 'q': // 64-bit
                q = va_arg(ap, long long int*);
                *q = unpacki64(buf);
                buf += 8;
                break;

            case 'Q': // 64-bit unsigned
                Q = va_arg(ap, unsigned long long int*);
                *Q = unpacku64(buf);
                buf += 8;
                break;

            case 'f': // float
                f = va_arg(ap, float*);
                fhold = unpacku16(buf);
                *f = unpack754_16(fhold);
                buf += 2;
                break;

            case 'd': // float-32
                d = va_arg(ap, double*);
                fhold = unpacku32(buf);
                *d = unpack754_32(fhold);
                buf += 4;
                break;

            case 'g': // float-64
                g = va_arg(ap, long double*);
                fhold = unpacku64(buf);
                *g = unpack754_64(fhold);
                buf += 8;
                break;

            case 's': // string
                s = va_arg(ap, char*);
                len = unpacku16(buf);
                buf += 2;
                if (maxstrlen > 0 && len > maxstrlen) count = maxstrlen - 1;
                else count = len;
                memcpy(s, buf, count);
                s[count] = '\0';
                buf += len;
                break;

            default:
                if (isdigit(*format)) { // track max str len
                    maxstrlen = maxstrlen * 10 + (*format-'0');
                }
        }

        if (!isdigit(*format)) maxstrlen = 0;
    }

    va_end(ap);
}


#define BUF_SIZE 2000

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t   cond = PTHREAD_COND_INITIALIZER;


//int rezultat =1;
bool devices_show=false;

void send_prio_to_task(char *task_id, char *signal)
{
    int prio=0;
    if(strcmp(signal,"VERY_LOW")==0){
        prio = 15;

    }
    if(strcmp(signal,"LOW")==0){
        prio = 5;

    }
    if(strcmp(signal,"NORMAL")==0){
        prio = 0;

    }
    if(strcmp(signal,"VERY_HIGH")==0){
        prio = -15;

    }
    if(strcmp(signal,"HIGH")==0){
        prio = -5;

    }


    char str[4];

    sprintf(str,"%d",prio);
    char command[64] = "renice -n ";
    strncat(command,str, sizeof command);
    strncat(command," -p ", sizeof command);
    strncat(command,task_id, sizeof command);
    printf("COMMAND %s\n",command);
    if(system(command) != 0){

        printf("comand failed\n");
    }

    //return (res== 0 ) ? TRUE : FALSE;

}
void send_signal_to_task(char *task_id, char *signal)
{
    printf("SIGNAL %s the task with ID %s\n", signal, task_id);
    if(task_id != NULL && signal != NULL)
    {
        char command[64] = "kill -";
        strncat(command,signal, sizeof command);
        strncat(command," ", sizeof command);
        strncat(command,task_id, sizeof command);
        printf("Task id %s",task_id);
        if(system(command) != 0)
            printf("comand failed\n");
//            xfce_err("Couldn't %s the task with ID %s", signal, task_id);
    }
}
void *accept_c(void *socket){
    printf("usli smo u accpet\n");
    struct	my_thread_info *info = socket;
   /*static*/ int rezultat ;
/*    char buffer[BUF_SIZE];
    gboolean res=FALSE;*/
   // data_s data;
  /*  struct Commands{

       int mem;
        gboolean show;
        gchar command [10];
        gchar task_id [256];
    }stuff;*/
    Commands commands;

    while (1) {
     //  pthread_mutex_lock (&m);
       /* info = malloc(sizeof(struct my_thread_info));
        info->thread_socket= *(int*)socket;*/
       int ret = (int )recv(info->thread_socket, &commands, sizeof(Commands), MSG_WAITALL);
        if(ret<0){
            printf("error condition didnt get received\n");
            //exit(1);
            pthread_cancel(t2);
            pthread_exit(&ret);
        }
        printf("ret accept  %d \n",ret);
       rezultat=commands.mem;
        devices_show=commands.show;

        printf("sHOW %s\n", commands.show==true ? "TRUE" : "FALSE");
        printf("SHOW %s\n", devices_show==true ? "TRUE" : "FALSE");

        printf("command %s\n ",commands.command);
        printf("id %s\n ",commands.task_id);

        if(strcmp(commands.task_id, "") != 0 && strcmp(commands.command, "") != 0){
            if(strcmp(commands.command, "STOP") == 0 ||
                    strcmp(commands.command, "CONT") == 0 ||
                    strcmp(commands.command, "KILL") == 0 ||
                    strcmp(commands.command, "TERM") == 0){
                send_signal_to_task(commands.task_id,commands.command);
            }
            else{

               /*res= */ send_prio_to_task(commands.task_id,commands.command);
            }
           // printf("DA li smo uspeli %s\n", res==TRUE ? "TRUE" : "FALSE");
        }
        if(rezultat==0){
         //   pthread_cond_wait(&cond,&m);
          //  rezultat=1;
          //  free(info);
            pthread_cond_signal(&cond);
          //  pthread_mutex_unlock (&m);
           printf("condition WAS met\n");

       }// else{

           // free(info);
       //     pthread_cond_signal(&cond);
         //   printf("condition signal was sent\n");
       // }

      //  pthread_mutex_unlock (&m);

    }

};



void *slanje(void *socket){

    int  ret=0;

    printf("usli smo u slanje\n");
        //unsigned int num_packets;

    time_t time1;
    static struct	my_thread_info *info;
    Task *task_array=NULL;
    Interrupts  *interrupts=NULL;
    Devices  *devices=NULL;

   // char buffer[1024];

    data_s data;

    while(1) {

        Memory_usage memory_usage={0};
        Cpu_usage cpu_usage={0} ;
        Network network={0};
        info = malloc(sizeof(struct my_thread_info));
        info->thread_socket= *(int*)socket;
//        if(rezultat==1){
//            pthread_cond_wait(&cond,&m);
//            printf("condition WAS met\n");
//        }


       // data.memory_usage.memory_percentage=0;
        data.memory_usage.memory_used=0;
        data.memory_usage.swap_total=0;
      //  data.memory_usage.swap_percentage=0;
        data.memory_usage.memory_total=0;
        data.memory_usage.swap_used=0;

        get_memory_usage(&memory_usage);
        time1 = time(NULL);
        /*    struct tm*/
  lokalno = *localtime(&time1);
        /*
//        if(rezultat==0){
//            pthread_cond_wait(&cond,&m);
//           printf("condtion was met\n");
//       }
*/
/*        char buffer[1400];

        memset(buffer,0,sizeof(buffer));
            sprintf(buffer, "%"PRIu64 "%"PRIu64 "%"PRIu64 "%"PRIu64
                    ,memory_usage.swap_used
                    ,memory_usage.swap_total
                    ,memory_usage.memory_used
                    ,memory_usage.memory_total
            );
        strcat(buffer,memory_usage.swap_percentage);
        strcat(buffer,memory_usage.memory_percentage);*/



        ret = (int) send(info->thread_socket, &memory_usage, sizeof(Memory_usage), 0);

        if (ret < 0) {
            printf("Error sending data!\n\t");
              break;
            pthread_cancel(t3);
            pthread_exit(&ret);
        } else {
            printf("ret %d \n",ret);

            /*    ret=(int)recv(info->thread_socket, &buffer, sizeof(buffer), 0);
            if (ret < 0) {
                printf("Error sending data!\n\t");
                break;
                pthread_cancel(t3);
                pthread_exit(&ret);
            }
            printf("ret %d buffer : %s \n",ret,buffer*//*==true ? "TRUE" : "FALSE"*//*);*/
            printf(" sending data!\n\t Memory Swap[%s] %" SCNu64 " %" SCNu64 "  %" SCNu64 " Memory[%s]\n"
                    ,memory_usage.swap_percentage
                    , memory_usage.swap_used
                    ,memory_usage.memory_total
                    , memory_usage.memory_used
                    , memory_usage.memory_percentage
            );

        }


        __int32_t h=0;

        interrupt_usage2(&interrupts,&h);



        __int32_t j=h;

        printf("BROJ INT %d \n",j);
        ret = (int) send(info->thread_socket, &j, sizeof(__int32_t), 0);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");
              break;
            pthread_cancel(t3);
            pthread_exit(&ret);
        }
        for(int r=0;r<h;r++){

        /*    printf("hello[%s %" SCNu64 " %" SCNu64 " %" SCNu64 " %" SCNu64 " %s %s %s %s]\n",interrupts[r].name, interrupts[r].CPU0, interrupts[r].CPU1,
                   interrupts[r].CPU2,
                   interrupts[r].CPU3,
                   interrupts[r].ime1,
                   interrupts[r].ime2,
                   interrupts[r].ime3,
                   interrupts[r].ime4 );*/
            ret = (int) send(info->thread_socket, &interrupts[r], sizeof(Interrupts), 0);


            if (ret < 0) {
                printf("Error sending data!\n\t");
                  break;
                pthread_cancel(t3);
                pthread_exit(&ret);
            }
            printf("return value of Interrupts ret: %d number of send %d  \n",ret,r );

        }









        __int32_t cpu_num= cpu_number();
          cpu_percentage(cpu_num,&cpu_usage);

            ret = (int) send(info->thread_socket, &cpu_usage, sizeof(Cpu_usage), 0);
            if (ret < 0) {
                printf("Error sending data!\n\t");
                  break;
                pthread_cancel(t3);
                pthread_exit(&ret);
            } else {
             //   printf("CPU usage %s %s %s %s  \n", cpu_usage.percentage0,cpu_usage.percentage1,cpu_usage.percentage2,cpu_usage.percentage3);

            }





       int niz_task=0;
        get_task_list(&task_array,&niz_task);
      //  num_packets = task_list->len;
      //  int broj_koji_treba_promenit=(int)num_packets;
        __int32_t niz_temp= (__int32_t) niz_task;
       ret = (int) send(info->thread_socket, &niz_temp, sizeof(__int32_t), 0);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");

            break;
            pthread_cancel(t3);
            pthread_exit(&ret);
        }
        for (int i = 0; i < niz_task; i++) {


            size_t g = strlen(task_array[i].name);
            for (int r = 0; r <= g; r++) {

                data.task.name[r] = task_array[i].name[r];

            }
            g = strlen(task_array[i].state);
            for (int r = 0; r <= g; r++) {

                data.task.state[r] = task_array[i].state[r];

            }
            g = strlen(task_array[i].uid_name);
            for (int r = 0; r <= g; r++) {

                data.task.uid_name[r] = task_array[i].uid_name[r];

            }
            data.task.uid = task_array[i].uid;
         //   data.task.cpu_system = task_array[i].cpu_system;
          //  data.task.cpu_user = task_array[i].cpu_user;
            data.task.vsz = task_array[i].vsz;
            data.task.rss = task_array[i].rss;
            data.task.prio = task_array[i].prio;

            data.task.pid = task_array[i].pid;
            data.task.ppid = task_array[i].ppid;
          /*  data.task.start_time = task_array[i].start_time;
            data.task.duration.tm_sec = task_array[i].duration.tm_sec;
            data.task.duration.tm_min = task_array[i].duration.tm_min;
            data.task.duration.tm_hour = task_array[i].duration.tm_hour;
            data.task.stime.tm_sec = task_array[i].stime.tm_sec;
            data.task.stime.tm_min = task_array[i].stime.tm_min;
            data.task.stime.tm_hour = task_array[i].stime.tm_hour;*/
       /*     printf("vreme trajanja rada %d %d %d\n", data.task.duration.tm_hour,
                   data.task.duration.tm_min,
                   data.task.duration.tm_sec);
            printf("start time %d %d %d\n", data.task.stime.tm_hour,
                   data.task.stime.tm_min,
                   data.task.stime.tm_sec);
            printf("Name [%s]  checked [%hu] pid [%d] start_time[%" SCNu64 "] prio [%d] %" SCNu64 " %" SCNu64 " %d %d %s %s [%s] [%s]\n",
                   data.task.name, data.task.checked, data.task.pid, data.task.start_time, data.task.prio,
                   data.task.rss, data.task.vsz,
                   data.task.uid,
                   data.task.ppid,
                   data.task.cpu_user,
                   data.task.cpu_system,
                   data.task.state,
                   data.task.uid_name);*/
        }

        for (int i = 0; i < niz_task; i++) {

            //Task *task;
           // task = &task_array[i];
            ret = (int) send(info->thread_socket, &task_array[i], sizeof(Task), 0);

            if (ret < 0) {
                printf("Error sending data!\n\t");
                //  break;
                pthread_cancel(t3);
                pthread_exit(&ret);
            } else {
                printf("return value task %d \n",ret);



            }
        }


      //  Devices  *devices;

        __int32_t niz=0;
        device2(&devices,devices_show,&niz);
        printf("prosli \n");




        ret = (int) send(info->thread_socket, &niz, sizeof(__int32_t), 0);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");

            pthread_cancel(t3);
            pthread_exit(&ret);
        }
        for(int r=0;r<niz;r++){

           /* printf("Devices % "SCNu64 ", %"SCNu64 ",%"SCNu64 ",%"SCNu64 "%"SCNu64 ", %s %s %s\n",
                   devices[r].used,devices[r].avail,
                   devices[r].fid,devices[r].free,devices[r].total,
                   devices[r].name,devices[r].directory,devices[r].type);*/

        }
  /*      for (int i = 0; i < niz; i++) {




            size_t g = strlen(devices[i].name);
            for (int r = 0; r <= g; r++) {

                data.devices.name[r] = devices[i].name[r];

            }
            g = strlen(devices[i].directory);
            for (int r = 0; r <= g; r++) {

                data.devices.directory[r] = devices[i].directory[r];

            }
            g = strlen(devices[i].type);
            for (int r = 0; r <= g; r++) {

                data.devices.type[r] = devices[i].type[r];

            }
            data.devices.avail =devices[i].avail;
            data.devices.fid = devices[i].fid;
            data.devices.free = devices[i].free;
            data.devices.total = devices[i].total;
            data.devices.used =devices[i].used;
            data.devices.checked=false;

               // printf("%lu, %lu,%lu,%lu %lu, %s %s %s\n",data.devices.used,data.devices.avail,data.devices.fid,data.devices.free,data.devices.total,data.devices.name,data.devices.directory,data.devices.type);
            ret = (int) send(info->thread_socket, &devices[i], sizeof(Devices), 0);

            if (ret < 0) {
                printf("Error sending data!\n\t");
                //  break;
                pthread_cancel(t3);
                pthread_exit(&ret);
            }
        }*/

        for(int i =0;i<niz ;i++){

            ret = (int) send(info->thread_socket, &devices[i], sizeof(Devices), 0);

            if (ret < 0) {
                printf("Error sending data!\n\t");
                //  break;
                pthread_cancel(t3);
                pthread_exit(&ret);
            }
            printf("Return value devices %d \n", ret);


        }


        printf("Before Network  %" SCNu64 ", %" SCNu64 "\n ",network.received_bytes,network.transmited_bytes);
        interface_name(&network);

        if(network.transmited_bytes>139803656033161 || network.received_bytes>139803656033161){

            printf("problems \n");
            printf("NEt trans:  %" SCNu64 " rec:  %" SCNu64 "\n",network.transmited_bytes,network.received_bytes);
            exit(1);
        }
        ret = (int) send(info->thread_socket, &network, sizeof(Network), 0);
        printf("Network  %" SCNu64 ", %" SCNu64 "\n ",network.received_bytes,network.transmited_bytes);
        if (ret < 0) {
            printf("Error sending data!\n\t");
            //  break;
            pthread_cancel(t3);
            pthread_exit(&ret);
        }
        printf("Return value network %d \n", ret);


   /*     ret = (int) send(info->thread_socket, &devices[1], sizeof(Devices), 0);

        if (ret < 0) {
            printf("Error sending data!\n\t");
            //  break;
            pthread_cancel(t3);
            pthread_exit(&ret);
        }*/





        free(task_array);
        free(devices);
        free(interrupts);
     //   free(cpu_usage);
        free(info);
            printf("pre\n");
            pthread_cond_wait(&cond, &m);
            printf("posle\n");


        }


    free(task_array);
    free(devices);
    free(interrupts);
    pthread_cancel(t3);
   // pthread_exit(&ret);

  return 0;
};
