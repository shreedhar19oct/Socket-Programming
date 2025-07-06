// echo_server.cpp
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(9999);

    bind(server_fd, (sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);

    int client = accept(server_fd, NULL, NULL);

    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes = read(client, buffer, sizeof(buffer));
        if (bytes <= 0) break;

        std::cout << "Received: " << buffer << "\n";
        send(client, buffer, bytes, 0);  // Echo back
    }

    close(client);
    close(server_fd);
    return 0;
}