/*************************************************************************
	> File Name: byteoreder.c
	> Author: 
	> Mail: 
	> Created Time: Fri Apr 10 01:37:13 2015
 ************************************************************************/

#include<stdio.h>
#include<arpa/inet.h>

int main()
{
  unsigned int x = 0x12345678;
  unsigned char *p = (unsigned char *)&x;
  printf("%x %x %x %x\n", p[0], p[1], p[2], p[3]);

  unsigned int y = htonl(x);
  p = (unsigned char *)&y;
  printf("%x %x %x %x\n", p[0], p[1], p[2], p[3]);

  return 0;
}
