#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address{};
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Create socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // Listen
    listen(server_fd, 3);

    std::cout << "Server listening on port " << PORT << "...\n";
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    // Receive HMAC key
    int bytes_read = read(new_socket, buffer, 1024);
    std::cout << "Received HMAC key (" << bytes_read << " bytes): ";
    for (int i = 0; i < bytes_read; ++i)
        printf("%02x", static_cast<unsigned char>(buffer[i]));
    std::cout << std::endl;

    close(new_socket);
    close(server_fd);
    return 0;
}
