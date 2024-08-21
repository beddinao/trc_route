#include "trc_route.h"

unsigned		short	csum(unsigned short *buf, int nwords)
{
	unsigned	long		sum;
	for(sum=0; nwords>0; nwords--)
		sum += *buf++;
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	return (unsigned short)(~sum);
}

void			_trc_route(struct timeval *tv) {

	char			packet[PK_SIZE];
	struct		iphdr	ip_hdr_in;
	struct		icmphdr	icmp_hdr_in;
	struct		sockaddr_in	addr;
	socklen_t			a_si = sizeof(addr);
	size_t			iphdr_size = sizeof(struct iphdr);
	size_t			icmphdr_size = sizeof(struct icmphdr);
	struct		timeval	st = {0}, en = {0};
	fd_set			r_set;
	int			ttl = 1, _i, _j=0;

	int32_t s_addr = inet_addr(g_vars.src_ip);
	int32_t d_addr = inet_addr(inet_ntoa(((struct sockaddr_in*)g_vars.dest->ai_addr)->sin_addr));
	uint16_t h_pid = htons(getpid());

	for (;;) {
		if (!_j) printf("%2i", ttl);
		memset(packet, 0, sizeof(packet));
		struct		iphdr	*ip_hdr = (struct iphdr*) packet;
		ip_hdr->version = 4;
		ip_hdr->id = h_pid;
		ip_hdr->ttl = ttl;
		ip_hdr->protocol = IPPROTO_ICMP;
		ip_hdr->saddr = s_addr;
		ip_hdr->daddr = d_addr;

		struct		icmphdr	*icmp_hdr = (struct icmphdr *)(packet + iphdr_size);
		icmp_hdr->type = ICMP_ECHO;
		icmp_hdr->un.echo.id = h_pid;
		icmp_hdr->checksum = 0;
		icmp_hdr->checksum = csum((unsigned short*)(packet + iphdr_size), icmphdr_size/2);

		ip_hdr->ihl = iphdr_size/4;
		ip_hdr->tot_len = iphdr_size + icmphdr_size;
		ip_hdr->check = 0;
		ip_hdr->check = csum((unsigned short*)packet, iphdr_size/2);
		gettimeofday(&st, NULL);
		_i = sendto(g_vars.sock, packet, iphdr_size + icmphdr_size, 0, g_vars.dest->ai_addr, a_si);
		if (_i < 0) { perror("sendto"); break; }

		FD_ZERO(&r_set);
		FD_SET(g_vars.sock, &r_set);
		_i = select(g_vars.sock + 1, &r_set, NULL, NULL, tv);
		if (_i < 0) { perror("select"); break; }
		else if (!_i) {
			if (_j > 4) {
				printf("\n");
				ttl++; _j = 0; continue ;
			}
			printf("  #");
			sleep(1); _j++;
			continue ;
		}
		gettimeofday(&en, NULL);

		memset(packet, 0, sizeof(packet));
		_i = recvfrom(g_vars.sock, packet, PK_SIZE, 0, (struct sockaddr*)&addr, &a_si);
		if (_i < 0) { perror("recvfrom"); break ; }
		memset(&icmp_hdr_in, 0, icmphdr_size);
		memcpy(&icmp_hdr_in, packet + iphdr_size, icmphdr_size);

		memset(packet, 0, sizeof(packet));
		printf("  %s", inet_ntoa(addr.sin_addr));
		if (!getnameinfo((struct sockaddr*)&addr, a_si, packet, sizeof(packet), NULL, 0, 0)) printf(" [%s]", packet);
		printf(" %.3f ms\n", ((double)(en.tv_sec-st.tv_sec)*1000) + ((double)(en.tv_usec-st.tv_usec)/1000));
		if (icmp_hdr_in.type == ICMP_ECHOREPLY) break;
		ttl++;
		_j = 0;
	}
}
