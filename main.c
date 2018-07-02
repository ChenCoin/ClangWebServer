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

		char* route(char*);
		if(strcasecmp(method, "GET") == 0){
			char* data = route(url);
			char response[128];
			sprintf(response, "HTTP/1.0 200 OK\r\n");
			sprintf(response,"%sContent-length: %ld\r\n",
				response,strlen(data));
			sprintf(response,"%sContent-type: %s\r\n\r\n",
				response,"text/html");
			write(client_fd, response, strlen(response));
			write(client_fd, data, strlen(data));
		}
		close(client_fd);
	}
	return 0;
}

char* route(char* url){
	char* home();
	char* error();
	char* todo(int);
	int event = -1;
	if(strcasecmp(url, "/") == 0)
		return home();
	else if(strcasecmp(url, "/1") == 0)
		return todo(1);
	else if(strcasecmp(url, "/2") == 0)
		return todo(2);
	else if(strcasecmp(url, "/3") == 0)
		return todo(3);
	else if(strcasecmp(url, "/4") == 0)
		return todo(4);
	else
		return error();
}

char* home(){
	return "hello";
}

char* error(){
	return "error";
}

char* todo(int item){
	return "data";
}
