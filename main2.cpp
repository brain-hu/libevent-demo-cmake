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
#include <event2/http.h>

void HttpGenericCallback(struct evhttp_request* request, void* arg)
{
    const struct evhttp_uri* evhttp_uri = evhttp_request_get_evhttp_uri(request);
    char url[8192];
    evhttp_uri_join(const_cast<struct evhttp_uri*>(evhttp_uri), url, 8192);

    printf("accept request url:%s\n", url);

    struct evbuffer* evbuf = evbuffer_new();
    if (!evbuf)
    {
        printf("create evbuffer failed!\n");
        return;
    }

    evbuffer_add_printf(evbuf, "Server response. Your request url is %s", url);
    
    evhttp_send_reply(request, HTTP_OK, "OK", evbuf);
    evbuffer_free(evbuf);
}

int main()
{
#ifdef _WIN32
    WSADATA wsa_data;
    WSAStartup(0x0201, &wsa_data);
#endif
    struct event_base* base = event_base_new();
    if (!base)
    {
        printf("create event_base failed!\n");
        return 1;
    }

    struct evhttp* http = evhttp_new(base);
    if (!http)
    {
        printf("create evhttp failed!\n");
        return 1;
    }

    evhttp_set_timeout(http, 120);


    if (evhttp_bind_socket(http, "0.0.0.0", 9999) != 0)
    {
        printf("bind socket failed! port:%d\n", 9999);
        return 1;
    }

    evhttp_set_gencb(http, HttpGenericCallback, NULL);

    event_base_dispatch(base);

    return 0;
}