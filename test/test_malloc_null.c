#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  void *ptr;

  ptr = malloc(0);
  if (ptr)
    printf("EXIST\n");
  else
    printf("DON'T EXIST\n");
  return (0);
}
