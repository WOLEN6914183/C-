/************************************************************
* �ļ��� ������TCP�ͻ���
*
* ��  �� �����ӱ��ط�����
*
* ��  �� �� xsx
*
* ��  �� ��2022/1/22
**************************************************************/

/*-----------------------------ͷ�ļ�------------------------------*/

#include<Windows.h>
#include<WinSock2.h>
#include<stdio.h>

/*-------------------------------��غ�---------------------------------*/

/*
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")      //�������������ǰ�������ⲿ�ֿ��Բ�������
*/
int main()
{
	WORD version = MAKEWORD(2, 2);  //�汾��
	WSADATA data;					//����
	WSAStartup(version, &data);		//����WinSock

	// 1�������׽���
	SOCKET _sock = socket(AF_INET,SOCK_STREAM,0);
	if (INVALID_SOCKET == _sock)
	{
		printf("���󣬽���sockʧ��....\n");
	}
	else
	{
		printf("����Sock�ɹ�.....\n");
	}
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	// 2, ���ӷ����� connect
	int ret =connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in));
	if (ret==SOCKET_ERROR)
	{
		printf("����ʧ��....\n");
	}
	else
	{
		printf("���ӳɹ�.....\n");
	}
	
	//3�����ܷ�������Ϣ recv
	char recvBuf[256] = {};
	int nlen =recv(_sock, recvBuf, 256, 0);
	if (nlen>0)
	{
		printf("���յ����ݣ�%s\n",recvBuf);
	}
	//4, �ر��׽���
	closesocket(_sock);

	WSACleanup();                   //�ر�WinSock
	getchar();
	return 0;
}