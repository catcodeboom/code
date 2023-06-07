#pragma once
#include "../include/Sock.h"
#include "message.pb.h"
namespace protoc {
    class Solution {
    private:
        class Task {
        public:
            Task(int fd) :
                sock(fd) {
            }
            void operator()() const {
                string message; // 读取到的内容
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
                        cout << "读取到了客户端发送的数据,长度是" << len << endl;
                        buf[len] = 0;
                        message += buf;
                        if (message.find('#') != string::npos) { // 表示提取到了一个完整的报文
                            string res = ConstructResponse(message);
                            send(sock, res.c_str(), res.size(), 0);
                        }
                        break;
                    }
                }
            }

        private:
            string ConstructResponse(string &message) const {
                int start = 0;
                int pos = message.find('#');
                string str = message.substr(start, pos); // str是序列化后的请求数据
                message.erase(0, pos + 1);
                slowstep::Request req;
                req.ParseFromString(str); // 将请求反序列化
                int left = req.x(), right = req.y();
                string op = req.op();
                if (op.size() != 1) {
                    return CreateInvalidResponse();
                }
                char oper = op[0];
                slowstep::Response res;
                res.set_flag(true);
                switch (oper) {
                case '+':
                    res.set_result(left + right);
                    break;
                case '-':
                    res.set_result(left - right);
                    break;
                case '*':
                    res.set_result(left * right);
                    break;
                case '/':
                    if (right == 0) {
                        return CreateInvalidResponse();
                    }
                    res.set_result(left / right);
                    break;
                default:
                    return CreateInvalidResponse();
                }
                string respnse;
                res.SerializeToString(&respnse);
                respnse += '#'; // 2个报文之间的分隔符
                return respnse;
            }
            string CreateInvalidResponse() const {
                slowstep::Response res;
                res.set_flag(false);
                res.set_result(INT_MAX);
                string ans;
                res.SerializePartialToString(&ans);
                ans += '#'; // 分隔符
                return ans;
            }
            int sock = -1;
        };

    public:
        static void ThreadPoolServer(short port = 8080) { // 线程池TCP服务器
            tcpsocket::TcpSocket server;
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
            tcpsocket::TcpClient client;
            client.Socket();
            client.Connect(ip, port);
            int sock = client.m_sock;
            string message; // 接收服务器的消息
            while (1) {
                slowstep::Request request;
                int left, right;
                string op;
                cout << "请输入左操作数#" << endl;
                using std::cin;
                cin >> left;
                cin.ignore(256, '\n');
                cout << "请输入右操作数#" << endl;
                cin >> right;
                cin.ignore(256, '\n');
                cout << "请输入操作符#(Enter退出)" << endl;
                std::getline(cin, op);
                if (op.size() == 0) {
                    break;
                }
                // cout << "op输入成功" << endl;
                request.set_x(left);
                request.set_y(right);
                request.set_op(op);
                // cout << "set完成" << endl;
                string msg;
                if (!request.SerializeToString(&msg)) {
                    cout << "序列化失败" << endl;
                }
                msg += '#'; // 作为分隔符
                // cout << "准备发送" << endl;
                send(sock, msg.c_str(), msg.size(), 0);
                // cout << "发送成功" << endl;
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
                    cout << "读取到了服务器发送的数据,长度是" << len << endl;
                    buf[len] = 0;
                    message += buf;
                    if (message.find('#') != string::npos) { // 表示提取到了一个完整的报文
                        int start = 0;
                        int pos = message.find('#');
                        string str = message.substr(start, pos); // str是序列化后的响应数据
                        message.erase(0, pos + 1);
                        slowstep::Response res;
                        res.ParseFromString(str); // 反序列化
                        if (res.flag() == false) {
                            cout << "客户端发送的数据有误" << endl;
                        } else {
                            cout << "运算结果是" << res.result() << endl;
                        }
                    }
                    break;
                }
            }
        }
    };
} // namespace protoc