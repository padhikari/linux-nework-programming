#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>

void child_func(int childnum);

int main(int argc, char * argv[]){

	int nchildren = 1;
	int pid;
	int x;
	
	//check the command line to see how many child processes to create
	if(argc > 1){
		nchildren = atoi(argv[1]);
	}
	
	//create child process
	for(x=0; x < nchildren; x++){
		
		if((pid = fork()) == 0){
			child_func(x+1);
			exit(0);
		}
	}
	
	//parent process waits for them to finish before returning
	wait(NULL);
	return 0;	
}

void child_func(int childnum){
	
	int sock;
	struct sockaddr_in sAddr;
	char buffer[25];
	
	//create client socket and bind it to a local port
	memset((void *) &sAddr, 0, sizeof(struct sockaddr_in));
	sAddr.sin_family = AF_INET;
	sAddr.sin_addr.s_addr = INADDR_ANY;
	sAddr.sin_port = 0;
	
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(sock, (const struct sockaddr *)&sAddr, sizeof(sAddr));
	
	//connect to whichever server is running on the local machine
	sAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sAddr.sin_port = htons(1972);
	
	if(connect(sock, (const struct sockaddr *)&sAddr, sizeof(sAddr)) != 0){
		perror("Client");
		return;
	}
	
	//send some chars to the server and read what the server sends back
	snprintf(buffer, 128, "data from client #%i.", childnum);
	sleep(1);
	printf("child #%i sent %i chars\n", childnum, 
							send(sock, buffer, strlen(buffer), 0));
	sleep(1);
	printf("child #%i received %i chars\n", childnum,
							recv(sock,buffer,25,0));
	
	//finally close the connection and return
	sleep(1);
	close(sock);								
}
