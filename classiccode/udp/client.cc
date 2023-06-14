#include "udpsock.h"
int main(int argc, char **argv) {
    if (argc != 3) {
        printf("输入服务器ip和端口\n");
        return 0;
    }
    Solution::ClientFunc(argv[1], atoi(argv[2]));
    return 0;
}