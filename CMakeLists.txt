cmake_minimum_required(VERSION 3.10)
project(lwip_tcpecho_raw)

# Path to your lwip root
set(LWIP_ROOT "~/tcpip/lwip")
set(CONTRIB_ROOT "~/tcpip/lwip/contrib")

# Include lwip core + include directories
include_directories(
    ${LWIP_ROOT}/src/include
    ${LWIP_ROOT}/contrib/ports/unix/include
    ${LWIP_PORT}/contrib/ports/unix
    ${LWIP_ROOT}/contrib/ports/unix/port/include
    ${LWIP_ROOT}/contrib/examples/example_app
    ${LWIP_PORT}/contrib/ports/unix/lib
    ${CONTRIB_ROOT}/apps/tcpecho_raw
)

# Sources : core+contrib+example
file(GLOB LWIP_CORE_SRCS
    ${LWIP_ROOT}/src/core/*.c
    ${LWIP_PORT}/src/core/ipv4/*.c
    ${LWIP_PORT}/src/core/ipv6/*.c
    ${LWIP_ROOT}/src/netif/*.c
    ${LWIP_ROOT}/src/api/*.c
)

set(LWIP_CORE_SRCS
    ${LWIP_ROOT}/src/core/init.c
    ${LWIP_ROOT}/src/core/def.c
    ${LWIP_ROOT}/src/core/dns.c
    ${LWIP_ROOT}/src/core/inet_chksum.c
    ${LWIP_ROOT}/src/core/ip.c
    ${LWIP_ROOT}/src/core/mem.c
    ${LWIP_ROOT}/src/core/memp.c
    ${LWIP_ROOT}/src/core/netif.c
    ${LWIP_ROOT}/src/core/pbuf.c
    ${LWIP_ROOT}/src/core/raw.c
    ${LWIP_ROOT}/src/core/stats.c
    ${LWIP_ROOT}/src/core/sys.c
    ${LWIP_ROOT}/src/core/tcp.c
    ${LWIP_ROOT}/src/core/tcp_in.c
    ${LWIP_ROOT}/src/core/tcp_out.c
    ${LWIP_ROOT}/src/core/timeouts.c
    ${LWIP_ROOT}/src/core/udp.c
    ${LWIP_ROOT}/src/core/ipv4/igmp.c
    ${LWIP_ROOT}/src/core/ipv4/autoip.c
    ${LWIP_ROOT}/src/core/ipv4/dhcp.c
    ${LWIP_ROOT}/src/core/ipv4/etharp.c
    ${LWIP_ROOT}/src/core/ipv4/icmp.c
    ${LWIP_ROOT}/src/core/ipv4/ip4.c
    ${LWIP_ROOT}/src/core/ipv4/ip4_addr.c
    ${LWIP_ROOT}/src/core/ipv4/ip4_frag.c
)

set(LWIP_API_SRCS
    ${LWIP_ROOT}/src/api/api_lib.c
    ${LWIP_ROOT}/src/api/api_msg.c
    ${LWIP_ROOT}/src/api/err.c
    ${LWIP_ROOT}/src/api/netbuf.c
    ${LWIP_ROOT}/src/api/netdb.c
    ${LWIP_ROOT}/src/api/netifapi.c
    ${LWIP_ROOT}/src/api/sockets.c
    ${LWIP_ROOT}/src/api/tcpip.c
)

set(LWIP_NETIF_SRCS
    ${LWIP_ROOT}/src/netif/ethernet.c
)

set(EXAMPLE_SRCS
    ${CONTRIB_ROOT}/apps/tcpecho_raw/tcpecho_raw.c
    ${CONTRIB_ROOT}/apps/tcpecho_raw/main.c
    ${CONTRIB_ROOT}/apps/tcpecho_raw/tcpecho_client.c
    ${CONTRIB_ROOT}/ports/unix/port/netif/tapif.c
)

set(PORT_SRCS
    ${LWIP_ROOT}/contrib/ports/unix/port/sys_arch.c
)

add_executable(tcpecho_raw ${LWIP_CORE_SRCS} ${LWIP_API_SRCS} ${LWIP_NETIF_SRCS} ${EXAMPLE_SRCS} ${PORT_SRCS} )

target_link_libraries(tcpecho_raw pthread rt)

