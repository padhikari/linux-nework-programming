#include<sys/types.h>  
#include<sys/socket.h> 
#include<stdlib.h> 
#include<stdio.h> 
#include<signal.h> 
#include<netinet/in.h>  
#include<arpa/inet.h>  
#include<unistd.h> 

int main(){

	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(9734);
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

	//create a connection queue, ignore child exit details, and wait for clients
	listen(server_sockfd, 5);
	
	signal(SIGCHLD, SIG_IGN);
	
	while(1){
		char ch;
		printf("server waiting\n");
		
		//accept the connection
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_address, &client_len);
		
		//fork to crate a process for this client and test to see wheather you are the parent or child
		if(fork() == 0){
			//if you are child, you can now read and write to the client on client_sockfd
			read(client_sockfd, &ch, 1);
			sleep(5);
			ch++;
			write(client_sockfd, &ch, 1);
			close(client_sockfd);
			exit(0);
		}
		else{
			close(client_sockfd);
		}
	}
	
} 
