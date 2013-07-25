#include "SrtConversionTool.h"



SRT::SRT()
{
}

SRT::~SRT()
{
}

SRT::SRT(string OriginalSrtFile, string DstFile):m_OriginalSrtFile(OriginalSrtFile), m_DstTxtFile(DstFile)
{
}

bool SRT::Convert()
{
    if (m_OriginalSrtFile == "" || m_DstTxtFile == "")
    {
        cout << "Error: 源Srt或目标Txt文件为空！"  << endl;
        return false;
    }

    ifstream Orgfile( m_OriginalSrtFile.c_str() );
    if (!Orgfile)
    {
        cout  << "error: unable to open srt file: "<< m_OriginalSrtFile << endl;
        return false;
    }

    ofstream DstTxt( m_DstTxtFile.c_str() );
    if (!DstTxt)
    {
        cout  << "error: unable to open destination file: "<< m_DstTxtFile << endl;
        return false;
    }

    string tempstr;
    //while(Orgfile >> tempstr)
    char ch_temp[256];
    while( Orgfile.getline(ch_temp, 256 ) )
    {
        cout << "内容：" << ch_temp << endl;
        if( strcmp(ch_temp, "")==0 )
            continue;
        string OutString;
        //determine whether LineStr is a digit (F = subtitle frame counter (as ASCII digits))
        bool IsSeqNo = true;
        for( unsigned int i = 0; i < strlen(ch_temp); i++ )
        {
            //不＝0是数字
            if (isdigit(ch_temp[i]) == 0)
                IsSeqNo = false;
        }
        if (IsSeqNo)
        {
            char ch_temp_next_line[256];
            Orgfile.getline(ch_temp_next_line, 256 );
            //00:00:45,264 --> 00:00:46,798
            tempstr = string(ch_temp_next_line);
            unsigned int findpos = tempstr.find("-->");
            if ( findpos != string::npos )
            {
                //cout << "时间轴：" << ch_temp_next_line << endl;
                //往前推5个应该是"," ,推后推6个应该是":"
                if (tempstr[findpos - 5] == ',' && tempstr[findpos + 6] == ':')
                {
                    //不写入txt
                }
                else
                {
                   // if ( ProcessLine(tempstr, OutString) )
                    {
                        cout << "A line has content ,so must write to dst file!" << endl;
                        DstTxt << tempstr;
                    }
                }
            }
            else
            {
                //说明前一行的数学不是序列号，需要写入目标txt文件
                //if ( ProcessLine(string(ch_temp), OutString) )
                {
                    DstTxt << string(ch_temp);
                }
            }
        }
        else
        {
            //不是帧序号，要写文件
            //如果最后是逗号不换行
            string WriteString = string(ch_temp);
            unsigned int unPos = WriteString.rfind(',');
            if (unPos != WriteString.size() -1 )
            {
                DstTxt << ch_temp << endl;;
                DstTxt << endl; //写一个空行
            }
            else
            {
                DstTxt << ch_temp;
            }
        }
    }
    Orgfile.close();
    DstTxt.close();
    return true;
}

//bool SRT::ProcessLine(string LineStr, string& Outstr)
//{
//    if (LineStr == "")
//        return false;
//
//}

int main()
{
    SRT c_Srt("The IT Crowd - 1x01 - Yesterday's Jam.DVD.en.srt", "The IT Crowd - 1x01 - Yesterday's Jam.DVD.en.txt");
    c_Srt.Convert();
    return 0;
}
