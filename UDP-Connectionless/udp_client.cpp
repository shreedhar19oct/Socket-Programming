// udp_client.cpp
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);  // UDP socket

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    const char* msg = "Hello UDP Server!";
    sendto(sockfd, msg, strlen(msg), 0, (sockaddr*)&server_addr, sizeof(server_addr));

    char buffer[1024];
    socklen_t len = sizeof(server_addr);
    int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (sockaddr*)&server_addr, &len);
    buffer[n] = '\0';

    std::cout << "Server: " << buffer << "\n";

    close(sockfd);
    return 0;
}