#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>
#include<string.h>

int main(int argc, char *argv[]){
	
	int simpleSocket = 0;
	int simplePort = 0;
	int returnStatus = 0;
	char buffer[256] = "";
	struct sockaddr_in simpleServer;
	
	if(argc != 3){
		fprintf(stderr, "Usage: %s <server> <port>\n", argv[0]);
		exit(1);
	}	
	
	//create a streaming socket
	
	simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if(simpleSocket == -1){
		
		fprintf(stderr, "Could not create a socket!\n");
		exit(1);
	}
	else{
		fprintf(stderr, "Socket created!\n");
	}
	
	//retrieve the port number for connecting
	simplePort = atoi(argv[2]);
	
	//set up the address structure
	bzero(&simpleServer, sizeof(simpleServer));
	simpleServer.sin_family = AF_INET;
	inet_addr(argv[2], &simpleServer.sin_addr.s_addr);
	simpleServer.sin_port = htons(simplePort);
	
	//connect to the address and port with our socket
	returnStatus = connect(simpleSocket, (struct sockaddr *)&simpleServer, sizeof(simpleServer));
	
	// get the message from the server
	returnStatus = read(simpleSocket, buffer, sizeof(buffer));
	
	if(returnStatus > 0){
		printf("%d:%s", returnStatus, buffer);
	}
	else{
		fprintf(stderr, "Return Status = %d\n", returnStatus);
	}	
	
	close(simpleSocket);
	return 0;	
}
