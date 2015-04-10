/*************************************************************************
	> File Name: echoser.c
	> Author: 
	> Mail: 
	> Created Time: Fri Apr 10 02:38:54 2015
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
  int listenfd;
  if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    ERR_EXIT("socket error");
  }

  struct sockaddr_in servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(5188);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

  int on = 1;
  if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
  {
    ERR_EXIT("setsockopt error");
  }

  if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
  {
    ERR_EXIT("bind error");
  }

  if(listen(listenfd, SOMAXCONN) < 0)
  {
    ERR_EXIT("listen error");
  }

  struct sockaddr_in peeraddr;
  memset(&peeraddr, 0, sizeof(peeraddr));
  socklen_t peerlen = sizeof(peeraddr);
  int conn;
  if((conn = accept(listenfd, (struct sockaddr *)&peeraddr, &peerlen)) < 0)
  {
    ERR_EXIT("accept error");
  }
  printf("recv connect ip=%s port=%d\n", inet_ntoa(peeraddr.sin_addr),
        ntohs(peeraddr.sin_port));

  char recvbuf[1024];
  while(1)
  {
    memset(recvbuf, 0, sizeof(recvbuf));

    // read client data by conncet fd
    int ret = read(conn, recvbuf, sizeof(recvbuf));

    // put the receive data on stdout
    fputs(recvbuf, stdout);

    // write data to client by connect fd
    write(conn, recvbuf, ret);
  }

  close(conn);
  close(listenfd);

  return 0;
}
