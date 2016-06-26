/*
  Tento program vypne ECHO a ICANON mod. Potom vypise obsah
  suborov zadanych v command-line, pricom po zaplneni obrazovky program
  vzdy vypise spravu a caka kym uzivatel stlaci nejaku klavesu. Az potom
  pokracuje v povodnej cinnosti (ako 'more').

  Klavesa prerusenia c_cc je nastavena na -1 , cize CTRL+C je vypnute.

  Poznamka:
    Obycajne sa CTRL+C osetruje pomocou signalov.
*/

#include <termio.h>
#include <stdio.h>

main(argc, argv)
int argc;
char **argv;
{
    struct termio tio, tin;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s file [file ...]\n", *argv);
        exit(1);
    }

    /*
       Obycajne by sme mali kontrolovat vystupne hodnoty
       z ioctl, pretoze ak je vstup presmerovany na subor, tak
       vratia chybovu hodnotu. My budeme predpokladat, ze terminal
       je vzdy pripojeny k standardnemu vstupu.
    */

    ioctl(0, TCGETA, &tio);

    tin = tio;
    tin.c_lflag &= ~ECHO;      /* turn off ECHO   */
    tin.c_lflag &= ~ICANON;    /* turn off ICANON */

    /*
     * Emulate CBREAK mode.
     */
    tin.c_cc[VMIN] = 1;
    tin.c_cc[VTIME] = 0;

    /*
      Nastavime novy mod. Znovu ignorujeme navratovu hodnoty.
    */
    ioctl(0, TCSETA, &tin);

    while (--argc)
        more(*++argv);

    /*
      Reset starych tty modov.
     */
    ioctl(0, TCSETA, &tio);

    exit(0);
}

/*
 * more - Tato funkcia zobrazi subor
 */
more(file)
char *file;
{
    FILE *fp;
    int line;
    char linebuf[1024];

    if ((fp = fopen(file, "r")) == NULL) {
        perror(file);
        return;
    }

    /*
      Naraz sa vypise iba 22 riadkov.
     */
    for (;;) {
        line = 1;
        while (line < 22) {
            /*
               Ak je koniec suboru, pockame na stlacenie klavesy este
               raz a vraciame sa z funkcie.
             */
            if (fgets(linebuf, sizeof(linebuf), fp) == NULL) {
                fclose(fp);
                prompt();
                return;
            }
            /*
              Inac vypiseme precitany riadok.
            */
            fwrite(linebuf, 1, strlen(linebuf), stdout);
            line++;
        }
        /*
          Preslo 22 riadkov, treba pockat na stlacenie klavesy.
        */
        prompt();
    }
}

/*
  prompt - funkcia cakajuca na stlacenie klavesy.
 */
prompt()
{
    char answer;

    printf("Type any character for next page: ");
    answer = getchar();
    putchar('\n');
}

