#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;
class AisSvr
{
    public:
    AisSvr()
    {
        ip.clear();
        port.clear();

    }
    int OnInit(std::string& config_filename)
    {
        //原因：构造函数没有返回值
        
    }
    bool Load(std::string& config_filename)
    {
        std::ifstream file(config_filename.c_str());
        if(!file.is_open())
        {
            return false;
        }
        //正常打开文件
        std::string line;
        std::vector<std::string> output;
        while(std::getline(file,line))
        {
            
        }
        //解析内容

    }
    private:
        std::string ip;//服务端侦听IP地址
        std::string port;//服务端侦听端口
};

int main()
{
    
    return 0;

}