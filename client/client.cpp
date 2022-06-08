#include "client.hpp"
#include "utils.hpp"

Client::Client() {
    id = socket(AF_INET, SOCK_STREAM, 0);
}

int Client::s_connect(int serverPort) {
    struct sockaddr_in remote = {0};

    remote.sin_addr.s_addr = inet_addr(LOCAL_HOST);
    remote.sin_family = AF_INET;
    remote.sin_port = htons(serverPort);

    return connect(id, (struct sockaddr *)& remote, sizeof(struct sockaddr_in)) != 0;
}

int Client::s_send(std::string msg) {
    return send(id, msg.c_str(), msg.length(), 0);
}

int Client::s_recv(std::string *rsp) {
    std::vector<char> writable(MAX_SIZE);

    int bytesRead = recv(id, writable.data(), MAX_SIZE, 0);
    *rsp = std::string(writable.cbegin(), writable.cbegin() + bytesRead);
    return bytesRead;
}
