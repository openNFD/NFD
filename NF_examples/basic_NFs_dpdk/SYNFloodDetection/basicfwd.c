/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2010-2015 Intel Corporation
 */
#include <map>
#include <stdint.h>
#include <inttypes.h>
#include <rte_eal.h>
#include <rte_ethdev.h>
#include <rte_cycles.h>
#include <rte_lcore.h>
#include <rte_mbuf.h>

#include "basic_classes.h"
#include <stdio.h>
#include <iostream>
#include <signal.h>

#define RX_RING_SIZE 4096 
#define TX_RING_SIZE 4096 

#define NUM_MBUFS 8191
#define MBUF_CACHE_SIZE 250
#define BURST_SIZE 32

#define FUNCTION SYNFD 

using namespace std;
/*
static const struct rte_eth_conf port_conf_default = {
	.rxmode = {
		.max_rx_pkt_len = ETHER_MAX_LEN,
		.ignore_offload_bitfield = 1,
	},
};
*/
clock_t begin_t;
clock_t end_t;
int _counter = 0;
unordered_map<string,int> F_Type::MAP = unordered_map<string,int>();
unordered_map<string,int> F_Type::MAP2 = unordered_map<string,int>();
int process(Flow &f);
Flow f_glb;

static struct rte_eth_conf port_conf_default;
/* basicfwd.c: Basic DPDK skeleton forwarding example. */

/*
 * Initializes a given port using global settings and with the RX buffers
 * coming from the mbuf_pool passed as a parameter.
 */
static inline int
port_init(uint16_t port, struct rte_mempool *mbuf_pool)
{
	struct rte_eth_conf port_conf = port_conf_default;
	const uint16_t rx_rings = 1, tx_rings = 1;
	uint16_t nb_rxd = RX_RING_SIZE;
	uint16_t nb_txd = TX_RING_SIZE;
	int retval;
	uint16_t q;
	struct rte_eth_dev_info dev_info;
	struct rte_eth_txconf txconf;

	if (!rte_eth_dev_is_valid_port(port))
		return -1;

	rte_eth_dev_info_get(port, &dev_info);
	if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_MBUF_FAST_FREE)
		port_conf.txmode.offloads |=
			DEV_TX_OFFLOAD_MBUF_FAST_FREE;

	/* Configure the Ethernet device. */
	retval = rte_eth_dev_configure(port, rx_rings, tx_rings, &port_conf);
	if (retval != 0)
		return retval;

	retval = rte_eth_dev_adjust_nb_rx_tx_desc(port, &nb_rxd, &nb_txd);
	if (retval != 0)
		return retval;

	/* Allocate and set up 1 RX queue per Ethernet port. */
	for (q = 0; q < rx_rings; q++) {
		retval = rte_eth_rx_queue_setup(port, q, nb_rxd,
				rte_eth_dev_socket_id(port), NULL, mbuf_pool);
		if (retval < 0)
			return retval;
	}

	txconf = dev_info.default_txconf;
	txconf.txq_flags = ETH_TXQ_FLAGS_IGNORE;
	txconf.offloads = port_conf.txmode.offloads;
	/* Allocate and set up 1 TX queue per Ethernet port. */
	for (q = 0; q < tx_rings; q++) {
		retval = rte_eth_tx_queue_setup(port, q, nb_txd,
				rte_eth_dev_socket_id(port), &txconf);
		if (retval < 0)
			return retval;
	}

	/* Start the Ethernet port. */
	retval = rte_eth_dev_start(port);
	if (retval < 0)
		return retval;

	/* Display the port MAC address. */
	struct ether_addr addr;
	rte_eth_macaddr_get(port, &addr);
	printf("Port %u MAC: %02" PRIx8 " %02" PRIx8 " %02" PRIx8
			   " %02" PRIx8 " %02" PRIx8 " %02" PRIx8 "\n",
			port,
			addr.addr_bytes[0], addr.addr_bytes[1],
			addr.addr_bytes[2], addr.addr_bytes[3],
			addr.addr_bytes[4], addr.addr_bytes[5]);

	/* Enable RX in promiscuous mode for the Ethernet device. */
	rte_eth_promiscuous_enable(port);

	return 0;
}

/* !!!!!!!!!!!!!!!!!!!!!!!!!!*/
/* INSERTION STARTS FROM HERE*/
void _init_(){
    (new F_Type())->init();
}
int _t1=100;
int _t2=1;
int _t3=1;
int _t4=1;
int _t5=1;
int _t6=1;
int _t7=1;
int _t8=1;
int _t9=1;
int _t10=1;
int _t11=1;
int _t12=1;
int _t13=1;
int _t14=1;
State<unordered_map<IP,int>> blist(*(new unordered_map<IP,int>()));
State<int> threshold(_t1);
int process(Flow &f){

if ((*(int*) f.headers[Flag_syn]) == _t2 && (*(int*) f.headers[Tag]) != _t3){
blist[f][(*(IP*) f.headers[Sip])]=blist[f][(*(IP*) f.headers[Sip])] + _t4;
(*(int*) f.headers[Tag])=_t5;
}
else if (((*(int*) f.headers[Tag]) == _t6)&&(blist[f][(*(IP*) f.headers[Sip])] == threshold[f])){
return -1;
}
else if (((*(int*) f.headers[Tag]) == _t7)&&(blist[f][(*(IP*) f.headers[Sip])] != threshold[f])){
}
else if ((*(int*) f.headers[Tag]) != _t8 && (*(int*) f.headers[Flag_syn]) != _t9 && (*(int*) f.headers[Flag_ack]) == _t10){
blist[f][(*(IP*) f.headers[Sip])]=blist[f][(*(IP*) f.headers[Sip])] - _t11;
}
else if ((*(int*) f.headers[Tag]) != _t12 && (*(int*) f.headers[Flag_syn]) != _t13 && (*(int*) f.headers[Flag_ack]) != _t14){
}
        f.clean();
        return 0;
}
int SYNFD(u_char * pkt,int totallength) {
    f_glb= Flow(pkt,totallength);
    return process(f_glb);
}
/*
 * The lcore main. This is the main thread that does the work, reading from
 * an input port and writing to an output port.
 */
static __attribute__((noreturn)) void
lcore_main(void)
{
	uint16_t port;
	char* packet;
	int counter = 0;

	/*
	 * Check that the port is on the same NUMA node as the polling thread
	 * for best performance.
	 */
	RTE_ETH_FOREACH_DEV(port)
		if (rte_eth_dev_socket_id(port) > 0 &&
				rte_eth_dev_socket_id(port) !=
						(int)rte_socket_id())
			printf("WARNING, port %u is on remote NUMA node to "
					"polling thread.\n\tPerformance will "
					"not be optimal.\n", port);

	printf("\nCore %u forwarding packets. [Ctrl+C to quit]\n",
			rte_lcore_id());

	/* Run until the application is quit or killed. */
	for (;;) {
		/*
		 * Receive packets on a port and forward them on the paired
		 * port. The mapping is 0 -> 1, 1 -> 0, 2 -> 3, 3 -> 2, etc.
		 */
		RTE_ETH_FOREACH_DEV(port) {
			
			/* Get burst of RX packets, from first port of pair. */
			struct rte_mbuf *bufs[BURST_SIZE];
			const uint16_t nb_rx = rte_eth_rx_burst(port, 0,
					bufs, BURST_SIZE);

			if (unlikely(nb_rx == 0))
				continue;
                        if (port == 0)
                        {
                                // processing packets
				_counter += nb_rx;
                                for (int index=0; index<nb_rx; index++)
                                {
                                        struct rte_mbuf * buf = bufs[index];
                                        u_char * pkt = (u_char *)buf->buf_addr;
                                        int length = (int)buf->pkt_len;
                                        FUNCTION(pkt, length);

                                }
                        }

			//printf("counter = %d  port = %d\n",counter,port);
			//counter++;
			/*
			if (nb_rx > 0)
			{
				counter++;
				printf("counter = %d nb_rx = %d\n",counter,nb_rx);
				printf("data len: %d\n",rte_pktmbuf_data_len(bufs[0]));
				printf("pkt  len: %d\n",rte_pktmbuf_pkt_len(bufs[0]));
				//packet = (char*)(bufs[0]->buf_addr);
				//packet[0] = '0';
				//printf("%d %d %d\n",packet[12],packet[13],packet[14]);
			}
			*/
			/* Send burst of TX packets, to second port of pair. */
			const uint16_t nb_tx = rte_eth_tx_burst(port ^ 1, 0,
					bufs, nb_rx);

			/* Free any unsent packets. */
			if (unlikely(nb_tx < nb_rx)) {
				uint16_t buf;
				for (buf = nb_tx; buf < nb_rx; buf++)
					rte_pktmbuf_free(bufs[buf]);
			}
		}
	}
}

void stop(int signo)
{
    end_t = clock();
    double total;
    total = (double)(end_t - begin_t)/CLOCKS_PER_SEC;
    printf("\n\n**************************************************\n");
    printf("%ld are forwarded ! Average Tput is %f \n",_counter, _counter / total);
    printf("counter = %ld  begin = %ld  end = %ld \n", _counter, begin_t ,end_t);
    printf("**************************************************\n\n");
    exit(0);
}

/*
 * The main function, which does initialization and calls the per-lcore
 * functions.
 */
int
main(int argc, char *argv[])
{
    	_init_();
	


	struct rte_mempool *mbuf_pool;
	unsigned nb_ports;
	uint16_t portid;
	
	port_conf_default.rxmode.max_rx_pkt_len = ETHER_MAX_LEN;
	port_conf_default.rxmode.ignore_offload_bitfield = 1;

	/* Initialize the Environment Abstraction Layer (EAL). */
	int ret = rte_eal_init(argc, argv);
	if (ret < 0)
		rte_exit(EXIT_FAILURE, "Error with EAL initialization\n");

	argc -= ret;
	argv += ret;

	/* Check that there is an even number of ports to send/receive on. */
	nb_ports = rte_eth_dev_count();
	if (nb_ports < 2 || (nb_ports & 1))
		rte_exit(EXIT_FAILURE, "Error: number of ports must be even\n");

	/* Creates a new mempool in memory to hold the mbufs. */
	mbuf_pool = rte_pktmbuf_pool_create("MBUF_POOL", NUM_MBUFS * nb_ports,
		MBUF_CACHE_SIZE, 0, RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id());

	if (mbuf_pool == NULL)
		rte_exit(EXIT_FAILURE, "Cannot create mbuf pool\n");

	/* Initialize all ports. */
	RTE_ETH_FOREACH_DEV(portid)
		if (port_init(portid, mbuf_pool) != 0)
			rte_exit(EXIT_FAILURE, "Cannot init port %"PRIu16 "\n",
					portid);

	if (rte_lcore_count() > 1)
		printf("\nWARNING: Too many lcores enabled. Only 1 used.\n");

	/* Call lcore_main on the master core only. */
	signal(SIGINT, stop);
	begin_t = clock();
	lcore_main();

	return 0;
}
