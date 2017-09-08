#include <sys/socket.h>
#include <sys/types.h>
#include <dirent.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int getPort(char *argv[]);
char* getDir(char *argv[]);
struct dirent* readFile(char* dir_path, char* file_name);
void setUpUdp(int port, FILE *fp);

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Program must take 2 arguments!\n");
		return 0;
	}

	int port = getPort(argv);
	char* dir = getDir(argv);
	printf("%s\n",dir);
	printf("%d\n", port);
	char* file_name = "example_data3";
	struct dirent* bla;
	bla = readFile(dir, file_name);
	printf("File name is: %s!!!!\n", bla->d_name);
	FILE *fp = fopen(bla->d_name, "r");
	setUpUdp(port, fp);
	fclose(fp);
	return 0;
}

int getPort(char *argv[])
{
	return atoi(argv[1]);
}

char* getDir(char *argv[])
{
	return argv[2];
}

struct dirent* readFile(char* dir_path, char* file_name)
{
	DIR *dir = opendir(dir_path);
	if (dir == NULL)
	{
		printf("Dir is NULL  \n");
	}

	struct dirent* file;

	while ((file = readdir(dir)) != NULL)
	{
		printf("%s\n", file->d_name);
		if (strcmp(file->d_name, file_name) == 0)
		{
			printf("Found file!\n");
			printf("%s\n", file->d_name);
			return file;
		}
	}
	return NULL;
}

void setUpUdp(int port, FILE *fp)
{
    int sockfd;
    struct sockaddr_in server, client;
    char buffer[512];

    // Create and bind a UDP socket.
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		printf("Could not open socket");
	}
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;

    // Network functions need arguments in network byte order instead
    // of host byte order. The macros htonl, htons convert the values.
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(atoi(argv[1]));
    int bindStatus = bind(sockfd, (struct sockaddr *) &server, (socklen_t) sizeof(server));
	if (bindStatus < 0)
	{
		printf("Error bindStatus = -1\n");
	}

    for (;;) {
		n = recvfrom(sockfd, buffer, 512, 0, (struct sockaddr * )&client, &sizeof(struct sockaddr_in));
		if (n < 0)
		{
			printf("recvfrom not working!!!");
		}
		fprintf(stdout, "Received: \n%s\n", )
		write(1, buffer, n);
		n = sendto(sockfd, "Got your message\n", 17, 0, (struct sockaddr *)&client, sizeof(struct sockaddr_in));
		if (n < 0)
		{
			printf("Error sendto")
		}

        // Receive up to one byte less than declared, because it will
        // be NUL-terminated later.
        socklen_t len = (socklen_t) sizeof(client);
        ssize_t n = recvfrom(sockfd, fp, sizeof(fp) - 1,
                             0, (struct sockaddr *) &client, &len);

        //message[n] = '\0';
        fprintf(stdout, "Received:\n%s\n", fp);
        fflush(stdout);

        sendto(sockfd, fp, (size_t) n, 0,
               (struct sockaddr *) &client, len);
	}
}
