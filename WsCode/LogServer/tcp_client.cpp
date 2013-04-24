
#include <unistd.h>
#include <ioLib.h>

#include "logtask.h"

tcp_client :: tcp_client(int _fd,
                         tcp_acceptor * _acceptor,
                         udp_listener * _listener)
{
    fd = _fd;
    acceptor = _acceptor;
    listener = _listener;
    buffer = new circular_buffer(BUFFER_SIZE);
}

//virtual
tcp_client :: ~tcp_client( void )
{
    listener->unregister_tcp_client(this);
    close(fd);
    delete buffer;
}

//virtual
void
tcp_client :: select_rw ( fd_mgr *, bool * do_read, bool * do_write )
{
    *do_read = true;
    *do_write = (buffer->used_space() > 0);
}

//virtual
fd_interface :: rw_response
tcp_client :: read ( fd_mgr * mgr )
{
    char buf[16];
    int cc;

    cc = ::read(fd, buf, 16);
    if (cc <= 0)
        return DEL;

    printf("tcp_client read %d bytes from client\n", cc);

    return OKAY;
}

//virtual
fd_interface :: rw_response
tcp_client :: write( fd_mgr * mgr )
{
    char * buf;
    int size;
    int cc;

    buf = buffer->read_pos();
    size = buffer->contig_readable();
    if (size == 0)
        return OKAY;

    cc = ::write(fd, buf, size);
    if (cc <= 0)
        return DEL;

    buffer->record_read(cc);

    return OKAY;
}

//virtual
bool
tcp_client :: write_to_fd( char * buf, int len )
{
    buffer->write(buf, len);
    return OKAY;
}

//virtual
bool
tcp_client :: over_write_threshold( void )
{
    if (buffer->free_space() < BUFFER_THRESHOLD)
        return true;
    return false;
}
