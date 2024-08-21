#include "trc_route.h"

_data	g_vars = {
	.sock = -1,
	.dest = NULL,
	.dest_ip = NULL,
	.src_ip = NULL,
	.d_ifr = 0,
	._ifr = DEF_IFR,
	.d_tim = -1
};

void	signal_handler(int sig_num) {
	if (sig_num) printf("quiting..\n");
	if (g_vars.sock > 0) close(g_vars.sock);
	if (g_vars.dest) freeaddrinfo(g_vars.dest);
	if (g_vars.d_ifr) free(g_vars._ifr);
	exit(sig_num);
}

void	print_usage() {
	printf("TRC_ROUTE\n");
	printf("- simple traceroute program to trace the route\n\tof a packet across the internet\n");
	printf("usage:\n");
	printf("./trc_route DESTINATION [-i=INTERFACE] [-t=TIMEOUT]\n");
	printf("DESTINATION: domain_name/ip_address of the target host\n");
	printf("-i: optional name of the interface to be used, default %s\n", DEF_IFR);
	printf("-t: optional number of seconds till network response, default 3\n");
	exit(1);
}

int	is_digit(char *str) {
	for (int i=0; str[i]; i++)
		if (str[i] < '0' || str[i] > '9')	return 0;
	return 1;
}

int	get_params(int c, char **v) {
	char		*p;
	for (int i=2; i < c && v[i]; i++) {
		if ((p = strchr(v[i], '='))) {
			if (!strncmp(v[i], "-i", 2) && strlen((p + 1)) > 0) {
				g_vars._ifr = strdup(++p);
				g_vars.d_ifr = 1;
			}
			else if (!strncmp(v[i], "-t", 2) && strlen((p + 1)) > 0
				&& is_digit((p + 1)))
				g_vars.d_tim = atoi(++p);
			else	return 0;
		}
		else if (i == c)	return 0;
	}
	return	1;
}

struct	addrinfo	*getAddr(char *host, char **dest) {
	struct	addrinfo		hints;
	struct	addrinfo		*res;
	int			_i;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_flags = AI_PASSIVE;
	_i = getaddrinfo(host, NULL, &hints, &res);
	if (_i != 0 || !res) {
		printf("host unreachable: (%s)\n", host);
		signal_handler(1);
	}
	*dest = inet_ntoa(((struct sockaddr_in*)res->ai_addr)->sin_addr);
	printf("TRC_route to %s (%s)\n", host, *dest);
	return	res;
}

int		main(int c, char **v) {

	if (c < 2 || c > 4
		|| (c > 2 && !get_params(c, v)))
		print_usage();

	struct	timeval	tv = {0};
	struct	ifreq	ifr_ip;
	int	_incd_ip_hdrs = 1,
		_ip_tos = IPTOS_LOWDELAY;

	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);

	g_vars.sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (g_vars.sock < 0) {
		perror("socket");
		signal_handler(1);
	}
	g_vars.dest = getAddr(v[1], &g_vars.dest_ip);
	tv.tv_sec = (g_vars.d_tim < 0) ? 3 : g_vars.d_tim;

	setsockopt(g_vars.sock, IPPROTO_IP, IP_TOS, &_ip_tos, sizeof(_ip_tos));
	setsockopt(g_vars.sock, IPPROTO_IP, IP_HDRINCL, &_incd_ip_hdrs, sizeof(_incd_ip_hdrs));
	strncpy(ifr_ip.ifr_name, g_vars._ifr, strlen(g_vars._ifr));
	if (ioctl(g_vars.sock, SIOCGIFADDR, &ifr_ip) != 0) {
		perror("ioctl");
		signal_handler(1);
	}
	g_vars.src_ip = inet_ntoa(((struct sockaddr_in*)&ifr_ip.ifr_addr)->sin_addr);
	printf(" ,  from %s (%s)\n", g_vars._ifr, g_vars.src_ip);
	_trc_route(&tv);
	signal_handler(0);
}

