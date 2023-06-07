#include "../include/Sock.h"
int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "需要输入服务器绑定的端口号" << endl;
        return 0;
    }
    tcpsocket::Solution::MultiProcessServer(atoi(argv[1]));
    return 0;
}