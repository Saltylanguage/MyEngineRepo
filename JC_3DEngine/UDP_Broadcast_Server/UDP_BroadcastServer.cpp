#include <iostream>
#include <conio.h>
#include <WinSock2.h>
#include <ctime>
#include <string>
#include <Windows.h>
#include <process.h>
#include <conio.h>



#pragma comment (lib, "ws2_32.lib")

#define PORT 8888


char currentDate[16];
char currentTime[16];

SOCKET listener;

char * buffer = new char[1024];

char recvBuff[50];
int recvBuffLen = 50;

sockaddr_in Sender_addr;

int len = sizeof(sockaddr_in);

void getDate()
{
	time_t timeInfo = time(0); // get time now
	tm *now = localtime(&timeInfo);
	strftime(currentDate, 80, "%d/%m/%Y", now);
}

void getTime()
{
	time_t t = time(0); // get time now
	struct tm *now = localtime(&t);
	strftime(currentTime, 80, "%H:%M:%S", now);
}

void recvFunct(void *param)
{
	while (1)
	{
		recvfrom(listener, recvBuff, recvBuffLen, 0, (sockaddr *)&Sender_addr, &len);
		std::cout << "received message: " << recvBuff << std::endl;
	}
}

void sendTime(void *param)
{
	while (true)
	{
		getTime();
		if (sendto(listener, currentTime, strlen(currentTime) + 1, 0, (sockaddr *)&Sender_addr, sizeof(Sender_addr)) < 0)
		{
			perror("\nSend To Listener Failed: ");
			_getch();
			closesocket(listener);
		}
		Sleep(1000);
	}
}

void sendDate(void *param)
{
	while (true)
	{
		getDate();
		if (sendto(listener, currentDate, strlen(currentDate) + 1, 0, (sockaddr *)&Sender_addr, sizeof(Sender_addr)) < 0)
		{
			perror("Send to Listner failed\n");
			_getch();
			closesocket(listener);
		}
		Sleep(10000);
	}
}

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	listener = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	char broadcast = 'a';

	if (setsockopt(listener, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0)
	{
		perror("broadcast options");
		closesocket(listener);
		return 1;
	}

	Sender_addr.sin_family = AF_INET;
	Sender_addr.sin_port = htons(PORT);
	Sender_addr.sin_addr.s_addr = inet_addr("255.255.255.255");

	// start 3 threads: 1 for listening, 1 for broadcasting time, and 1 foor broadcasting date
	_beginthread(sendTime, 0, NULL);
	_beginthread(sendDate, 0, NULL);
	//_beginthread(recvFunct, 0, NULL);

	std::cout << "spawned threads, press any key to exit.. \n";
	_getch(); //check for key press to exit program.
	closesocket(listener);

	WSACleanup();

	return 0;
}


