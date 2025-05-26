#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>

#define SERVER_IP "hmac-server"
#define PORT 8080
#define KEY_LEN 32
#define MSG_LEN 128
#define HMAC_LEN 32  // SHA256

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr{};
    unsigned char key[KEY_LEN];
    unsigned char message[MSG_LEN] = "This is a secret message from client.";
    unsigned char hmac[HMAC_LEN];
    unsigned char buffer[KEY_LEN + MSG_LEN + HMAC_LEN];

    // Generate random key
    RAND_bytes(key, KEY_LEN);

    // Compute HMAC
    unsigned int len = 0;
    HMAC(EVP_sha256(), key, KEY_LEN, message, MSG_LEN, hmac, &len);

    // Prepare buffer: key + message + hmac
    memcpy(buffer, key, KEY_LEN);
    memcpy(buffer + KEY_LEN, message, MSG_LEN);
    memcpy(buffer + KEY_LEN + MSG_LEN, hmac, HMAC_LEN);

    // Connect to server
    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr);
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // Send
    send(sock, buffer, sizeof(buffer), 0);
    std::cout << "Message and HMAC sent to server.\n";

    close(sock);
    return 0;
}

