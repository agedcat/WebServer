# WebServer

用C++实现的高性能WEB服务器，经过webbenchh压力测试可以实现上万的QPS

项目地址：https://github.com/Aged-cat/WebServer

## 功能

- 利用IO复用技术Epoll与线程池实现多线程的Reactor高并发模型；
- 利用正则与状态机解析HTTP请求报文，实现处理静态资源的请求；
- 利用标准库容器封装char，实现自动增长的缓冲区；
- 基于堆结构实现的定时器，关闭超时的非活动连接；
- 改进了线程池的实现，QPS提升了45%+；

## 项目详解

[WebServer项目——buffer详解](https://www.agedcat.com/post/66ac85ff.html)

[WebServer项目——epoller详解](https://www.agedcat.com/post/bcf82ea4.html)

[WebServer项目——timer详解](https://www.agedcat.com/post/f410f66e.html)

[WebServer项目——threadpool详解](https://www.agedcat.com/post/678e35eb.html)

[WebServer项目——HTTPconnection详解](https://www.agedcat.com/post/8b7b6922.html)

[WebServer项目——HTTPrequest详解](https://www.agedcat.com/post/8b528cc7.html)

[WebServer项目——HTTPresponse详解](https://www.agedcat.com/post/5b7b173e.html)

[WebServer项目——webserver详解](https://www.agedcat.com/post/1308746a.html)

## 环境要求

- Linux
- C++11

## 项目启动

```
mkdir bin
make
./bin/myserver
```

## 压力测试

```
./webbench-1.5/webbench -c 100 -t 10 http://ip:port/
./webbench-1.5/webbench -c 1000 -t 10 http://ip:port/
./webbench-1.5/webbench -c 5000 -t 10 http://ip:port/
./webbench-1.5/webbench -c 10000 -t 10 http://ip:port/
```

- 测试环境: Ubuntu:20 cpu:i7-4790 内存:16G

## 性能表现

与[markparticle](https://github.com/markparticle/WebServer/)的C++服务器做一个比较(表格中的为QPS的值)：

|      |  10   |  100  | 1000  | 10000 |
| :--: | :---: | :---: | :---: | :---: |
| old  | 8929  | 9126  | 9209  |  155  |
| new  | 11478 | 13578 | 13375 |  106  |

性能提升了45%

## 致谢

@[markparticle](https://github.com/markparticle/WebServer/)


