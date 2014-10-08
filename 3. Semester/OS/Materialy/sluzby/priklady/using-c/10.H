
extern int MyPid;        /* the shell's process id       */
extern int MyPgrp;       /* the shell's process group    */
extern int TermPgrp;     /* the terminal's process group */

#define	JSTOPPED		(1L<<1)
#define	JRUNNING		(1L<<2)
#define	JNEEDNOTE		(1L<<3)

#define	PTTYINPUT		(1L<<1)
#define	PTTYOUTPUT	(1L<<2)
#define	PSTOPSIGNAL	(1L<<3)
#define	PSTOPPED		(1L<<4)
#define	PDONE		(1L<<5)
#define	PEXITED		(1L<<6)
#define	PCOREDUMP		(1L<<7)
#define	PSIGNALED		(1L<<8)

struct _PROC {
	int pid;
	int status;
	int exitcode;
	int termsig;
	struct _PROC *next;
};
typedef struct _PROC PROC;

struct _JOB {
	int status;
	int pgrp;
	PROC	*procs;
};
typedef struct _JOB JOB;

