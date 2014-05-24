/* soubor: getch.h			-*-c-*-
   verze: 1.0   4.10. 1998
   autor: Vaclav Brozik  brozik@students.zcu.cz
   licence: public domain
   popis: modul emuluje dosovske funkce z <conio.h>
          kbhit(), getch(), getche()
*/

#ifndef _GETCH_H
#define _GETCH_H

/* konfigurace */
#define GETCH_USE_SELECT	/* pouzij volani select() ve funkci kbhit() */
				/* jinak pouzij parametr terminalu VTIME */
#define GETCH_USLEEP 5000	/* cekani v kbhit() v mikrosekundach */
				/* pri nastaveni GETCH_USE_SELECT */
#define GETCH_SLEEP 1		/* totez v 1/10 s - pri VTIME */
				/* pri nenastaveni GETCH_USE_SELECT */


#define GETCH_SIGINT 1		/* flag pro parametr funkce getch_init() */

#ifdef __cplusplus
extern "C" {
#endif

extern int kbhit(void);
extern int getch(void);
extern int getche(void);

extern int getch_init(int sigcatch);
extern void getch_end(void);
extern void getch_sigcatch(int sig);

#ifdef __cplusplus
	   }
#endif

#endif /* _GETCH_H */
