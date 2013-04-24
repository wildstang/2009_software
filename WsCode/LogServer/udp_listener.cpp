
#include <sockLib.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "logtask.h"

udp_listener :: udp_listener(int port)
{
    fd = socket( AF_INET, SOCK_DGRAM, 0 );
    if (fd < 0)
        // what next?
        fprintf(stderr, "socket: %s\n", strerror(errno));

    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = INADDR_ANY;
    if (bind(fd, (struct sockaddr *)&sa, sizeof(sa)) < 0)
        // what now?
        fprintf(stderr, "bind udp socket: %s\n", strerror(errno));
}

//virtual
udp_listener :: ~udp_listener( void )
{
    if (clients.get_cnt() > 0)
    {
        fprintf(stderr, "not all clients are dead?\n");
        fd_interface * fdi;
        while ((fdi = clients.dequeue_head()) != NULL)
            delete fdi;
    }
    close(fd);
}

//virtual
void
udp_listener :: select_rw ( fd_mgr *, bool * do_read, bool * do_write )
{
    *do_read = true;
    *do_write = false;
}

//virtual
fd_interface :: rw_response
udp_listener :: read ( fd_mgr * mgr )
{
    char buf[MAX_PACKET_SIZE];
    int cc;

    cc = ::read(fd, buf, sizeof(buf));
    if (cc < 0)
    {
        fprintf(stderr, "udp receive: %s\n",
                strerror(errno));
        return OKAY;
    }
    if (cc == 0)
    {
        fprintf(stderr, "udp receive 0???\n");
        return OKAY;
    }

    fd_interface * fdi;

    for (fdi = clients.get_head();
         fdi;
         fdi = clients.get_next(fdi))
    {
        tcp_client * client = (tcp_client *) fdi;

        client->write_to_fd(buf, cc);
    }

    return OKAY;
}

//virtual
fd_interface :: rw_response
udp_listener :: write( fd_mgr * mgr )
{
    // not used
    return OKAY;
}

//virtual
bool
udp_listener :: write_to_fd( char * buf, int len )
{
    // not used
    return true;
}

//virtual
bool
udp_listener :: over_write_threshold( void )
{
    // not used
    return false;
}

void
udp_listener :: register_tcp_client( tcp_client * c )
{
    clients.add(c);
    printf("registered new tcp_client\n");
}

void
udp_listener :: unregister_tcp_client( tcp_client * c )
{
    clients.remove(c);
    printf("deleted tcp_client\n");
}
