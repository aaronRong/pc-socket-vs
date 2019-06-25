#ifndef __LL_RELAYCON__
#define __LL_RELAYCON__
#include <stdbool.h>

/* enum definition */
typedef enum _e_LL_Relay_NO
{
	LL_RELAY_ONE					= 0x00,
	LL_RELAY_TWO,
	LL_RELAY_THREE,
}e_LL_Relay_NO;

typedef enum _e_LL_Relay_State
{
	LL_RELAY_ON						= 0x00,
	LL_RELAY_OFF,
}e_LL_Relay_State;

/* function declaration */
bool open(const char* serverIp, unsigned short commPort);
bool alarm(int id, unsigned short seconds);
bool stop(int id);
bool isalarm(int id);
bool close(void);

#endif