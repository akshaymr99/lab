#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char **argv){
 
 if(argc !=2){
 printf("Usage: %s <port>\n",argv[0]);
 exit(0);
 }
 
 
 char *ip ="127.0.0.1";
 int port=atoi(argv[1]);
 
 int sockfd;
 struct sockaddr_in server_addr;

  char buffer[1024];
  socklen_t addr_size;
  int n;
  
  sockfd=socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd<0){
  perror("[-]socket error");
  exit(1);
  }
  
  memset(&server_addr, '\0', sizeof(server_addr));
  server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
    
    printf("Enter the message:");
    fgets(buffer,1024,stdin);
    sendto(sockfd,buffer,strlen(buffer),0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("[+] Data send: %s\n", buffer);
 
 return 0;

}	
