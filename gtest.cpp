#include <gtest/gtest.h>
#include "tcp_server.h"

TEST(TCPServerTest, TestServer) {
    TCPServer server(12345, "config.ini");

    // Start the server in a separate thread
    std::thread server_thread([&server]() {
        server.start();
    });

    // Wait for the server to start
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Create a TCP client and connect to the server
    TCPClient client("127.0.0.1", 12345);
    ASSERT_TRUE(client.connect());

    // Send a message to the server
    std::string message = "Hello, server!";
    client.send(message);

    // Wait for the server to receive the message
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Check if the message is received by the server
    std::string received_message = server.get_last_message();
    ASSERT_EQ(message, received_message);

    // Stop the server
    server.stop();

    // Wait for the server thread to exit
    server_thread.join();
}

/******
This test code creates a TCPServer instance and starts it in a separate thread. It then creates a TCPClient instance and connects to the server. It sends a message to the server and waits for the server to receive the message. It then checks if the message is received by the server by calling the get_last_message method of the TCPServer instance. Finally, it stops the server and waits for the server thread to exit.

To run this test code, you need to link it with the gtest and pthread libraries. Here is an example command to compile and run the test code:

bash
Copy code
g++ -std=c++11 -I/path/to/gtest/include -L/path/to/gtest/lib -pthread tcp_server_test.cpp tcp_server.cpp -lgtest -lgtest_main -o tcp_server_test
./tcp_server_test
Replace /path/to/gtest with the actual path to the Google Test library on your system.
***/
