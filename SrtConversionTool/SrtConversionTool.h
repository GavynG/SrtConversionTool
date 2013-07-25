#include <iostream>
#include <STRING>
#include <fstream>
#include <string.h>

/*
Class brief : Convert .Srt to plain printable text(.txt)!
author       : Andy Guo
website     : www.xycabin.com
Date          : 2013-07-20
Refer         : Srt file specification :https://en.wikipedia.org/wiki/SubRip#Specifications
*/

using namespace std;
class SRT
{
public:
    SRT();
    ~SRT();
    SRT(string OriginalSrtFile, string DstFile);
    bool Convert();
    //处理一行文本
    //bool ProcessLine(string LineStr, string& Outstr);
private:
    //SRT文件全路径
    string m_OriginalSrtFile;
    //目标Txt文件全路径
    string m_DstTxtFile;
};
