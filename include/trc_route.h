#ifndef TRC_ROUTE_H
# define TRC_ROUTE_H

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <sys/ioctl.h>
#include <net/if.h>

# define DEF_IFR "enp0s3"
# define PK_SIZE 4000

typedef	struct {
	int		sock;
	struct	addrinfo	*dest;
	char		*dest_ip;
	char		*src_ip;
	int		d_ifr;
	char		*_ifr;
	int		d_tim;
}	_data;

extern	_data	g_vars;

void		_trc_route(struct timeval*);

#endif
