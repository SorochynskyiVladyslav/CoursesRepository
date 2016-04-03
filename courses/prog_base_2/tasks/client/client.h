#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480 // How much is printed out to the screen

SOCKET newSocket (SOCKET recvSocket);
void connectSocket (SOCKET recvSocket, SOCKADDR_IN recvSockAddr);
void request (SOCKET recvSocket, const char* host_name);
void secretRequest (SOCKET recvSocket, char* host_name, char* buffer);
void getResponse (SOCKET recvSocket, char* buffer);
char* findBestStudent (char* buffer);
void sendResult (SOCKET recvSocket, char* host_name, char * result);


#endif // CLIENT_H_INCLUDED
