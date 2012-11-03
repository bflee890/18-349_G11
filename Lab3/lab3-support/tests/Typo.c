File Edit Options Buffers Tools C Help
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

int main(void) {
  struct timeval start, end;
  char inputString[50];
  double mtime, secs, usecs;
  while (1) {
    printf("> ");
    gettimeofday(&start, NULL);
    fgets(inputString, 50, stdin);
    printf("%s", inputString);
    gettimeofday(&end, NULL);
    secs  = end.tv_sec  - start.tv_sec;
    usecs = end.tv_usec - start.tv_usec;
    mtime = (secs + usecs/1000000.0);
    printf("%0.1f\n", mtime);
  }
}
