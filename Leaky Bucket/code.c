#include <stdio.h>
#define MIN(x, y) (x < y ? x : y)

void main()
{
  int bucketSize, outputRate, input[100] = {0}, i = 0, j = 1, remaining = 0;
  printf("Enter bucket size: ");
  scanf("%d", &bucketSize);
  printf("Enter output rate: ");
  scanf("%d", &outputRate);
  while (input[i++] != -1)
  {
    printf("Enter input rate for second %d (-1 to stop): ", i + 1);
    scanf("%d", &input[i]);
  }
  printf("Second\tReceived\tSent\tDropped\tRemaining\n");
  while (remaining != 0 || input[j] != -1)
  {
    int received = (input[j] == -1) ? 0 : input[j++];
    remaining += received;
    int sent = MIN(remaining, outputRate);
    remaining -= sent;
    int dropped = remaining > bucketSize ? remaining - bucketSize : 0;
    remaining = MIN(remaining, bucketSize);
    printf("%d\t%d\t\t%d\t%d\t%d\n", j, received, sent, dropped, remaining);
  }
}