//  
//  TDInvFileUtils.h  
//  MyCocoa2DTest  
//  
//  
//  
  
#ifndef __MyCocoa2DTest__TDInvFileUtils__  
#define __MyCocoa2DTest__TDInvFileUtils__  
  
#include <iostream>  
#include "cocos2d.h"  
using namespace cocos2d;  
using namespace std;  
  
/** 负责操作文件储存和读取 
 */  
#define SaveStringToXML CCUserDefault::sharedUserDefault()->setStringForKey  

#define SaveIntegerToXML CCUserDefault::sharedUserDefault()->setIntegerForKey  

#define SaveBooleanToXML CCUserDefault::sharedUserDefault()->setBoolForKey  

#define LoadStringFromXML CCUserDefault::sharedUserDefault()->getStringForKey  

#define LoadIntegerFromXML CCUserDefault::sharedUserDefault()->getIntegerForKey  

#define LoadBooleanFromXML CCUserDefault::sharedUserDefault()->getBoolForKey  

#define Flush CCUserDefault::sharedUserDefault()->flush

  
class TDInvFileUtils {  
public:  
    /** 读取本地文件，返回数据 */  
    static string getFileByName(string pFileName);  
      
    /** 储存内容到文件 */  
    static bool saveFile(const char* pContent,string pFileName);  
      
};  

class Cocos2DxFileUtils{
public:
	static void saveStringDataToSD(const char* key,const char* value="");
    static void saveIntegerDataToSD(const char* key,int value=1);
	static const char* getStringDataFromSD(const char* key,const char* value="");
    static int getIntegerDataFromSD(const char* key,int value = -1);
};
  
#endif /* defined(__MyCocoa2DTest__TDInvFileUtils__) */

