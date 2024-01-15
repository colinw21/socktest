#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/time.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
	int s;
	struct sockaddr_in addr = {
		.sin_family = AF_INET,
	};
	char buf[4096];
	ssize_t rc;
	int i, count = 10000;
	struct timeval t1, t2, t;

	if (argc < 2) {
		printf("Input address\n");
		return 1;
	}

	if (!inet_aton(argv[1], &addr.sin_addr)) {
		printf("Invalid address\n");
		return 1;
	}
	addr.sin_port = htons(6000);

	s = socket(AF_INET, SOCK_DGRAM, 0);

	if (connect(s, (struct sockaddr*) &addr, sizeof(addr))) {
		close(s);
		return 1;
	}

	gettimeofday(&t1, NULL);

	for (i = 0; i< count;i++) {
		rc = write(s, buf, 1400);
		if (rc < 1400)
			printf("write err: %zd\n", rc);
		rc = read(s, buf, sizeof(buf));
		if (rc < 1400)
			printf("read err: %zd\n", rc);
	}
	gettimeofday(&t2, NULL);
	timersub(&t2, &t1, &t);

	printf("done:%d, time:%ld.%ld\n", i, t.tv_sec, t.tv_usec);
		
	close(s);
	return 0;
}
