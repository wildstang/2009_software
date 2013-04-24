
#include <sockLib.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "logtask.h"

tcp_acceptor :: tcp_acceptor(int port, udp_listener * _listener)
{
    fd = socket( AF_INET, SOCK_STREAM, 0 );
    if ( fd < 0 )
    {
        fprintf( stderr, "\nsocket: %s\n", strerror( errno ));
        exit( 1 );
    }
    int v = 1;
    setsockopt( fd, SOL_SOCKET, SO_REUSEADDR, (char*) &v, sizeof( v ));
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons( port );
    sa.sin_addr.s_addr = INADDR_ANY;
    if ( bind( fd, (struct sockaddr *)&sa, sizeof( sa )) < 0 )
    {
        fprintf( stderr, "\nbind tcp: %s\n", strerror( errno ));
        exit( 1 );
    }
    listen( fd, 1 );
    make_nonblocking();
    listener = _listener;
}

//virtual
tcp_acceptor :: ~tcp_acceptor(void)
{
    close( fd );
}

//virtual
void
tcp_acceptor :: select_rw ( fd_mgr *, bool * do_read, bool * do_write )
{
    *do_read = true;
    *do_write = false;
}

//virtual
fd_interface :: rw_response
tcp_acceptor :: read ( fd_mgr * mgr )
{
    struct sockaddr_in sa;
    socklen_t  salen;

    salen = sizeof( sa );
    int new_fd = accept( fd, (struct sockaddr *)&sa, (int *)&salen );

    if ( new_fd < 0 )
    {
        if ( errno != EAGAIN )
            fprintf( stderr, "\naccept: %s\n", strerror( errno ));
        return OKAY;
    }

    tcp_client * c = new tcp_client(new_fd,this,listener);

    mgr->register_fd(c);
    listener->register_tcp_client(c);

    return OKAY;
}

//virtual
fd_interface :: rw_response
tcp_acceptor :: write( fd_mgr * mgr )
{
    // never called.
    return OKAY;
}

//virtual
bool
tcp_acceptor :: write_to_fd( char * buf, int len )
{
    // not used on an acceptor
	return false;
}

//virtual
bool
tcp_acceptor :: over_write_threshold( void )
{
    // not used on an acceptor
	return false;
}
