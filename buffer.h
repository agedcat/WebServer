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
    const char* curWritePtrConst() const;
    char* curWritePtr();
    //更新读指针
    void updateReadPtr(size_t len);
    void updateReadPtrUntilEnd(const char* end);//将读指针直接更新到指定位置
    //更新写指针
    void updateWritePtr(size_t len);
    //将读指针和写指针初始化
    void initPtr();

    //保证将数据写入缓冲区
    void ensureWriteable(size_t len);
    //将数据写入到缓冲区
    void append(const char* str,size_t len);
    void append(const std::string& str);
    void append(const void* data,size_t len);
    void append(const Buffer& buffer);

    //IO操作的读与写接口
    ssize_t readFd(int fd,int* Errno);
    ssize_t writeFd(int fd,int* Errno);

    //将缓冲区的数据转化为字符串
    std::string AlltoStr();

    //test
    void printContent()
    {
        std::cout<<"pointer location info:"<<readPos_<<" "<<writePos_<<std::endl;
        for(int i=readPos_;i<=writePos_;++i)
        {
            std::cout<<buffer_[i]<<" ";
        }
        std::cout<<std::endl;
    }

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