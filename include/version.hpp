﻿#pragma once
#include <string>
/*
* v1.2
* V1.2
* 1.2
* 1.2.3
* 1.2.3.4
* 10.1.2
* v0.2-alpha 内部测试版 -> Dev
* v0.2-alpha.xx 内部测试版 -> Dev
* v0.2-dev 内部测试版 -> Dev
* v0.2.0-alpha.xx 内部测试版 -> Dev
* v0.2.0-dev 内部测试版 -> Dev
* v5.9-beta.3 测试版  -> Beta
* 如果 - 后面不是 alpha 或 beta, 结束转化
*/

// 比较原理 都化为一个中间数 比如 1.2 化为 [1,2]

class Version {
public:
    enum Status {
        Dev,
        Beta,
        Release
    };
    int major = 0;
    int minor = 0;
    int revision = 0;
    int betaversion = 0;
    Status status = Status::Release;

private:
    enum ParseCheckPosition {
        enummajor,
        enumminor,
        enumrevision,
        enumbetaversion,
    };
    ParseCheckPosition parseCheckPos = ParseCheckPosition::enummajor;
public:
	Version(const char* v) {
        Parse(v);
	}

    Version(int major, int minor, int revision, Status status = Status::Release, int betaversion = 0)
    : major(major), minor(minor), revision(revision), status(status), betaversion(betaversion)
    {}

public:
    bool operator==(const Version& b) const {
        if (major != b.major) return false;
        if (minor != b.minor) return false;
        if (revision != b.revision) return false;
        //if (betaversion != b.betaversion) return false;
        return true;
    }

    bool operator<=(const Version& b) const {
        if (major > b.major) return false;
        if (minor > b.minor) return false;
        if (revision > b.revision) return false;
        //if (betaversion > b.betaversion) return false;
        return true;
    }

    bool operator<(const Version& b) const {
        return *this <= b && *this != b;
    }

    bool operator>=(const Version& b) const {
        return b <= *this;
    }

    bool operator>(const Version& b) const {
        return b < *this;
    }
public:
    std::string toString(bool hasStatus = false, bool hasBetaVer = false) {
        std::string ret = std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(revision);
        if (hasBetaVer) {
            ret += "." + std::to_string(betaversion);
        }
        if (hasStatus) {
            if (status == Status::Dev)  ret += " - Dev";
            if (status == Status::Beta)  ret += " - Beta";
            if (status == Status::Release)  ret += " - Release";
        }
        return ret;
    }

    /**
     * @brief 返回类似 v1.40.100-alpha.456 的版本结构
     * @return 
    */
    std::string toDetailedString() {
        std::string ret = "v" + std::to_string(major) + "." + std::to_string(minor);
        if (revision != 0) {
            ret += "." + std::to_string(revision);
        }
        if (status == Status::Dev)  ret += "-alpha";
        if (status == Status::Beta)  ret += "-beta";
        if (status != Status::Release) {
            ret += "." + std::to_string(betaversion);
        }
        return ret;
    }

private:
    /**
     * @brief 将a~z的字符转为大写,其他字符原样返回
     * @param c 字符 a~z
     * @return 返回大写的A~Z
    */
    char ToUpper(char c) {
        if (c >= 97 && c <= 122) { // a ~ z
            return c - 32;
        }
        return c;
    }

    /**
     * @brief 将A~Z的字符转为小写,其他字符原样返回
     * @param c 字符 A~Z
     * @return 返回小写的a~z
    */
    char ToLower(char c) {
        if (c >= 65 && c <= 90) {  // A ~ Z
            return c + 32;
        }
        return c;
    }

    /**
     * @brief 检查版本是否是alpha beta
     * 
     * @param sourcevalue
     * @param checkvalue            判断字符是否和这个相等 必须小写 这个数不能是空字符串 因为没有意义
     * @return                      <0: 遇到了 \0, 0: 不是, >0 是
    */
    int CheckIsAlphaOrBeta(const char* sourcevalue, const char* checkvalue) {
        int _increase = 1;          // 如果返回值大于0 则返回这个数,来告诉调用者应该将原始字节偏移多少才能跳过这个检查值
        for (const char* _v = sourcevalue; *_v != '\0'; _v++)
        {
            if (ToLower(*_v) != *checkvalue) {
                return 0;
            }
            if (*(checkvalue + 1) == '\0') {
                return _increase;
            }
            if (*(checkvalue + 1) == ' ') { // 空格跳过
                _increase++;
                continue;
            }
            checkvalue++;
            _increase++;
        }
        return -1;
    }

    /**
     * @brief 反序列化 将字符串反序列化为内部参数
     * @param v 
    */
    void Parse(const char* v) {
        for (;;) {
            if (*v == '\0') {
                break;
            }
            // parseCheckPos == ParseCheckPosition::enummajor
            if (parseCheckPos == ParseCheckPosition::enummajor) {
                if (*v == 'v' || *v == 'V') {
                    v++;
                    continue;
                }
                if (*v == '.') {
                    parseCheckPos = ParseCheckPosition::enumminor;
                    v++;
                    continue;
                }
                if (isdigit(*v) != 0) {
                    major = major * 10 + (*v - '0');
                    v++;
                    continue;
                }
                v++;
                continue;
            }
            // parseCheckPos == ParseCheckPosition::minor
            if (parseCheckPos == ParseCheckPosition::enumminor) {
                if (*v == '.') {
                    parseCheckPos = ParseCheckPosition::enumrevision;
                    v++;
                    continue;
                }
                if (isdigit(*v) != 0) {
                    minor = minor * 10 + (*v - '0');
                    v++;
                    continue;
                }
                if (*v == '-' || *v == '_') {
                    v++;

                    // 检查是否是 alpha 或者 dev
                    int ret = CheckIsAlphaOrBeta(v, "alpha");
                    if(!ret) ret = CheckIsAlphaOrBeta(v, "dev");
                    if (ret < 0) break;
                    if (ret > 0) { // 是 alpha 内部测试版 -> Dev
                        status = Status::Dev;
                        parseCheckPos = ParseCheckPosition::enumbetaversion;
                        v += ret;
                        if (*v == '.') {
                            v++;
                        }
                        continue;
                    }
                    // 检查是否是 beta
                    ret = CheckIsAlphaOrBeta(v, "beta");
                    if (ret < 0) break;
                    if (ret > 0) { // 是 beta
                        status = Status::Beta;
                        parseCheckPos = ParseCheckPosition::enumbetaversion;
                        v += ret;
                        if (*v == '.') {
                            v++;
                        }
                        continue;
                    }
                }
                v++;
                continue;
            }
            // parseCheckPos == ParseCheckPosition::enumrevision
            if (parseCheckPos == ParseCheckPosition::enumrevision) {
                if (*v == '.') {
                    parseCheckPos = ParseCheckPosition::enumbetaversion;
                    v++;
                    continue;
                }
                if (isdigit(*v) != 0) {
                    revision = revision * 10 + (*v - '0');
                    v++;
                    continue;
                }
                if (*v == '-' || *v == '_') {
                    v++;

                    // 检查是否是 alpha 或者 dev
                    int ret = CheckIsAlphaOrBeta(v, "alpha");
                    if (!ret) ret = CheckIsAlphaOrBeta(v, "dev");
                    if (ret < 0) break;
                    if (ret > 0) { // 是 alpha 内部测试版 -> Dev
                        status = Status::Dev;
                        parseCheckPos = ParseCheckPosition::enumbetaversion;
                        v += ret;
                        if (*v == '.') {
                            v++;
                        }
                        continue;
                    }
                    // 检查是否是 beta
                    ret = CheckIsAlphaOrBeta(v, "beta");
                    if (ret < 0) break;
                    if (ret > 0) { // 是 beta
                        status = Status::Beta;
                        parseCheckPos = ParseCheckPosition::enumbetaversion;
                        v += ret;
                        if (*v == '.') {
                            v++;
                        }
                        continue;
                    }
                }
                v++;
                continue;
            }
            // parseCheckPos == ParseCheckPosition::enumbetaversion
            if (parseCheckPos == ParseCheckPosition::enumbetaversion) {
                // 这里遇到'.'就结束了, 版本字符串的结构只能支持到 0.0.0.0
                if (*v == '.') {
                    break;
                }
                if (isdigit(*v) != 0) {
                    betaversion = betaversion * 10 + (*v - '0');
                    v++;
                    continue;
                }

                v++;
                continue;
            }
        }
    }
};