#include "cpu_usage.h"
#include "network_bandwith.h"
#include "interrupts.h"
#include "task_manager.h"

#include "drawing.h"


#include "testing_tree.h"
#include "memory_usage.h"
#include "window.h"
#include "common.h"
#include "buttons.h"
#include "buttons_s.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include"pthread.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "functions.h"
#define BUF_SIZE 2000
#define CLADDR_LEN 100
#define PACKET_SIZE 1400
#define PORT_NUM 5004

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr) {

    if (widget == graph1) {

        do_drawing2(widget, cr, bjorg, time_step);
    }
    else if (widget == graph2) {

        do_drawing(widget, cr, bjorg2);
    }
    else if (widget == graph3) {

        do_drawing3(widget, cr, bjorg, time_step);
    }
    else  if (widget == graph4) {

        //do_drawing4(widget, cr);
        do_drawing4(widget, cr,interrupt_array_d);
    }
return TRUE;

}




void inc_refresh() {

    if (t >= 10000) {

        t = 10000;
    }
    else
    {
        t += 250;
    }

    timeout_refresh();



};

void dec_refresh() {


    if (t <= 250) {
        t = 250;
        //  printf("promena refresh rate \n");

    }
    else {
        t -= 250;
    }
    timeout_refresh();

};


void graph_refresh(GtkWidget *widget, gboolean CPU) {

//    if (widget == button_graph0) {
//
//
//        CPU0_line = CPU;
//        printf("CPU0 LINE %s\n", CPU0_line==TRUE ? "TRUE" : "FALSE");
//
//
//    }
//    else if (widget == button_graph1) {
//
//
//        CPU1_line = CPU;
//
//        printf("CPU1 LINE %s\n", CPU1_line==TRUE ? "TRUE" : "FALSE");
//
//    }
//    else if (widget == button_graph2) {
//
//        CPU2_line = CPU;
//        printf("CPU2 LINE %s\n", CPU2_line==TRUE ? "TRUE" : "FALSE");
//
//
//    }
//    else /* (widget == button_graph3)*/ {
//
//        CPU3_line = CPU;
//        printf("CPU3 LINE %s\n", CPU3_line==TRUE ? "TRUE" : "FALSE");
//
//    }

    timeout_refresh();
   // time_handler(window);


};

static gboolean time_handler(GtkWidget *widget) {

    gtk_widget_queue_draw(widget);

    return TRUE;
}


void timeout_refresh() {

    if (!g_source_remove(refresh)) {
        g_critical ("Unable to remove source");
        return;
    }
    refresh = 0;
    init_timeout();

}

void init_timeout2() {
    received_transfered();
    network_change_rc(label7);
    network_change_ts(label8);
    bjorg2++;

    if (bjorg2 >= 60) {


        bjorg2 = 60;
    }
//    if (refresh == 0) {
//
//        refresh = g_timeout_add(t, (GSourceFunc) init_timeout2, NULL);
//    }

}


void conekcija(gchar * argv){

    struct sockaddr_in addr ,cl_addr;
    int sockfd, len ,ret, ret1;
    char buffer[BUF_SIZE];
    char buffer2[BUF_SIZE];
    char clientAddr[CLADDR_LEN];
    pthread_t t1,t2;
//    if(argc <2){
//
//        printf("no port provided");
//        exit(1);
//    }
    int portnum=atoi(argv);
    // int portnum=5555;
    printf("port number %d ",portnum);
    sockfd =socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        printf("Error creating socket!\n");
        exit(1);
    }
    printf("Socket created \n");

    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(portnum);


    ret = bind(sockfd,(struct sockaddr *) &addr, sizeof(addr));
    if (ret < 0){
        printf("Error binding!\n");
        exit(1);
    }
    printf("Binding done...\n");

    printf("Waiting for a connection...\n");

    listen(sockfd, 5); //hello is anybody going to call me :{
    printf("da li smo prosli \n");
    len =sizeof(cl_addr);
    newsockfd = accept(sockfd,(struct sockaddr *) &cl_addr, &len);
    if (newsockfd < 0) {
        printf("Error accepting connection!\n");
        exit(1);
    }

    inet_ntop(AF_INET, &(cl_addr.sin_addr), clientAddr, CLADDR_LEN);
    printf("Connection accepted from %s...\n", clientAddr);

    memset(buffer,0,BUF_SIZE);
    printf("time to send some shit over the ethernet\n");
//    if(pthread_mutex_init(&mut, NULL)!=0){
//        printf("mutex init failed \n");
//        exit(1);
//    }

    printf("making threads\n");

}

void *init_timeout() {

    guint i=0,j=0;




    //GArray *new_task_list;
    GArray *new_task_list=g_array_new (FALSE, FALSE, sizeof (Task));
    GArray *new_device_list=g_array_new (FALSE, FALSE, sizeof (Devices));
    GArray *new_interrupt_list= g_array_new (FALSE, FALSE, sizeof (Interrupts));
  //  new_task_list =  get_task_list2();
  //  new_device_list   = device(device_all);
    Cpu_usage1 cpu_usage1;


    primanje(&newsockfd,new_interrupt_list,&cpu_usage1,new_task_list,new_device_list);
   // primanje(&newsockfd,new_interrupt_list,&cpu_usage1);
    //primanje_interrupta(&newsockfd);
     start_stop();

    //new_interrupt_list=interrupt_usage();
    poredjenje(new_interrupt_list,interrupt_array_temp,interrupt_array_d);
   g_array_free(interrupt_array_temp,TRUE);
    interrupt_array_temp=g_array_new (FALSE, FALSE, sizeof (Interrupts));

    upis(new_interrupt_list,interrupt_array_temp);
  //  interrupt_array_temp=interrupt_usage();
    //   printf("%d\n",interrupt_array_temp->len);





    for(i = 0; i < names_array->len; i++) //uzimamo element niza
    {
        Devices *tmp = &g_array_index(names_array, Devices, i);
        tmp->checked = FALSE;
        // printf("%s\n",tmp->name);
        for(j = 0; j < new_device_list->len; j++)
        {
            Devices *new_tmp = &g_array_index(new_device_list, Devices, j);

            if(strcmp(new_tmp->directory, tmp->directory)==0 &&strcmp(new_tmp->name, tmp->name)==0 && strcmp(new_tmp->type, tmp->type)==0&&
                        new_tmp->fid==tmp->fid && new_tmp->total ==tmp->total
                    )  //poredimo elemente nizova
            {
              //  if(strcmp(new_tmp->name, tmp->name)==0) {

                    if((gint)tmp->avail != (gint)new_tmp->avail //ako ima razlika
                       /* || strcmp(tmp->used,new_tmp->used)*/ ||
                   //    strcmp(tmp->type,new_tmp->type)!=0 ||
                     //  strcmp(tmp->name,new_tmp->name)!=0 ||
                       (unsigned int)tmp->used != (unsigned int)new_tmp->used ||
                       (unsigned int)tmp->free != (unsigned int)new_tmp->free ||
                       (unsigned int)tmp->total != (unsigned int)new_tmp->total) //||
                        // (unsigned int)tmp->time != (unsigned int)tmp->old_time)
                    {
                        tmp->avail = new_tmp->avail;
                        //strcpy(tmp->name, new_tmp->name);
                     //   strcpy(tmp->type, new_tmp->type);
                        tmp->used = new_tmp->used;
                        tmp->total = new_tmp->total;
                        tmp->free = new_tmp->free;

                        refresh_list_item_device(i);
                      //  printf("I %d name %s directory %s size %lu\n",i,tmp->name,tmp->directory,tmp->total);
                    }
                    tmp->checked = TRUE; //
                    new_tmp->checked = TRUE;
                    break;
             //   }

            }
            else
                tmp->checked = FALSE;
        }
    }
    /* check for unchecked old-tasks for deleting */
    i = 0;
    while( i < names_array->len)
    {

        Devices *tmp = &g_array_index(names_array, Devices, i);
     //   printf("name %s I %d checked %s \n",tmp->name,i,tmp->checked  ? "TRUE" : "FALSE");
        if(!tmp->checked)//element niza koji se ne nalazi vise u novom nizu
        {
            remove_list_item_device(tmp->directory,tmp->name,tmp->type);
            g_array_remove_index(names_array, i);
           // printf("we removed a item from the list I [%d] name: %s directry: %s\n",i,tmp->name,tmp->directory);
            dev_num--;
        }
        else
            i++;

    }


    /* check for unchecked new tasks for inserting */
    for(i = 0; i < new_device_list->len; i++)
    {
        Devices *new_tmp = &g_array_index(new_device_list, Devices, i);

        if(!new_tmp->checked)
        {
            Devices *new_device = new_tmp;

            g_array_append_val(names_array, *new_device);
            //   if(( new_task->uid == own_uid))
            add_new_list_item_dev(dev_num);
          //  printf("new item added for no reason %d name %s\n",i,new_device->name);
            dev_num++;
        }
    }

////////////

    for(i = 0; i < task_array->len; i++)
    {
       Task *tmp = &g_array_index(task_array, Task, i);
        tmp->checked = FALSE;
           // printf("%s\n",tmp->name);
        for(j = 0; j < new_task_list->len; j++)
        {
            Task *new_tmp = &g_array_index(new_task_list, Task, j);

            if(new_tmp->pid == tmp->pid)
            {

                if((gint)tmp->ppid != (gint)new_tmp->ppid || strcmp(tmp->state,new_tmp->state)!=0 ||
                        (unsigned int)tmp->cpu_system != (unsigned int)new_tmp->cpu_system ||
                        (unsigned int)tmp->cpu_user != (unsigned int)new_tmp->cpu_user ||
                        (unsigned int)tmp->rss != (unsigned int)new_tmp->rss) //||
                       // (unsigned int)tmp->time != (unsigned int)tmp->old_time)
                {
                    tmp->ppid = new_tmp->ppid;
                    strcpy(tmp->state, new_tmp->state);
                    tmp->cpu_user = new_tmp->cpu_user;
                    tmp->cpu_system = new_tmp->cpu_system;
                    tmp->rss = new_tmp->rss;

                    refresh_list_item(i);
                }
                tmp->checked = TRUE;
                new_tmp->checked = TRUE;
                break;
            }
            else
                tmp->checked = FALSE;
        }
    }

    /* check for unchecked old-tasks for deleting */
    i = 0;
    while( i < task_array->len)
    {

       Task *tmp = &g_array_index(task_array, Task, i);

        if(!tmp->checked)
        {
            remove_list_item((gint)tmp->pid);
            g_array_remove_index(task_array, i);
            tasks_num--;
        }
        else
            i++;

    }


    /* check for unchecked new tasks for inserting */
    for(i = 0; i < new_task_list->len; i++) {
        Task *new_tmp = &g_array_index(new_task_list, Task, i);

        if (!new_tmp->checked) {
            Task *new_task = new_tmp;

            g_array_append_val(task_array, *new_task);
            //   if(( new_task->uid == own_uid))
            add_new_list_item(tasks_num);
            tasks_num++;
        }
    }
    cpu_percent_change(&cpu_usage1);//nije ovde
//get_memory_usage();//nije ovde



    cpu_change(&cpu_usage1);


   memory_change(label);// nije ovde
    swap_change(label1); // nije ovde

    time_handler(window);
   // g_array_free(new_task_list, TRUE);

     //g_array_free(interrupt_array_temp, TRUE);
   // g_array_free(new_interrupt_list,TRUE);
   // g_array_unref(interrupt_array_d);


    g_array_free(new_device_list,TRUE);
    bjorg++;



    time_step = 60000 / t;

    if (bjorg >= time_step) {


        bjorg = time_step;
    }


    if (refresh == 0) {

        refresh = g_timeout_add(t, (GSourceFunc) init_timeout, NULL);
    }

};


int main(int argc, char *argv[]) {

    pthread_t t1,t2;

gtk_init(&argc, &argv);
        if(argc<2){

            printf("port not providec \n");
            exit(1);
        }
  //  pthread_create(&t1,NULL,conekcija,(void*)argv[1]);
    conekcija(argv[1]);


    dev_swindow = gtk_scrolled_window_new(NULL,
                                          NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(dev_swindow), GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_ALWAYS);
    process_swindow = gtk_scrolled_window_new(NULL,
                                              NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(process_swindow), GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_ALWAYS);



    ncpu = cpu_number();

    interface_name();
    //array_interrupts();



    task_array=g_array_new (FALSE, FALSE, sizeof (Task));

    interrupt_array_temp=g_array_new (FALSE, FALSE, sizeof (Interrupts));
    interrupt_array_d=g_array_new (FALSE, TRUE, sizeof (Interrupts));


    //names_temp=g_array_new (FALSE, FALSE, sizeof (Devices));
    names_array=g_array_new (FALSE, FALSE, sizeof (Devices));



    for (int i = 0; i < 8; i++) {
        history[i] = g_array_new(FALSE, TRUE, sizeof(gfloat));

    }
    for (int i = 0; i <= 3; i++) {

        g_array_set_size(history[i], 240);//max steps
    }
    for (int i = 4; i <= 5; i++) {

        g_array_set_size(history[i], 60);
    }
    for (int i = 6; i <= 7; i++) {


        g_array_set_size(history[i], 240);
    }

  //  GArray *new_interrupt_list;

  //  interrupt_array_temp=interrupt_usage();





       // upis(new_interrupt_list,interrupt_array_temp);

     //   g_array_free(new_interrupt_list,TRUE);

    window= main_window(dev_swindow,process_swindow);
    g_signal_connect(button, "clicked", G_CALLBACK(inc_refresh), NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(dec_refresh), NULL);
    g_signal_connect(button_proc, "toggled", G_CALLBACK(button_clicked_view_process), NULL);

    g_signal_connect(button_dev, "toggled", G_CALLBACK(dev_button_clicked2), NULL);



    g_signal_connect(button_graph, "clicked", G_CALLBACK(graph_button_clicked), NULL);
    g_signal_connect(button_condition, "clicked", G_CALLBACK(start_stop), NULL);
    g_signal_connect_swapped ((gpointer) treeview, "button-press-event", G_CALLBACK(on_treeview1_button_press_event), NULL);


    g_signal_connect(G_OBJECT(graph1), "draw",
                     G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(G_OBJECT(graph2), "draw",
                     G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(G_OBJECT(graph3), "draw",
                     G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(G_OBJECT(graph4), "draw",
                     G_CALLBACK(on_draw_event), NULL);



    g_timeout_add(1000, (GSourceFunc) init_timeout2, NULL);
        init_timeout();


// pthread_create(&t1,NULL,init_timeout,NULL);
//pthread_create(&t2,NULL,init_timeout2,NULL);


    gtk_widget_show_all(window);

//
//    gtk_widget_hide(dev_swindow);
//   gtk_widget_hide(process_swindow);
//    gtk_widget_hide(hbox1);
//    gtk_widget_hide(hbox3);
//    gtk_widget_hide(hbox2);


    gtk_main();
 //   g_thread_join(tg);


    if (refresh > 0){
        g_source_remove (refresh);

    }






    return 0;
}
