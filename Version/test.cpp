// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "../include/VersionParse/Version.hpp"

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
    std::Version ver1("1.0.7");
    std::Version ver2("1.1.0");
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

    std::string read;
    std::cout << "现在比较两个版本号,请输入第一个版本:";
    std::cin >> read;
    std::Version ver5(read.c_str());
    std::cout << (ver5 ? "ver5 有效" : "ver5 无效") << std::endl;
    std::cout << "现在比较两个版本号,请输入第二个版本:";
    std::cin >> read;
    std::Version ver6(read.c_str());
    std::cout << (ver6 ? "ver6 有效" : "ver6 无效") << std::endl;

    if(ver5 < ver6) {
        std::cout << ver5.toString(1) << " < " << ver6.toString(1) << std::endl;
    }
    else if(ver5 > ver6) {
        std::cout << ver5.toDetailedString() << " > " << ver6.toDetailedString() << std::endl;
    }
    else {
        std::cout << ver5.toDetailedString() << " = " << ver6.toDetailedString() << std::endl;
    }
}


