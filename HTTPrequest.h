// encode UTF-8

// @Author        : Aged_cat
// @Date          : 2021-05-04

#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <regex>

#include "buffer.h"

class HTTPrequest
{
public:
    enum PARSE_STATE{
        REQUEST_LINE,
        HEADERS,
        BODY,
        FINISH,
    };

    enum HTTP_CODE {
        NO_REQUEST = 0,
        GET_REQUEST,
        BAD_REQUEST,
        NO_RESOURSE,
        FORBIDDENT_REQUEST,
        FILE_REQUEST,
        INTERNAL_ERROR,
        CLOSED_CONNECTION,
    };

    HTTPrequest() {init();};
    ~HTTPrequest()=default;

    void init();
    bool parse(Buffer& buff); //解析HTTP请求

    //获取HTTP信息
    std::string path() const;
    std::string& path();
    std::string method() const;
    std::string version() const;
    std::string getPost(const std::string& key) const;
    std::string getPost(const char* key) const;

    bool isKeepAlive() const;

private:
    bool parseRequestLine_(const std::string& line);//解析请求行
    void parseRequestHeader_(const std::string& line); //解析请求头
    void parseDataBody_(const std::string& line); //解析数据体


    void parsePath_();
    void parsePost_();

    static int convertHex(char ch);

    PARSE_STATE state_;
    std::string method_,path_,version_,body_;
    std::unordered_map<std::string,std::string>header_;
    std::unordered_map<std::string,std::string>post_;

    static const std::unordered_set<std::string>DEFAULT_HTML;
   


};





#endif  //HTTP_REQUEST_H