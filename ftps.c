#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE 1024

 void write_file(int sockfd){
 int n;
 FILE *fp;
 printf("enter the filename to write\n");
 char a[10];
 scanf("%s",&a);
 char *filename= a;
 char buffer[SIZE];

  fp= fopen(filename, "w");
  if (fp== NULL){
    perror("[-]Error in creating\n");
    exit(1);
  }
  while(1){
  n=recv(sockfd,buffer,SIZE, 0);
  if(n <= 0){
  break;
  return;
  }
  fprintf(fp,"%s",buffer);
  bzero(buffer, SIZE);
 }
 return;
 }

 int main(){
   char *ip = "127.0.0.1";
   int port= 8080;
   int e;

   int sockfd,newsock;
   struct sockaddr_in server_addr, new_addr;
   socklen_t addr_size;
   char buffer[SIZE];

   sockfd = socket(AF_INET,SOCK_STREAM, 0);
   if (sockfd<0){
     perror("[-]Error in socket.\n");
     exit(1);
   }
   printf("[+]Server socket created\n");
   server_addr.sin_family=AF_INET;
   server_addr.sin_port= port;
   server_addr.sin_addr.s_addr= inet_addr(ip);

   e=bind(sockfd,(struct sockaddr*) &server_addr, sizeof(server_addr));
   if(e<0){
     perror("[-]Error in binding\n");
     exit(1);
   }

  printf("[+]Binding success\n");
  e=listen(sockfd,0);
  if(e==0){
    printf("[+]Listening...\n");
  }else {
    perror("[-]Error in listening");
    exit(1);
  }
  addr_size = sizeof(new_addr);
  newsock = accept(sockfd,(struct sockaddr*)&new_addr, &addr_size);

  write_file(newsock);
  printf("[+]Data written in the file :%s\n");
 }
