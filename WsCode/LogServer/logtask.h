
#include "fd_mgr.h"
#include "circular_buffer.h"

typedef enum {
  LOG_TASK_RUNNING = 0,
  LOG_TASK_KILL,
  LOG_TASK_DEAD,
} LogTaskStateType;

#define UDP_LISTENER_PORT  5309
#define TCP_CLIENT_PORT    5310

class tcp_acceptor;
class udp_listener;
class tcp_client;

extern LogTaskStateType g_log_task_die_flag;

extern int log_task_main();

class udp_listener : public fd_interface {
    LList <fd_interface,FD_MGR_DLL2_EXTERN_INDEX>  clients;
public:
    static const int MAX_PACKET_SIZE = 8192;
    udp_listener(int port);
    /*virtual*/ ~udp_listener( void );
    /*virtual*/ void select_rw ( fd_mgr *, bool * do_read, bool * do_write );
    /*virtual*/ rw_response read ( fd_mgr * mgr );
    /*virtual*/ rw_response write( fd_mgr * mgr );
    /*virtual*/ bool write_to_fd( char * buf, int len );
    /*virtual*/ bool over_write_threshold( void );
    void register_tcp_client( tcp_client * c );
    void unregister_tcp_client( tcp_client * c );
};

class tcp_acceptor : public fd_interface {
    udp_listener * listener;
public:
    tcp_acceptor(int port, udp_listener * _listener);
    /*virtual*/ ~tcp_acceptor( void );
    /*virtual*/ void select_rw ( fd_mgr *, bool * do_read, bool * do_write );
    /*virtual*/ rw_response read ( fd_mgr * mgr );
    /*virtual*/ rw_response write( fd_mgr * mgr );
    /*virtual*/ bool write_to_fd( char * buf, int len );
    /*virtual*/ bool over_write_threshold( void );
};

class tcp_client : public fd_interface {
    tcp_acceptor * acceptor;
    udp_listener * listener;
    circular_buffer * buffer;
    static const int BUFFER_SIZE = 16384;
    static const int BUFFER_THRESHOLD = 2048;
public:
    tcp_client(int _fd, tcp_acceptor * _acceptor,
               udp_listener * _listener);
    /*virtual*/ ~tcp_client( void );
    /*virtual*/ void select_rw ( fd_mgr *, bool * do_read, bool * do_write );
    /*virtual*/ rw_response read ( fd_mgr * mgr );
    /*virtual*/ rw_response write( fd_mgr * mgr );
    /*virtual*/ bool write_to_fd( char * buf, int len );
    /*virtual*/ bool over_write_threshold( void );
};

