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
        cout << "Error: ԴSrt��Ŀ��Txt�ļ�Ϊ�գ�"  << endl;
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
        cout << "���ݣ�" << ch_temp << endl;
        if( strcmp(ch_temp, "")==0 )
            continue;
        string OutString;
        //determine whether LineStr is a digit (F = subtitle frame counter (as ASCII digits))
        bool IsSeqNo = true;
        for( unsigned int i = 0; i < strlen(ch_temp); i++ )
        {
            //����0������
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
                //cout << "ʱ���᣺" << ch_temp_next_line << endl;
                //��ǰ��5��Ӧ����"," ,�ƺ���6��Ӧ����":"
                if (tempstr[findpos - 5] == ',' && tempstr[findpos + 6] == ':')
                {
                    //��д��txt
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
                //˵��ǰһ�е���ѧ�������кţ���Ҫд��Ŀ��txt�ļ�
                //if ( ProcessLine(string(ch_temp), OutString) )
                {
                    DstTxt << string(ch_temp);
                }
            }
        }
        else
        {
            //����֡��ţ�Ҫд�ļ�
            //�������Ƕ��Ų�����
            string WriteString = string(ch_temp);
            unsigned int unPos = WriteString.rfind(',');
            if (unPos != WriteString.size() -1 )
            {
                DstTxt << ch_temp << endl;;
                DstTxt << endl; //дһ������
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
