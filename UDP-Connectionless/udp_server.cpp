// udp_server.cpp
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);  // UDP socket

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8888);

    bind(sockfd, (sockaddr*)&server_addr, sizeof(server_addr));  // Bind

    char buffer[1024];
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);

    int len = recvfrom(sockfd, buffer, sizeof(buffer), 0, (sockaddr*)&client_addr, &client_len);
    buffer[len] = '\0';
    std::cout << "Client: " << buffer << "\n";

    const char* reply = "Got your message!";
    sendto(sockfd, reply, strlen(reply), 0, (sockaddr*)&client_addr, client_len);

    close(sockfd);
    return 0;
}