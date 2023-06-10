#pragma once
#include "../include/Sock.h"
#include "../include/httplib.h"
#include <iostream>
using std::cout;
using std::endl;
namespace httpdemo {
    class Solution {
    public:
        static void ServerFunc() {
            httplib::Server ser;
            ser.Get("/xyz", [](const httplib::Request &request, httplib::Response &res) {
                // cout << "客户端请求的内容为:" << endl;
                // cout << request.body << endl;
                // 读取客户端的请求内容,据此构建响应
                res.set_content("Hello world!", "text"); // 响应内容"Hello world!",响应类型"text"
                // res.status = 200;                        // 状态码设置为200
                res.status = 404; // 状态码设置为404
            });
            ser.listen("0.0.0.0", 8080);
        }
        static void ClientFunc() {
            httplib::Client cli("0.0.0.0", 8080);
            auto res = cli.Get("/xyz"); // cli获取指定路径下的数据
            if (res->status == 200) {
                cout << res->body << endl;
            } else {
                cout << httplib::to_string(res.error()) << endl;
            }
        }

    public:
        static void DisPlayHttpRequest(short port = 8080) {
            tcpsocket::TcpSocket server;
            int listen = server.Socket();
            server.Bind(port);
            server.Listen();
            while (1) {
                int sock = server.Accept();
                if (sock < 0) {
                    continue;
                }
                char buf[BUFSIZ];
                ssize_t len = read(sock, buf, BUFSIZ);
                buf[len] = 0;
                cout << "读取到的http请求为:" << endl;
                cout << buf << "==============================" << endl;
                string http_res;
                http_res += "HTTP/1.0 200 ok\n";           // 状态行
                http_res += "Content-type:text/plain\n\n"; // text/plain表示普通文本
                http_res += "hello world";                 // 正文
                send(sock, http_res.c_str(), http_res.size(), 0);
                close(sock);
            }
        }
        static void Http301(short port = 8080) { // 进行永久重定向
            tcpsocket::TcpSocket server;
            int listen = server.Socket();
            server.Bind(port);
            server.Listen();
            while (1) {
                int sock = server.Accept();
                if (sock < 0) {
                    continue;
                }
                char buf[BUFSIZ];
                ssize_t len = read(sock, buf, BUFSIZ);
                buf[len] = 0;
                cout << "读取到http请求" << endl;
                string http_res;
                http_res += "HTTP/1.1 301 Moved Permanently\n";    // 状态行
                http_res += "Location: https://www.baidu.com\n\n"; // text/plain表示普通文本
                send(sock, http_res.c_str(), http_res.size(), 0);
                close(sock);
            }
        }
        static void Http307(short port = 8080) { // 进行临时重定向
            tcpsocket::TcpSocket server;
            int listen = server.Socket();
            server.Bind(port);
            server.Listen();
            while (1) {
                int sock = server.Accept();
                if (sock < 0) {
                    continue;
                }
                char buf[BUFSIZ];
                ssize_t len = read(sock, buf, BUFSIZ);
                buf[len] = 0;
                cout << "读取到http请求" << endl;
                string http_res;
                http_res += "HTTP/1.1 307 Temporary Redirect\n";   // 状态行
                http_res += "Location: https://www.baidu.com\n\n"; // text/plain表示普通文本
                send(sock, http_res.c_str(), http_res.size(), 0);
                close(sock);
            }
        }
    };
} // namespace httpdemo