#include "client.h"

int main(int argc , char *argv[])
{
    WSADATA wsa;
    SOCKADDR_IN recvSockAddr;
    SOCKET recvSocket;
    int numrcv = 0;
    struct hostent * remoteHost;
    char * ip;
    const char * host_name = "pb-homework.appspot.com";
    char * buffer = malloc(sizeof(char) * MAXBUFLEN);
    memset(buffer, 0, MAXBUFLEN);

    printf("\nInitialising Winsock... ");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
    printf("Initialised. ");

    remoteHost = gethostbyname(host_name);
	ip = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
	printf("IP address is: %s.\n", ip);
    memset(&recvSockAddr, 0, sizeof(recvSockAddr)); // zero the sockaddr_in structure
    recvSockAddr.sin_port=htons(PORT); // specify the port portion of the address
    recvSockAddr.sin_family=AF_INET; // specify the address family as Internet
    recvSockAddr.sin_addr.s_addr= inet_addr(ip); // specify ip address

    recvSocket = newSocket(recvSocket);
    connectSocket(recvSocket, recvSockAddr);
    request (recvSocket, host_name);
    getResponse (recvSocket, buffer);
    printf("%s\r\n", buffer);
    secretRequest (recvSocket, host_name, buffer);
    free(buffer);
    buffer = malloc(sizeof(char) * MAXBUFLEN);
    getResponse (recvSocket, buffer);
    printf("%s\n", buffer);

    char* result = findBestStudent (buffer);
    sendResult (recvSocket, host_name, result);

    free(buffer);
    buffer = malloc(sizeof(char) * MAXBUFLEN);

    // get server response and print it
    getResponse (recvSocket, buffer);
    printf("\nServer response:\n\n%s\n", buffer);






    closesocket(recvSocket);
    WSACleanup();
    return 0;
}

SOCKET newSocket (SOCKET recvSocket) {
    if((recvSocket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
    printf("Socket created.\n");
    return recvSocket;
}

void connectSocket (SOCKET recvSocket, SOCKADDR_IN recvSockAddr) {
    if(connect(recvSocket,(SOCKADDR*)&recvSockAddr,sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        printf("ERROR: socket could not connect\r\n");
        closesocket(recvSocket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

void request (SOCKET recvSocket, const char* host_name) {
    char request[200];
    sprintf(request, "GET /var/1 HTTP/1.1\r\nHost:%s\r\n\r\n", host_name);  // add Host header with host_name value
    send(recvSocket, request, strlen(request), 0);
}

void secretRequest (SOCKET recvSocket, char* host_name, char* buffer) {
	char secret[50];
	char request[200];
	strcpy(secret, strstr(buffer, "secret"));
	sprintf(request, "GET /var/1?%s HTTP/1.1\r\nHost:%s\r\n\r\n", secret, host_name);
	send(recvSocket, request, strlen(request), 0);
}

void getResponse (SOCKET recvSocket, char* buffer){
    int numrcv = recv(recvSocket, buffer, MAXBUFLEN, NO_FLAGS_SET);

    if (numrcv == SOCKET_ERROR)
    {
        printf("ERROR: recvfrom unsuccessful\r\n");
        int status = closesocket(recvSocket);
        if(status == SOCKET_ERROR)
			printf("ERROR: closesocket unsuccessful\r\n");
        status = WSACleanup();
        if (status == SOCKET_ERROR)
			printf("ERROR: WSACleanup unsuccessful\r\n");
        system("pause");
        exit(EXIT_FAILURE);
    }
}

char* findBestStudent (char* buffer) {
    char* name;
    char* tmp;
    char result[100] = "result=";
    tmp = buffer;
    int amount = 0;
    while (amount != 6){
        if (*buffer == '\n'){
            amount++;
        }
        buffer++;
    }
    tmp = buffer;
    amount = 0;
    while (*tmp != '\0') {
        if (*tmp == '\n') {
            amount++;
        }
        tmp++;
    }
    int arr[amount];
    int i = 0, max = 0;
    tmp = buffer;
    while (*tmp != '\0') {
        if (*tmp == ' ') {
            arr[i] = atoi (tmp);
            i++;
        }
        tmp++;
    }
    for (i = 0; i < amount; i++) {
        if (arr[i] > arr[max]){
            max = i;
        }
    }
    tmp = buffer;
    i = 0;
    while (*tmp != '\0' && i != max) {
        if (*tmp == '\n') {
            i++;
        }
        tmp++;
    }
    name = strtok(tmp, " ");
    strcat(result, name);
    return result;
}

void sendResult (SOCKET recvSocket, char* host_name, char * result){
	char request[500];
	sprintf(request, "POST /var/1 HTTP/1.0\r\nHost: %s\r\nContent-length: %d\r\n\r\n%s", host_name, strlen(result), result);
	//puts(request);
	send(recvSocket, request, strlen(request), 0);
}
