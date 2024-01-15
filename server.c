#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
	int s;
	struct sockaddr_in addr = {
		.sin_family = AF_INET,
	};
	struct sockaddr_in addr_c;
	socklen_t addr_len;
	char buf[4096];
	ssize_t rc;

	s = socket(AF_INET, SOCK_DGRAM, 0);


	addr.sin_port = htons(6000);
	if (bind(s, (struct sockaddr*) &addr, sizeof(addr))) {
		close(s);
		return 1;
	}

	while (1) {
		addr_len = sizeof(addr_c);
		rc = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)&addr_c, &addr_len);

		if (rc <= 0)
			break;

		if (sendto(s, buf, rc, 0, (struct sockaddr*)&addr_c, addr_len) < 0)
			printf("sendto err\n");
	}
		
	close(s);
	return 0;
}
