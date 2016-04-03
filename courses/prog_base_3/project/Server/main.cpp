#include <iostream>
#include <io.h>
#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

using namespace std;

int main(int argc , char *argv[])
{
    WSADATA wsa;
    SOCKET s , new_socket;
    struct sockaddr_in server , client;
    int c;
    char *message;



    cout << "\nInitialising Winsock..." << endl;
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        cout << "Failed. Error Code : " << WSAGetLastError();
        return 1;
    }
    cout << "Initialised" << endl;

    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        cout << "Could not create socket : " << WSAGetLastError();
    }
    cout << "Socket created." << endl;

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 666 );

    //Bind
    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        cout << "Bind failed with error code : " << WSAGetLastError();
        exit(EXIT_FAILURE);
    }
    cout << "Bind done" << endl;

    //Listen to incoming connections
    listen(s , 3);

    //Accept and incoming connection
    cout << "Waiting for incoming connections..." << endl;

    c = sizeof(struct sockaddr_in);
    int recv_size;
    char server_reply[2000];

    if( (new_socket = accept(s, (struct sockaddr *)&client, &c)) != INVALID_SOCKET )
    {
        cout << "Connection accepted" << endl;

        //Reply to the client
        message = "Hello Client , I have received your connection\n";
        send(new_socket , message , strlen(message) , 0);
        while (1){
        if((recv_size = recv(new_socket, server_reply , 2000 , 0)) == SOCKET_ERROR)
        {
        cout << "recv failed" << endl;
        }
        server_reply[recv_size] = '\0';
        cout << "Reply received: " << server_reply << endl;
        send(new_socket , "message2" , 8 , 0);
        Sleep(1000);
        }
    }

    if (new_socket == INVALID_SOCKET)
    {
        cout << "accept failed with error code : " << WSAGetLastError();
        return 1;
    }

    closesocket(s);
    WSACleanup();





    return 0;
}
