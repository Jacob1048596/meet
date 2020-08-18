#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<boost/algorithm/string.hpp>
#include<time.h>
#include<stdio.h>
class StringTools
{
    public:
       static void Split(const std::string& input,const std::string& split_char,std::vector<std::string>* output)
        {
            boost::split(*output,input,boost::is_any_of(split_char),boost::token_compress_off);
        }

};

//输出[时间 日志等级 文件 ：行号]具体的日志信息

class LogTime
{
    public:
        static void GetTimeStamp(std::string* time_stamp)
        {
            time_t sys_time;
            time(&sys_time);

            struct tm *st=localtime(&sys_time);
            char buf[30]={0};
            snprintf(buf,sizeof(buf)-1,"%04d-%02d-%02d %02d-%02d-%02d",st->tm_year+1900,st->tm_mon+1,st->tm_mday,st->tm_hour,st->tm_min,st->tm_sec);
            time_stamp->assign(buf,strlen(buf));
        }
};

//划分日志等级
const char* Level[]=
{
    "INFO",
    "WARNING",
    "ERROR",
    "FATAL",
    "DEBUG"
};

enum LogLevel
{
    INFoO=0,
    WARNING,
    ERROR,
    FATAL,
    DEBUG
};

std::ostream& Log(LogLevel lev, const char* file,int line,const std::string& log_msg)
{
    //获取日志等级
    std::string log_level=Level[lev];
    //获取时间戳
    std::string time_stamp;
    LogTime::GetTimeStamp(&time_stamp);
    //组织输出内容
    std::cout<<"["<<time_stamp<<" "<<log_level<<" "<<file<<":"<<line<<"]"
    <<" "<<log_msg;
    return std::cout;
}

#define LOG(lev,msg) Log(lev,__FILE__,__LINE__,msg)