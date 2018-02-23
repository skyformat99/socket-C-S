#include <io.h>  
#include <fstream>  
#include <string>  
#include <vector>  
#include <iostream>
#include"findname.h"

using namespace std;


//��ȡ���е��ļ���  
void GetAllFiles(string path, vector<string>& files)
{

	long   hFile = 0;
	//�ļ���Ϣ    
	struct _finddata_t fileinfo;//�����洢�ļ���Ϣ�Ľṹ��    
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)  //��һ�β���  
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))  //������ҵ������ļ���  
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)  //�����ļ��в���  
				{
					//files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					GetAllFiles(p.assign(path).append("\\").append(fileinfo.name), files);
				}
			}
			else //������ҵ��Ĳ������ļ���   
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));  //���ļ�·�����棬Ҳ����ֻ�����ļ���:    p.assign(path).append("\\").append(fileinfo.name)  
			}

		} while (_findnext(hFile, &fileinfo) == 0);

		 
	}
	else
	{
		files.push_back(p.assign(path));
	}
	_findclose(hFile); //��������  
}

//��ȡ�ض���ʽ���ļ���  
void GetAllFormatFiles(string path, vector<string>& files, string format)
{
	//�ļ����    
	long   hFile = 0;
	//�ļ���Ϣ    
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*" + format).c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					//files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
					GetAllFormatFiles(p.assign(path).append("\\").append(fileinfo.name), files, format);
				}
			}
			else
			{
				files.push_back(p.assign(fileinfo.name));  //���ļ�·�����棬Ҳ����ֻ�����ļ���:    p.assign(path).append("\\").append(fileinfo.name)  
			}
		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}
}

bool IsDir(string path, vector<string>& files)
{
	
	long   hFile = 0;
	//�ļ���Ϣ    
	struct _finddata_t fileinfo;//�����洢�ļ���Ϣ�Ľṹ��    
	string p;
	if ((hFile = _findfirst(p.assign(path).c_str(), &fileinfo)) != -1)  //��һ�β���  
	{
		if ((fileinfo.attrib &  _A_SUBDIR))  //������ҵ������ļ���  
		{
			return true;
		}
		else //������ҵ��Ĳ������ļ���   
		{
			return false;
		}
		_findclose(hFile); //��������  
	}

}

int Isfile(string path, vector<string>& files, int a)
{

	long   hFile = 0;
	//�ļ���Ϣ    
	struct _finddata_t fileinfo;//�����洢�ļ���Ϣ�Ľṹ��    
	string p;
	if ((hFile = _findfirst(p.assign(path).c_str(), &fileinfo)) != -1)  //��һ�β���  
	{
		if ((fileinfo.attrib &  _A_SUBDIR))  //������ҵ������ļ���  
		{
			a = a + 1;
			return a;
		}
		else //������ҵ��Ĳ������ļ���   
		{
			a = a + 2;
			return a;
		}
		_findclose(hFile); //��������  
	}

}

// �ú�����������������һ��Ϊ·���ַ���(string���ͣ����Ϊ����·��)��  
// �ڶ�������Ϊ�ļ������ļ����ƴ洢����(vector����,���ô���)��  
// ���������е��ø�ʽ(��������������ļ�"AllFiles.txt"�У���һ��Ϊ����)��  

//int main()
//{
	//string filePath = "C:\\222";
	//vector<string> files;
	//char * distAll = "AllFiles.txt";

	//��ȡ���е��ļ����������ļ����ļ�  
	//GetAllFiles(filePath, files);  

	//��ȡ���и�ʽΪjpg���ļ�  
	//string format = ".dll";
	//GetAllFormatFiles(filePath, files, format);
	//ofstream ofn(distAll);
	//int size = files.size();
	//ofn << size << endl;

	//for (int i = 0; i<size; i++)
	//{
		//ofn << files[i] << endl; // д���ļ�  
		//cout << files[i] << endl;
		//cout << files[i] << endl;//�������Ļ  
	//}
	//cout << files[0] << endl;
	//ofn.close();

	//return 0;
//}