#pragma once

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <functional>
#include <regex>

namespace StringUtils {

    // ==================== 基础操作 ====================

    /**
     * @brief 去除字符串首尾空白字符
     * @param str 输入字符串
     * @return 去除空白后的字符串
     */
    inline std::string trim(const std::string& str) {
        auto front = std::find_if_not(str.begin(), str.end(), [](unsigned char ch) { return std::isspace(ch); });
        auto back = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char ch) { return std::isspace(ch); }).base();
        return (back <= front) ? std::string() : std::string(front, back);
    }

    /**
     * @brief 去除字符串左侧空白字符
     */
    inline std::string trimLeft(const std::string& str) {
        auto front = std::find_if_not(str.begin(), str.end(), [](unsigned char ch) { return std::isspace(ch); });
        return std::string(front, str.end());
    }

    /**
     * @brief 去除字符串右侧空白字符
     */
    inline std::string trimRight(const std::string& str) {
        auto back = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char ch) { return std::isspace(ch); }).base();
        return std::string(str.begin(), back);
    }

    // ==================== 分割与连接 ====================

    /**
     * @brief 分割字符串
     * @param str 输入字符串
     * @param delimiter 分隔符
     * @param skipEmpty 是否跳过空字符串
     * @return 分割后的字符串数组
     */
    inline std::vector<std::string> split(const std::string& str,
        char delimiter,
        bool skipEmpty = true) {
        std::vector<std::string> result;
        std::stringstream ss(str);
        std::string item;

        while (std::getline(ss, item, delimiter)) {
            if (!skipEmpty || !item.empty()) {
                result.push_back(item);
            }
        }
        return result;
    }

    /**
     * @brief 使用字符串作为分隔符进行分割
     */
    inline std::vector<std::string> split(const std::string& str,
        const std::string& delimiter,
        bool skipEmpty = true) {
        std::vector<std::string> result;
        size_t start = 0;
        size_t end = str.find(delimiter);

        while (end != std::string::npos) {
            std::string token = str.substr(start, end - start);
            if (!skipEmpty || !token.empty()) {
                result.push_back(token);
            }
            start = end + delimiter.length();
            end = str.find(delimiter, start);
        }

        std::string lastToken = str.substr(start);
        if (!skipEmpty || !lastToken.empty()) {
            result.push_back(lastToken);
        }

        return result;
    }

    /**
     * @brief 连接字符串数组
     * @param strings 字符串数组
     * @param delimiter 分隔符
     * @return 连接后的字符串
     */
    inline std::string join(const std::vector<std::string>& strings,
        const std::string& delimiter = "") {
        if (strings.empty()) {
            return "";
        }

        std::string result;
        for (size_t i = 0; i < strings.size(); ++i) {
            if (i > 0) result += delimiter;
            result += strings[i];
        }
        return result;
    }

    /**
     * @brief 连接字符串数组（迭代器版本）
     */
    template<typename InputIt>
    inline std::string join(InputIt begin, InputIt end,
        const std::string& delimiter = "") {
        if (begin == end) {
            return "";
        }

        std::string result;
        for (auto it = begin; it != end; ++it) {
            if (it != begin) result += delimiter;
            result += *it;
        }
        return result;
    }

    // ==================== 子串操作 ====================

    /**
     * @brief 模拟 QString::mid 功能
     * @param str 输入字符串
     * @param pos 起始位置
     * @param n 字符数（-1 表示到末尾）
     * @return 子字符串
     */
    inline std::string mid(const std::string& str, int pos, int n = -1) {
        if (pos < 0) {
            pos = 0;
        }

        if (pos >= static_cast<int>(str.length())) {
            return "";
        }

        if (n < 0 || pos + n > static_cast<int>(str.length())) {
            n = static_cast<int>(str.length()) - pos;
        }

        return str.substr(pos, n);
    }

    /**
     * @brief 获取字符串左侧n个字符
     */
    inline std::string left(const std::string& str, int n) {
        if (n <= 0) {
            return "";
        }

        if (n >= static_cast<int>(str.length())) {
            return str;
        }

        return str.substr(0, n);
    }

    /**
     * @brief 获取字符串右侧n个字符
     */
    inline std::string right(const std::string& str, int n) {
        if (n <= 0) {
            return "";
        }

        if (n >= static_cast<int>(str.length())) {
            return str;
        }

        return str.substr(str.length() - n, n);
    }

    // ==================== 大小写转换 ====================

    /**
     * @brief 转换为小写
     */
    inline std::string toLower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), [](unsigned char ch) { return std::tolower(ch); });
        return result;
    }

    /**
     * @brief 转换为大写
     */
    inline std::string toUpper(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), [](unsigned char ch) { return std::toupper(ch); });
        return result;
    }

    // ==================== 查找与替换 ====================

    /**
     * @brief 检查字符串是否以指定前缀开头
     */
    inline bool startsWith(const std::string& str, const std::string& prefix) {
        return str.compare(0, prefix.length(), prefix) == 0;
    }

    /**
     * @brief 检查字符串是否以指定后缀结尾
     */
    inline bool endsWith(const std::string& str, const std::string& suffix) {
        if (suffix.length() > str.length()) {
            return false;
        }

        return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
    }

    /**
     * @brief 检查字符串是否包含
     */
    inline bool contains(const std::string& str, const std::string& suffix) {
        return str.find(suffix) != std::string::npos;
    }

    /**
     * @brief 查找子字符串（大小写敏感）
     * @return 位置索引，未找到返回 std::string::npos
     */
    inline size_t find(const std::string& str, const std::string& subStr,
        size_t startPos = 0, bool caseSensitive = true) {
        if (!caseSensitive) {
            std::string strLower = toLower(str);
            std::string subStrLower = toLower(subStr);
            return strLower.find(subStrLower, startPos);
        }
        return str.find(subStr, startPos);
    }

    /**
     * @brief 替换所有匹配的子字符串
     */
    inline std::string replaceAll(std::string str,
        const std::string& from,
        const std::string& to) {
        if (from.empty()) {
            return str;
        }

        size_t startPos = 0;
        while ((startPos = str.find(from, startPos)) != std::string::npos) {
            str.replace(startPos, from.length(), to);
            startPos += to.length();
        }
        return str;
    }

    /**
     * @brief 替换第一个匹配的子字符串
     */
    inline std::string replaceFirst(std::string str,
        const std::string& from,
        const std::string& to) {
        size_t startPos = str.find(from);
        if (startPos != std::string::npos) {
            str.replace(startPos, from.length(), to);
        }
        return str;
    }

    // ==================== 类型转换 ====================

    /**
     * @brief 字符串转换为整数（兼容旧编译器）
     */
    template<typename T>
    inline T toInt(const std::string& str, T defaultValue = T()) {
        try {
            long long val = std::stoll(str);  // 统一用 stoll
            return static_cast<T>(val);
        }
        catch (...) {
            return defaultValue;
        }
    }

    /**
     * @brief 字符串转换为浮点数（兼容旧编译器）
     */
    template<typename T>
    inline T toFloat(const std::string& str, T defaultValue = T()) {
        try {
            double val = std::stod(str);  // 统一用 stod
            return static_cast<T>(val);
        }
        catch (...) {
            return defaultValue;
        }
    }

    /**
     * @brief 数值转换为字符串
     */
    template<typename T>
    inline std::string toString(T value) {
        return std::to_string(value);
    }

    // 特化：std::string 直接返回
    inline std::string toString(const std::string& value) {
        return value;
    }

    // ==================== 检查与验证 ====================

    /**
     * @brief 检查字符串是否为空或仅包含空白字符
     */
    inline bool isEmptyOrWhitespace(const std::string& str) {
        return str.empty() || std::all_of(str.begin(), str.end(), [](unsigned char ch) { return std::isspace(ch); });
    }

    /**
     * @brief 检查字符串是否仅包含数字
     */
    inline bool isDigits(const std::string& str) {
        return !str.empty() && std::all_of(str.begin(), str.end(), [](unsigned char ch) { return std::isdigit(ch); });
    }

    /**
     * @brief 检查字符串是否仅包含字母
     */
    inline bool isAlpha(const std::string& str) {
        return !str.empty() && std::all_of(str.begin(), str.end(), [](unsigned char ch) { return std::isalpha(ch); });
    }

    /**
     * @brief 检查字符串是否仅包含字母和数字
     */
    inline bool isAlnum(const std::string& str) {
        return !str.empty() && std::all_of(str.begin(), str.end(), [](unsigned char ch) { return std::isalnum(ch); });
    }

    // ==================== 正则表达式 ====================

    /**
     * @brief 正则表达式匹配
     */
    inline bool regexMatch(const std::string& str, const std::string& pattern) {
        try {
            std::regex re(pattern);
            return std::regex_match(str, re);
        }
        catch (const std::regex_error&) {
            return false;
        }
    }

    /**
     * @brief 正则表达式查找
     */
    inline bool regexSearch(const std::string& str, const std::string& pattern) {
        try {
            std::regex re(pattern);
            return std::regex_search(str, re);
        }
        catch (const std::regex_error&) {
            return false;
        }
    }

    /**
     * @brief 正则表达式替换
     */
    inline std::string regexReplace(const std::string& str,
        const std::string& pattern,
        const std::string& replacement) {
        try {
            std::regex re(pattern);
            return std::regex_replace(str, re, replacement);
        }
        catch (const std::regex_error&) {
            return str;
        }
    }

    // ==================== 其他实用函数 ====================

    /**
     * @brief 反转字符串
     */
    inline std::string reverse(const std::string& str) {
        return std::string(str.rbegin(), str.rend());
    }

    /**
     * @brief 获取字符串长度（考虑多字节字符）
     */
    inline size_t length(const std::string& str) {
        return str.length();
    }

    /**
     * @brief 统计子字符串出现次数
     */
    inline int count(const std::string& str, const std::string& subStr) {
        if (subStr.empty()) return 0;

        int count = 0;
        size_t pos = 0;
        while ((pos = str.find(subStr, pos)) != std::string::npos) {
            ++count;
            pos += subStr.length();
        }
        return count;
    }

    /**
     * @brief 移除所有指定字符
     */
    inline std::string removeAll(std::string str, char ch) {
        str.erase(std::remove(str.begin(), str.end(), ch), str.end());
        return str;
    }

    /**
     * @brief 移除所有空白字符
     */
    inline std::string removeWhitespace(const std::string& str) {
        std::string result;
        std::copy_if(str.begin(), str.end(), std::back_inserter(result),
            [](unsigned char ch) { return !std::isspace(ch); });
        return result;
    }

    // ==================== STL 操作 ====================

    /**
     * @brief 查找元素下标
     * @return 位置索引，未找到返回 -1
     */
    template<typename T>
    inline size_t indexOf(const std::vector<T>& vec, const T& value) {
        auto it = std::find(vec.begin(), vec.end(), value);
        if (it != vec.end()) {
            return std::distance(vec.begin(), it);
        }
        return -1;
    }

    /**
     * @brief 检查数组是否包含
     */
    template<typename T>
    inline bool contains(const std::vector<T>& vec, const T& val) {
        return std::find(vec.begin(), vec.end(), val) != vec.end();
    }

    /**
     * @brief 检查map是否包含
     */
    template<typename T, typename Value>
    inline bool contains(const std::map<T, Value>& vec, const T& key) {
        return vec.find(key) != vec.end();
    }
}
