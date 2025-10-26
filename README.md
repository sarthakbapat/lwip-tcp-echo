## lwIP Raw TCP Echo (Server + Client) on Linux (NO_SYS = 0)

This project demonstrates a lightweight TCP client–server communication setup using the lwIP stack (Lightweight IP) in NO_SYS = 0 mode on Linux.
The tcpecho_raw server is used from the official Lwip stack and client is added to connect to it over a virtual tap0 interface.
It uses the UNIX tapif interface to emulate Ethernet communication and showcases how lwIP handles sockets, pbufs, and PCBs through its raw API and callback mechanism.
Created as part of my exploration into embedded networking and TCP/IP stack internals, with a focus on the lwIP raw API and callback-based communication model.

### Features

1. Tcp client using Lwip callbacks.
2. Communication with server over a virtual tap0 interface.
3. Multi-client testing with pthread on Linux.
4. Lwip networking stack instead of Linux network stack.

### Architecture

        +------------------------+
        |  Application Layer     |  Server/Client Logic
        +------------------------+
        |  LwIP Raw TCP API      |
        | (tcp_input, tcp_output)|
        +------------------------+
        |  IP Layer (IPv4)       |
        +------------------------+
        |  Ethernet Layer        |
        |  tapif_input / output  |
        +------------------------+
        |  TAP Interface (tap0)  |
        +------------------------+

### Network Setup (Linux)

```bash
sudo ip tuntap add dev tap0 mode tap user $USER
sudo ip addr add 192.168.100.1/24 dev tap0
sudo ip link set tap0 up 
```

### Usage

1. Clone the official LwIP stack source in linux from: https://github.com/lwip-tcpip/lwip.git
2. For convenience, add all the source and header files from this repo to contrib/apps/tcpecho_raw in LwIP repo.
3. Modify the CMakeLists.txt (needed) as per your repo path.
4. Create tap0 virtual interface.
5. Build with CMake and test.

#### Credits
This project builds on the lwIP TCP/IP stack (BSD 3-Clause Licensed).
© Copyright The lwIP Contributors.
