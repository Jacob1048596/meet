#pragma once
#include<stdio.h>
#include<string>
#include<mysql/mysql.h>
#include"tools.hpp"

class DataBaseSvr
{
    public:
        DataBaseSvr(std::string& host,std::string& user,std::string passwd,std::string db,uint16_t port)
        {
            host_=host;
            user_=user;
            passwd_=passwd;
            db_=db;
            port_=port;
            mysql_init(&mysql_);
        }
        ~DataBaseSvr()
        {
            mysql_close(&mysql_);
        }

        bool Connect2Mysql()
        {
            //操作句柄，mysql主机ip，用户，密码，数据库，端口，NULL，xxx
          if(!mysql_real_connect(&mysql_,host_.c_str(),user_.c_str(),
          passwd_.c_str(),db_.c_str(),port_,NULL,CLIENT_FOUND_ROWS))
          {
              LOG(ERROR,"connect erroe")<<mysql_errno(&mysql_)<<std::endl;
              return false;
          }
          return true;
        }
    private:
    //操作句柄
    MYSQL mysql_;
    std::string host_;
    std::string user_;
    std::string passwd_;
    std::string db_;
    uint16_t port_;
};