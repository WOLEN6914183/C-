/************************************************************
* 文件名 ：简易TCP服务端
* 
* 作  用 ：建立TCP服务器最大连接数为5，显示新加入的客户端地址
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
	#pragma comment(lib,"ws2_32.lib")   //如果在属性中提前设置了这部分可以不用声明
*/

int main()
{
	WORD version=MAKEWORD(2,2);  //版本号
	WSADATA data;                //数据
	WSAStartup(version,&data);   //启动WinSock
   
	//-- 用Socket API建立个简易的TCP服务器
	// 1,建立一个socket
	SOCKET _sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);      /*参数：1，AF_INET    :套接字类型 
																	   2，SOCK_STREAM:sock网络类型数据流
																	   3, IPPROTO_TCP:使用什么类型的协议*/
	//2,bind 绑定用于接受客户端连接的网络端口
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;

	if (bind(_sock, (sockaddr*)&_sin, sizeof(_sin)) == SOCKET_ERROR)
	{
		printf("ERROR,绑定端口失败.....\n");
	}
	else
	{
		printf("绑定端口成功......\n");
	}
	//3,listen 监听端口
	if (SOCKET_ERROR == listen(_sock, 5))
	{
		printf("监听失败\n");
	}
	else
	{
		printf("监听成功\n");
	}

	sockaddr_in clientAddr = {};
	int nAddrLen = sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;
	char msgBuf[] = "Hellow I am server..";
	while (true)
	{
		//4，accept 等待接受客户端连接
		_cSock = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
		if (INVALID_SOCKET == _cSock)
		{
			printf("错误，接收到无效客户端SOCKET...\n");
		}
		// 5,send 向客户端发送一条数据
		printf("新客户端加入....IP：%s",inet_ntoa(clientAddr.sin_addr));
		send(_cSock, msgBuf, strlen(msgBuf) + 1, 0);
	}

	//6，关闭套接字
	closesocket(_sock);
	WSACleanup();
	return 0;
}
