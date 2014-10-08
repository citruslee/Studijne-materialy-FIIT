/*
  Tento program vypne ECHO a zapne CBREAK mod. Potom vypise obsah
  suborov zadanych v command-line, pricom po zaplneni obrazovky program
  vzdy vypise spravu a caka kym uzivatel stlaci nejaku klavesu. Az potom
  pokracuje v povodnej cinnosti (ako 'more').

  Struktura 'tchars' je pozita na vypnutie CTRL+C, pretoze preruseny program
  by mohol zanechat terminal v nezelanom stave.

  Poznamka:
    Obycajne sa CTRL+C osetruje pomocou signalov.
*/

#include <sys/ioctl.h>
#include <stdio.h>

main(argc, argv)
int argc;
char **argv;
{
    struct sgttyb sgo, sgn;
    struct tchars tco, tcn;

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
    ioctl(0, TIOCGETP, &sgo);
    ioctl(0, TIOCGETC, &tco);

    sgn = sgo;
    sgn.sg_flags &= ~ECHO;      /* turn off ECHO   */
    sgn.sg_flags |= CBREAK;     /* turn on CBREAK  */

    tcn = tco;
    tcn.t_intrc = -1;           /* zakazeme CTRL+C */

    /*
      Nastavime nove mody. Znovu ignorujeme navratove hodnoty.
    */
    ioctl(0, TIOCSETP, &sgn);
    ioctl(0, TIOCSETC, &tcn);

    /*
      Cyklus pre vsetky argumenty z command-line.
    */
    while (--argc)
        more(*++argv);

    /*
      Reset starych tty modov.
     */
    ioctl(0, TIOCSETP, &sgo);
    ioctl(0, TIOCSETC, &tco);

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

