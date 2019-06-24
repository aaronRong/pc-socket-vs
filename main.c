#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996) 

#define SERVER_IP		"192.168.0.10"

static SOCKET socket_client;         //���ش����Ŀͻ���socket
static struct sockaddr_in server_in; //���ڴ洢�������Ļ�����Ϣ

static void analysis(char* data, int datal);

int main(int argc, char* argv[])
{
	char   recData[255];          //����ط�һ��Ҫ�������ô�С���������ÿ���ܻ�ȡ��������
	int ret;                      //recv�����ķ���ֵ ������״̬ÿ��״̬�ĺ������·��н���

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

	server_in.sin_family = AF_INET;    //IPV4Э����
	server_in.sin_port = htons(80);  //�������Ķ˿ں�
	server_in.sin_addr.S_un.S_addr = inet_addr(SERVER_IP); //����IP
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
		recv���� ��ʵ�ʾ��Ǵ�socket�Ļ���������������
		����ֵ���ǿ������ֽ����Ĵ�С��
		���涨������壨revData����С��255������recv�ĵ������������ֻ������Ϊ255��
		�������Ϊ����255����ֵ����ִ��recv����ʱǡ�û����������ݴ���255��
		�ͻᵼ���ڴ�й©������retֵС���㣬�������״̬�����������ý�����������
		����ΪrevData�Ĵ�С����ô���������ڵ�����С��255��ʱ��
		ֻ��Ҫִ��һ��recv�Ϳ��Խ������������ݶ��������������������������ݴ�
		��255��ʱ�򣬾�Ҫִ�ж��recv����������������û�����ݵ�ʱ�򣬻ᴦ������
		״̬�����while������ͣ�����ֱ���µ����ݽ������߳����쳣��
		************************************************************************/
		if (ret > 0)
		{
			recData[ret] = 0x00;//��������²�����ô��������ô��ֻ��Ϊ���ܰ��ִ�����ʽ�����
			analysis(recData, ret);

		}
		else if (ret == 0)
		{
			//��ret == 0 ˵�����������ߡ�
			printf("lost connection , Ip = %s\n", inet_ntoa(server_in.sin_addr));
			break;
		}
		else//ret < 0
		{
			//��ret < 0 ˵���������쳣 ��������״̬��������߶�ȡ����ʱ����ָ�����ȡ�
			//������������Ҫ�����Ͽ��Ϳͻ��˵����ӡ�
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
	//���������ǿ��Զ��ѽ��յ������ݽ��д���

	//һ����������ﶼ�Ǵ���ճ�����ĵط�

	//���ճ��֮�� �����������ݷ��͸����ݴ�����
}
