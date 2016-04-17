#include "servheader.h"


int main(int argc , char *argv[])
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        cout << "Failed to initialise Winsock. Error Code : " << WSAGetLastError();
        return 1;
    }

    int nPort = 5000;
    SOCKET serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == serverSock) {
        cout << "Invalid socket!" << endl;
        return 1;
    }

    SOCKADDR_IN serverSockAddr;
    serverSockAddr.sin_port = htons(nPort);
    serverSockAddr.sin_family = AF_INET;
    serverSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(serverSock, (LPSOCKADDR)&serverSockAddr, sizeof(serverSockAddr)) == SOCKET_ERROR) {
        cout << "Cannot bind to port " << nPort << endl;
        closesocket(serverSock);
        WSACleanup();
        return 1;
    }

    u_long iMode = 1;
    int iResult = ioctlsocket(serverSock, FIONBIO, &iMode);
    if (iResult != NO_ERROR) {
        cout << "ioctlsocket failed with error: " << iResult << endl;
        closesocket(serverSock);
        WSACleanup();
        return 1;
    }

    if (listen(serverSock, SOMAXCONN) == SOCKET_ERROR) {
        cout << "socket listen error " << WSAGetLastError() << endl;
        closesocket(serverSock);
        WSACleanup();
        return 1;
    }

    vector <Client> clients();








    WSACleanup();





    return 0;
}
