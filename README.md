# Version - C++ �İ汾�����л���

## �ص�  
  **��һ��ͷ�ļ� ֱ�Ӽ�����Ŀ����**

## ����
  - ������Ŀ  
  - ��`include/version.hpp`�ļ����뵽�����Ŀ����  

## ���ʹ��  
  *�ǳ���,���ļ���һ����`Version` ֱ�������ļ���Ȼ�󴴽����ͺ�*

###   ������ 1 
```cpp
// ������
Version(int,int,int,Status = Status::Release,int = 0)

Version ver(1.2.3);
//��Ĭ��ΪRelease�汾,��Ȼ�������ر�ָ��
Version ver(1.2.3,Status::Dev,1);
//�������ְ汾��ָ��
//������
Status::Release // Ĭ��
//���԰�
Status::Beta
//�ڲ���
Status::Dev
```

###   ������ 2 
```cpp
// ������
Version(const char* versionStr)
// ʹ�ô˹��캯�����Խ�һ�����ɵ��ַ��������л�ΪVersion
// ֧����������
/*
* v1.2
* V1.2
* 1.2
* 1.2.3
* 1.2.3.4
* 10.1.2
* v0.2-alpha �ڲ����԰� -> Dev
* v0.2-alpha.xx �ڲ����԰� -> Dev
* v0.2-dev �ڲ����԰� -> Dev
* v0.2-dev.xx �ڲ����԰� -> Dev
* v0.2.0-alpha.xx �ڲ����԰� -> Dev
* v0.2.0-dev.xx �ڲ����԰� -> Dev
* v5.9-alpha.3 �ڲ����԰� -> Dev
* v5.9-beta.3 ���԰�  -> Beta
* ��� - ���治�� alpha �� beta, ����ת��
*/
```

###   ֱ�ӱȽϰ汾��С 
```cpp
//֧�ֱȽϷ� > >= < <= ==

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

###   ���л�  
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
