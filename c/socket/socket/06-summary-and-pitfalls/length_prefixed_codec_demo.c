#include <arpa/inet.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MESSAGE_SIZE 1024

static size_t encode_frame(const char *msg, unsigned char *out, size_t out_size) {
    size_t len = strlen(msg);
    if (len > MAX_MESSAGE_SIZE || out_size < len + sizeof(uint32_t)) {
        return 0;
    }

    uint32_t net_len = htonl((uint32_t)len);
    memcpy(out, &net_len, sizeof(net_len));
    memcpy(out + sizeof(net_len), msg, len);
    return len + sizeof(net_len);
}

static int try_decode_frame(const unsigned char *buf, size_t buf_len,
                            char *out, size_t out_size, size_t *used) {
    if (buf_len < sizeof(uint32_t)) {
        return 0;
    }

    uint32_t net_len;
    memcpy(&net_len, buf, sizeof(net_len));
    uint32_t body_len = ntohl(net_len);

    if (body_len > MAX_MESSAGE_SIZE || body_len + 1 > out_size) {
        return -1;
    }

    if (buf_len < sizeof(uint32_t) + body_len) {
        return 0;
    }

    memcpy(out, buf + sizeof(uint32_t), body_len);
    out[body_len] = '\0';
    *used = sizeof(uint32_t) + body_len;
    return 1;
}

int main(void) {
    unsigned char stream[4096];
    size_t stream_len = 0;

    const char *messages[] = {"hello", "world", "tcp is a byte stream"};
    for (size_t i = 0; i < sizeof(messages) / sizeof(messages[0]); i++) {
        size_t n = encode_frame(messages[i], stream + stream_len,
                                sizeof(stream) - stream_len);
        if (n == 0) {
            fprintf(stderr, "encode failed\n");
            return 1;
        }
        stream_len += n;
    }

    printf("encoded %zu bytes as one byte stream\n", stream_len);

    size_t offset = 0;
    while (offset < stream_len) {
        char msg[MAX_MESSAGE_SIZE + 1];
        size_t used = 0;
        int rc = try_decode_frame(stream + offset, stream_len - offset,
                                  msg, sizeof(msg), &used);
        if (rc == 1) {
            printf("decoded message: %s\n", msg);
            offset += used;
        } else if (rc == 0) {
            printf("need more bytes\n");
            break;
        } else {
            fprintf(stderr, "invalid frame\n");
            return 1;
        }
    }

    return 0;
}
