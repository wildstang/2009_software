
#include <stdio.h>
#include <sys/times.h>

#include "logtask.h"

LogTaskStateType g_log_task_die_flag = LOG_TASK_RUNNING;

int
log_task_main()
{
    struct timeval tv;
    udp_listener * listener;
    tcp_acceptor * acceptor;
    fd_mgr       * mgr;

    listener = new udp_listener(UDP_LISTENER_PORT);
    acceptor = new tcp_acceptor(TCP_CLIENT_PORT, listener);
    mgr = new fd_mgr(false);

    mgr->register_fd( listener );
    mgr->register_fd( acceptor );

    while (g_log_task_die_flag == LOG_TASK_RUNNING)
    {
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        mgr->loop( &tv );
    }

    mgr->unregister_fd(listener);
    delete mgr;
    delete listener;

    g_log_task_die_flag = LOG_TASK_DEAD;

    while(1)
    {
    }

    return 0;
}
