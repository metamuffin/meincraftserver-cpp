#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#include "socket_setup.hpp"

#define MAX_EVENTS 200

int epoll_register_fd(int epollfd, int events, int fd) {
	struct epoll_event ev;

	ev.events = EPOLLIN;
	ev.data.fd = listenfd;

	return epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

int main() {
	int ret = 0;
	int listenfd;
	int first_fd, * other_fds = NULL, num_other_fds = 0;
	int epollfd;

	epollfd = epoll_create1(EPOLL_CLOEXEC);
	if (epollfd == -1) {
		return 1;
	}

	listenfd = create_listen_socket(3001);
	if (listenfd == -1) {
		perror("create_listen_socket failed");
		ret = 1;
		goto err_closeepoll;
	}

	first_fd = accept(listenfd, NULL, NULL);
	if (first_fd == -1) {
		perror("accept failed");
		ret = 1;
		goto err_closeboth;
	}

	printf("Got first fd: %d\n", first_fd);

	struct epoll_event events[MAX_EVENTS];
	int num_events, running = 1;

	char read_buf[1025];
	read_buf[0] = '\0';

	while (running) {
		num_events = epoll_wait(epollfd, events, MAX_EVENTS, 1000);

		for (int i = 0; i < num_events; i++) {
			// i don't think the listenfd can generate any events except for
			// EPOLLIN on new connections, so skip reading events[i].events
			if (events[i].data.fd == listenfd) {
				int new_fd = accept(listenfd, NULL, NULL);
				if (new_fd == -1) {
					perror("accept failed");
					ret = 1;
					goto err_closeboth;
				}

				int ret = epoll_register_fd(epollfd, EPOLLIN, new_fd);
				if (ret == -1) {
					perror("epoll_register_fd failed");
					ret = 1;
					goto err_closeboth;
				}

				num_other_fds++;
				int* tmp = (int*) realloc(other_fds, num_other_fds * sizeof(*other_fds));
				if (tmp == NULL) {
					perror("realloc failed");
					ret = 1;
					goto err_closeboth;
				}
				other_fds = tmp;
				other_fds[num_other_fds - 1] = new_fd;
			}
			else if (events[i].data.fd == first_fd) {
				if (events[i].data.events & POLLIN) {

				}
			}
		}
	}

err_closeboth:
	close(listenfd);

err_closeepoll:
	close(epollfd);

	free(other_fds);
	return ret;
}

