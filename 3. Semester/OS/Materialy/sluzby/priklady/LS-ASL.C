/*
  Tento program funguje ako ls -asl.
  Vypise obsah zadanych adresarov (ak nie je zadany ziaden adresar,
  vypise sa obsah aktualneho adresara).
  Vypis je kvoli jednoduchosti neusporiadany, namiseto mien uzivatelov
  a grup su vypisane iba ich id-cisla.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <stdio.h>

char *modes[] = {
    "---", "--x", "-w-", "-wx",
    "r--", "r-x", "rw-", "rwx"
};

main(argc, argv)
int argc;
char **argv;
{
    struct stat sbuf;

    /*
      Ak je bez argumentov, vypis iba aktualneho adresara.
     */
    if (argc < 2) {
        list(".");
        exit(0);
    }

    /*
      Inac preberieme postupne vsetky argumenty.
     */
    while (--argc) {
        /*
          Ak ten argument nie ja ani len subor...chyba!
         */
        if (stat(*++argv, &sbuf) < 0) {
            perror(*argv);
            continue;
        }

        /*
          Ak je to adresar, vypiseme jeho obsah, ak je to subor->
          vypiseme o nom informacie.
         */
        if ((sbuf.st_mode & S_IFMT) == S_IFDIR)
            list(*argv);
        else
            printout(".", *argv);
    }

    exit(0);
}

/*
  list - tato funkcia cita zadany adresar a vypisuje informacie
         o polozkach v nom.
*/

list(name)
char *name;
{
    DIR *dp;
    struct direct *dir;

    /*
      Otvorime adresar.
     */
    if ((dp = opendir(name)) == NULL) {
        fprintf(stderr, "%s: cannot open.\n", name);
        return;
    }

    /*
      Pre kazdu polozku vykoname cyklus:
     */
    while ((dir = readdir(dp)) != NULL) {
        /*
          Preskocime vymazane subory.
         */
        if (dir->d_ino == 0)
            continue;

        /*
          Vypiseme informacie o existujucich suboroch.
         */
        printout(name, dir->d_name);
    }

    closedir(dp);
}

/*
  printout - Funkcia, ktora vypise informacie o subore
*/

printout(dir, name)
char *dir, *name;
{
    int i, j;
    char perms[10];
    struct stat sbuf;
    char newname[1024];

    /*
      Urobime si plne meno suboru (aj z cestou).
     */
    sprintf(newname, "%s/%s", dir, name);

    /*
      Vieme ze subor existuje, takze 'stat' nam naozaj precita informacie
      o tomto subore.
    */

    stat(newname, &sbuf);

    /*
      Vypiseme velkost v kB.
    */
    printf("%5d ", (sbuf.st_size + 1023) / 1024);

    /*
      Zistime typ suboru (subor, adresar, znakove/blokove zariadenie)
     */
    switch (sbuf.st_mode & S_IFMT) {
    case S_IFREG:    putchar('-'); break;
    case S_IFDIR:    putchar('d'); break;
    case S_IFCHR:    putchar('c'); break;
    case S_IFBLK:    putchar('b'); break;
    default:         putchar('?'); break;
    }

    /*
       Zistime vsetky prava (vlastnik, skupina, ostatni).
     */
    *perms = NULL;
    for (i = 2; i >= 0; i--) {
        j = (sbuf.st_mode >> (i*3)) & 07;
        /*
          Vypiseme prislusne prava (tieto prava mame
          v poli modes).
         */
        strcat(perms, modes[j]);
    }

    /*
      Obsluzime specialne bity, ktore vymenia prislusne
      znaky 'x'.
     */
    if ((sbuf.st_mode & S_ISUID) != 0)
        perms[2] = 's';
    if ((sbuf.st_mode & S_ISGID) != 0)
        perms[5] = 's';
    if ((sbuf.st_mode & S_ISVTX) != 0)
        perms[8] = 't';

    /*
      Teraz vytlacime prava, pocet liniek na subor, user a group ID.
     */
    printf("%s%3d %5d/%-5d ", perms, sbuf.st_nlink, sbuf.st_uid,
        sbuf.st_gid);

    /*
      Vytlacime velkost suboru v bajtoch a cas poslednej modifikacie.
      Rutine 'ctime' konvertuje cas do ASCII.
     */
    printf("%7d %.12s ", sbuf.st_size, ctime(&sbuf.st_mtime)+4);

    /*
      A nakoniec samozrejme vypiseme meno suboru.
     */
    printf("%s\n", name);
}

