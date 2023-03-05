If both the server and the client are running on the same PC, you can use the loopback IP address 127.0.0.1 or the special hostname localhost to connect to the server. Here is an example of how to modify the constructor of the TCPClient class to use the loopback IP address:

c++
Copy code
TCPClient::TCPClient(int server_port) :
    m_server_ip("127.0.0.1"), m_server_port(server_port) {}
And here is an example of how to modify the constructor of the TCPServer class to use the loopback IP address:

c++
Copy code
TCPServer::TCPServer(int port_num, std::string config_file) :
    m_port_num(port_num), m_config_file(config_file), m_running(false) {
    m_server_ip = "127.0.0.1";
}
In both cases, we set the IP address to 127.0.0.1, which is the loopback IP address that refers to the same machine that the code is running on.
