#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SIZE 1024

void send_file(FILE *fp,int sockfd){
char data[SIZE] = {0};
while(fgets(data, SIZE,fp)!= NULL){
 if (send(sockfd,data, sizeof(data),0) == -1){
 perror("[-]Error in sending data.");
 exit(1);
 }
 bzero(data, SIZE);
 }
}

int main(){
  char *ip = "127.0.0.1";
  int port= 8080;
  int e;
  int sockfd,newsock;
  struct sockaddr_in server_addr;
  FILE *fp;
  printf("enter the filename to read\n");
  char a[10];
  scanf("%s",&a);
  char *filename = a;
  sockfd = socket(AF_INET,SOCK_STREAM, 0);
  if (sockfd<0){
    perror("[-]Error in socket.");
    exit(1);
  }
  printf("[+]Server socket created\n");
  server_addr.sin_family=AF_INET;
  server_addr.sin_port= port;
  server_addr.sin_addr.s_addr= inet_addr(ip);
  e= connect(sockfd ,(struct server_addr*)&server_addr,sizeof(server_addr));
  if(e== -1){
  perror("[-]Error in connecting..\n");
  exit(1);}
  printf("[+]connected to server\n");
  fp= fopen(filename, "r");
  if (fp== NULL){
    perror("[-]Error in reading\n");
    exit(1);
  }
  send_file(fp,sockfd);
  printf("[+]File data send success\n");
  close(sockfd);
  printf("[+]Disconnected from server\n");

}
