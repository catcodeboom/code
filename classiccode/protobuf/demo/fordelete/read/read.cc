#include "people.pb.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
using std::cout;
using std::endl;
using std::string;
int main() {
    std::shared_ptr<std::ifstream> ifs(new std::ifstream("../a.bin", std::ios::in | std::ios::binary), [](std::ifstream *ifs) {ifs->close();delete ifs; });
    if (!ifs->is_open()) {
        cout << "打开文件失败" << endl;
        return 0;
    }
    people p;
    p.ParseFromIstream(ifs.get());
    cout << "姓名:" << p.name() << endl;
    cout << "年龄:" << p.age() << endl;
    const google::protobuf::Reflection *rf = people::GetReflection();
    const google::protobuf::UnknownFieldSet &unknownset = rf->GetUnknownFields(p); // 获取p的未知字段
    for (int i = 0; i < unknownset.field_count() /*未知字段的数量*/; i++) {
        const google::protobuf::UnknownField &elem = unknownset.field(i);
        cout << "未知字段的字段编号为:" << elem.number() << endl;
        switch (elem.type() /*未知字段的类型*/) {
        case google::protobuf::UnknownField::Type::TYPE_FIXED32:
            cout << "未知字段的值为:" << elem.fixed32() << endl;
            break;
        case google::protobuf::UnknownField::Type::TYPE_FIXED64:
            cout << "未知字段的值为:" << elem.fixed64() << endl;
            break;
        case google::protobuf::UnknownField::Type::TYPE_VARINT:
            cout << "未知字段的值为:" << elem.varint() << endl;
            break;
        case google::protobuf::UnknownField::Type::TYPE_GROUP:
            elem.group();
            break;
        case google::protobuf::UnknownField::Type::TYPE_LENGTH_DELIMITED:
            cout << "未知字段的值为:" << elem.length_delimited() << endl;
            break;
        default:
            break;
        }
    }
    return 0;
}