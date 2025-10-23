#include "lwip/init.h"
#include "lwip/tcpip.h"
#include "lwip/netif.h"
#include "netif/etharp.h"
#include "tcpecho_raw.h"
#include "netif/tapif.h"
#include "tcpecho_client.h"
#include <pthread.h>

struct netif serv_netif;
ip4_addr_t ipaddr, netmask, gw;

static void client_start_callback(void *arg)
{
	printf("Running client.\n");
	tcp_client_start();
}

void* run_client(void *arg)
{
	int id = (int)arg;
	sleep(2);
	printf("Running the client in tcpip thread.\n");
	printf("Client %d thread id is %ld\n", id, pthread_self());
	tcpip_callback(client_start_callback, NULL);

//	while(1) {
//		sys_check_timeouts();
//	}

}

void run_server(void *arg)
{

	printf("Running the server thread.\n");

	tcpecho_raw_init();

//	while(1) {
//		sys_check_timeouts();	}
//	}
}

static void lwip_netif_init(void *arg)
{
	IP4_ADDR(&ipaddr, 192, 168, 100, 2);
	IP4_ADDR(&netmask, 255, 255, 255, 0);
	IP4_ADDR(&gw, 192, 168, 100, 1);

	netif_add(&serv_netif, &ipaddr, &netmask, &gw, NULL, tapif_init, tcpip_input);
	netif_set_default(&serv_netif);
	netif_set_up(&serv_netif);
	printf("Netif init done.\n");
}

int main(void)
{

	tcpip_init(lwip_netif_init, NULL);
	printf("Tcpip init done.\n");

	pthread_t client_thread_1, client_thread_2;

	// Start the server thread.
//	pthread_create(&server_thread, NULL, run_server, NULL);
	printf("Before server.\n");
	tcpip_callback(run_server, NULL);
	printf("After server.\n");
	// Start the client thread.
	pthread_create(&client_thread_1, NULL, run_client, 1);
	pthread_create(&client_thread_2, NULL, run_client, 2);
//	pthread_join(client_thread, NULL);
//	pthread_join(server_thread, NULL);
	
	while(1) {
//		sys_check_timeouts();
		sys_msleep(1000);
	}

	return 0;
}
