//
// Created by Yu Gan on 2018/4/18.
//

#include "http2_session.h"

static int on_frame_recv_cb(nghttp2_session *session, const nghttp2_frame *frame, void *user_data){
    http2_session *sess = (http2_session *) user_data;
    if (frame->hd.flags & NGHTTP2_FLAG_END_STREAM) {
        sess->on_resp_complete(sess, frame->hd.stream_id);  
    }
    return 0;
}

static void init_http2_session(http2_session *sess) {
    nghttp2_session_callbacks *callbacks;
    nghttp2_session_callbacks_new(&callbacks);
    nghttp2_session_callbacks_set_on_frame_recv_callback(callbacks, on_frame_recv_cb);
    nghttp2_session_client_new(&sess->session_, callbacks, sess);

}

http2_session* create_http2_session(connection *c, http2_response_complete_cb cb) {
    http2_session *sess = malloc(sizeof(http2_session));
    http2_request *req = malloc(sizeof(http2_request));
    sess->h2_req = req;
    sess->conn = c;
    sess->on_resp_complete = cb;
    sess->req_timestamps = NULL;
    init_http2_session(sess);
    return sess;
}

void print_header(FILE *f, const uint8_t *name, size_t namelen,
                         const uint8_t *value, size_t valuelen) {
    fwrite(name, 1, namelen, f);
    fprintf(f, ": ");
    fwrite(value, 1, valuelen, f);
    fprintf(f, "\n");
}

void print_headers(FILE *f, nghttp2_nv *nva, size_t nvlen) {
    size_t i;
    for (i = 0; i < nvlen; ++i) {
    print_header(f, nva[i].name, nva[i].namelen, nva[i].value, nva[i].valuelen);
    }
    fprintf(f, "\n");
}

void send_client_connection_header(http2_session *sess) {
//    nghttp2_settings_entry iv[1] = {
//            {NGHTTP2_SETTINGS_MAX_CONCURRENT_STREAMS, 100}};
    int rv;

    /* client 24 bytes magic string will be sent by nghttp2 library */
    rv = nghttp2_submit_settings(sess->session_, NGHTTP2_FLAG_NONE, NULL,
                                 0);
    if (rv != 0) {
        errx(1, "Could not submit SETTINGS: %s", nghttp2_strerror(rv));
    }
}














