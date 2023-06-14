#pragma once
#include <arpa/inet.h>
#include <cassert>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
// 使用udp做一个聊天室
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;
class udpSock {
public:
    int Socket() {
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock < 0) {
            printf("创建套接字失败\n");
            exit(0);
        }
        return sock;
    }
    void Bind(u_int16_t port) {
        struct sockaddr_in server_addr;
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        server_addr.sin_port = htons(port);
        if (bind(sock, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            printf("绑定地址结构失败\n");
            exit(0);
        }
    }

private:
    int sock;
};
class Solution {
private:
    static void DisPlayClientAddress(struct sockaddr_in &client_addr) {
        cout << "客户端ip:" << inet_ntoa(client_addr.sin_addr) << endl;
        cout << "客户端端口:" << ntohs(client_addr.sin_port) << endl;
    }
    static void SetFdNoBlock(int fd) {
        int fl = fcntl(fd, F_GETFL);
        assert(fl != -1);
        fl |= O_NONBLOCK;
        assert(fcntl(fd, F_SETFL, fl) != -1);
    }

public:
    static void ServerFunc(u_int16_t port = 8080) {
        auto addrhash = [](const struct sockaddr_in &addr) {
            uint32_t hash = 0;
            uint64_t ip_port = ((uint64_t)addr.sin_addr.s_addr << 32) | addr.sin_port;
            uint32_t seed = 0x12345678;
            const uint32_t m = 0x5bd1e995;
            const int r = 24;
            uint32_t h = seed ^ 8;
            uint32_t k = (uint32_t)(ip_port);
            k *= m;
            k ^= k >> r;
            k *= m;
            h *= m;
            h ^= k;
            h ^= h >> 13;
            h *= m;
            h ^= h >> 15;
            hash = h;
            return hash;
        };
        auto addreuqal = [](const struct sockaddr_in &left, const struct sockaddr_in &right) {
            return left.sin_family == right.sin_family && left.sin_addr.s_addr == right.sin_addr.s_addr && left.sin_port == right.sin_port;
        };
        unordered_set<struct sockaddr_in, decltype(addrhash), decltype(addreuqal)> clientset(20, addrhash, addreuqal);
        udpSock udpserver;
        int sock = udpserver.Socket();
        udpserver.Bind(port);
        char buffer[BUFSIZ] = {0};
        while (1) {
            struct sockaddr_in client_addr;
            memset(&client_addr, 0, sizeof(client_addr));
            socklen_t size = sizeof(client_addr);
            ssize_t len = recvfrom(sock, buffer, BUFSIZ, 0, (struct sockaddr *)&client_addr, &size);
            assert(len > 0);
            // 面向数据报
            cout << "=======================================" << endl;
            printf("服务器读取到长度为%lu的数据\n", len);
            buffer[len] = 0;
            DisPlayClientAddress(client_addr);
            printf("客户端发送过来的数据是%s\n", buffer);
            cout << "=======================================" << endl;
            string sendmsg = buffer;
            sendmsg.append(1, '(').append(inet_ntoa(client_addr.sin_addr)).append(1, ':').append(std::to_string(ntohs(client_addr.sin_port))).append(1, ')');
            clientset.insert(client_addr);
            for (auto &addr : clientset) {
                sendto(sock, sendmsg.c_str(), sendmsg.size(), 0, (const struct sockaddr *)&addr, sizeof(addr)); // 无连接,即使ip和port不存在,也可以发送,只是报文被丢弃
            }
        }
    }
    static void ClientFunc(string ip, u_int16_t port) {
        udpSock client;
        int sock = client.Socket();
        SetFdNoBlock(sock);
        string message;
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        inet_aton(ip.c_str(), &server_addr.sin_addr);
        char buf[BUFSIZ];
        while (1) {
            cout << "输入要发送的消息(Enter结束)" << endl;
            std::getline(std::cin, message);
            if (message.empty()) {
                close(sock);
                break;
            }
            sendto(sock, message.c_str(), message.size(), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));
            struct sockaddr_in tmp;
            socklen_t tmplen = sizeof(tmp);
            cout << "=======================================" << endl;
            ssize_t len;
            while ((len = recvfrom(sock, buf, BUFSIZ, 0, (struct sockaddr *)&tmp, &tmplen)) != -1) {
                buf[len] = 0;
                cout << buf << endl;
            }
            cout << "=======================================" << endl;
        }
    }
};