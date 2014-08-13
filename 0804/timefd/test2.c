#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/timerfd.h>
#include <poll.h>
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


    struct pollfd event[1];
    event[0].fd = timerfd;
    event[0].events = POLLIN;
    char buf[1024];

    while(1)
    {
        int ret = poll(event, 1, 10000);
        if(ret == -1)
            ERR_EXIT("poll");
        else if(ret == 0)
            printf("timeout\n");
        else
        {
            //这里必须read，否则poll被不停的触发
            if(read(timerfd, buf, sizeof buf) == -1)
                ERR_EXIT("read");
            printf("foobar .....\n");
        }
    }


    close(timerfd);


    return 0;
}

