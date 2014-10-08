/* soubor: getch.c			-*-c-*-
   verze: 1.0   4.10. 1998
   autor: Vaclav Brozik  brozik@students.zcu.cz
   licence: public domain
   popis: modul emuluje dosovske funkce z <conio.h>
          kbhit(), getch(), getche()
*/

#include <unistd.h>
#include <signal.h>
#include <termio.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "getch.h"

#define STDIN 0
#define TTY "/dev/tty"

#ifdef GETCH_USE_SELECT		/* pouzij select() v kbhit() */
#  define NONBLOCK O_NONBLOCK	/* read() nemusi blokovat */
#  include <sys/time.h>		/* funkce select() */
#  include <sys/types.h>
static fd_set fdset;		/* mnozina deskriptoru souboru pro select() */
static fd_set fdset0;		/* kopie */
static struct timeval tv;	/* casove omezeni pro select() */
static struct timeval tv0;	/* kopie */
#else
#  define NONBLOCK 0		/* pouzit parametr terminalu VTIME */
#endif /* GETCH_USE_SELECT */


static struct termio savetty;	/* pro ulozeni nastaveni terminalu */
static struct termio newtty;	/* nove nastaveni terminalu */
static int rd_chr = -1;		/* precteny znak (jednoznakovy buffer) */
static int readed = 0;		/* 0 - neni nacten znak (to je anglictina!) */
static int tty = 0;		/* tty handler */
static int sigcatch_del = 0;	/* priznak odstraneni ovladace signalu */


int getch_init(int sigcatch)
     /* inicializace modulu
	sigcatch - priznak, zda zachytavat SIGINT
	           (jine signaly zachytite vlastnim volanim funkce signal())
        navrat -   0=OK, -1=KO */
{
  readed = 0;
  rd_chr = -1;
  if((tty = open(TTY, O_RDONLY | O_SYNC | NONBLOCK)) == -1) /* otevri /dev/tty s O_SYNC */
    return(-1);
  if(ioctl(tty, TCGETA, &savetty) == -1) /* uloz nastaveni terminalu */
  {
    close(tty);
    return -1;
  }
  if(sigcatch & GETCH_SIGINT)
  {
    signal(SIGINT, getch_sigcatch); /* zachyceni signalu - uklid */
    sigcatch_del = 1;
  }
  newtty = savetty;
  newtty.c_lflag &= ~ICANON;	/* vypnout kanonicky rezim */
  newtty.c_lflag &= ~ECHO;	/* vypnout echo */
  newtty.c_cc[VMIN] = 1;	/* minimalne 1 znak */
#ifndef GETCH_USE_SELECT
  newtty.c_cc[VTIME] = GETCH_SLEEP; /* cekej n * 1/10 s */
#else
  FD_ZERO(&fdset);
  FD_SET(tty, &fdset);
  tv.tv_sec  = GETCH_USLEEP / 1000000L;
  tv.tv_usec = GETCH_USLEEP % 1000000L;
#endif /* GETCH_USE_SELECT */
  if(ioctl(tty, TCSETAF, &newtty) == -1) /* test zmeny rezimu terminalu */
    return -1;
  if(ioctl(tty, TCSETAF, &savetty) == -1)
    return -1;
  return 0;
}

int kbhit(void)
     /* test stisku klavesy (klavesa jde pozdeji jeste precist funkci getch())
        navrat -   ASCII kod nebo 0 */
{
  char c;

  readed = 1;
  newtty.c_cc[VMIN] = 0;	/* nemusime cist zadny znak - tj. bez cekani */
  ioctl(tty, TCSETAF, &newtty);	/* zmen rezim terminalu */
#ifdef GETCH_USE_SELECT
  fdset0 = fdset;		/* parametry select() meni -> udelat kopie */
  tv0 = tv;
  select(tty+1, &fdset0, NULL, NULL, &tv0); /* pockej na znak z /dev/tty */
#endif /* GETCH_USE_SELECT */
  if(read(tty, &c, 1) <= 0)	/* zkus cist znak */
  {
    c = 0;			/* neni stisknuta klavesa */
    readed = 0;
    rd_chr = -1;
  }
  else
    rd_chr = c;
  newtty.c_cc[VMIN] = 1;
  ioctl(tty, TCSETAF, &savetty); /* obnov puvodni rezim terminalu */
  
  return c;
}

int getch(void)
     /* precteni klavesy
        navrat -   ASCII znak */
{
  char c;
  
  if(!readed)			/* neni precteny znak po funkci kbhit() */
  {
    ioctl(tty, TCSETAF, &newtty); /* zmen rezim terminalu */
    if(read(STDIN, &c, 1) <= 0)
      rd_chr = -1;
    else
      rd_chr = c;
    ioctl(tty, TCSETAF, &savetty);
  }
  readed = 0;			/* precteny znak je vyzvednut */
  if(rd_chr == -1)
    return 0;
  else
    return (rd_chr);
}

int getche(void)
     /* precteni klavesy + echo
        navrat -   ASCII znak */
{
  char c;
  
  if(!readed)
  {
    newtty.c_lflag |= ECHO;	/* zapnout echo */
    ioctl(tty, TCSETAF, &newtty);
    if(read(STDIN, &c, 1) <= 0)
      rd_chr = -1;
    else
      rd_chr = c;
    ioctl(tty, TCSETAF, &savetty);
    newtty.c_lflag &= ~ECHO;
  }
  readed = 0;
  if(rd_chr == -1)
    return 0;
  else
    return (rd_chr);
}

void getch_end(void)
     /* uklid */
{
  ioctl(tty, TCSETAF, &savetty); /* puvodni nastaveni terminalu */
  close(tty);			/* zavri /dev/tty */
  if(sigcatch_del)
  {
    signal(SIGINT, SIG_DFL);	/* nastav default ovladac pro SIGINT */
    sigcatch_del = 0;
  }
}

void getch_sigcatch(int sig)
     /* ovladac signalu */
{
  ioctl(tty, TCSETAF, &savetty);
  close(tty);
  signal(sig, SIG_DFL);
  kill(getpid(), sig);
}

