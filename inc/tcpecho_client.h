#include "lwip/tcp.h"
#include <stdio.h>
#include <string.h>

#define SERVER_IP 192.168.100.2
#define SERVER_PORT 7

static struct tcp_pcb *client_pcb = NULL;
static const char test_msg[] = "Hello from client LWIP\n";

static err_t client_connected(void *arg, struct tcp_pcb *tpcb, err_t err);
static err_t client_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static err_t client_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
static void client_error(void *arg, err_t err);
static void tcp_client_send(struct tcp_pcb *tpcb);

