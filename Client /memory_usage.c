//
// Created by dushn on 3.8.17..
//

#include "memory_usage.h"
#include "functions.h"
#include "common.h"
struct _Memory_usage memory_usage;



//void 	get_memory_usage(){
void 	get_memory_usage(data_s *memory){
    printf("made it in memory_usage\n");
    guint64 memory_total=0; guint64 memory_free=0; guint64 memory_cache=0; guint64 memory_buffers=0; guint64 swap_total=0; guint64 swap_free=0;

    FILE *file;
    gchar buffer[1024];
    char *filename = "/proc/meminfo";
    gushort found = 0;
   // printf("opening file %s",filename);
    file = fopen (filename, "r ");

   // printf("we made it ");

    while (found < 6 && fgets (buffer, 1024, file) != NULL)
    {
        found += sscanf (buffer, "MemTotal:\t%llu kB", (unsigned long long*)&memory_total);
        //printf("%c",found);
      //  printf("%llu\n",memory_total);
        found += sscanf (buffer, "MemFree:\t%llu kB", (unsigned long long*)&memory_free);
        found += sscanf (buffer, "Cached:\t%llu kB", (unsigned long long*)&memory_cache);
      //  printf("%c",found);
        found += sscanf (buffer, "Buffers:\t%llu kB", (unsigned long long*)&memory_buffers);
        found += sscanf (buffer, "SwapTotal:\t%llu kB", (unsigned long long*)&swap_total);
        found += sscanf (buffer, "SwapFree:\t%llu kB", (unsigned long long*)&swap_free);
    }
    fclose (file);

    //ispis je u kB
    memory_total *= 1024;
    memory_free *= 1024;
    memory_cache *= 1024;
    memory_buffers *= 1024;
    swap_total *= 1024;
    swap_free *= 1024;
    memory_usage.memory_total= memory_total;
    memory_usage.swap_total= swap_total;


    unsigned long long memory_used= memory_total - memory_free - memory_cache - memory_buffers;
   // printf("its all in the memory %llu\n",memory_usage.memory_used);
    unsigned long long  swap_used = swap_total-swap_free;
    memory_usage.swap_percentage= (float)(swap_total != 0) ? swap_used * 100 / (float)swap_total : 0;
           // swap_percentage/swap_total*100;
    memory_usage.swap_used=swap_used;
    memory_usage.memory_used=memory_used;


    float   percentage =(memory_total != 0) ? memory_used * 100 / (float)memory_total : 0;
            /*(float)memory_used/(float)memory_total *100 ;*/
    memory_usage.percentage = percentage;

  //  union DATA_S data_s;
    memory->memory_usage.memory_total= memory_usage.memory_total;
    memory->memory_usage.swap_total= memory_usage.swap_total;
    memory->memory_usage.swap_used= memory_usage.swap_used;
    memory->memory_usage.swap_percentage= memory_usage.swap_percentage;
    memory->memory_usage.memory_used= memory_usage.memory_used;
    memory->memory_usage.percentage= memory_usage.percentage;
//    data_s.memory_usage.memory_total= memory_usage.memory_total;
//    data_s.memory_usage.swap_total= memory_usage.swap_total;
//    data_s.memory_usage.swap_used= memory_usage.swap_used;
//    data_s.memory_usage.swap_percentage= memory_usage.swap_percentage;
//    data_s.memory_usage.memory_used= memory_usage.memory_used;
//    data_s.memory_usage.percentage= memory_usage.percentage;





}

