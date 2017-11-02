//
// Created by dushn on 10.10.17..
//

#include "testing_tree.h"
#include "buttons.h"
#include "devices.h"
#include "main_header.h"
#include "task_manager.h"





GtkTreeStore * create_list_store(void)
{
    GtkCellRenderer *cell_renderer;
    GtkTreeViewColumn *column;

    list_store = gtk_tree_store_new(NUM_COLS, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING
            ,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

    cell_renderer = gtk_cell_renderer_text_new();


    column = gtk_tree_view_column_new_with_attributes(("Tasks"), cell_renderer, "text",COL_TASK, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_TASK);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), COL_TASK, compare_string_list_item, (void*)COL_TASK, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes(("USERS"), cell_renderer, "text",COL_UNAME, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_UNAME);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), COL_UNAME, compare_string_list_item, (void*)COL_UNAME, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes(("PID"), cell_renderer, "text", COL_PID, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_PID);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), COL_PID, compare_int_list_item, (void *)COL_PID, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes(("PPID"), cell_renderer, "text", COL_PPID, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_PPID);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), COL_PPID, compare_int_list_item, (void *)COL_PPID, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes(("State"), cell_renderer, "text", COL_STATE, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_STATE);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), COL_STATE, compare_string_list_item, (void *)COL_STATE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes(("VM-Size"), cell_renderer, "text", COL_VSZ, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_VSZ);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), COL_VSZ, compare_int_list_item_size,(void *) COL_VSZ, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes(("RSS"), cell_renderer, "text", COL_RSS, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_RSS);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), COL_RSS, compare_int_list_item_size, (void *)COL_RSS, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);



    column = gtk_tree_view_column_new_with_attributes(("CPU%"), cell_renderer, "text", COL_CPU, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_CPU);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), COL_CPU, compare_int_list_item, (void *)COL_CPU, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes(("Prio"), cell_renderer, "text", COL_PRIO, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_PRIO);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), COL_PRIO, compare_int_list_item, (void *)COL_PRIO, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes(("Start time"), cell_renderer, "text", COL_STIME, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_STIME);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), COL_STIME, compare_int_list_item_time, (void *)COL_STIME, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes(("Duration "), cell_renderer, "text", COL_DUR, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_DUR);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), COL_DUR, compare_int_list_item_time, (void *)COL_DUR, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);



    // change_list_store_view_devices();
    return list_store;
}
GtkTreeStore * create_list_store_dev(void)
{
    GtkCellRenderer *cell_renderer;
    GtkTreeViewColumn *column;

    list_store1 = gtk_tree_store_new(NUM_COLS_DEV, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

    cell_renderer = gtk_cell_renderer_text_new();


    column = gtk_tree_view_column_new_with_attributes(("Devices"), cell_renderer, "text",COL_DEV, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_DEV);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store1), COL_DEV, compare_string_list_item, (void*)COL_DEV, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

    column = gtk_tree_view_column_new_with_attributes(("Available"), cell_renderer, "text",COL_AVAILABLE, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_AVAILABLE);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store1), COL_AVAILABLE, compare_int_list_item_size, (void*)COL_AVAILABLE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

    column = gtk_tree_view_column_new_with_attributes(("Used"), cell_renderer, "text", COL_USED, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_USED);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store1), COL_USED, compare_int_list_item_size, (void *)COL_USED, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

    column = gtk_tree_view_column_new_with_attributes(("Type"), cell_renderer, "text", COL_TYPE, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_TYPE);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store1), COL_TYPE, compare_string_list_item, (void *)COL_TYPE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

    column = gtk_tree_view_column_new_with_attributes(("Directory"), cell_renderer, "text", COL_DIR, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_DIR);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store1), COL_DIR, compare_string_list_item, (void *)COL_DIR, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

    column = gtk_tree_view_column_new_with_attributes(("Total"), cell_renderer, "text", COL_TOTAL, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_TOTAL);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store1), COL_TOTAL, compare_int_list_item_size,(void *) COL_TOTAL, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

    column = gtk_tree_view_column_new_with_attributes(("Free"), cell_renderer, "text", COL_FREE, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_FREE);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store1), COL_FREE, compare_int_list_item_time, (void *)COL_FREE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);







    // change_list_store_view_devices();
    return list_store1;
}
void add_new_list_item(gint i)
{
    GtkTreeIter iter;

    gtk_tree_store_append(GTK_TREE_STORE(list_store), &iter, NULL);

    fill_list_item(i, &iter);
}
void add_new_list_item_dev(gint i)
{
    GtkTreeIter iter;

    gtk_tree_store_append(GTK_TREE_STORE(list_store1), &iter, NULL);

    fill_list_item_device(i, &iter);
}
/* change the task view (user, root, other) */
//void change_task_view(void)
//{
//    gtk_tree_store_clear(GTK_TREE_STORE(list_store));
//    gint i = 0;
//
//    //for(i = 0; i < tasks; i++)
//    for(i = 0; i < tasks_num; i++)
//
//    {
//        Task task = g_array_index(task_array, Task, i);
//
//        if((task.uid == own_uid && show_user_tasks) || (task.uid == 0 && show_root_tasks) || (task.uid != own_uid && task.uid != 0 && show_other_tasks))
//            add_new_list_item(i);
//    }
//
//    init_timeout();
//}
void change_list_store_view_devices(GtkWidget *widget, gboolean visible)
{
//    dev=0
//            avail=1;
//    used=2;
//    type=3;
//    dir=4;
//    total=5;
//    free=6;.
    if(button_device_devices==widget){

        gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview1), 0), visible);
    }
    else if(button_device_avail==widget){

        gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview1), 1), visible);
    }
    else if(button_device_used==widget){

        gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview1), 2), visible);
    }
    else if(button_device_type==widget){

        gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview1), 3), visible);
    }
    else if(button_device_directory==widget){

        gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview1), 4), visible);
    }
    else if(button_device_total==widget){

        gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview1), 5), visible);
    }

    else /*(button_device_free==widget)*/{

        gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview1), 6), visible);
    }

}
void change_list_store_view_process(GtkWidget *widget, gboolean visible)
{
    //task=0
    if(button_process_task==widget){

        gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), 0), visible);
    }
    else if(button_process_user==widget){

        gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), 1), visible);
    }
    else if(button_process_pid==widget){

        gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), 2), visible);
    }
    else if(button_process_ppid==widget){

        gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), 3), visible);
    }
    else if(button_process_state==widget){

        gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), 4), visible);
    }
    else if(button_process_vm_size==widget){

        gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), 5), visible);
    }
    else if(button_process_rss==widget){

        gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), 6), visible);
    }

    else if (button_process_cpu==widget){

        gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), 7), visible);
    }
    else if (button_process_prio==widget){

        gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), 8), visible);

    }
    else{

        gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), 9), visible);
    }


}









void differenceBetweenTimePeriod(struct tm start, struct tm stop, struct tm *diff)
{
    if(stop.tm_sec > start.tm_sec){
        --start.tm_min;
        start.tm_sec += 60;
    }

    diff->tm_sec = start.tm_sec - stop.tm_sec;
    if(stop.tm_min > start.tm_min){
        --start.tm_hour;
        start.tm_min += 60;
    }

    diff->tm_min = start.tm_min - stop.tm_min;
    diff->tm_hour = start.tm_hour - stop.tm_hour;
}

void fill_list_item(gint i, GtkTreeIter *iter)
{

    if(iter != NULL)
    {
        Task *task = &g_array_index(task_array, Task, i);
        gchar cpu[16], value[14];
        gchar *rss, *vsz;
        gchar *prio;
        gchar *stime;
        gchar *duration;

        rss = g_format_size_full(task->rss, G_FORMAT_SIZE_IEC_UNITS);
        vsz = g_format_size_full(task->vsz, G_FORMAT_SIZE_IEC_UNITS);

        g_snprintf(value, 14, (more_precision) ? "%.2f" : "%.f", task->cpu_user + task->cpu_system);

        g_snprintf(cpu, 16, ("%s%%"), value);
        gchar *pid = g_strdup_printf("%i", task->pid);
        gchar *ppid = g_strdup_printf("%i", task->ppid);
        gchar *state = g_strdup_printf("%s", task->state);

        gchar *name = g_strdup_printf("%s", task->name);
        gchar *uname = g_strdup_printf("%s", task->uid_name);
        prio=  g_strdup_printf("%hi", task->prio);
     //   stime= g_strdup_printf("%ld", task->start_time/100);//sec
        int sec, hr, min, t;




        sec=task->start_time/100;
        hr =sec /3600;
        t = sec%3600;
        min = t/60;
        sec = t%60;


        int h,m,s;


        s=h=m=0;
        s=sec+pocetno.tm_sec;
        if(s>60)
        {
            m=s/60;
            s=s%60;
        }
        m=m+min+pocetno.tm_min;
        if(m>60)
        {
            h=m/60;
            m=m%60;
        }
        h=h+pocetno.tm_hour+hr;


        stime= g_strdup_printf("%d:%d:%d",h,m,s);
      //  duration= g_strdup_printf("%d:%d:%d",h,m,s);
     /*   struct tm  start_time, diff;


        start_time.tm_sec=s;
        start_time.tm_min=m;
        start_time.tm_hour=h;
        differenceBetweenTimePeriod(tm, start_time, &diff);*/


        duration=g_strdup_printf("%d:%d:%d",task->duration.tm_hour,task->duration.tm_min,task->duration.tm_sec);






        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COL_TASK, name, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COL_PID, pid, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COL_PPID, ppid, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COL_STATE, state, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COL_VSZ, vsz, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COL_RSS, rss, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COL_CPU, cpu, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COL_UNAME, uname, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COL_PRIO, prio, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COL_STIME, stime, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COL_DUR, duration, -1);



        g_free(pid);
        g_free(ppid);
        g_free(state);
        g_free(name);
        g_free(uname);
        g_free(rss);
        g_free(vsz);
        g_free(prio);
        g_free(stime);
        g_free(duration);
    }
}



void fill_list_item_device(gint i, GtkTreeIter *iter)
{




    gchar *total, *avail, *used, *free,*directory,*type;

    if(iter != NULL)
    {
        Devices *devices = &g_array_index(names_array, Devices, i);
        gchar *name = g_strdup_printf("%s", devices->name);
        used = g_format_size_full((guint64) devices->used, G_FORMAT_SIZE_IEC_UNITS);
        total = g_format_size_full((guint64) devices->total, G_FORMAT_SIZE_IEC_UNITS);
        avail = g_format_size_full((guint64) devices->avail, G_FORMAT_SIZE_IEC_UNITS);
        free = g_format_size_full((guint64) devices->free, G_FORMAT_SIZE_IEC_UNITS);
        directory=g_strdup_printf("%s", devices->directory);
        type=g_strdup_printf("%s", devices->type);



        gtk_tree_store_set(GTK_TREE_STORE(list_store1), iter, COL_DEV, name, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store1), iter, COL_AVAILABLE, avail, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store1), iter, COL_USED, used, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store1), iter, COL_FREE, free, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store1), iter, COL_TOTAL, total, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store1), iter, COL_DIR, directory, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store1), iter, COL_TYPE, type, -1);



        g_free(name);
        g_free(used);
        g_free(total);
        g_free(avail);
        g_free(free);
        g_free(directory);
        g_free(type);

    }
}



void refresh_list_item_device(gint i)
{
    GtkTreeIter iter;
    static gint g=0;
    gboolean valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(list_store1), &iter);
    Devices *device = &g_array_index(names_array, Devices, i);
    while(valid)
    {
        gchar *str_data = "";
        gchar *str_data1 = "";
        gchar *str_data2 = "";
        gtk_tree_model_get(GTK_TREE_MODEL(list_store1), &iter, 0, &str_data, -1); //COL_DEV
        gtk_tree_model_get(GTK_TREE_MODEL(list_store1), &iter, 1, &str_data1, -1); //COL_DIR
        gtk_tree_model_get(GTK_TREE_MODEL(list_store1), &iter, 2, &str_data2, -1);  //type
        //printf("type %s\n",str_data2);

        if(strcmp(device->name , str_data)==0 && strcmp(device->directory , str_data1)==0 /* && strcmp(device->type , str_data2)*/)
        {
            g_free(str_data);
            g_free(str_data1);
            g_free(str_data2);
//            printf("Refresh times%d\n",g);
//            printf("NAME OF the device %s\n",str_data);
//            printf("NAME OF the device %s\n",device->name);
//            printf("NAME OF the directory %s\n",device->directory);
            fill_list_item_device(i, &iter);
            g++;
            break;
        }

        g_free(str_data);
        g_free(str_data1);
        g_free(str_data2);
        valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(list_store1), &iter);
    }
}

void refresh_list_item(gint i)
{
    GtkTreeIter iter;
    gboolean valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(list_store), &iter);
    Task *task = &g_array_index(task_array, Task, i);
    while(valid)
    {
        gchar *str_data = "";
        gtk_tree_model_get(GTK_TREE_MODEL(list_store), &iter, 1, &str_data, -1);

        if(task->pid == atoi(str_data))
        {
            g_free(str_data);
            fill_list_item(i, &iter);
            break;
        }

        g_free(str_data);
        valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(list_store), &iter);
    }
}
void remove_list_item(gint pid)
{
    GtkTreeIter iter;
    gboolean valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(list_store), &iter);

    while(valid)
    {
        gchar *str_data = "";
        gtk_tree_model_get(GTK_TREE_MODEL(list_store), &iter, 1, &str_data, -1);

        if(pid == atoi(str_data))
        {
            g_free(str_data);
            gtk_tree_store_remove(GTK_TREE_STORE(list_store), &iter);
            break;
        }

        g_free(str_data);
        valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(list_store), &iter);
    }
}
void remove_list_item_device(gchar *directory,gchar *name,gchar *type)
{
    GtkTreeIter iter;
    gboolean valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(list_store1), &iter);

    while(valid)
    {
        gchar *str_data = "";
        gchar *str_data1 = "";
        gchar *str_data2 = "";
        gtk_tree_model_get(GTK_TREE_MODEL(list_store1), &iter, 0, &str_data, -1); //COL_DEV
        gtk_tree_model_get(GTK_TREE_MODEL(list_store1), &iter, 1, &str_data1, -1); //COL_DIR
        gtk_tree_model_get(GTK_TREE_MODEL(list_store1), &iter, 1, &str_data2, -1); //COL_DIR

        if(strcmp(directory,str_data1)==0 && strcmp(name,str_data)==0 && strcmp(directory,str_data2)==0)
        {
            g_free(str_data);
            g_free(str_data1);
            g_free(str_data2);

            gtk_tree_store_remove(GTK_TREE_STORE(list_store1), &iter);
            break;
        }

        g_free(str_data);
        g_free(str_data1);
        g_free(str_data2);
        valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(list_store1), &iter);
    }
}
gint compare_string_list_item(GtkTreeModel *model, GtkTreeIter *iter1, GtkTreeIter *iter2, gpointer column)
{
    gchar *s1 = "";
    gchar *s2 = "";
    gchar *temp = "";
    gchar *temp1 = "";

    gint ret = 0;

    gtk_tree_model_get(model, iter1, GPOINTER_TO_INT(column), &s1, -1);
    gtk_tree_model_get(model, iter2, GPOINTER_TO_INT(column), &s2, -1);

    if(s1 != NULL && s2 != NULL) {
        temp=s1;
        temp1=s2;
        while((*s1>0 && *s1<65) || (*s1>=91 && *s1<=96)  || *s1>=123){
           // printf("[%s]\n",s1);
                temp=s1+1;

                *s1=*temp;
               // s1=s1+1;


        }
        while((*s2>0 && *s2<65) || (*s2>=91 && *s2<=96)  || *s2>=123){
         //   printf("[%s]\n",s2);
            temp1=s2+1;

            *s2=*temp1;


        }


            if(temp[0]>=65 && temp[0]<=90){
                temp[0]+=32;
            }
            if(temp1[0]>=65 && temp1[0]<=90){
                temp1[0]+=32;
            }

            ret = strcmp(temp, temp1);

        }
    else{


        ret = 0;
    }


    if(s1 != NULL)
      //  s1=s1-j;
        g_free(s1);
    if(s2 != NULL)
        g_free(s2);

    return ret;
}
gint compare_int_list_item(GtkTreeModel *model, GtkTreeIter *iter1, GtkTreeIter *iter2, gpointer column)
{
    gchar *s1 = "";
    gchar *s2 = "";

    gint ret = 0;

    gtk_tree_model_get(model, iter1, column, &s1, -1);
    gtk_tree_model_get(model, iter2, column, &s2, -1);

    gint i1 = 0;
    gint i2 = 0;

    if(s1 != NULL)
        i1= atoi(s1);

    if(s2 != NULL)
        i2 = atoi(s2);

    ret = i1 - i2;

    if(s1 != NULL)
        g_free(s1);
    if(s2 != NULL)
        g_free(s2);

    return ret;
}
gint compare_int_list_item_size(GtkTreeModel *model, GtkTreeIter *iter1, GtkTreeIter *iter2, gpointer column)
{
    gchar *s1 = "";
    gchar *s2 = "";
    gchar *z ;
    gchar *z1  ;
    gchar *size ;
    gchar *size1 ;


    gint ret = 0;
    gint ret1 = 0;
    gint ret2 = 0;


    gtk_tree_model_get(model, iter1, column, &s1, -1);
    gtk_tree_model_get(model, iter2, column, &s2, -1);

  z=  g_strrstr (s1, ",");
  z1=  g_strrstr (s2, ",");
  size= g_strstr_len (s1, strlen(s1)," ") ; //prvi razmak
  size1=  g_strstr_len (s2, strlen(s2)," ") ;
    size=size+1;//pomerimo za jedan
    size1=size1+1;
    gint i1 = 0;
    gint i2 = 0;
    gint i3 = 0;
    gint i4 = 0;
    gint isize=0;
    gint  isize1=0;




        ret2 = strcmp(size, size1);// velicine
        if(ret2!=0){    //ako su razlicite velicine
           if(strcmp(size, "MiB")==0 ) {

              isize=3;

           }
            if(strcmp(size1, "MiB")==0 ) {

                isize1=3;

            }
            if(strcmp(size, "KiB")==0 ) {

                isize=2;

            }
            if(strcmp(size1, "KiB")==0 ) {

                isize1=2;

            }
            if(strcmp(size, "GiB")==0 ) {

                isize=4;

            }
            if(strcmp(size1, "GiB")==0 ) {

                isize1=4;

            }
            if(strcmp(size, "bytes")==0 ) {

                isize=1;

            }

            if(strcmp(size1, "bytes")==0 ) {

                isize1=1;

            }

            ret2=isize- isize1;
            return ret2;
        }

    if(z!=NULL) //ako su iste velicine
        i3 = atoi(z+1); //preskacemo zarez

    if(z1!=NULL)
        i4 = atoi(z1+1); //preskacemo zarez

    if(s1 != NULL)
        i1 = atoi(s1);
    g_free(s1);

    if(s2 != NULL)
        i2 = atoi(s2);
    g_free(s2);

    ret = i1 - i2;
    ret1 = i3 - i4;
    if(ret==0){ //ako je vrednost pre zareza jednaka

        return ret1;
    }






    return ret;
}

gint compare_int_list_item_time(GtkTreeModel *model, GtkTreeIter *iter1, GtkTreeIter *iter2, gpointer column)
{
    gchar *s1 = "";
    gchar *s2 = "";
    gchar *dt ;
    gchar *dt1  ;
    gchar *dt2;
    gchar *dt3 ;


    gint ret = 0;
    gint ret1 = 0;
    gint ret2 = 0;




    gtk_tree_model_get(model, iter1, column, &s1, -1);
    gtk_tree_model_get(model, iter2, column, &s2, -1);

    //minuti postavi pointer na prve : na koje naidje u broju karatktera koje mu postavimo
   dt= g_strstr_len (s1, strlen(s1), ":");
    dt1= g_strstr_len (s2, strlen(s2), ":");

    dt=dt+1;//preskacemo 2 tacke
    dt1=dt1+1;
    dt2= g_strrstr (dt, ":");//sekunde
    dt3= g_strrstr (dt1, ":");//sekunde postavi pointer na :
    dt2=dt2+1;//preskacemo :
    dt3=dt3+1;

    gint i1 = 0;
    gint i2 = 0;
    gint i3 = 0;
    gint i4 = 0;


    if(s1!=NULL){
        i1=atoi(s1); //koliko je sati

    }
    if(s2!=NULL){
        i2=atoi(s2); //koliko je sati

    }
    ret=i1-i2;
    if(ret==0){ //ako je u isto sati

      //  if(dt!=NULL) {

            i3 = atoi(dt);
       // }


      //  if(dt1!=NULL)
            i4 = atoi(dt1);
        ret1= i3-i4;
    }
    else {
        g_free(s1);
        g_free(s2);
        return ret;
    }

    if(ret1==0){ //ako je u isto minuta
        i3=0;
        i4=0;

     /*   dt=dt+1;//preskacemo :
        dt1=dt1+1;*/
     //   if(dt2!=NULL) {

            i3 = atoi(dt2);
      //  }


     //   if(dt3!=NULL)
            i4 = atoi(dt3);
        ret2=i3-i4;
    }
    else {
        g_free(s1);
        g_free(s2);
        return ret1;

    }
    g_free(s1);
    g_free(s2);
    return ret2;
}
