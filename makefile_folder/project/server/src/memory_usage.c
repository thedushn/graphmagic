//
// Created by dushn on 3.8.17..
//

#include <inttypes.h>
#include "memory_usage.h"


//void 	get_memory_usage(){
void get_memory_usage(Memory_usage *memory_usage) {
    //  printf("made it in memory_usage\n");
    __uint64_t memory_total = 0;
    __uint64_t memory_free = 0;
    __uint64_t memory_cache = 0;
    __uint64_t memory_buffers = 0;
    __uint64_t swap_total = 0;
    __uint64_t swap_free = 0;
    //  __uint64_t memory_available=0;
    FILE *file;
    char buffer[1024];
    char *filename = "/proc/meminfo";
    short found = 0;
    __uint64_t swap_used = 0;
    float swap_percentage = 0;

    float percentage = 0;
    // printf("opening file %s",filename);
    file = fopen(filename, "r ");

    // printf("we made it ");

    while (found < 6 && fgets(buffer, 1024, file) != NULL) {


        found += sscanf(buffer, "MemTotal:\t %" SCNu64 " kB", &memory_total);
        found += sscanf(buffer, "MemFree:\t%" SCNu64 " kB", &memory_free);
        found += sscanf(buffer, "Cached:\t%" SCNu64 " kB", &memory_cache);
        found += sscanf(buffer, "Buffers:\t%" SCNu64 " kB", &memory_buffers);
        found += sscanf(buffer, "SwapTotal:\t%" SCNu64 " kB", &swap_total);
        found += sscanf(buffer, "SwapFree:\t%" SCNu64 " kB", &swap_free);

    }
    fclose(file);

    //ispis je u kB
    memory_total *= 1024;
    memory_free *= 1024;
    memory_cache *= 1024;
    memory_buffers *= 1024;
    swap_total *= 1024;
    swap_free *= 1024;

    memory_usage->memory_total = memory_total;
    memory_usage->swap_total = swap_total;


#ifdef __arm__

    __uint64_t memory_used=memory_total - memory_free;
#else

    __uint64_t memory_used = memory_total - memory_free - memory_cache - memory_buffers;
#endif


    printf(" memory_total %" SCNu64 " memory_free %" SCNu64 " memory_cache %"
                   SCNu64 " memory_buffers %" SCNu64 " memory_used %" SCNu64 "\n ", memory_total, memory_free,
           memory_cache, memory_buffers, memory_used

    );

    swap_used = swap_total - swap_free;

    swap_percentage = (float) (swap_total != 0) ? swap_used * 100 / (float) swap_total : 0;
    // swap_percentage/swap_total*100;
    if (sprintf(memory_usage->swap_percentage, "%f", swap_percentage) < 0) {

        printf("nije uspelo convertovanje %s \n", memory_usage->swap_percentage);
    }
    memory_usage->swap_used = swap_used;
    memory_usage->memory_used = memory_used;


    percentage = (memory_total != 0) ? memory_used * 100 / memory_total : 0;


    if (sprintf(memory_usage->memory_percentage, "%f", percentage) < 0) {

        printf("nije uspelo convertovanje %s \n", memory_usage->memory_percentage);
    }




/////
    /* memory->memory_usage.memory_total= memory_usage.memory_total;
     memory->memory_usage.swap_total= memory_usage.swap_total;
     memory->memory_usage.swap_used= memory_usage.swap_used;
     memory->memory_usage.swap_percentage= memory_usage.swap_percentage;
     memory->memory_usage.memory_used= memory_usage.memory_used;
     memory->memory_usage.memory_percentage= memory_usage.memory_percentage;*/
//////





}

