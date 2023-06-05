#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
#define NORMAL 1
#define WARNING 2
#define DEBUG 3
#define DATAL 4
#define LOG(LEVEL, MESSAGE) log(#LEVEL, MESSAGE, __FILE__, __LINE__)
void log(string level, string message, string file, int line) {
    cout << "日志等级:" << level << endl;
    cout << "时间:" << __TIME__ << endl;
    cout << "日志消息:" << message << endl;
    cout << "文件:" << level << endl;
    cout << "行号:" << endl;
}
int main() {
    LOG(NORMAL, "hello"); // --->log("NORMAL","hello","Test.cc",20)s
    return 0;
}