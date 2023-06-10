#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
using std::cout;
using std::endl;
using std::string;
class Solution {
private:
    static void WriteNumToFile(string filename) {
        std::ofstream ofs(filename, std::ios::out | std::ios::trunc);
        if (!ofs.is_open()) {
            cout << "打开文件失败" << endl;
            ofs.close();
            return;
        }
        for (int i = 0; i < 100; i++) {
            ofs << i << ' ';
        }
        ofs.close();
    }

public:
    // int stat(const char* pathname,struct stat* statbuf);获取文件的信息
    static void getFileSize() {
        string filepath = "./test.txt";
        WriteNumToFile("./test.txt");
        struct stat filestat;
        if (stat(filepath.c_str(), &filestat) < 0) {
            cout << "获取文件属性失败" << endl;
            return;
        }
        cout << "文件的大小是" << filestat.st_size << "字节" << endl;
        cout << "文件的硬链接数是" << filestat.st_nlink << endl;
        cout << "文件的Inode编号是" << filestat.st_ino << endl;
    }
};