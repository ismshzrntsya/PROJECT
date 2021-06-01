#include <sys/socket.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <netdb.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h> 
#include <arpa/inet.h> 
#include <time.h> 
#include <stddef.h>

int main(int argc, char *argv[]) 
{ 
	int sockfd = 0, n = 0; 
	char recvBuff[1024]; 
	struct sockaddr_in serv_addr; 
	time_t time1=time(NULL); 
	char cTime[50]; 
	struct tm *tm = localtime(&time1); 
	strftime(cTime, sizeof(cTime), "%c", tm);
	memset(recvBuff, '0',sizeof(recvBuff)); 
	
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Error : Could not create socket \n"); 
		return 1; 
	} 

	memset(&serv_addr, '0', sizeof(serv_addr)); 
	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(5000); 
	argv[1] = "192.168.56.102"; 
	printf("%s %s/n/n ",cTime,argv[1]); 
	printf(" timeClient: connecting to 192.168.56.102 Port=525 \n"); 

	if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0) 
	{ 
		printf("\n inet_pton error occured\n"); 
		return 1; 
	} 

	if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\n Error : Connect Failed \n"); 
		return 1; 
	} 	
	printf("\n timeClient: connected to timeServer. \n"); 

	while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0) 
	{ 
		recvBuff[n] = 0; 
		if(fputs(recvBuff, stdout) == EOF) 
		{ 
			printf("\n Error : Fputs error\n");
		}
	}

	if(n < 0) 
	{ 
		printf("\n Read error \n"); 
		exit(0); 
	} 
		
	printf("\n timeClient: now terminated. \n"); 
	return 0; 
}
