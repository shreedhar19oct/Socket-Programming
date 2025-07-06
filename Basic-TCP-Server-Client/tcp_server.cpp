// tcp_server.cpp
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);  // Create TCP socket
    if (server_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;       // Accept from any IP
    server_addr.sin_port = htons(8080);             // Port 8080

    bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr));  // Bind IP+Port

    listen(server_fd, 1);  // Listen for 1 connection

    std::cout << "Waiting for connection...\n";

    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);
    int client_socket = accept(server_fd, (sockaddr*)&client_addr, &client_len);  // Accept connection

    char buffer[1024] = {0};
    read(client_socket, buffer, sizeof(buffer));  // Receive message
    std::cout << "Client says: " << buffer << "\n";

    const char* reply = "Hello Client!";
    send(client_socket, reply, strlen(reply), 0);  // Send response

    close(client_socket);
    close(server_fd);
    return 0;
}