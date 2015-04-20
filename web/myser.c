/*************************************************************************
	> File Name: myser.c
	> Author: 
	> Mail: 
	> Created Time: Mon Apr 20 03:38:29 2015
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main()
{
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("the sockfd is %d\n", sockfd);
  if(0 > sockfd)
  {
    perror("socket fail");
    return 0;
  }

  struct sockaddr_in servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(6666);
  if(0 > bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)))
  {
    perror("bind fail");
    return 0;
  }
  
  if(0 > listen(sockfd, 2))
  {
    perror("listen fail");
    return 0;
  }

  struct sockaddr_in cliaddr;
  memset(&cliaddr, 0, sizeof(cliaddr));
  socklen_t clilen = sizeof(cliaddr);
  int connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
  if(0 > connfd)
  {
    perror("accept fail");
    return 0;
  }

  printf("recv connect IP=%s port=%d\n", inet_ntoa(cliaddr.sin_addr),
        ntohs(cliaddr.sin_port)); 

  char recvmsg[1024];
  while(1)
  {
    memset(&recvmsg, 0, sizeof(recvmsg));
    int n = recv(connfd, recvmsg, sizeof(recvmsg), 0);
    printf("the ser n is %d, the recvmsg[%d] is %c\n", n, recvmsg[n]);
    if(0 > n) 
    {
      perror("recv fail");
      return 0;
    }
    //recvmsg[n] = '\0'; 
    printf("the recv string is %s\n", recvmsg);
    char s[] = {"Client Query"};
    int r = strcmp(s, recvmsg);
    printf("r is %d\n", r);
    if(0 == r)
    {
      fputs(recvmsg, stdout);
      //printf("Recevie Query\n"); 
    }
  }

  close(connfd);
  close(sockfd);
  return 0;
}
