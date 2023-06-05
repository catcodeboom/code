#pragma once
// 封装一个日志
#include <cstdarg> //va_start,va_list,va_end宏的头文件
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
using std::string;
// 日志级别
#define DEBUG 0
#define NORMAL 1
#define WARNING 2
#define ERROR 3
#define FATAL 4 // 致命
static const char *levelmap[] = {"DEBUG", "NORMAL", "WARNING", "ERROR", "FATAL"};
static void logMessage(int level, const char *format, ...) {
#ifdef DEBUG_SHOW // 可通过gcc编译选项添加宏
    if (level == DEBUG) {
        return;
    }
#endif
    static char buffer[BUFSIZ]; // 可反复使用
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof buffer, format, args); // 将可变参数存放至buffer中
    va_end(args);
    FILE *pf = fopen("./log/README.log", "a"); // 追加方式打开，不存在就创建
    if (pf == nullptr) {
        // 直接将日志输出到屏幕
        fprintf(stderr, "%s\n%s\n%s\n%s\n", buffer, __FILE__, __DATE__, __TIME__);
        return;
    }
    // 否则将日志写到文件
    fprintf(pf, "%s\n%s\n%s\n%s\n", buffer, __FILE__, __DATE__, __TIME__);
    fclose(pf);
    return;
}