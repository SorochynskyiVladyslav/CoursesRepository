#ifndef SERVHEADER_H_INCLUDED
#define SERVHEADER_H_INCLUDED

#include <iostream>
#include <vector>
#include <io.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Librar
using namespace std;


class Client {
public:
    SOCKET s;
    string name;
    Client (SOCKET s, string name);
};


#endif // SERVHEADER_H_INCLUDED
