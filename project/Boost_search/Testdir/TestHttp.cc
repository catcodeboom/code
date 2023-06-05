#include "../ThirdPart/cpp-httplib/httplib.h"
const std::string root_path = "../wwwroot";
int main() {
    httplib::Server ser;
    ser.set_base_dir(root_path);
    ser.Get("/hi", [](const httplib::Request &req, httplib::Response &rsp) {
        rsp.set_content("你好", "text/plain;charset=UTF-8");
    });
    ser.listen("0.0.0.0", 8081);
    return 0;
}