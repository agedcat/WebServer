// encode UTF-8

// @Author        : Aged_cat
// @Date          : 2021-05-21

#include <unistd.h>
#include "webserver.h"

int main() {
    /* 守护进程 后台运行 */
    //daemon(1, 0); 

    WebServer server(1316, 3, 60000, false, 4);            
    server.Start();
} 