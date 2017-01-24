#include <stdio.h>
#include <stdbool.h>

int main(void)
{
  printf("int: %ld\n", sizeof(int));
  printf("size_t: %ld\n", sizeof(size_t));
  printf("bool: %ld\n", sizeof(bool));

  return (0);
}
