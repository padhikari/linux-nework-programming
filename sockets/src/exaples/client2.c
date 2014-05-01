#include<sys/types.h>  
#include<sys/socket.h> 
#include<stdlib.h> 
#include<stdio.h>  
#include<netinet/in.h>  
#include<arpa/inet.h>  
#include<unistd.h>  
  
int main(){  

	int sockfd;  
	int len;  
	struct sockaddr_in address;  
	int result;  
	char ch = 'A';  

	//create a socket for the client
	sockfd = socket(AF_INET, SOCK_STREAM, 0);  

	//name the socket, as agreed with the server 
	address.sin_family = AF_INET;  
	address.sin_addr.s_addr = inet_addr("127.0.0.1");  
	address.sin_port = htons(9734);  
	len = sizeof(address);  

	//now connect our socket to the server's socket 
	result = connect(sockfd, (struct sockaddr *)&address, len);  

	if(result == -1) {  
		perror("oops: client3");  
		exit(1);  
	}  

	//we can now read/write via sockfd  
	write(sockfd, &ch, 1);  
	read(sockfd, &ch, 1);  
	printf("char from server = %c\n", ch);  
	close(sockfd);  
	exit(0);  
}  
