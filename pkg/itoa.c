#include<stdio.h>
#include<stdlib.h>


char* getDecStr (char* str, int len, int val)
{
  int i;

  for(i=1; i<=len; i++)
  {
    str[len-i] = (char) ((val % 10) + '0');
    val/=10;
  }

  str[i-1] = '\0';
  return(str);

}
