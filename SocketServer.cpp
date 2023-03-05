#include <iostream>
#include <fstream>
#include <thread>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>

class TCPServer {
public:
    TCPServer() {}
    ~TCPServer() {}

    bool init() {
        // Read the port number from the INI file
        std::ifstream inifile("config.ini");
        std::string line;
        while (std::getline(inifile, line)) {
            if (line.find("port") != std::string::npos) {
                m_port = std::stoi(line.substr(line.find("=") + 1));
                break;
            }
        }

        // Create a socket
        m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (m_sockfd < 0) {
            std::cerr << "Error creating socket" << std::endl;
            return false;
        }

        // Bind the socket to the port
        struct sockaddr_in serv_addr;
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(m_port);
        if (bind(m_sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            std::cerr << "Error binding socket to port " << m_port << std::endl;
            return false;
        }

        return true;
    }

    void start() {
        std::thread accept_thread([this](){
            while (true) {
                // Listen for connections
                if (listen(m_sockfd, 5) < 0) {
                    std::cerr << "Error listening on socket" << std::endl;
                    break;
                }

                // Accept a connection
                struct sockaddr_in cli_addr;
                socklen_t cli_len = sizeof(cli_addr);
                int newsockfd = accept(m_sockfd, (struct sockaddr *)&cli_addr, &cli_len);
                if (newsockfd < 0) {
                    std::cerr << "Error accepting connection" << std::endl;
                    break;
                }

                // Handle the connection
                handleConnection(newsockfd);
            }
        });
        accept_thread.detach();
    }

private:
    int m_sockfd;
    int m_port;
    std::ofstream m_logfile;

    void handleConnection(int sockfd) {
        // Print client info
        struct sockaddr_in cli_addr;
        socklen_t cli_len = sizeof(cli_addr);
        getpeername(sockfd, (struct sockaddr *)&cli_addr, &cli_len);
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &cli_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
        std::cout << "Client connected from " << client_ip << std::endl;

        // Receive data from the client
        char buffer[1024];
        while (true) {
            int bytes_read = recv(sockfd, buffer, sizeof(buffer), 0);
            if (bytes_read <= 0) {
                // Connection lost
                std::cout << "Connection lost from " << client_ip << std::endl;
                break;
            }

            // Write the data to the log file
            m_logfile.open("server.log", std::ios::app);
            m_logfile << "Data received from " << client_ip << ": " << buffer << std::endl;
            m_logfile.close();

            // Print the data to the console
            std::cout << "Data received from " << client_ip << ": " << buffer << std::endl;
        }

        // Clean up the socket
        close(sockfd);
    }
};

int main() {
    // Initialize and start the server
    TCPServer server;
    if (!server.init()) {
        std::cerr << "Error initializing server" << std::endl;
        return 1;
    }
    server.start();

    // Wait for the server to finish
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}


