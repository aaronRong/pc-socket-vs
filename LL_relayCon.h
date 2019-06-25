#ifndef __LL_RELAYCON__
#define __LL_RELAYCON__

/* enum definition */
typedef enum _e_LL_Status
{
	LL_STATUS_PASS					= 0x000,
	LL_STATUS_ERROR				= 0x001,

	LL_STATUS_WINSOCK_VER_ERR		= 0x100,
	LL_STATUS_SOCKET_CREATE_ERR	= 0x101,
	LL_STATUS_SOCKET_CONNECT_ERR	= 0x102,
	LL_STATUS_SOCKET_SERVER_ERR	= 0x103,

	LL_STATUS_SOCKET_SEND_ERR		= 0x200, 
	LL_STATUS_SOCKET_recv_ERR		= 0x201,

	LL_STATUS_SOCKET_CLOSED		= 0x300,

}e_LL_Status;

typedef enum _e_LL_Relay_NO
{
	LL_RELAY_ONE					= 0x00,
	LL_RELAY_TWO,
	LL_RELAY_THREE,
}e_LL_Relay_NO;

typedef enum _e_LL_Relay_State
{
	LL_RELAY_ON					= 0x00,
	LL_RELAY_OFF,
}e_LL_Relay_State;

/* function declaration */
e_LL_Status LL_configSocketComm(char* serverIp, unsigned int commPort);
e_LL_Status LL_relaySet(e_LL_Relay_NO relayNo, e_LL_Relay_State state);
e_LL_Relay_State getRelayStatus(e_LL_Relay_NO relayNo);

#endif