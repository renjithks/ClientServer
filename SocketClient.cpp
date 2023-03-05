#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

class TCPClient {
public:
    TCPClient(std::string server_ip, int server_port) :
        m_server_ip(server_ip), m_server_port(server_port) {}
    ~TCPClient() {}

    bool connect() {
        // Create a socket
        m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (m_sockfd < 0) {
            std::cerr << "Error creating socket" << std::endl;
            return false;
        }

        // Resolve the server address
        struct hostent *server = gethostbyname(m_server_ip.c_str());
        if (server == NULL) {
            std::cerr << "Error resolving server address" << std::endl;
            return false;
        }

        // Connect to the server
        struct sockaddr_in serv_addr;
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(m_server_port);
        memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
        if (::connect(m_sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            std::cerr << "Error connecting to server" << std::endl;
            return false;
        }

        return true;
    }

    void send(const std::string& message) {
        ::send(m_sockfd, message.c_str(), message.length(), 0);
    }

    void close() {
        ::close(m_sockfd);
    }

private:
    int m_sockfd;
    std::string m_server_ip;
    int m_server_port;
};

