#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996) 

#define SERVER_IP		"192.168.0.10"

static SOCKET socket_client;         //本地创建的客户端socket
static struct sockaddr_in server_in; //用于存储服务器的基本信息

static void analysis(char* data, int datal);

int main(int argc, char* argv[])
{
	char   recData[255];          //这个地方一定要酌情设置大小，这决定了每次能获取多少数据
	int ret;                      //recv函数的返回值 有三种状态每种状态的含义在下方有解释

	WORD socket_version;
	WSADATA wsadata;
	socket_version = MAKEWORD(2, 2);
	if (WSAStartup(socket_version, &wsadata) != 0)
	{
		printf("WSAStartup error!");
		system("pause");
		return;
	}

	socket_client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socket_client == INVALID_SOCKET)
	{
		printf("invalid socket !");
		system("pause");
		return;
	}

	server_in.sin_family = AF_INET;    //IPV4协议族
	server_in.sin_port = htons(80);  //服务器的端口号
	server_in.sin_addr.S_un.S_addr = inet_addr(SERVER_IP); //服务IP
	if (connect(socket_client, (struct sockaddr*) & server_in, sizeof(server_in)) == SOCKET_ERROR)
	{
		printf("connect error\n");
		system("pause");
		return 0;
	}
	else {}

	printf("connect %s:%d\n", inet_ntoa(server_in.sin_addr), server_in.sin_port);
	send(socket_client, "relay one on", strlen("relay one on"), 0);
	while (1)
	{
		ret = recv(socket_client, recData, 255, 0);
		/************************************************************************
		recv函数 的实质就是从socket的缓冲区里拷贝出数据
		返回值就是拷贝出字节数的大小。
		上面定义的载体（revData）大小是255，所以recv的第三个参数最大只能设置为255，
		如果设置为大于255的数值，当执行recv函数时恰好缓冲区的内容大于255，
		就会导致内存泄漏，导致ret值小于零，解除阻塞状态。因此这里最好将第三个参数
		设置为revData的大小，那么当缓冲区内的数据小于255的时候
		只需要执行一次recv就可以将缓冲区的内容都拷贝出来，但当缓冲区的数据大
		于255的时候，就要执行多次recv函数。当缓冲区内没有内容的时候，会处于阻塞
		状态，这个while函数会停在这里。直到新的数据进来或者出现异常。
		************************************************************************/
		if (ret > 0)
		{
			recData[ret] = 0x00;//正常情况下不必这么做，我这么做只是为了能按字串的形式输出它
			analysis(recData, ret);

		}
		else if (ret == 0)
		{
			//当ret == 0 说明服务器掉线。
			printf("lost connection , Ip = %s\n", inet_ntoa(server_in.sin_addr));
			break;
		}
		else//ret < 0
		{
			//当ret < 0 说明出现了异常 例如阻塞状态解除，或者读取数据时出现指针错误等。
			//所以我们这里要主动断开和客户端的链接。
			printf("something wrong of %s\n", inet_ntoa(server_in.sin_addr));
			closesocket(socket_client);
			break;
		}
	}

	closesocket(socket_client);
	WSACleanup();
	return 0;
}

static void analysis(char* data, int datal)
{
	printf("recv data:%s  datal:%d\n", data, datal);
	//在这里我们可以对已接收到的数据进行处理

	//一般情况下这里都是处理“粘包”的地方

	//解决粘包之后 将完整的数据发送给数据处理函数
}
