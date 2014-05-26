#include <limits.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

main(argc,argv)
int argc;
char *argv[];
{
  int fildes[2];
  int c;

  if (-1==pipe(fildes)) {
	printf("Can't create interprocess channel!\n");
	return 2;
  }
  switch (fork()) {
	case 0:
	  close(fildes[1]);
	  printf("Child: I am here!\n");
 	  while (1) {
	    if (!read(fildes[0],&c,1)) {
		printf("Child: All data have been read.\n");
		close(fildes[0]);
		return 0;
	    }
	    printf("Child: Received character '%c'.\n",c);
	  }
	case -1:
	  printf("Can't create child process!\n");
	  return 1;
	default:
	  close(fildes[0]);
	  printf("Parent: I am here!\n");
 	  while (1) {
	    if (!read(0,&c,1)) {
		close(fildes[1]);
		printf("Parent: All data have been sent.\n");
		wait(0);
		return 0;
	    }
	    printf("Parent: Writing character '%c'.\n",c);
	    write(fildes[1],&c,1);
	  }

  }
}


