// encode UTF-8

// @Author        : Aged_cat
// @Date          : 2021-05-04

#ifndef BUFFER_H
#define BUFFER_H

#include<vector>
#include<iostream>
#include<cstring>
#include<atomic>
#include<unistd.h> //read() write()
#include<sys/uio.h> //readv() writev()
#include<assert.h>

class Buffer{
public:
    Buffer(int initBufferSize=1024);
    ~Buffer()=default;

    //缓存区中可以读取的字节数
    size_t writeableBytes() const;
    //缓存区中可以写入的字节数
    size_t readableBytes() const;
    //缓存区中已经读取的字节数
    size_t readBytes() const;

    //获取当前读指针
    const char* curReadPtr() const;
    //获取当前写指针
    const char* curWritePtr() const;
    //更新读指针
    void updateReadPtr();
    //更新写指针
    void updateWritePtr();
    //将读指针和写指针初始化
    void initPtr();

    //保证将数据写入缓冲区
    void ensureWriteable(size_t len);
    //将数据写入到缓冲区
    void Append();

    //IO操作的读与写接口
    ssize_t ReadFd(int fd,int* Errno);
    ssize_t WriteFd(int fd,int* Errno);

    //将缓冲区的数据转化为字符串
    std::string AlltoStr();

private:
    //返回指向缓冲区初始位置的指针
    char* BeginPtr_();
    const char* BeginPtr_() const;
    //用于缓冲区空间不够时的扩容
    void allocateSpace(size_t len);

    std::vector<char>buffer_; //buffer的实体
    std::atomic<std::size_t>readPos_;//用于指示读指针
    std::atomic<std::size_t>writePos_;//用于指示写指针

};

# endif //BUFFER_H