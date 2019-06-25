#include <stdio.h>
#include <winsock2.h>
#include "LL_relayCon.h"

#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996) 

/* definition */
#define MAX_RECV_LEN		(30UL)

/* global varaible */
static SOCKET socketClient;
static struct sockaddr_in serverIn;
static relayState[3] = { LL_RELAY_OFF , LL_RELAY_OFF , LL_RELAY_OFF};

const char relayTcp[6][20] = {
	"relay one on",
	"relay one off",
	"relay two on",
	"relay two off",
	"relay three on",
	"relay three off",
};

const char relayTcpBack[6][20] = {
	"relay one on done",
	"relay one off done",
	"relay two on done",
	"relay two off done",
	"relay three on done",
	"relay three off done",
};

/*
* Author Name: aaron.gao
* Time: 2019.6.25
*/
e_LL_Status LL_configSocketComm(char* serverIp, unsigned int commPort)
{
	WORD socket_version;
	WSADATA wsadata;
	socket_version = MAKEWORD(2, 2);			/* call different winsock version */
	if (WSAStartup(socket_version, &wsadata) != 0)
	{
		printf("WSAStartup error!");
		system("pause");
		return LL_STATUS_WINSOCK_VER_ERR;
	}

	socketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);		/* ipv4, reliable transmission */
	if (socketClient == INVALID_SOCKET)
	{
		printf("invalid socket !");
		system("pause");
		return LL_STATUS_SOCKET_CREATE_ERR;
	}

	serverIn.sin_family = AF_INET;				/* ipv4 */
	serverIn.sin_port = htons(commPort);		/* port from little-endian to big-endian */
	serverIn.sin_addr.S_un.S_addr = inet_addr(serverIp);	/* convert ip */
	if (connect(socketClient, (struct sockaddr*) & serverIn, sizeof(serverIn)) == SOCKET_ERROR)		/* build socket transmission */
	{
		printf("connect error\n");
		system("pause");
		return LL_STATUS_SOCKET_CONNECT_ERR;
	}

	return LL_STATUS_PASS;
}

/*
* Author Name: aaron.gao
* Time: 2019.6.25
*/
e_LL_Status LL_relaySet(e_LL_Relay_NO relayNo, e_LL_Relay_State state)
{
	unsigned int len = 0;
	unsigned int ret = 0;
	unsigned char recvBuf[30];

	/* send */
	len = send(socketClient, relayTcp[relayNo*2 + state], strlen(relayTcp[relayNo * 2 + state]), 0);
	if (SOCKET_ERROR == len)
	{
		return LL_STATUS_SOCKET_SEND_ERR;
	}

	/* recv */
	len = recv(socketClient, recvBuf, MAX_RECV_LEN, 0);
	if (len <= 0)
	{
		return LL_STATUS_SOCKET_SERVER_ERR;
	}
	ret = strncmp(relayTcpBack[relayNo * 2 + state], recvBuf, len);
	if (ret != 0)
	{
		return LL_STATUS_SOCKET_recv_ERR;
	}

	/* set state */
	relayState[relayNo] = state;

	return LL_STATUS_PASS;
}

/* 
* Author Name: aaron.gao
* Time: 2019.6.25
*/
e_LL_Relay_State getRelayStatus(e_LL_Relay_NO relayNo)
{
	return relayState[relayNo];
}

/*
*
*
*/
e_LL_Status  closeSocket(void)
{
	closesocket(socketClient);
	WSACleanup();

	return LL_STATUS_PASS;
}