# Algoritmos_HMAC
Little example for HMAC communication between two dockers containers, for learning purposes

---
## 📦 Project Structure
project/\n
├── Dockerfile # Builds both client and server
├── docker-compose.yml # Defines containers and networking
├── client.cpp # Sends message + HMAC to server
└── server.cpp # Verifies the received HMAC


## 🚀 How to Run

### 1. Clone the Repository

If you haven’t already:

```bash
git clone https://github.com/Rengyx/Algoritmos_HMAC.git
cd project/
```
```bash
docker-compose up --build
```
