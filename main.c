#include <stdio.h>
#include <winsock2.h>
#include "LL_relayCon.h"

#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996) 

#define SERVER_IP		"192.168.0.10"
#define PORT_NO			80

/* function declaration */
void whiteTest(e_LL_Relay_NO relayNo);

/*
* Author Name: aaron.gao
* Time: 2019.6.25
*/
int main(int argc, char* argv[])
{
	bool status = false;
	unsigned long loop = 0;

	status = open(SERVER_IP, PORT_NO);
	printf("status:%d\n", status);

	while (1)
	{
		whiteTest(LL_RELAY_ONE);
		Sleep(1000);
		
		whiteTest(LL_RELAY_TWO);
		Sleep(1000);

		whiteTest(LL_RELAY_THREE);
		Sleep(1000);

		loop++;
		printf("loop:%d\n", loop);
	}

	return 0;
}

/*
* Author Name: aaron.gao
* Time: 2019.6.25
*/
void whiteTest(e_LL_Relay_NO relayNo)
{
	bool status;

	/* alarm */
	printf("alarm %d...\n", relayNo);
	status = alarm(relayNo, 3);
	if (true != status)
	{
		printf("relay %d alarm fail, status:%d\n", relayNo, status);
	}
	Sleep(300);

	/* check alarm */
	status = isalarm(relayNo);
	if (status == true)
	{
		printf("relay %d is alarm\n", relayNo);
	}
	else
	{
		printf("relay %d is not alarm\n", relayNo);
	}
	Sleep(300);

	/* stop alarm */
	stop(relayNo);
	printf("stop alarm %d\n", relayNo);
	Sleep(300);

	/* check alarm */
	status = isalarm(relayNo);
	if (status == true)
	{
		printf("relay %d is alarm\n", relayNo);
	}
	else
	{
		printf("relay %d is not alarm\n", relayNo);
	}
}