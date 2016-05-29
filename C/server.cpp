#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		return 1;
	}

	int serv_sock = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in servaddr;
	memset((void*)&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));

	if (bind(serv_sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		perror("bind error : ");
		return 2;
	}

	if (listen(serv_sock, 5) < 0) {
		perror("listen error : ");
		return 3;
	}

	while (1) {
		int clnt_len;
		struct sockaddr_in clientaddr;
		int clnt_sock = accept(serv_sock, (struct sockaddr *)&clientaddr, (socklen_t*)&clnt_len);

		char buf[5] = {0,};
		read(clnt_sock, buf, 4);
		printf("%s\n", buf);
		close(clnt_sock);
	}


	return 0;
}