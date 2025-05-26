#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <openssl/hmac.h>

#define PORT 8080
#define KEY_LEN 32
#define MSG_LEN 128
#define HMAC_LEN 32  // SHA256 output

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address{};
    int addrlen = sizeof(address);
    unsigned char buffer[KEY_LEN + MSG_LEN + HMAC_LEN] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    std::cout << "Server waiting for connection...\n";
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    read(new_socket, buffer, sizeof(buffer));

    // Parse key, message, and HMAC
    unsigned char *key = buffer;
    unsigned char *message = buffer + KEY_LEN;
    unsigned char *received_hmac = buffer + KEY_LEN + MSG_LEN;

    // Compute HMAC
    unsigned char computed_hmac[HMAC_LEN];
    unsigned int len = 0;
    HMAC(EVP_sha256(), key, KEY_LEN, message, MSG_LEN, computed_hmac, &len);

    // Compare
    bool valid = memcmp(received_hmac, computed_hmac, HMAC_LEN) == 0;
    std::cout << "Received message: " << std::string((char*)message, MSG_LEN) << "\n";
    std::cout << "HMAC is " << (valid ? "valid ✅" : "invalid ❌") << "\n";

    close(new_socket);
    close(server_fd);
    return 0;
}

