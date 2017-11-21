void *slanje(void *socket){

    int  ret;

    guint num_packets;

    struct	my_thread_info *info = socket;

    while(1) {
          // pthread_mutex_lock(&m);
//        if(rezultat==1){
//            pthread_cond_wait(&cond,&m);
//            printf("condition WAS met\n");
//        }
        data_s data;


        get_memory_usage(&data);
        time_t time1 = time(NULL);
        /*    struct tm*/ tm1 = *localtime(&time1);
//        if(rezultat==0){
//            pthread_cond_wait(&cond,&m);
//           printf("condtion was met\n");
//       }


        ret = (int) send(info->thread_socket, &data, sizeof(data_s), 0);

        if (ret < 0) {
            printf("Error sending data!\n\t");
            //  break;
            exit(1);
        } else {

//                printf(" sending data!\n\t %f %lli %lli %lli \n", data.memory_usage.swap_percentage,
//                       data.memory_usage.swap_used
//                        ,data.memory_usage.memory_total,
//                       data.memory_usage.memory_used);

        }


        GArray *ginterrupts = interrupt_usage();
        num_packets = ginterrupts->len;

        //  char num_packtes_c[BUF_SIZE];
        //          sprintf(num_packtes_c, "%d", num_packets);.
        //     printf("num of packets %d\n",num_packets);
        ret = (int) send(info->thread_socket, &num_packets, sizeof(guint), 0);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");
            //  break;
            exit(1);
        }
        for (int i = 0; i < ginterrupts->len; i++) {

            Interrupts *interrupts1;
            interrupts1 = &g_array_index(ginterrupts, Interrupts, i);
            data.interrupts.CPU0 = interrupts1->CPU0;
            data.interrupts.CPU1 = interrupts1->CPU1;
            data.interrupts.CPU2 = interrupts1->CPU2;
            data.interrupts.CPU3 = interrupts1->CPU3;
            for (int j = 0; j < sizeof(interrupts1->name); j++) {
                data.interrupts.name[j] = interrupts1->name[j];
            }

            upis_imena(interrupts1, &data.interrupts);

            ret = (int) send(info->thread_socket, &data, sizeof(data_s), 0);

            if (ret < 0) {
                printf("Error sending data!\n\t");
                //  break;
                exit(1);
            } else {

                //    printf(" sending data!\n\t %lu %lu %lu %lu %s %s %s %s %s  \n", data.interrupts.CPU0,data.interrupts.CPU1,data.interrupts.CPU2,
                //            data.interrupts.CPU3,  data.interrupts.name,data.interrupts.ime1,data.interrupts.ime2,data.interrupts.ime3,data.interrupts.ime4);

            }

        }

        int ncpu = cpu_number();
          cpu_percentage(ncpu,&data.cpu_usage);

        ret = (int) send(info->thread_socket, &data, sizeof(data_s), 0);
        if (ret < 0) {
            printf("Error sending data!\n\t");
            //  break;
            exit(1);
        } else {
//            printf("CPU usage %f %f %f %f\n",data.cpu_usage.percentage0,
//                   data.cpu_usage.percentage1,
//                   data.cpu_usage.percentage2,
//                   data.cpu_usage.percentage3);
        }
        GArray *task_list =g_array_new(FALSE,FALSE,sizeof(Task));

        get_task_list(task_list);
        num_packets = task_list->len;
//
       ret = (int) send(info->thread_socket, &num_packets, sizeof(guint), 0);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");

            exit(1);
        }
        for (int i = 0; i < task_list->len; i++) {

            Task *tasks;

            tasks = &g_array_index(task_list, Task, i);
            size_t g = strlen(tasks->name);
            for (int r = 0; r <= g; r++) {

                data.task.name[r] = tasks->name[r];

            }
            g = strlen(tasks->state);
            for (int r = 0; r <= g; r++) {

               data.task.state[r] = tasks->state[r];

            }
            g = strlen(tasks->uid_name);
            for (int r = 0; r <= g; r++) {

               data.task.uid_name[r] = tasks->uid_name[r];

            }
            data.task.uid = tasks->uid;
            data.task.cpu_system = tasks->cpu_system;
            data.task.cpu_user = tasks->cpu_user;
            data.task.vsz = tasks->vsz;
            data.task.rss = tasks->rss;
            data.task.prio = tasks->prio;

            data.task.pid = tasks->pid;
            data.task.ppid = tasks->ppid;
            data.task.start_time=tasks->start_time;
            data.task.duration.tm_sec =tasks->duration.tm_sec;
            data.task.duration.tm_min =tasks->duration.tm_min;
            data.task.duration.tm_hour =tasks->duration.tm_hour;
            data.task.stime.tm_sec =tasks->stime.tm_sec;
            data.task.stime.tm_min =tasks->stime.tm_min;
            data.task.stime.tm_hour =tasks->stime.tm_hour;
            data.task.checked=FALSE;
         //   printf( "vreme trajanja rada %d %d %d\n",tasks->duration.tm_hour,
          //          tasks->duration.tm_min,
          //          tasks->duration.tm_sec);
            ret = (int) send(info->thread_socket, &data, sizeof(data_s), 0);

            if (ret < 0) {
                printf("Error sending data!\n\t");
                //  break;
                exit(1);
            }
          }


    GArray *devices_list= device(devices_show);
        num_packets = devices_list->len;
//
        ret = (int) send(info->thread_socket, &num_packets, sizeof(int), 0);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");

            exit(1);
        }
        for (int i = 0; i < devices_list->len; i++) {

            Devices *devices;

            devices = &g_array_index(devices_list, Devices, i);
            size_t g = strlen(devices->name);
            for (int r = 0; r <= g; r++) {

                data.devices.name[r] = devices->name[r];

            }
            g = strlen(devices->directory);
            for (int r = 0; r <= g; r++) {

                data.devices.directory[r] = devices->directory[r];

            }
            g = strlen(devices->type);
            for (int r = 0; r <= g; r++) {

                data.devices.type[r] = devices->type[r];

            }
            data.devices.avail = devices->avail;
            data.devices.fid = devices->fid;
            data.devices.free = devices->free;
            data.devices.total = devices->total;
            data.devices.used = devices->used;
            data.devices.checked=FALSE;

         //    printf("%lu, %lu,%lu,%lu %lu, %s %s %s\n",data.devices.used,data.devices.avail,data.devices.fid,data.devices.free,data.devices.total,data.devices.name,data.devices.directory,data.devices.type);
            ret = (int) send(info->thread_socket, &data, sizeof(data_s), 0);

            if (ret < 0) {
                printf("Error sending data!\n\t");
                //  break;
                exit(1);
            }
        }

        data.network=received_transfered();
        ret = (int) send(info->thread_socket, &data, sizeof(data_s), 0);
       // printf("%lli, %lli",data.network.received_bytes,data.network.transmited_bytes);
        if (ret < 0) {
            printf("Error sending data!\n\t");
            //  break;
            exit(1);
        }




        tm1.tm_year+=1900;
        tm1.tm_mon+=1;
        ret = (int) send(info->thread_socket, &tm1, sizeof(tm1), 0);
        if (ret<0) {
            printf("ERROR: Return Code  is %d\n", ret);
            exit(1);
        }
       g_array_free(devices_list,TRUE);
        g_array_free(ginterrupts,TRUE);
        g_array_free(task_list,TRUE);
//      gchar *  rec_bytes = g_format_size_full(data.network.received_bytes, G_FORMAT_SIZE_IEC_UNITS);
//        gchar *  transmitted_bytes = g_format_size_full(data.network.transmited_bytes, G_FORMAT_SIZE_IEC_UNITS);

//            printf("%s %s \n",rec_bytes,transmitted_bytes);
//            g_free(rec_bytes);
//            g_free(transmitted_bytes);
        //    pthread_mutex_unlock(&m);
            pthread_cond_wait(&cond, &m);

         //  sleep(1); //treba uvesti cond variable koja kaze sada salji sada ne salji :P  #thread2
        }


}