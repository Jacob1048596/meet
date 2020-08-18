#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<string>
#include<fstream>
#include<vector>

#include"httplib.h"
#include"database.hpp"
#include"tools.hpp"
using namespace std;
class AisSvr
{
    public:
    AisSvr()
    {
        svr_ip_.clear();
        svr_port_=-1;
        db_=NULL;
        db_ip_.clear();
        db_user_.clear();
        db_passwd_.clear();
        db_name_.clear();
        db_port_=-1;
    }
    int OnInit(const std::string& config_filename)
    {
        //原因：构造函数没有返回值

        if(!Load(config_filename))
        {
            LOG(ERROR,"OPEN connfig file failed")<<std::endl;
            return -1;
        }
        //2.初始化数据库模块
        db_=new DataBaseSvr(db_ip_,db_user_,db_passwd_,db_name_,db_port_);
        if(!db_)
        {
            LOG(ERROR,"creat database failed")<<std::endl;
            return -2;
        }

        if(db_->Connect2Mysql())
        {
             LOG(ERROR,"CONNECT database failed")<<std::endl;
            return -3;
        }
        
        return 0;
    }

    void start()
    {
        //注册，用户名字，密码，邮箱
        http_svr_.Post("/register",[](const httplib::Request req,httplib::Response& res)
        {
         (void)req;
         res.set_header("Content-type","application/json");
         res.set_header("Set-Cookie","JSESSIONID=123123");
        });
        //登录
        //面试预约
        //提交预约数据
        http_svr_.listen()
        http_svr_.Get("")
    }
    bool Load(const std::string& config_filename)
    {
        std::ifstream file(config_filename.c_str());
        if(!file.is_open())
        {
            LOG(ERROR,"open file failed");
            return false;
        }
        //正常打开文件
        std::string line;
        std::vector<std::string> output;
        while(std::getline(file,line))
        {
            output.clear();
            StringTools::Split(line,"=",&output);
           


            if(strcmp(output[0].c_str(),"svr_ip")==0)
                {
                    if(output[1].empty())
                    {
                        LOG(ERROR,"IP is empty")<<std::endl;
                        return false;
                    }
                    svr_ip_=output[1];
                }
                else if(strcmp(output[0].c_str(),"svr_port")==0)
                {
                    if(output[1].empty())
                    {
                        LOG(ERROR,"PORT is empty")<<std::endl;
                        return false;
                    }
                    svr_port_=output[1];
                } else if(strcmp(output[0].c_str(),"db_user")==0)
                {
                    if(output[1].empty())
                    {
                        LOG(ERROR,"DB_USER is empty")<<std::endl;
                        return false;
                    }
                    db_user_=output[1];
                } else if(strcmp(output[0].c_str(),"db_passwd")==0)
                {
                    if(output[1].empty())
                    {
                        LOG(ERROR,"DB_PASSWD is empty")<<std::endl;
                        return false;
                    }
                    db_passwd_=output[1];
                } else if(strcmp(output[0].c_str(),"db_name")==0)
                {
                    if(output[1].empty())
                    {
                        LOG(ERROR,"DB_NAME is empty")<<std::endl;
                        return false;
                    }
                    db_name_=output[1];
                } else if(strcmp(output[0].c_str(),"db_ip")==0)
                {
                    if(output[1].empty())
                    {
                        LOG(ERROR,"DB_IP is empty")<<std::endl;
                        return false;
                    }
                    db_ip_=output[1];
                } else if(strcmp(output[0].c_str(),"db_port")==0)
                {
                    if(output[1].empty())
                    {
                        LOG(ERROR,"DB_PORT is empty")<<std::endl;
                        return false;
                    }
                    db_port_=atoi(output[1].c_str());
                }
               return true;
        }
         std::cout<<svr_ip_<<":"<<svr_port_<<endl;
        //解析内容
    }
    private:
        std::string svr_ip_;//服务端侦听IP地址
        std::string svr_port_;//服务端侦听端口

        DataBaseSvr* db_;

       std::string db_ip_;
       std::string db_user_;
       std::string db_passwd_;
       std::string db_name_;
       uint16_t db_port_;

       httplib::Server http_svr_;
};

int main()
{
    
    AisSvr as;
   int ret= as.OnInit("cofig_ais.cfg");
   if(ret<0)
   {
       LOG(ERROR,"initserver failed")<<std::endl;
       return -1;
   }


    return 0;

}