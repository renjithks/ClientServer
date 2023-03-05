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

Yes, you can connect a USB hardware device to a virtual machine running Ubuntu in VirtualBox and control it from within the virtual environment.

Here are the steps to connect a USB device to a virtual machine in VirtualBox:

Make sure that the VirtualBox Extension Pack is installed. This can be downloaded from the VirtualBox website.

Connect the USB device to your host computer.

In VirtualBox, select the virtual machine that you want to connect the USB device to, and click on the Settings button.

In the Settings window, click on the USB tab.

Check the "Enable USB Controller" box, and select the type of USB controller that you want to use (e.g. USB 1.1, USB 2.0, or USB 3.0).

Click on the "Add" button to add a new USB filter.

In the USB Device Filters window, click on the "Add New" button.

Select the USB device that you want to connect to the virtual machine from the list of available devices, and click on "OK".

Click "OK" to close the USB Settings window.

Start the virtual machine. The USB device should now be available to the virtual machine.

Once the USB device is connected to the virtual machine, you can control it from within the virtual environment just as you would with a physical Ubuntu machine.
