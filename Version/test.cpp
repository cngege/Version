// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "../include/version.hpp"

int main()
{
    const char* v = "1.40.100-alpha.456";
    Version ver(v);

    std::cout << ver.toDetailedString() << std::endl;
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
    Version ver1("1.10.5");
    Version ver2("1.10.6");
    if (ver1 < ver2) {
        std::cout << ver1.toString(1) << " < " << ver2.toString(1) << std::endl;
    }
    else if (ver1 > ver2) {
        std::cout << ver1.toDetailedString() << " > " << ver2.toDetailedString() << std::endl;
    }
    else {
        std::cout << ver1.toDetailedString() << " = " << ver2.toDetailedString() << std::endl;
    }
}


