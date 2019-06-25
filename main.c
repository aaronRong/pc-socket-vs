#include <stdio.h>
#include <winsock2.h>
#include "LL_relayCon.h"

#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996) 

#define SERVER_IP		"192.168.0.10"
#define PORT_NO			80

int main(int argc, char* argv[])
{
	e_LL_Status status;
	unsigned long loop = 0;

	status = LL_configSocketComm(SERVER_IP, PORT_NO);
	printf("status:%d\n", status);

	while (1)
	{
		status = LL_relaySet(LL_RELAY_ONE, LL_RELAY_ON);
		if (LL_STATUS_PASS != status)
		{
			printf("relay one on fail, status:%d\n", status);
		}
		Sleep(100);

		status = LL_relaySet(LL_RELAY_ONE, LL_RELAY_OFF);
		if (LL_STATUS_PASS != status)
		{
			printf("relay one off fail, status:%d\n", status);
		}
		Sleep(100);

		status = LL_relaySet(LL_RELAY_TWO, LL_RELAY_ON);
		if (LL_STATUS_PASS != status)
		{
			printf("relay two on fail, status:%d\n", status);
		}
		Sleep(100);

		status = LL_relaySet(LL_RELAY_TWO, LL_RELAY_OFF);
		if (LL_STATUS_PASS != status)
		{
			printf("relay two off fail, status:%d\n", status);
		}
		Sleep(100);

		status = LL_relaySet(LL_RELAY_THREE, LL_RELAY_ON);
		if (LL_STATUS_PASS != status)
		{
			printf("relay three on fail, status:%d\n", status);
		}
		Sleep(100);

		status = LL_relaySet(LL_RELAY_THREE, LL_RELAY_OFF);
		if (LL_STATUS_PASS != status)
		{
			printf("relay three off fail, status:%d\n", status);
		}
		Sleep(100);

		loop++;
		printf("loop:%d\n", loop);
	}

	return 0;
}