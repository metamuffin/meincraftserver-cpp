#include "socket_setup.h"

#include <sys/socket.h>
#include <arpa/inet.h>

int create_listen_socket(int port) {
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1) {
		return -1;
	}

	struct sockaddr_in addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	int ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
	if (ret == -1) {
		goto cleanup_err;
	}

	ret = listen(fd, 100);
	if (ret == -1) {
		goto cleanup_err;
	}

	return fd;

cleanup_err:
	return -1;
}

