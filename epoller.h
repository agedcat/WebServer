// encode UTF-8

// @Author        : Aged_cat
// @Date          : 2021-05-04

#ifndef EPOLLER_H
#define EPOLLER_H

#include<sys/epoll.h> //epoll_ctl()
#include<fcntl.h> //fcntl()
#include<unistd.h> //close()
#include<assert.h>
#include<vector>
#include<errno.h>

class Epoller{
public:
    explicit Epoller(int maxEvent=1024);
    ~Epoller();

    //将描述符fd加入epoll监控
    bool addFd(int fd,uint32_t events);
    //修改描述符fd对应的事件
    bool modFd(int fd,uint32_t events);
    //将描述符fd移除epoll的监控
    bool delFd(int fd);
    //用于返回监控的结果，成功时返回就绪的文件描述符的个数
    int wait(int timewait = -1);

    //获取fd的函数
    int getEventFd(size_t i) const;
    //获取events的函数
    uint32_t getEvents(size_t i) const;

private:
    int epollerFd_;//这是标志epoll的描述符
    std::vector<struct epoll_event>events_; //就绪的事件
};

#endif //EPOLLER_H