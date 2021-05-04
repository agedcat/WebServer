// encode UTF-8

// @Author        : Aged_cat
// @Date          : 2021-05-04

#ifndef HTTP_CONNECTION_H
#define HTTP_CONNECTION_H

#include<arpa/inet.h>


#include "buffer.h"
#include "HTTPrequest.h"
#include "HTTPresponse.h"

class HTTPconnection{
public:
    HTTPconnection();
    ~HTTPconnection();

    void initHTTPConn(int socketFd,const sockaddr_in& addr);

    //每个连接中定义的对缓冲区的读写接口
    ssize_t readBuffer();
    ssize_t writeBuffer();

    //关闭HTTP连接的接口
    void closeHTTPConn();
    //定义处理该HTTP连接的接口，主要分为request的解析和response的生成
    bool handleHTTPConn();

    //其他方法 TO DO

    static bool isET;

private:
    int fd_;                  //HTTP连接对应的描述符
    bool isClose_;            //标记是否关闭连接

    Buffer readBuffer_;       //读缓冲区
    Buffer writeBuffer_;      //写缓冲区

    HTTPrequest* request_;    
    HTTPresponse* response_;

};

#endif //HTTP_CONNECTION_H