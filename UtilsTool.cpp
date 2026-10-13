#include "UtilsTool.h"
#include <iostream>
#include <fstream>
#include <sstream>
std::ofstream g_ofsFileLog;
std::string trim(const std::string &s)
{
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

std::vector<std::string> StringSplit(const std::string& input, const std::string& spliter)
{
    std::vector<std::string> output;

    size_t pos = 0;
    size_t start = 0;
    do{
        pos = input.find(spliter, start);
        if (pos > start)
        {
            output.push_back(input.substr(start, pos - start));
            start = pos + spliter.size();
        }
        else
            start += spliter.size();
    }while(pos != std::string::npos);
    return output;
}

void InitLogFile(std::string logFile)
{
    g_ofsFileLog.open(logFile);
}

void CloseLogFile()
{
    if(g_ofsFileLog.is_open())
    {
        g_ofsFileLog.close();
    }
}

void RecordLog(std::string logStr)
{
    g_ofsFileLog << logStr;
}


