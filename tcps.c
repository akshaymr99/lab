#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

#include  <netinet/in.h>


void error(char *msg)
{
    perror(msg);
    exit(1);
}
int main(int argc,char *argv[]) {
 
 char buffer[256];
 int sockfd,portno,client_socket,clilen,n;
 if(argc<2){
  fprintf(stderr,"Error,no port provided\n");
  exit(1);
 }
 
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 if(sockfd < 0)
  error("ERROR opening socket");
  struct sockaddr_in server_address,client_address;
  bzero((char *) &server_address, sizeof(server_address));
  portno = atoi(argv[1]);
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(portno);
  server_address.sin_addr.s_addr = INADDR_ANY;
  if (bind(sockfd,(struct sockaddr*) &server_address, sizeof(server_address))<0)
   error("ERROR on binding");
   listen(sockfd,5);
  clilen= sizeof(client_address);
  client_socket= accept(sockfd,(struct sockaddr*) &client_address, &clilen);
  if(client_socket < 0)
    error("ERROR on accept");
    bzero(buffer,256);
    n=read(client_socket,buffer,255);
    if(n<0) 
    error("ERROR reading from socket");
    printf("Here is the message: %s\n",buffer);
    n=write(client_socket,"I got your message",18);
    if(n < 0) 
    error("ERROR writing to socket");
    return 0;

}


