#include "udpsock.h"
int main(int argc, char **argv) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3333);
    addr.sin_addr.s_addr = inet_addr("123.123.123.123");
    char msg[] = "hello world";
    if (sendto(sock, msg, strlen(msg), 0, (const struct sockaddr *)&addr, sizeof(addr)) > 0) {
        printf("sendto函数调用成功\n");
    }
    close(sock);
    return 0;
}