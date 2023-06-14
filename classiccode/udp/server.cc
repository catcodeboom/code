#include "udpsock.h"
int main(int argc, char **argv) {
    if (argc != 2) {
        printf("输入端口\n");
        return 0;
    }
    Solution::ServerFunc(atoi(argv[1]));
    return 0;
}