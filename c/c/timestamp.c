#include <stdio.h>
#include <time.h>
#include <sys/time.h> // struct timeval

/*
    // get time stamp

    struct timeval tv;
    gettimeofday(&tv, NULL);

    time_t seconds = time(NULL);

    // time stamp to format time

    tm *localtime(const time_t *timer)
    tm *localtime_r(const time_t *timer, tm *tp)

    tm *gmtime(const time_t *timer)
    tm *gmtime_r(const time_t *timer, tm *tp)

 */

void getTimeStamp() {
    time_t stamp;
    time(&stamp);
    printf("%ld\n", stamp);

    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("%ld\n", tv.tv_sec);
}

// localtime
void getFormatTime1() {
    time_t seconds = time(NULL);
    struct tm *time = localtime(&seconds);

    char buf[64] = {};
    snprintf(buf, sizeof(buf), "%4d/%02d/%02d %02d:%02d:%02d",
             time->tm_year + 1900,
             time->tm_mon + 1,
             time->tm_mday,
             time->tm_hour,
             time->tm_min,
             time->tm_sec);
    printf("%s\n", buf);
}

/// gmtime
void getFormatTime2() {
    time_t seconds = time(NULL);
    struct tm *time = gmtime(&seconds);

    char buf[64] = {};
    snprintf(buf, sizeof(buf), "%4d/%02d/%02d %02d:%02d:%02d",
             time->tm_year + 1900,
             time->tm_mon + 1,
             time->tm_mday,
             time->tm_hour,
             time->tm_min,
             time->tm_sec);
    printf("%s\n", buf);
}

int main(int argc, char *argv[]) {
    getTimeStamp();
    getFormatTime1();
    getFormatTime2();
    return 0;
}