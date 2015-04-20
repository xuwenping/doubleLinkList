/*************************************************************************
	> File Name: mycli.c
	> Author: 
	> Mail: 
	> Created Time: Mon Apr 20 03:38:14 2015
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
  if(0 > sockfd)
  {
    perror("socket fail");
    return 0;
  }

  struct sockaddr_in servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(6666);
  if(0 > connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)))
  {
    perror("connect fail");
    return 0;
  }
  
  char sendmsg[1024] = {0};
  while(fgets(sendmsg, sizeof(sendmsg), stdin))
  {
    send(sockfd, sendmsg, strlen(sendmsg), 0);

    memset(sendmsg, 0, sizeof(sendmsg));
  }

  close(sockfd);
  return 0;
}
