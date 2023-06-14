#pragma once
#include "Student.pb.h"
#include "bird.pb.h"
#include "car.pb.h"
#include "company.pb.h"
#include "people.pb.h"
#include "person.pb.h"
#include <fstream>
#include <google/protobuf/any.h>
#include <iostream>
using std::cout;
using std::endl;
class Solution {
public:
    static void TestStudent() {
        GOOGLE_PROTOBUF_VERIFY_VERSION; // 验证库版本的兼容性,不兼容则退出进程
        slowstep::student stu;
        stu.set_age(18);
        stu.set_name("Tom");
        stu.mutable_name();
        stu.mutable_name();
        std::ofstream ofs("./a.bin", std::ios::out);
        if (ofs.is_open() == false) {
            cout << "打开文件失败" << endl;
            ofs.close();
            return;
        }
        if (!stu.SerializeToOstream(&ofs)) {
            cout << "序列化失败" << endl;
        }
        ofs.close();
        google::protobuf::ShutdownProtobufLibrary(); // 删除protobuf库分配的全局对象
    }
    static void TestCompany() {
        GOOGLE_PROTOBUF_VERIFY_VERSION;
        slowstep::contact con;
        con.peoples_size();
        con.peoples(0);
        con.add_peoples("Tom");
        con.set_peoples(0, "Jack");
        google::protobuf::ShutdownProtobufLibrary();
    }
    static void TestCar() {
        GOOGLE_PROTOBUF_VERIFY_VERSION;
        carspace::car c;
        c.set_car_color(colorspace::color::RED);
        cout << colorspace::color_Name(c.car_color()) << endl;
        google::protobuf::ShutdownProtobufLibrary();
    }
    static void TestPeople() {
        GOOGLE_PROTOBUF_VERIFY_VERSION;
        people x;
        google::protobuf::Any *elem = x.mutable_name();
        Name n;
        n.set_m_name("Tom");
        elem->PackFrom(n);
        if (x.has_name()) {
            cout << "已经对Any字段的属性进行了设置" << endl;
        }
        if (x.name().Is<Name>()) { // 通过"inline bool google::protobuf::Any::Is<T>() const"方法判断对Any类型赋予的是何种类型的值
            cout << "对Any类型设置的值为Name" << endl;
        }
        Name ret;
        x.name().UnpackTo(&ret);
        cout << ret.m_name() << endl;
        google::protobuf::ShutdownProtobufLibrary();
    }
    static void TestPerson() {
        person p;
        p.set_qq("12345");
        switch (p.ContactInformation_case()) {
        case person::ContactInformationCase::kQq:
            cout << "设置了QQ" << endl;
            cout << "QQ为" << p.qq() << endl;
            break;
        case person::ContactInformationCase::kWechat:
            cout << "设置了微信" << endl;
            cout << "微信为" << p.wechat() << endl;
            break;
        case person::ContactInformationCase::CONTACTINFORMATION_NOT_SET:
            cout << "没有进行设置" << endl;
            break;
        default:
            break;
        }
    }
    static void TestBird() {
        bird b;
        b.mutable_remark()->insert({"迁徙", "迁徙到北方"});
        for (auto &[title, content] : b.remark()) {
            cout << "标题:" << title << endl;
            cout << "内容:" << content << endl;
        }
    }
};