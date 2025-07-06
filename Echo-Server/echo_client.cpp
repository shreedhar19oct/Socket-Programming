// tcp_client.cpp
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);  // Create socket
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);  // Server IP

    connect(sock, (sockaddr*)&server_addr, sizeof(server_addr));  // Connect to server

    const char* msg = "Hi Server!";
    send(sock, msg, strlen(msg), 0);  // Send message

    char buffer[1024] = {0};
    read(sock, buffer, sizeof(buffer));  // Receive reply
    std::cout << "Server says: " << buffer << "\n";

    close(sock);
    return 0;
}