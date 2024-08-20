#include "global.h"
#include "session.h"
#include "server.h"

int main(int argc, char *argv[]) {
    global();
    session();
    server();
    return 0;
}