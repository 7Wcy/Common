#ifndef UTILSTOOL_H
#define UTILSTOOL_H
#include <string>
#include <vector>

std::string trim(const std::string &s);

std::vector<std::string> StringSplit(const std::string& input, const std::string& spliter);

void InitLogFile(std::string logFile);

void CloseLogFile();

void RecordLog(std::string logStr);

#endif // JHUTILS_H
