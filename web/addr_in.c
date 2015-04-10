/*************************************************************************
	> File Name: addr_in.c
	> Author: 
	> Mail: 
	> Created Time: Fri Apr 10 02:07:39 2015
 ************************************************************************/

#include<stdio.h>
#include<arpa/inet.h>

int main()
{
  unsigned int addr = inet_addr("192.168.0.100");
  printf("add = %u\n", addr);
  printf("add = %u\n", ntohl(addr));

  struct in_addr ipaddr;
  ipaddr.s_addr = addr;
  printf("%s\n", inet_ntoa(ipaddr));

  return 0;
}
