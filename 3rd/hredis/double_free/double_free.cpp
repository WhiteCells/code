#include <hiredis/hiredis.h>
#include <iostream>

int main(int argc, char *argv[]) {
    redisContext *connection = redisConnect("127.0.0.1", 6379);
    if (!connection) {
        std::cout << "connection failed" << std::endl;
    }
    redisReply *reply = (redisReply *)redisCommand(connection, "set test1 val1");
    if (reply) {
        std::cout << "reply" << std::endl;
    }
    redisReply *reply2 = (redisReply *)redisCommand(connection, "get tet1");
    if (!reply2) {
        std::cout << "reply2 null" << std::endl;
    } else if (reply2->type == REDIS_REPLY_ERROR) {
        std::cout << "error" << std::endl;
    } else if (reply2->type != REDIS_REPLY_STRING) {
        std::cout << "no string" << std::endl;
        std::cout << reply2->type << std::endl; // #define REDIS_REPLY_NIL 4
    }
    // std::cout << reply2->str << std::endl;

    freeReplyObject(reply2);
    // freeReplyObject(reply2);

    redisFree(connection);
    return 0;
}