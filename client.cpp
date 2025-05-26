#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>

#define PORT 8080
#define SERVER_IP "hmac-server"
#define KEY_LENGTH 32  // 256-bit key

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr{};
    unsigned char key[KEY_LENGTH];

    // Generate random HMAC key
    if (!RAND_bytes(key, KEY_LENGTH)) {
        std::cerr << "Key generation failed!" << std::endl;
        return 1;
    }

    std::cout << "Generated HMAC key: ";
    for (int i = 0; i < KEY_LENGTH; ++i)
        printf("%02x", key[i]);
    std::cout << std::endl;

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr);

    // Connect to server
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // Send key
    send(sock, key, KEY_LENGTH, 0);
    std::cout << "Key sent to server." << std::endl;

    close(sock);
    return 0;
}
