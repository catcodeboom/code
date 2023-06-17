#include "ThreadPool.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>
using std::cerr;
using std::cout;
using std::endl;
using std::string;
namespace tcpsocket {
    class TcpSocket {
    public:
        int Socket() {
            m_listensock = socket(AF_INET, SOCK_STREAM, 0);
            if (m_listensock < 0) {
                cerr << "创建套接字失败" << endl;
                exit(0);
            }
            return m_listensock;
        }
        void Bind(short port) {
            int reuse = 1;
            setsockopt(m_listensock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
            struct sockaddr_in s_addr;
            memset(&s_addr, 0, sizeof(s_addr));
            s_addr.sin_family = AF_INET;
            s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
            s_addr.sin_port = htons(port);
            if (bind(m_listensock, (const struct sockaddr *)&s_addr, sizeof(s_addr)) < 0) {
                cerr << "绑定地址结构失败" << endl;
                exit(0);
            }
        }
        void Listen(int max = 20) {
            if (listen(m_listensock, max) < 0) {
                cout << "设置全连接队列最大长度失败" << endl;
                exit(0);
            }
        }
        int Accept() {
            struct sockaddr_in c_addr;
            memset(&c_addr, 0, sizeof(c_addr));
            socklen_t len = sizeof(c_addr);
            int ans = accept(m_listensock, (struct sockaddr *)&c_addr, &len);
            if (ans < 0) {
                cerr << "获取新链接失败" << endl;
            } else {
                char ip[50];
                cout << "===============" << endl;
                cout << "客户端ip:" << inet_ntoa(c_addr.sin_addr) << endl;
                cout << "客户端端口:" << ntohs(c_addr.sin_port) << endl;
                cout << "===============" << endl;
            }
            return ans;
        }
        ~TcpSocket() {
            close(m_listensock);
        }

    private:
        int m_listensock = -1;
    };
    class TcpClient {
    public:
        void Socket() {
            m_sock = socket(AF_INET, SOCK_STREAM, 0);
            if (m_sock < 0) {
                cerr << "创建套接字失败" << endl;
                exit(0);
            }
        }
        bool Connect(string ip, short port) {
            struct sockaddr_in s_addr;
            memset(&s_addr, 0, sizeof(s_addr));
            s_addr.sin_family = AF_INET;
            s_addr.sin_port = htons(port);
            inet_pton(AF_INET, ip.c_str(), &s_addr.sin_addr);
            if (connect(m_sock, (const struct sockaddr *)&s_addr, sizeof(s_addr)) < 0) {
                cerr << "与服务器建立连接失败" << endl;
                exit(0);
                return false;
            }
            return true;
        }
        ~TcpClient() {
            close(m_sock);
        }
        int m_sock;
    };
    class Solution {
        static void WriteAndReadForServer(int sock) {
            while (1) {
                char buf[BUFSIZ];
                ssize_t len = recv(sock, buf, BUFSIZ, 0);
                switch (len) {
                case 0:
                    cout << "读到了文件结尾,并且客户端已经关闭" << endl;
                    close(sock);
                    return;
                case -1:
                    if (errno == EAGAIN) {
                        cout << "文件描述符被设置了非阻塞,并且此次读取没有数据" << endl;
                    } else {
                        cerr << "读取出错" << endl;
                        close(sock);
                        return;
                    }
                default:
                    cout << "读取到了客户端发送的数据,长度是" << len;
                    buf[len] = 0;
                    cout << ",内容是:" << buf << endl;
                    string message = "xyz(发送给客户端)";
                    send(sock, message.c_str(), message.size(), 0);
                    break;
                }
            }
        }
        static void WriteAndReadForClient(TcpClient &client) {
            int sock = client.m_sock;
            while (1) {
                string message;
                cout << "请输入要发送给服务器的消息(Enter结束)#" << endl;
                std::getline(std::cin, message);
                if (message.size() == 0) {
                    return;
                }
                send(sock, message.c_str(), message.size(), 0);
                char buf[BUFSIZ];
                ssize_t len = recv(sock, buf, BUFSIZ, 0);
                switch (len) {
                case 0:
                    cout << "读到了文件结尾,并且服务器已经关闭" << endl;
                    close(sock);
                    return;
                case -1:
                    if (errno == EAGAIN) {
                        cout << "文件描述符被设置了非阻塞,并且此次读取没有数据" << endl;
                    } else {
                        cerr << "读取出错" << endl;
                        close(sock);
                        return;
                    }
                default:
                    cout << "读取到了服务器发送的数据,长度是" << len;
                    buf[len] = 0;
                    cout << ",内容是:" << buf << endl;
                    break;
                }
            }
        }

    public:
        static void MultiProcessServer(short port = 8080) { // 多进程TCP服务器
            TcpSocket server;
            int listen = server.Socket();
            server.Bind(port);
            server.Listen();
            while (1) {
                int sock = server.Accept();
                if (sock < 0) {
                    continue;
                }
                if (fork() == 0) {     // 子进程
                    close(listen);     // 关闭用于监听的文件描述符
                    if (fork() == 0) { // 孙子进程
                        WriteAndReadForServer(sock);
                        exit(0);
                    }
                    close(sock);
                    exit(0); // 子进程退出
                }
                // 表示父进程或创建子进程失败
                close(sock);
                wait(nullptr); // 回收子进程
            }
        }
        static void MultiThreadServer(short port = 8080) { // 多线程TCP服务器
            TcpSocket server;
            int listen = server.Socket();
            server.Bind(port);
            server.Listen();
            while (1) {
                int sock = server.Accept();
                if (sock < 0) {
                    continue;
                }
                std::thread t(WriteAndReadForServer, sock);
                t.detach();
            }
        }

    private:
        struct Task {
            Task(int fd) :
                sock(fd) {
            }
            void operator()() const {
                WriteAndReadForServer(sock);
            }

        private:
            int sock = -1;
        };

    public:
        static void ThreadPoolServer(short port = 8080) { // 线程池TCP服务器
            TcpSocket server;
            threadpool::ThreadPool<Task> pool;
            int listen = server.Socket();
            server.Bind(port);
            server.Listen();
            while (1) {
                int sock = server.Accept();
                if (sock < 0) {
                    continue;
                }
                pool.push_tack(new Task(sock));
            }
        }
        static void ClientSendMessage(string ip, short port) { // 客户端
            TcpClient client;
            client.Socket();
            if (!client.Connect(ip, port)) {
                return;
            }
            WriteAndReadForClient(client);
        }
    };
} // namespace tcpsocket