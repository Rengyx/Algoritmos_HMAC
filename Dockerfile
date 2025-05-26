# Dockerfile
FROM ubuntu:20.04

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    g++ \
    libssl-dev \
    openssl \
    netcat \
    && apt-get clean

COPY . /app
WORKDIR /app

# Build both client and server
RUN g++ server.cpp -o server -lssl -lcrypto
RUN g++ client.cpp -o client -lssl -lcrypto

CMD ["bash"]

