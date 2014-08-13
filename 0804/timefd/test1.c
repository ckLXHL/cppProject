#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/timerfd.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    //创建定时器的fd
    int timerfd = timerfd_create(CLOCK_REALTIME, 0);
    if(timerfd == -1)
        ERR_EXIT("timerfd_create");

    //开启定时器，并设置时间
    struct itimerspec howlong;
    memset(&howlong, 0, sizeof howlong);
    howlong.it_value.tv_sec = 5;  //初始时间
    howlong.it_interval.tv_sec = 1; //间隔时间
    if(timerfd_settime(timerfd, 0, &howlong, NULL) == -1)
        ERR_EXIT("timerfd_settime");

    int ret;
    char buf[1024];

    while((ret = read(timerfd, buf, sizeof buf)) > 0)
    {
        printf("foobar ....\n");
    }

    close(timerfd);


    return 0;
}

