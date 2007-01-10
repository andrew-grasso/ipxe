#ifndef _GPXE_IP_H
#define _GPXE_IP_H

/** @file
 *
 * IP protocol
 *
 */

#include <ip.h>
#include <gpxe/retry.h>
#include <gpxe/hotplug.h>

/* IP constants */

#define IP_VER		0x40
#define IP_MASK_VER	0xf0
#define IP_MASK_HLEN 	0x0f
#define IP_MASK_OFFSET	0x1fff
#define IP_MASK_DONOTFRAG	0x4000
#define IP_MASK_MOREFRAGS	0x2000
#define IP_PSHLEN 	12

/* IP header defaults */
#define IP_TOS		0
#define IP_TTL		64

#define IP_FRAG_PKB_SIZE	1500
#define IP_FRAG_TIMEOUT		50

/* IP4 pseudo header */
struct ipv4_pseudo_header {
	struct in_addr src;
	struct in_addr dest;
	uint8_t zero_padding;
	uint8_t protocol;
	uint16_t len;
};

/** An IPv4 address/routing table entry */
struct ipv4_miniroute {
	/** List of miniroutes */
	struct list_head list;

	/** Network device */
	struct net_device *netdev;
	/** Reference to network device */
	struct reference netdev_ref;

	/** IPv4 address */
	struct in_addr address;
	/** Subnet mask */
	struct in_addr netmask;
	/** Gateway address */
	struct in_addr gateway;
};

/* Fragment reassembly buffer */
struct frag_buffer {
	/* Identification number */
	uint16_t ident;
	/* Source network address */
	struct in_addr src;
	/* Destination network address */
	struct in_addr dest;
	/* Reassembled packet buffer */
	struct pk_buff *frag_pkb;
	/* Reassembly timer */
	struct retry_timer frag_timer;
	/* List of fragment reassembly buffers */
	struct list_head list;
};

struct pk_buff;
struct net_device;
struct net_protocol;
struct tcpip_protocol;

extern struct list_head ipv4_miniroutes;

extern struct net_protocol ipv4_protocol;

extern int add_ipv4_address ( struct net_device *netdev,
			      struct in_addr address, struct in_addr netmask,
			      struct in_addr gateway );
extern void del_ipv4_address ( struct net_device *netdev );

#endif /* _GPXE_IP_H */
