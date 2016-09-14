#include <stdio.h>

int main()
{

  char c = 2;
  short s = 0x1000;

  c=c+s;
  printf("%d \n", c);
  
  char str[] = "hello", *p = str;

  printf("%d\n", ((p+3)-&str[1]));

  char a[] = {1,2,3,4,5}, *ptr = a;

  printf("%d\n", ((ptr+3)-&a[1]));
}
