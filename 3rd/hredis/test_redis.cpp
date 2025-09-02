#include <stdio.h>
#include <string.h>
#include <hiredis/hiredis.h>

void testRedis() {
    bool success = true;
    redisReply *reply = nullptr;
    redisContext *context = nullptr;

    // connect
    context = redisConnect("127.0.0.1", 6379);
    success = (context && !context->err);
    if (!success) {
        redisFree(context);
        return;
    }
    printf("connect %s\n", success ? "successed" : "failed");

    // auth user pass
    const char *redis_user = "default";
    const char *redis_pass = "3215";
    reply = (redisReply *)redisCommand(context,
                                       "auth %s %s",
                                       redis_user,
                                       redis_pass);
    success = (reply->type != REDIS_REPLY_ERROR);
    printf("auth %s\n", success ? "successed" : "failed");
    freeReplyObject(reply); // prevent memory leaks

    // set key val
    const char *command1 = "set stest1 value1";
    reply = (redisReply *)redisCommand(context, command1);
    success = (reply && reply->type == REDIS_REPLY_STATUS
               && strcmp(reply->str, "OK") == 0 || strcmp(reply->str, 0) == 0);
    printf("%s %s\n", command1, success ? "successed" : "failed");
    freeReplyObject(reply);

    // strlen key
    const char *command2 = "strlen stest1";
    reply = (redisReply *)redisCommand(context, command2);
    success = reply && reply->type == REDIS_REPLY_INTEGER;
    if (success) {
        int len = reply->integer;
        printf("%s success\n", command1);
        printf("'stest1' length: %d\n", len);
    } else {
        printf("%s failed\n", command1);
    }
    freeReplyObject(reply);

    // get key
    const char *command3 = "get stest1";
    reply = (redisReply *)redisCommand(context, command3);
    success = (reply != nullptr && reply->type == REDIS_REPLY_STRING);
    printf("%s %s\n", command3, success ? "successed" : "failed");
    printf("key: stest1, val: %s\n", reply->str);
    freeReplyObject(reply);

    // lpush key val
    const char *command4 = "lpush key2 val0";
    reply = (redisReply *)redisCommand(context, command4);
    success = (reply != nullptr
               && reply->type == REDIS_REPLY_INTEGER
               && reply->integer > 0);
    printf("%s %s\n", command4, success ? "successed" : "failed");
    if (reply->type == REDIS_REPLY_ERROR) {
        printf("%s\n", reply->str);
    }
    freeReplyObject(reply);


    redisFree(context);
}

int main(int argc, char *argv[]) {
    testRedis();
    return 0;
}