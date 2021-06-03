// encode UTF-8

// @Author        : Aged_cat
// @Date          : 2021-05-04

#ifndef HTTP_CONNECTION_H
#define HTTP_CONNECTION_H

#include<arpa/inet.h> //sockaddr_in
#include<sys/uio.h> //readv/writev
#include<iostream>
#include<sys/types.h>
#include<assert.h>

#include "buffer.h"
#include "HTTPrequest.h"
#include "HTTPresponse.h"

class HTTPconnection{
public:
    HTTPconnection();
    ~HTTPconnection();

    void initHTTPConn(int socketFd,const sockaddr_in& addr);

    //每个连接中定义的对缓冲区的读写接口
    ssize_t readBuffer(int* saveErrno);
    ssize_t writeBuffer(int* saveErrno);

    //关闭HTTP连接的接口
    void closeHTTPConn();
    //定义处理该HTTP连接的接口，主要分为request的解析和response的生成
    bool handleHTTPConn();

    //其他方法
    const char* getIP() const;
    int getPort() const;
    int getFd() const;
    sockaddr_in getAddr() const;

    int writeBytes()
    {
        return iov_[1].iov_len+iov_[0].iov_len;
    }

    bool isKeepAlive() const
    {
        return request_.isKeepAlive();
    }

    static bool isET;
    static const char* srcDir;
    static std::atomic<int>userCount;

private:
    int fd_;                  //HTTP连接对应的描述符
    struct sockaddr_in addr_;
    bool isClose_;            //标记是否关闭连接

    int iovCnt_;
    struct iovec iov_[2];

    Buffer readBuffer_;       //读缓冲区
    Buffer writeBuffer_;      //写缓冲区

    HTTPrequest request_;    
    HTTPresponse response_;

};

#endif //HTTP_CONNECTION_H