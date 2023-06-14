#include "people.pb.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
using std::cout;
using std::endl;
using std::string;
int main() {
    std::shared_ptr<std::ofstream> ofs(new std::ofstream("../a.bin", std::ios::out | std::ios::binary), [](std::ofstream *ofs) {ofs->close();delete ofs; });
    if (!ofs->is_open()) {
        cout << "打开文件失败" << endl;
        return 0;
    }
    people p;
    string name;
    cout << "输入新增联系人的姓名(Enter结束)" << endl;
    std::getline(std::cin, name);
    int birthday;
    cout << "输入新增联系人的生日" << endl;
    std::cin >> birthday;
    std::cin.ignore(256, '\n');
    p.set_birthday(birthday);
    p.set_name(name);
    if (!p.SerializeToOstream(ofs.get())) {
        cout << "序列化到文件失败" << endl;
    }
    system("clear");
    return 0;
}