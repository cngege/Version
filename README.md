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
* v1.2
* V1.2
* 1.2
* 1.2.3
* 1.2.3.4
* 10.1.2
* v0.2-alpha 内部测试版 -> Dev
* v0.2-alpha.xx 内部测试版 -> Dev
* v0.2-dev 内部测试版 -> Dev
* v0.2-dev.xx 内部测试版 -> Dev
* v0.2.0-alpha.xx 内部测试版 -> Dev
* v0.2.0-dev.xx 内部测试版 -> Dev
* v5.9-alpha.3 内部测试版 -> Dev
* v5.9-beta.3 测试版  -> Beta
* 如果 - 后面不是 alpha 或 beta, 结束转化
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
//ret: v1.40-alpha.456
```
