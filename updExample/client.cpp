
#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

using namespace std;


int main() {
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1); 
        if (WSAStartup(DLLVersion, &wsaData) != 0) {
            cout << "Error" << '\n';
            
        };

        char maa[10];

    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(3425);
    addr.sin_family = AF_INET; 


    SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);

        if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
            cout << "Error: failed connect tot server" << '\n';
            return 1;
        }
        else {
            cout << "Connected" << '\n';
        }
        string cmd;
       
        while (1) {
            cout << "Enter the command" << '\n';
            cin.getline(maa, 10);
            send(Connection, maa, sizeof(maa), NULL);
            cout << '\n';
            if (!strcmp(maa, "OFF")) {
                break;
            }
        }

        closesocket(Connection);
    return 0;
}
