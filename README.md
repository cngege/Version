# Version - C++ 的版本反序列化器

## 🧆特点  
  **仅一个头文件 直接加入项目即可**

## 🎋引用
  - 下载项目  
  - 将`include/version.hpp`文件加入到你的项目即可  

## 🚀如何使用  
  *非常简单,该文件仅一个类`Version` 直接引用文件，然后创建它就好*

###   ➕创建类 1 
```cpp
// 创建它
Version(int,int,int,Status = Status::Release,int = 0)

Version ver(1.2.3);
//类默认为Release版本,当然除非你特别指定
Version ver(1.2.3,Status::Dev,1);
//类有三种版本可指定
//发布版
Status::Release // 默认
//测试版
Status::Beta
//内部版
Status::Dev
```

###   ➕创建类 2 
```cpp
// 创建它
Version(const char* versionStr)
// 使用此构造函数可以将一定规律的字符串反序列化为Version
// 支持以下类型
/*
* v1.2   > 主版本号1 次版本号2
* V1.2
* 1.2
* 1.2.3    > 主版本号1 次版本号2 修订号3
* 1.2.3.4   > ... 修订号3, 内部版本号4
* 10.1.2
* v0.2-alpha    > 内部测试版 -> Dev   主版本号0 次版本号2 版本Dev-开发版
* v0.2-alpha.xx    > 内部测试版 -> Dev 主版本号0 次版本号2 内部版本号xx，版本Dev-开发版
* v0.2-dev    > 内部测试版 -> Dev 主版本号0 次版本号2 修订号0 内部版本号0 版本Dev-开发版
* v0.2-dev.xx    > 内部测试版 -> Dev ...内部版本号xx 版本Dev-开发版
* v0.2.0-alpha.xx    > 内部测试版 -> Dev ...
* v0.2.0-dev.xx    > 内部测试版 -> Dev ...
* v5.9-alpha.3    > 内部测试版 -> Dev 主版本号5 次版本号9 修订号0 内部版本号3 版本Dev-开发版
* v5.9-beta.3    > 测试版  -> Beta 主版本号5 次版本号9 修订号0 内部版本号3 版本beta-测试版
* 如果 - 后面不是 alpha、dev 或 beta, 结束转化
*/
```

###   🔠直接比较版本大小 
```cpp
//支持比较符 > >= < <= ==

Version ver1("1.2.3");
Version ver2("1.2.4");

ver1 < ver2
//ret:  true

ver1 > ver2
//ret:  false

ver1 >= ver2
//ret:  false

ver1 != ver2
//ret:  true

if(ver1)
// true

```

###   🍳序列化  
```cpp
version ver("1.40-alpha.456");

//std::string toString(bool hasStatus = false, bool hasBetaVer = false) 
ver.toString();
//ret: 1.40.0
ver.toString(true);
//ret: 1.40.0 - Dev
ver.toString(true,true);
//ret: 1.40.0.456 - Dev


//std::string toDetailedString()
ver.toDetailedString();
//ret: v1.40-dev.456
```

###   👓注意
- 如果你将反序列化的版本号 为1.0.0
- 在使用字符串反序列化时 修订号中的0可以省去
- 但为保反序列化不出错，次要版本号中的0绝不可省去
- 即最简写法为 1.0 以下为参考写法
- v1 ❌
- v2.0 ✔️
- v1. ❌
- v2.2-dev ✔️
- v0.0.0 ✔️
- v0.0 ✔️
- v.1.2 ❌
- .1.2 ❌
- v1.2_dev.3 ✔️

直接使用 `if(ver)` 判断是否反序列化成功  
