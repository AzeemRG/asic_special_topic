#include <stdio.h>

extern int load(int x, int y);

int main()
{
  int result = 0;
  int count = 20;
  result = load(0x0, count+1);
  printf("Sum of numbers from 1 to 20 is %d\n", result);
}
