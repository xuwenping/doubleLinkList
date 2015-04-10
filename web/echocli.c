/*************************************************************************
	> File Name: echocli.c
	> Author: 
	> Mail: 
	> Created Time: Fri Apr 10 02:56:10 2015
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

#define ERR_EXIT(m) \
    do {            \
      perror(m);    \
      exit(EXIT_FAILURE); \
       } while(0);

int main()
{
  int sock;
  if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    ERR_EXIT("socket error");
  }

  struct sockaddr_in servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(5188);
  //servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  inet_aton("127.0.0.1", &servaddr.sin_addr);

  if(connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    ERR_EXIT("conncet error");

  char sendbuf[1024] = {0};
  char recvbuf[1024] = {0};
  while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
  {
    write(sock, sendbuf, strlen(sendbuf));
    read(sock, recvbuf, sizeof(recvbuf));

    fputs(recvbuf, stdout);

    memset(sendbuf, 0, sizeof(sendbuf));
    memset(recvbuf, 0, sizeof(recvbuf));
  }

  close(sock);

  return 0;
}
