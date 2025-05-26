
# 🔐 HMAC Signature Exchange via C++ and Docker

This project demonstrates how to securely send a message with an HMAC signature from a **client** container to a **server** container using **C++**, **OpenSSL**, and **Docker Compose**.

---

## 📦 Project Structure

```
project/
├── Dockerfile            # Builds both client and server
├── docker-compose.yml    # Defines containers and networking
├── client.cpp            # Sends message + HMAC to server
└── server.cpp            # Verifies the received HMAC
```

---

## 🚀 How to Run

### 1. Clone the Repository

If you haven’t already:

```bash
git clone https://your-repo-url
cd project/
```

> Or simply place the provided files in a `project/` folder.

---

### 2. Build and Run with Docker Compose

```bash
docker-compose up --build
```

This will:

- Build a common Docker image for both client and server
- Start the `hmac-server` container (server)
- Start the `hmac-client` container after a short delay (client)
- The client will:
  - Generate a random 256-bit HMAC key
  - Send a message and its HMAC signature
- The server will:
  - Extract and verify the signature
  - Print the result

---

## ✅ Example Output

### Client

```
Message and HMAC sent to server.
```

### Server

```
Server waiting for connection...
Received message: This is a secret message from client.
HMAC is valid ✅
```

---

## 🛠 Requirements

- Docker
- Docker Compose

---

## 📌 Notes

- Uses **OpenSSL** for HMAC generation (SHA256).
- Containers communicate via a custom Docker network.
- Message is fixed to 128 bytes; HMAC and key to 32 bytes each.
- This is a demo — in real systems, use secure key exchange and encryption (e.g., TLS).

---

## 📤 Want to Extend It?

- ✅ Add HMAC verification on the client
- 📁 Use mounted volumes to share keys or messages
- 🔄 Enable two-way messaging
- 📡 Secure with TLS using `SSL_*` OpenSSL API

