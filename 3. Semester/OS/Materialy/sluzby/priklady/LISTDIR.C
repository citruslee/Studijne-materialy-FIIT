/*
   Tento program vypise zoznam suborov v aktualnom adresari.
*/

/*
 * For use with 4.2 and 4.3BSD systems.
 */
#include <sys/types.h>
#include <sys/dir.h>
#include <stdio.h>

main()
{
    DIR *dp;
    struct direct *dir;

    /*
      Otvorime aktualny adresar prikazom opendir (pozrite
      podrobnejsie v manuali.
    */

    if ((dp = opendir(".")) == NULL) {
        fprintf(stderr, "cannot open directory.\n");
        exit(1);
    }

    /*
      V cykle precitame vsetky polozky adresara (prikaz readdir).
     */
    while ((dir = readdir(dp)) != NULL) {
        /*
          Preskocime subory, ktore su vymazane.
         */
        if (dir->d_ino == 0)
            continue;
        /*
          Ostane subory vypiseme. (len mena).
        */
        printf("%s\n", dir->d_name);
    }

    /*
      Na konci prace s adresarom ho treba uzavriet! (closedir)
    */
    closedir(dp);
    exit(0);
}

