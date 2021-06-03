// encode UTF-8

// @Author        : Aged_cat
// @Date          : 2021-05-04


#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <unordered_map>
#include <fcntl.h>  //open
#include <unistd.h> //close
#include <sys/stat.h> //stat
#include <sys/mman.h> //mmap,munmap
#include <assert.h>

#include "buffer.h"

class HTTPresponse
{
public:
    HTTPresponse();
    ~HTTPresponse();

    void init(const std::string& srcDir,std::string& path,bool isKeepAlive=false,int code=-1);
    void makeResponse(Buffer& buffer);
    void unmapFile_();
    char* file();
    size_t fileLen() const;
    void errorContent(Buffer& buffer,std::string message);
    int code() const {return code_;}


private:
    void addStateLine_(Buffer& buffer);
    void addResponseHeader_(Buffer& buffer);
    void addResponseContent_(Buffer& buffer);

    void errorHTML_();
    std::string getFileType_();

    int code_;
    bool isKeepAlive_;

    std::string path_;
    std::string srcDir_;

    char* mmFile_;
    struct  stat mmFileStat_;

    static const std::unordered_map<std::string, std::string> SUFFIX_TYPE;
    static const std::unordered_map<int, std::string> CODE_STATUS;
    static const std::unordered_map<int, std::string> CODE_PATH;
    
};



#endif //HTTP_RESPONSE_H