#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

main() {
  int pid;

  pid=fork();
  switch (pid) {
    case 0:
      printf("I am a child process.\n");
      break;
    case -1:
      printf("Cannot create child process!\n");
      return 1;
    default:
      printf("I am the parent process.. I have created a child with PID=%d.\n",
             pid);
      wait(0);
      break;
  }
  return 0;
}
