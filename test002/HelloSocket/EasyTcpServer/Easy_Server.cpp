/************************************************************
* �ļ��� ������TCP�����
* 
* ��  �� ������TCP���������������Ϊ5����ʾ�¼���Ŀͻ��˵�ַ
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
	#pragma comment(lib,"ws2_32.lib")   //�������������ǰ�������ⲿ�ֿ��Բ�������
*/

int main()
{
	WORD version=MAKEWORD(2,2);  //�汾��
	WSADATA data;                //����
	WSAStartup(version,&data);   //����WinSock
   
	//-- ��Socket API���������׵�TCP������
	// 1,����һ��socket
	SOCKET _sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);      /*������1��AF_INET    :�׽������� 
																	   2��SOCK_STREAM:sock��������������
																	   3, IPPROTO_TCP:ʹ��ʲô���͵�Э��*/
	//2,bind �����ڽ��ܿͻ������ӵ�����˿�
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;

	if (bind(_sock, (sockaddr*)&_sin, sizeof(_sin)) == SOCKET_ERROR)
	{
		printf("ERROR,�󶨶˿�ʧ��.....\n");
	}
	else
	{
		printf("�󶨶˿ڳɹ�......\n");
	}
	//3,listen �����˿�
	if (SOCKET_ERROR == listen(_sock, 5))
	{
		printf("����ʧ��\n");
	}
	else
	{
		printf("�����ɹ�\n");
	}

	sockaddr_in clientAddr = {};
	int nAddrLen = sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;
	char msgBuf[] = "Hellow I am server..";
	while (true)
	{
		//4��accept �ȴ����ܿͻ�������
		_cSock = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
		if (INVALID_SOCKET == _cSock)
		{
			printf("���󣬽��յ���Ч�ͻ���SOCKET...\n");
		}
		// 5,send ��ͻ��˷���һ������
		printf("�¿ͻ��˼���....IP��%s",inet_ntoa(clientAddr.sin_addr));
		send(_cSock, msgBuf, strlen(msgBuf) + 1, 0);
	}

	//6���ر��׽���
	closesocket(_sock);
	WSACleanup();
	return 0;
}
