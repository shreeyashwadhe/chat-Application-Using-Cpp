#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#include<string>

using namespace std;
#pragma comment(lib, "ws2_32.lib")

bool initialize() {
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

void SendChatMessage(SOCKET s) {
    cout << "Enter your chat name: "<<endl;
    string name;
    getline(cin, name);

    while (true) {
        string message;
        getline(cin, message);

        if (message == "quit") {
            cout << "Stopping the application..." << endl;
            break;
        }

        string fullMessage = name + ": " + message;
        int bytesent = send(s, fullMessage.c_str(), fullMessage.length(), 0);
        if (bytesent == SOCKET_ERROR) {
            cout << "Error sending message" << endl;
            break;
        }
    }

    closesocket(s);
    WSACleanup();
}

void ReceiveMessage(SOCKET s) {
    char buffer[4096];
    int recvlength;

    while (true) {
        recvlength = recv(s, buffer, sizeof(buffer), 0);
        if (recvlength <= 0) {
            cout << "Disconnected from the server" << endl;
            break;
        }
        string msg(buffer, recvlength);
        cout << msg << endl;
    }

    closesocket(s);
    WSACleanup();
}

int main() {
    if (!initialize()) {
        cout << "Winsock initialization failed" << endl;
        return 1;
    }

    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        cout << "Invalid socket" << endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(12345);

    if (inet_pton(AF_INET, "127.0.0.1", &(serveraddr.sin_addr)) != 1) {
        cout << "Invalid address" << endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    if (connect(s, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR) {
        cout << "Unable to connect to server" << endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    cout << "Connected to server!" << endl;

    thread sender(SendChatMessage, s);
    thread receiver(ReceiveMessage, s);

    sender.join();
    receiver.join();

    return 0;
}
