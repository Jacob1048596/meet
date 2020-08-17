#include"httplib.h"
#include<unistd.h>
#include<iostream>

void test(httplib::Request& req,httplib::Response &res)
{
    (void)req;
    printf("begin\n");
    res.set_header("Content-type","application/json");
    res.set_header("Set-Cookie","JSESSIONID=123123");
}
int main()
{
    httplib::Server ser;
    ser.Get("/a",[](const httplib::Request req,httplib::Response& res){
         (void)req;
         res.set_header("Content-type","application/json");
         res.set_header("Set-Cookie","JSESSIONID=123123");
    });
    ser.Get("/b",[](const httplib::Request req,httplib::Response& res){
         (void)req;
         std::cout<<req.get_header_value("Cookie")<<std::endl;
         res.set_header("Content-type","application/json");
         res.set_header("Set-Cookie","JSESSIONID=123123");
    });
    ser.listen("0,0,0,0",16666);
    return 0;
}