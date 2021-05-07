/*** 
 * @Author: wujing
 * @Date: 2021-05-07 12:14:03
 * @LastEditTime: 2021-05-07 12:39:27
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
#include "fstream"

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

#define FLOG(sFileName) Log(sFileName) << "[" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << "]: "

#endif
