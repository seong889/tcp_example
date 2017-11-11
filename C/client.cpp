#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("Usage : %s <IP> <PORT>\n", argv[0]);
		return 1;
	}

	int sock = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in clnt_addr;
	clnt_addr.sin_family = AF_INET;
	clnt_addr.sin_addr.s_addr = inet_addr(argv[1]);
	clnt_addr.sin_port = htons(atoi(argv[2]));

	int clnt_len = sizeof(clnt_addr);

	if (connect(sock, (struct sockaddr *)&clnt_addr, clnt_len) < 0) {
		perror("connect error : ");
		return 2;
	}

	write(sock, "test", 4);	

	close(sock);

	return 0;
}
