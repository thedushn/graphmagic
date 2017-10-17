//
// Created by dushn on 3.8.17..
//

#include "memory_usage.h"
#include "main_header.h"
struct Memory_usage memory_usage;










void	get_memory_usage(){

    guint64 memory_total; guint64 memory_free; guint64 memory_cache; guint64 memory_buffers; guint64 swap_total; guint64 swap_free;

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

    memory_usage.memory_total= memory_total;
    memory_usage.swap_total= swap_total;

    memory_usage.memory_used= memory_total-memory_free;
    unsigned long long memory_used =memory_total-memory_free;
   // printf("its all in the memory %llu\n",memory_usage.memory_used);
   float swap_used = swap_total-swap_free;
    memory_usage.swap_used= swap_used/swap_total*100;
  //  printf("Swap used %lu\n",memory_usage.swap_used);


    float   percentage = (float)memory_used/(float)memory_total *100 ;
    memory_usage.percentage = percentage;
  //  printf("%d",memory_usage.percentage);
 // printf("Percentage %f",percentage);

//    memory_total *= 1024;
//    memory_free *= 1024;
//    memory_cache *= 1024;
//    memory_buffers *= 1024;
//    swap_total *= 1024;
//    swap_free *= 1024;



}
void swap_change(gpointer data){




    // static guint i =0;
    gfloat  j = memory_usage.swap_used;

    g_array_prepend_val(history[7],  j);
    if (history[7]->len > 1)
        g_array_remove_index (history[7], history[7]->len - 1);
    swap_usage_text = g_strdup_printf(("SWAP: %lu%%"),memory_usage.swap_used);
    gtk_label_set_text (GTK_LABEL (data), swap_usage_text);
    g_free(swap_usage_text);

}
void memory_change(gpointer data){


    //get_memory_usage();

    gfloat  j = memory_usage.percentage;



    g_array_prepend_val(history[6], j);

    if (history[6]->len > 1)
        g_array_remove_index (history[6], history[6]->len - 1);






    memory_usage_text = g_strdup_printf (("Memory: %0.2f%%"),memory_usage.percentage);
    gtk_label_set_text (GTK_LABEL (data), memory_usage_text);
    g_free(memory_usage_text);
    //return TRUE;
}
