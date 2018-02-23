#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <string>
#include <io.h>  
#include <fstream>  
#include <vector>  
#include <iostream>
#include <WinSock2.h>
#include"findname.h"
using namespace std;

#define PORT 8087  
#define SERVER_IP "192.168.1.221"  
#define BUFFER_SIZE 1024  
#define FILE_NAME_MAX_SIZE 512  
#pragma comment(lib, "WS2_32")  

int main()
{
	// ��ʼ��socket dll  
	WSADATA wsaData;
	WORD socketVersion = MAKEWORD(2, 0);
	if (WSAStartup(socketVersion, &wsaData) != 0)
	{
		printf("Init socket dll error!");
		exit(1);
	}



	//ָ������˵ĵ�ַ  
	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
	server_addr.sin_port = htons(PORT);


	
	while (1)
	{
		/*
		//����socket  
		SOCKET c_Socket = socket(AF_INET, SOCK_STREAM, 0);
		if (SOCKET_ERROR == c_Socket)
		{
			printf("Create Socket Error!");
			system("pause");
			exit(1);
		}

		if (SOCKET_ERROR == connect(c_Socket, (LPSOCKADDR)&server_addr, sizeof(server_addr)))
		{
			printf("Can Not Connect To Server IP!\n");
			system("pause");
			exit(1);
		}
		*/
		//�����ļ���  
		char file_name[FILE_NAME_MAX_SIZE + 1];
		memset(file_name, 0, FILE_NAME_MAX_SIZE + 1);
		printf("Please Input File Name On Client: ");
		scanf("%s", &file_name);

		string filePath = file_name;
		vector<string> files;
		

		//��ȡ���е��ļ����������ļ����ļ�  
		GetAllFiles(filePath, files);

		int size = files.size();


		for (int i = 0; i<size; i++)
		{
			//����socket  
			SOCKET c_Socket = socket(AF_INET, SOCK_STREAM, 0);
			if (SOCKET_ERROR == c_Socket)
			{
				printf("Create Socket Error!");
				system("pause");
				exit(1);
			}

			if (SOCKET_ERROR == connect(c_Socket, (LPSOCKADDR)&server_addr, sizeof(server_addr)))
			{
				printf("Can Not Connect To Server IP!\n");
				system("pause");
				exit(1);
			}
			char filename[FILE_NAME_MAX_SIZE + 1];
			strcpy(filename, files[i].c_str());

			char buffer[BUFFER_SIZE];
			memset(buffer, 0, BUFFER_SIZE);
			strncpy(buffer, filename, strlen(filename)>BUFFER_SIZE ? BUFFER_SIZE : strlen(filename));

			//������������ļ���  
			if (send(c_Socket, buffer, BUFFER_SIZE, 0) < 0)
			{
				printf("Send File Name Failed\n");
				system("pause");
				exit(1);
			}

			//���ļ���׼��д��  
			FILE * fp = fopen(filename, "rb");  //windows����"rb",��ʾ��һ��ֻ���Ķ������ļ�  
			if (NULL == fp)
			{
				printf("File: %s Not Found\n", filename);
			}
			else
			{
				memset(buffer, 0, BUFFER_SIZE);
				int length = 0;

				while ((length = fread(buffer, sizeof(char), BUFFER_SIZE, fp)) > 0)
				{
					if (send(c_Socket, buffer, length, 0) < 0)
					{
						printf("Send File: %s Failed\n", filename);
						break;
					}
					memset(buffer, 0, BUFFER_SIZE);
				}

				fclose(fp);
				printf("File: %s Transfer Successful!\n", filename);

			}
			closesocket(c_Socket);
		}
		
		/*
		char buffer[BUFFER_SIZE];
		memset(buffer, 0, BUFFER_SIZE);
		strncpy(buffer, file_name, strlen(file_name)>BUFFER_SIZE ? BUFFER_SIZE : strlen(file_name));

		//������������ļ���  
		if (send(c_Socket, buffer, BUFFER_SIZE, 0) < 0)
		{
			printf("Send File Name Failed\n");
			system("pause");
			exit(1);
		}

		//���ļ���׼��д��  
		FILE * fp = fopen(file_name, "rb");  //windows����"rb",��ʾ��һ��ֻ���Ķ������ļ�  
		if (NULL == fp)
		{
			printf("File: %s Not Found\n", file_name);
		}
		else
		{
			memset(buffer, 0, BUFFER_SIZE);
			int length = 0;

			while ((length = fread(buffer, sizeof(char), BUFFER_SIZE, fp)) > 0)
			{
				if (send(c_Socket, buffer, length, 0) < 0)
				{
					printf("Send File: %s Failed\n", file_name);
					break;
				}
				memset(buffer, 0, BUFFER_SIZE);
			}

			fclose(fp);
			printf("File: %s Transfer Successful!\n", file_name);

		}
		closesocket(c_Socket);*/
	}
	
	
	//�ͷ�winsock��  
	WSACleanup();

	system("pause");
	return 0;
}