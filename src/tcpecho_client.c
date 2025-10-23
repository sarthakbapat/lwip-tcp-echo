#include "lwip/tcp.h"
#include <stdio.h>
#include <string.h>
#include "tcpecho_client.h"


void tcp_client_start()
{
	ip_addr_t server_ip;
	err_t err;

	IP4_ADDR(&server_ip, 192, 168, 100, 2);

	client_pcb = tcp_new();
	if (client_pcb == NULL) {
		printf("Failed to create client pcb.\n");
	}
	
	err = tcp_connect(client_pcb, &server_ip, SERVER_PORT, client_connected);
	if (err != ERR_OK) {
		printf("Client tcp_connect failed.\n");
	} else {
		printf("Client connecting to server.\n");
	}

}

static err_t client_connected(void *arg, struct tcp_pcb *tpcb, err_t err)
{
	printf("Client connected to the server.\n");
	tcp_recv(tpcb, client_recv);
	tcp_sent(tpcb, client_sent);

	tcp_client_send(tpcb);
	return ERR_OK;
}

static err_t client_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	if (p == NULL) {
		printf("Client - Connection closed by the server.\n");
		tcp_close(tpcb);
		return ERR_OK;
	}

	printf("Client received echo: ");
	struct pbuf *tmp;
	for (tmp=p; tmp != NULL; tmp=tmp->next)
	{
		fwrite(tmp->payload, 1, tmp->len, stdout);
	}
	printf("\n");

	tcp_recved(tpcb, p->tot_len);
	pbuf_free(p);

	return ERR_OK;
}

static err_t client_sent(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
	printf("Data sent successfully.\n");
	return ERR_OK;
}

static void client_error(void *arg, err_t err)
{
	printf("Error: %d\n", err);
}

static void tcp_client_send(struct tcp_pcb *tpcb)
{
	err_t err;
	err = tcp_write(tpcb, test_msg, strlen(test_msg), TCP_WRITE_FLAG_COPY);
	if (err == ERR_OK) {
		tcp_output(tpcb);
	} else {
		printf("Client: tcp write failed, %d\n", err);
	}

}
