#include "../include/Sock.h"
int main(int argc, char **argv) {
    if (argc != 3) {
        cout << "需要输入服务器的ip和端口" << endl;
        return 0;
    }
    string ip = argv[1];
    short port = atoi(argv[2]);
    tcpsocket::Solution::ClientSendMessage(ip, port);
    return 0;
}