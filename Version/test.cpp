// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "../include/version.hpp"

int main()
{
    const char* v = "1.40-alpha.456";
    //v = "1.40.1.12";
    std::Version ver(v);

    std::cout << "toString: " << ver.toString(1,1) << std::endl;
    std::cout << "toDetailedString: " << ver.toDetailedString() << std::endl;
    std::cout << "major: " << ver.major << std::endl;
    std::cout << "minor: " << ver.minor << std::endl;
    std::cout << "revision: " << ver.revision << std::endl;
    std::cout << "betaversion: " << ver.betaversion << std::endl;
    if (ver.status == ver.Beta) {
        std::cout << ">> status: Beta"<< std::endl;
    }
    if (ver.status == ver.Dev) {
        std::cout << ">> status: Dev" << std::endl;
    }
    if (ver.status == ver.Release) {
        std::cout << ">> status: Release" << std::endl;
    }

    std::cout << "==========比较==========" << std::endl;
    // 比较
    std::Version ver1("1.10.6");
    std::Version ver2("1.10.6");
    if (ver1 < ver2) {
        std::cout << ver1.toString(1) << " < " << ver2.toString(1) << std::endl;
    }
    else if (ver1 > ver2) {
        std::cout << ver1.toDetailedString() << " > " << ver2.toDetailedString() << std::endl;
    }
    else {
        std::cout << ver1.toDetailedString() << " = " << ver2.toDetailedString() << std::endl;
    }

    if (ver1 != ver2) {
        std::cout << ver1.toDetailedString() << " != " << ver2.toDetailedString() << std::endl;
    }
    std::cout << "==========测试空版本,以及反序列化失败的情况==========" << std::endl;
    std::Version ver3("");
    std::cout << ver3.toString() << " ver3.toString()" << std::endl;
    std::cout << ver3.toString(1) << " ver3.toString(1)" << std::endl;
    std::cout << ver3.toString(1, 1) << " ver3.toString(1,1)" << std::endl;

    std::cout << (ver3 ? "ver3 有效" : "ver3 无效") << std::endl;
    
    std::cout << "==========测试意外情况==========" << std::endl;
    std::Version ver4("v1.");
    std::cout << (ver4 ? "ver4 有效" : "ver4 无效") << std::endl;
    std::cout << ver4.toDetailedString() << std::endl;
}


