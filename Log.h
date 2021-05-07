/*** 
 * @Author: wujing
 * @Date: 2021-05-07 12:14:03
 * @LastEditTime: 2021-05-07 15:21:05
 * @LastEditors: wujing
 * @Description: 
 * @FilePath: /Log/Log.h
 * @可以输入预定的版权声明、个性签名、空行等
 */
#ifndef __MYLOG_H__
#define __MYLOG_H__

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#include <sys/time.h>
#include <string.h>

using namespace std;

class Logstream
{
public:
    template <typename T>
    inline Logstream &operator<<(const T &log)
    {
        m_oss << log;
        return *this;
    }

    inline Logstream &operator<<(std::ostream &(*)(std::ostream &))
    {
        // 接收std::endl
        std::cout << m_oss.str() << std::endl;
        return *this;
    }

    std::ostringstream m_oss;
};

class Log : public Logstream
{
private:
    /* data */
    string m_sFileName;

public:
    Log(string sFileName);
    ~Log();

private:
    void _write(string sFileName);
};

Log::Log(string sFileName) : m_sFileName(sFileName)
{
}

Log::~Log()
{
    _write(m_sFileName);
}

void Log::_write(string sFileName)
{
    ofstream outfile;
    outfile.open(sFileName + ".log", ios::app);
    outfile << m_oss.str() << endl;
    outfile.close();
}

static string getTime()
{
    time_t timep;
    time(&timep);
    char tmp[256];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
    return tmp;
}

static string getCurrentFormatTimeString()
{
    struct timeval tv;
    char timeArray[40];
    stringstream ss;

    gettimeofday(&tv, NULL);

    memset(timeArray, 0, sizeof(timeArray));

    strftime(timeArray, sizeof(timeArray) - 1, "%F %T", localtime(&tv.tv_sec));

    ss << string(timeArray) << "." << tv.tv_usec;

    return ss.str();
}

#define FLOG(sFileName) Log(sFileName) << "[" << getCurrentFormatTimeString() << " " << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << "]: "

#endif
