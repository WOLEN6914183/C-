/************************************************************
* 文件名 ：简易TCP客户端
*
* 作  用 ：连接本地服务器
*
* 作  者 ： xsx
*
* 日  期 ：2022/1/22
**************************************************************/

/*-----------------------------头文件------------------------------*/

#include<Windows.h>
#include<WinSock2.h>
#include<stdio.h>

/*-------------------------------相关宏---------------------------------*/

/*
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")      //如果在属性中提前设置了这部分可以不用声明
*/
int main()
{
	WORD version = MAKEWORD(2, 2);  //版本号
	WSADATA data;					//数据
	WSAStartup(version, &data);		//启动WinSock

	// 1，创建套接字
	SOCKET _sock = socket(AF_INET,SOCK_STREAM,0);
	if (INVALID_SOCKET == _sock)
	{
		printf("错误，建立sock失败....\n");
	}
	else
	{
		printf("建立Sock成功.....\n");
	}
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	// 2, 连接服务器 connect
	int ret =connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in));
	if (ret==SOCKET_ERROR)
	{
		printf("连接失败....\n");
	}
	else
	{
		printf("连接成功.....\n");
	}
	
	//3，接受服务器信息 recv
	char recvBuf[256] = {};
	int nlen =recv(_sock, recvBuf, 256, 0);
	if (nlen>0)
	{
		printf("接收到数据：%s\n",recvBuf);
	}
	//4, 关闭套接字
	closesocket(_sock);

	WSACleanup();                   //关闭WinSock
	getchar();
	return 0;
}