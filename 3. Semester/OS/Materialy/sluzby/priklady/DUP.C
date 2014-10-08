#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>     /* definition of OPEN_MAX */

main(argc, argv)
int argc;
char *argv[];
{
 	int fd1,fd2;
	char c;
	int finish=0;

	if (argc!=2) {
	  printf("Usage: dup filename\n");
	  return 1;
	} 
	fd1=open(argv[1],O_RDONLY,0);
	if (fd1==-1) {
	  printf("Can't open file %s for reading!\n",argv[1]);
	  return 2;
	}
	fd2=dup(fd1);
	while (finish!=3) {
	  if (read(fd1,&c,1)) printf("%c",c);
	  else finish|=1;
	  if (read(fd2,&c,1)) printf("%c",c);
	  else finish|=2;
	}
	return 0;
}
