/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: 一  7/20 21:58:14 2020
 ************************************************************************/

#include<stdio.h>
#define MAX 10
int port；
char *conf = "./footballd.conf";
int main(int argc, char **argv) {
    int opt, listener, epollfd;
    pthread_t red_t, blue_t;
    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch (opt) {
            case 'p':
                port = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage : %s -p port\n", argv[0]);
                exit(1);
        }
    }
    //判断一配置文件合法性,如果不做合法性判断，在下面一行代码中，会很容易出现段错误，为什么呢？
    if (!port) port = atoi(get_conf_value(conf, "PORT"));
    if ((listener = socket_create_udp(port)) < 0) {
        perror("socket_create_udp()");
        exit(1);
    }
    epollfd = epoll_create(1);
    //安全判断
    truct epoll_event ev, events[MAX];
    ev.events = EPOLLIN;
    ev.data.fd = listener;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listener, &ev) < 0) {
        perror("epoll_ctl");
        exit(1);
    }
    while (1) {
        int nfds = epoll_wait(epollfd, events, MAX, -1);
        if (nfds < 0) {
            perror("epoll_wait()");
            exit(1);
        }
        for (int i = 0; i < nfds; i++) {
            struct User user;
            bzero(&user, sizeof(user));
            if (events[i].data.fd == listener) {
                int new_fd = udp_accept(listener, &user);
                if (new_fd > 0) {
                    printf("New Connection!\n");
                    //可用多线程，持续接受数据试试，如果需要的话，请参考我们上课写的程序
                }
            }
        }
    }
    return 0;
}
