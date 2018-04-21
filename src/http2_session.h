//
// Created by Yu Gan on 2018/4/18.
//

#ifndef WRK2_HTTP2_SESSION_H
#define WRK2_HTTP2_SESSION_H

#include "nghttp2/nghttp2.h"
#include "hashmap.h"
#include "wrk.h"

#define HTTP2_REQ_METHOD_LEN 16
#define HTTP2_REQ_PATH_LEN 256
#define HTTP2_REQ_HOST_LEN 256

typedef struct http2_request{
    char scheme[8];
    char method[HTTP2_REQ_METHOD_LEN + 1];
    char host[HTTP2_REQ_HOST_LEN + 1] ;
    int port;
    char path[HTTP2_REQ_PATH_LEN + 1];
    char *body;
    
} http2_request;

struct connection;
struct http2_session;
typedef int (*http2_response_complete_cb) (struct http2_session *, uint32_t);

typedef struct http2_session{
    struct connection *conn;
    nghttp2_session *session_;
    map_t req_timestamps;
    map_t resp_timestamps;
    http2_request *h2_req;
    http2_response_complete_cb on_resp_complete;

} http2_session;


http2_session* create_http2_session(struct connection *c, http2_response_complete_cb cb);

void print_header(FILE *f, const uint8_t *name, size_t namelen,
                         const uint8_t *value, size_t valuelen);

void print_headers(FILE *f, nghttp2_nv *nva, size_t nvlen); 

#endif //WRK2_HTTP2_SESSION_H
