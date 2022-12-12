#include <iostream>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <ctime>
#ifndef _WIN32
#include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#include <sys/socket.h>
#endif

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>

static void cb(evutil_socket_t fd, short what, void* arg)
{
    static int n = 0;
    std::cout << "event ocurrence every 2 seconds." << ++n << std::endl;
    if (n == 2) {
        event_base* base = (event_base*)arg;
        event_base_loopbreak(base);
    }

}

int main()
{
#ifdef _WIN32
    WSADATA wsa_data;
    WSAStartup(0x0201, &wsa_data);
#endif
    timeval two_sec = { 2, 0 };
    event_base* base = event_base_new();
    
    event* timeout = event_new(base, -1, EV_PERSIST | EV_TIMEOUT, cb, base);
    //event* timeout = event_new(base, -1, EV_TIMEOUT, cb, NULL);

    event_add(timeout, &two_sec);
    event_base_dispatch(base);
    event_base_free(base);
    return 0;

    //std::cout << "Hello World!\n";
}