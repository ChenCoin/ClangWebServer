#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define errorExit(...)\
	({printf(__VA_ARGS__);exit(1);})

int main(int argc, char **argv){
	int PORT;
	(argc == 2) ?: errorExit("need a port\n");
	PORT = atoi(argv[1]);
	
	int createServer(int);
	int handle(int);
	int server = createServer(PORT);
	handle(server);

	return 0;
}

int createServer(int PORT){
	int serverfd;
	struct sockaddr_in server_addr;
	(serverfd = socket(AF_INET,SOCK_STREAM,0))
		?: errorExit("Socket error\n");
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	(bind(serverfd, (struct sockaddr *)
		&server_addr, sizeof(server_addr)) >= 0)
		?: errorExit("Bind error, about PORT?\n");
	(listen(serverfd, 5) >= 0)
		?: errorExit("Listen error\n");
	return serverfd;
}

int handle(int serverfd){
	struct sockaddr_in client_fdAddr;
	int addr_len = sizeof(struct sockaddr_in);
	char buffer[1024];
	while(1)
	{
		int client_fd = accept(serverfd, 
			(struct sockaddr*)&client_fdAddr, 
			(socklen_t*)&addr_len );
		if(client_fd < 0)continue;
		
		read(client_fd, buffer, 1024);
		char method[128],url[128];
		sscanf(buffer,"%s %s", method, url);
		printf("receive uri:%s\n\n", url);

		int route(int, char*);
		if(strcasecmp(method, "GET") == 0)
			route(client_fd,url);
		close(client_fd);
	}
	return 0;
}

int route(int client, char* url){
	int home(int);
	int error(int);
	int todo(int, int);
	int event = -1;
	if(strcasecmp(url, "/") == 0)home(client);
	else if(strcasecmp(url, "/1") == 0)todo(client, 1);
	else if(strcasecmp(url, "/2") == 0)todo(client, 2);
	else if(strcasecmp(url, "/3") == 0)todo(client, 3);
	else if(strcasecmp(url, "/4") == 0)todo(client, 4);
	else error(client);
	return 0;
}

int home(int client){
	char* data = "hello";
	char response[128];
	sprintf(response, "HTTP/1.0 200 OK\r\n");
	sprintf(response,"%sContent-length: %ld\r\n",
		response,strlen(data));
	sprintf(response,"%sContent-type: %s\r\n\r\n",
		response,"text/html");
	write(client, response, strlen(response));
	write(client, data, strlen(data));
	return 0;
}

int error(int client){
	char* data = "error";
	char response[128];
	sprintf(response, "HTTP/1.0 200 OK\r\n");
	sprintf(response,"%sContent-length: %ld\r\n",
		response,strlen(data));
	sprintf(response,"%sContent-type: %s\r\n\r\n",
		response,"text/html");
	write(client, response, strlen(response));
	write(client, data, strlen(data));
	return 0;
}

int todo(int client, int item){
	char data[6];
	sprintf(data, "%d", item);
	char response[128];
	sprintf(response, "HTTP/1.0 200 OK\r\n");
	sprintf(response,"%sContent-length: %ld\r\n",
		response,strlen(data));
	sprintf(response,"%sContent-type: %s\r\n\r\n",
		response,"text/html");
	write(client, response, strlen(response));
	write(client, data, strlen(data));
	return 0;
}
