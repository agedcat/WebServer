// encode UTF-8

// @Author        : Aged_cat
// @Date          : 2021-05-04

#ifndef TIMER_H
#define TIMER_H

#include<queue>
#include<deque>
#include<unordered_map>
#include<ctime>
#include<chrono>
#include<functional>
#include<memory>

#include "HTTPconnection.h"

//typedef std::function<void()> TimeoutCallBack;
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds MS;
typedef Clock::time_point TimeStamp;
typedef std::unique_ptr<HTTPconnection> HTTPconnection_Ptr;

class TimerNode{
    int id;             //用来标记定时器
    TimeStamp expire;   //设置过期时间
    //TimeoutCallBack cb; //设置一个回调函数用来方便删除定时器时将对应的HTTP连接关闭
    HTTPconnection_Ptr HTTPconn_Ptr;  //指向定时器对应的HTTP连接
    //需要的功能可以自己设定
};

struct timerCmp{
    //设置优先队列的比较函数
    bool operator()(std::shared_ptr<TimerNode> &a,std::shared_ptr<TimerNode> &b)
    {
        //to do
    }

};

class TimerManager{
    typedef std::shared_ptr<TimerNode> SP_TimerNode;
public:
    TimerManager();
    ~TimerManager();
    //设置定时器 
    void addTimer(int id,int timeout,HTTPconnection_Ptr HTTPconn_Ptr);
    //处理过期的定时器
    void handle_expired_event();

private:
    std::priority_queue<SP_TimerNode,std::deque<SP_TimerNode>,timerCmp> TimerNodeQueue; //保存所有的定时器

//需要的方法等可以定义

};






#endif //TIMER_H