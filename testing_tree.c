//
// Created by dushn on 10.10.17..
//

#include "testing_tree.h"
#include "main_header.h"
#include "task-manager.h"
void handle_task_menu(GtkWidget *widget, gchar *signal)
{
    if(signal != NULL)
    {
        gchar *s;
        printf("signal %s",signal);
        if (strcmp(signal, "KILL") == 0) s = ("Really kill the task?");
        else s = ("Really terminate the task?");

        if(strcmp(signal, "STOP") == 0 || strcmp(signal, "CONT") == 0 )
        {
            gchar *task_id = "";
            GtkTreeModel *model;
            GtkTreeIter iter;

            if(gtk_tree_selection_get_selected(selection, &model, &iter))
            {
                gtk_tree_model_get(model, &iter, 1, &task_id, -1);
                send_signal_to_task(task_id, signal);
                init_timeout();
            }
        }
    }
}
void send_signal_to_task(gchar *task_id, gchar *signal)
{
    if(task_id != "" && signal != NULL)
    {
        gchar command[64] = "kill -";
        g_strlcat(command,signal, sizeof command);
        g_strlcat(command," ", sizeof command);
        g_strlcat(command,task_id, sizeof command);

       if(system(command) != 0)
           printf("comand failed\n");
//            xfce_err("Couldn't %s the task with ID %s", signal, task_id);
    }
}

gint compare_string_list_item(GtkTreeModel *model, GtkTreeIter *iter1, GtkTreeIter *iter2, gpointer column)
{
    gchar *s1 = "";
    gchar *s2 = "";

    gint ret = 0;

    gtk_tree_model_get(model, iter1, GPOINTER_TO_INT(column), &s1, -1);
    gtk_tree_model_get(model, iter2, GPOINTER_TO_INT(column), &s2, -1);

    if(s1 != NULL && s2 != NULL)
        ret = strcmp(s1, s2);
    else
        ret = 0;

    if(s1 != NULL)
        g_free(s1);
    if(s2 != NULL)
        g_free(s2);

    return ret;
}
void on_quit(void)
{


    gtk_main_quit();
}
GtkWidget* create_main_window (void)
{
    GtkWidget *window;
    GtkWidget *vbox1;
    GtkWidget *bbox1;
    GtkWidget *scrolledwindow1;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;

    GtkWidget *system_info_box;


    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), ("xfce4-taskmanager"));
    gtk_window_set_default_size (GTK_WINDOW (window), 1400, 1400);

    vbox1 = gtk_vbox_new (FALSE, 10);
    gtk_widget_show (vbox1);
    gtk_container_add (GTK_CONTAINER (window), vbox1);
    gtk_container_set_border_width (GTK_CONTAINER (vbox1), 10);

    system_info_box = gtk_hbox_new (FALSE, 10);
    gtk_widget_show (system_info_box);
    gtk_box_pack_start (GTK_BOX (vbox1), system_info_box, FALSE, TRUE, 0);

    cpu_usage_progress_bar_box = gtk_event_box_new ();
    cpu_usage_progress_bar = gtk_progress_bar_new ();
    gtk_progress_bar_set_text (GTK_PROGRESS_BAR (cpu_usage_progress_bar), ("cpu usage"));
    gtk_widget_show (cpu_usage_progress_bar);
    gtk_widget_show (cpu_usage_progress_bar_box);
    gtk_container_add (GTK_CONTAINER (cpu_usage_progress_bar_box), cpu_usage_progress_bar);
    gtk_box_pack_start (GTK_BOX (system_info_box), cpu_usage_progress_bar_box, TRUE, TRUE, 0);

    mem_usage_progress_bar_box = gtk_event_box_new ();
    mem_usage_progress_bar = gtk_progress_bar_new ();
    gtk_progress_bar_set_text (GTK_PROGRESS_BAR (mem_usage_progress_bar), ("memory usage"));
    gtk_widget_show (mem_usage_progress_bar);
    gtk_widget_show (mem_usage_progress_bar_box);
    gtk_container_add (GTK_CONTAINER (mem_usage_progress_bar_box), mem_usage_progress_bar);
    gtk_box_pack_start (GTK_BOX (system_info_box), mem_usage_progress_bar_box, TRUE, TRUE, 0);

    scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
    gtk_widget_show (scrolledwindow1);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start (GTK_BOX (vbox1), scrolledwindow1, TRUE, TRUE, 0);
    gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_SHADOW_IN);

    treeview = gtk_tree_view_new ();
    gtk_widget_show (treeview);
    gtk_container_add (GTK_CONTAINER (scrolledwindow1), treeview);

    create_list_store();

    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));

    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(list_store));

    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(list_store), 1, GTK_SORT_ASCENDING);

    bbox1 = gtk_hbutton_box_new();
    gtk_box_pack_start(GTK_BOX(vbox1), bbox1, FALSE, TRUE, 0);
    gtk_widget_show (bbox1);

    button2 = gtk_button_new_from_stock ("gtk-preferences");
    gtk_widget_show (button2);
    gtk_box_pack_start (GTK_BOX (bbox1), button2, FALSE, FALSE, 0);

    button3 = gtk_toggle_button_new_with_label (("more details"));
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button3), full_view);
    gtk_widget_show (button3);
    gtk_box_pack_start (GTK_BOX (bbox1), button3, FALSE, FALSE, 0);

    button1 = gtk_button_new_from_stock ("gtk-quit");
    gtk_widget_show (button1);
    gtk_box_pack_start (GTK_BOX (bbox1), button1, FALSE, FALSE, 0);

    g_signal_connect ((gpointer) window, "destroy", G_CALLBACK (on_quit), NULL);
    g_signal_connect_swapped ((gpointer) treeview, "button-press-event", G_CALLBACK(on_treeview1_button_press_event), NULL);
    g_signal_connect ((gpointer) button1, "clicked",  G_CALLBACK (on_quit),  NULL);
    g_signal_connect ((gpointer) button2, "button_release_event",  G_CALLBACK (on_button1_button_press_event),  NULL);
    g_signal_connect ((gpointer) button3, "toggled",  G_CALLBACK (on_button3_toggled_event),  NULL);

    return window;
}

GtkTreeStore * create_list_store(void)
{
    GtkCellRenderer *cell_renderer;
    GtkTreeViewColumn *column;
#define COLUMN_PROPERTIES "expand", TRUE, "clickable", TRUE, "reorderable", TRUE, "resizable", TRUE, "visible", TRUE
    list_store = gtk_tree_store_new(NUM_COLS, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

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
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), COL_PPID, compare_string_list_item, (void *)COL_PPID, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes(("State"), cell_renderer, "text", COL_STATE, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_STATE);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), COL_STATE, compare_int_list_item, (void *)COL_STATE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes(("VM-Size"), cell_renderer, "text", COL_VSZ, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_VSZ);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), COL_VSZ, compare_int_list_item,(void *) COL_VSZ, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes(("RSS"), cell_renderer, "text", COL_RSS, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_RSS);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), COL_RSS, compare_int_list_item, (void *)COL_RSS, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);



    column = gtk_tree_view_column_new_with_attributes(("CPU%"), cell_renderer, "text", COL_CPU, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, COL_CPU);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), COL_CPU, compare_int_list_item, (void *)COL_CPU, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);


    // change_list_store_view();
    return list_store;
}
void add_new_list_item(gint i)
{
    GtkTreeIter iter;

    gtk_tree_store_append(GTK_TREE_STORE(list_store), &iter, NULL);

    fill_list_item(i, &iter);
}
/* change the task view (user, root, other) */
void change_task_view(void)
{
    gtk_tree_store_clear(GTK_TREE_STORE(list_store));
    gint i = 0;

    //for(i = 0; i < tasks; i++)
    for(i = 0; i < tasks_num; i++)

    {
        Task task = g_array_index(task_array, Task, i);

        if((task.uid == own_uid && show_user_tasks) || (task.uid == 0 && show_root_tasks) || (task.uid != own_uid && task.uid != 0 && show_other_tasks))
            add_new_list_item(i);
    }

    init_timeout();
}
void change_list_store_view(void)
{
    gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), COLUMN_PPID), full_view);
    gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), COLUMN_MEM), full_view);
    gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), COLUMN_RSS), full_view);
}
void on_show_tasks_toggled (GtkMenuItem *menuitem, gint uid)
{
    if(uid == own_uid)
        show_user_tasks = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menuitem));
    else if(uid == 0)
        show_root_tasks = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menuitem));
    else
        show_other_tasks = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menuitem));

    change_task_view();
}

void on_show_cached_as_free_toggled (GtkMenuItem *menuitem, gint uid)
{
    show_cached_as_free = !show_cached_as_free;
    change_task_view();
}
GtkWidget* create_taskpopup (void)
{
    GtkWidget *taskpopup;
    GtkWidget *menu_item;

    taskpopup = gtk_menu_new ();

    menu_item = gtk_menu_item_new_with_mnemonic (("Stop"));
    gtk_widget_show (menu_item);
    gtk_container_add (GTK_CONTAINER (taskpopup), menu_item);
    g_signal_connect ((gpointer) menu_item, "activate", G_CALLBACK (handle_task_menu), "STOP");

    menu_item = gtk_menu_item_new_with_mnemonic (("Continue"));
    gtk_widget_show (menu_item);
    gtk_container_add (GTK_CONTAINER (taskpopup), menu_item);
    g_signal_connect ((gpointer) menu_item, "activate", G_CALLBACK (handle_task_menu), "CONT");

    menu_item = gtk_menu_item_new_with_mnemonic (("Term"));
    gtk_widget_show (menu_item);
    gtk_container_add (GTK_CONTAINER (taskpopup), menu_item);
    g_signal_connect ((gpointer) menu_item, "activate", G_CALLBACK (handle_task_menu), "TERM");

    menu_item = gtk_menu_item_new_with_mnemonic (("Kill"));
    gtk_widget_show (menu_item);
    gtk_container_add (GTK_CONTAINER (taskpopup), menu_item);
    g_signal_connect ((gpointer) menu_item, "activate", G_CALLBACK (handle_task_menu), "KILL");

    return taskpopup;
}

GtkWidget* create_mainmenu (void)
{
    GtkWidget *mainmenu;
    GtkWidget *info1;
    GtkWidget *trennlinie1;
    GtkWidget *show_user_tasks1;
    GtkWidget *show_root_tasks1;
    GtkWidget *show_other_tasks1;
    GtkWidget *show_cached_as_free1;
    GtkAccelGroup *accel_group;

    accel_group = gtk_accel_group_new ();

    mainmenu = gtk_menu_new ();

    info1 = gtk_image_menu_item_new_from_stock ("gtk-about", accel_group);
    gtk_widget_show (info1);
    gtk_menu_shell_append(GTK_MENU_SHELL(mainmenu), info1);

    trennlinie1 = gtk_separator_menu_item_new ();
    gtk_widget_show (trennlinie1);
    gtk_menu_shell_append(GTK_MENU_SHELL(mainmenu), trennlinie1);
    gtk_widget_set_sensitive (trennlinie1, FALSE);

    show_user_tasks1 = gtk_check_menu_item_new_with_mnemonic (("Show user tasks"));
    gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM(show_user_tasks1), show_user_tasks);
    gtk_widget_show (show_user_tasks1);
    gtk_menu_shell_append(GTK_MENU_SHELL(mainmenu), show_user_tasks1);

    show_root_tasks1 = gtk_check_menu_item_new_with_mnemonic (("Show root tasks"));
    gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM(show_root_tasks1), show_root_tasks);
    gtk_widget_show (show_root_tasks1);
    gtk_menu_shell_append(GTK_MENU_SHELL(mainmenu), show_root_tasks1);

    show_other_tasks1 = gtk_check_menu_item_new_with_mnemonic (("Show other tasks"));
    gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM(show_other_tasks1), show_other_tasks);
    gtk_widget_show (show_other_tasks1);
    gtk_menu_shell_append(GTK_MENU_SHELL(mainmenu), show_other_tasks1);

    show_cached_as_free1 = gtk_check_menu_item_new_with_mnemonic (("Show memory used by cache as free"));
    gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM(show_cached_as_free1), show_cached_as_free);
    gtk_widget_show (show_cached_as_free1);
    gtk_menu_shell_append(GTK_MENU_SHELL(mainmenu), show_cached_as_free1);

    // g_signal_connect ((gpointer) info1, "activate", G_CALLBACK (on_info1_activate), NULL);
    g_signal_connect ((gpointer) show_user_tasks1, "toggled", G_CALLBACK (on_show_tasks_toggled), (void *)own_uid);
    g_signal_connect ((gpointer) show_root_tasks1, "toggled", G_CALLBACK (on_show_tasks_toggled), (void *)0);
    g_signal_connect ((gpointer) show_other_tasks1, "toggled", G_CALLBACK (on_show_tasks_toggled), (void *)-1);
    g_signal_connect ((gpointer) show_other_tasks1, "toggled", G_CALLBACK (on_show_cached_as_free_toggled), (void *)0);

    gtk_menu_set_accel_group (GTK_MENU (mainmenu), accel_group);

    return mainmenu;
}
void on_button1_button_press_event(GtkButton *button, GdkEventButton *event)
{
    GdkEventButton *mouseevent = (GdkEventButton *)event;
    if(mainmenu == NULL)
        mainmenu = create_mainmenu ();
    gtk_menu_popup(GTK_MENU(mainmenu), NULL, NULL, NULL, NULL, mouseevent->button, mouseevent->time);
}

void on_button3_toggled_event(GtkButton *button, GdkEventButton *event)
{
    full_view = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
    change_list_store_view();
}

gboolean on_treeview1_button_press_event(GtkButton *button, GdkEventButton *event)
{
    if(event->button == 3)
    {
        printf("i was here\n");
        GdkEventButton *mouseevent = (GdkEventButton *)event;
        if(taskpopup == NULL)
            taskpopup = create_taskpopup ();
        gtk_menu_popup(GTK_MENU(taskpopup), NULL, NULL, NULL, NULL, mouseevent->button, mouseevent->time);
    }
    return FALSE;
}




void fill_list_item(gint i, GtkTreeIter *iter)
{






    if(iter != NULL)
    {
        Task *task = &g_array_index(task_array, Task, i);
        gchar cpu[16], value[14];
//
        gchar *rss, *vsz;
        rss = g_format_size_full(task->rss, G_FORMAT_SIZE_IEC_UNITS);
        vsz = g_format_size_full(task->vsz, G_FORMAT_SIZE_IEC_UNITS);
//
        g_snprintf(value, 14, (more_precision) ? "%.2f" : "%.f", task->cpu_user + task->cpu_system);
    //    printf("cpu_user %d cpu_system %d \n ",task->cpu_user,task->cpu_system);
        g_snprintf(cpu, 16, ("%s%%"), value);
        gchar *pid = g_strdup_printf("%i", task->pid);
        gchar *ppid = g_strdup_printf("%i", task->ppid);
        gchar *state = g_strdup_printf("%s", task->state);
        //  gchar *size = g_strdup_printf("%i kB", task->vsz);
        //   gchar *rss = g_strdup_printf("%i kB", task->rss);
        gchar *name = g_strdup_printf("%s", task->name);
        gchar *uname = g_strdup_printf("%s", task->uid_name);
        //  gchar *time = g_strdup_printf("%0d%%", (guint)task->time_percentage);

        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COL_TASK, name, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COL_PID, pid, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COL_PPID, ppid, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COL_STATE, state, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COL_VSZ, vsz, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COL_RSS, rss, -1);

        // gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COLUMN_TIME, time, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COL_CPU, cpu, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COL_UNAME, uname, -1);
        //   gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COLUMN_CPU2, cpu, -1);

        g_free(pid);
        g_free(ppid);
        g_free(state);
        // g_free(size);

        g_free(name);
        g_free(uname);
        //  g_free(time);
        g_free(rss);
        g_free(vsz);
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
        i1 = atoi(s1);

    if(s2 != NULL)
        i2 = atoi(s2);

    ret = i1 - i2;

    if(s1 != NULL)
        g_free(s1);
    if(s2 != NULL)
        g_free(s2);

    return ret;
}
//static void
//show_hide_status_icon (void)
//{
//    gboolean show_status_icon;
//    g_object_get (settings, "show-status-icon", &show_status_icon, NULL);
//    gtk_status_icon_set_visible (status_icon, show_status_icon);
//}

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
static void
status_icon_activated (void)
{
    if (!(gtk_widget_get_visible (window)))
        gtk_widget_show (window);
    else
        gtk_widget_hide (window);
}