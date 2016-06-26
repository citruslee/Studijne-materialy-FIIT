/*
  lseekdemo - ukazka pouzitia volania lseek. Vytvorime si databazu
              akychsi uzivatelov a zapisujeme do nej ich UID a mena.
              Funckia putrec zarucuje, ze bude kazda polozka zaradena
              na spravne miesto
*/

/*
  If you're on System V, change <sys/file.h> to <sys/fcntl.h>.
*/

#include <sys/file.h>

struct record {
    int uid;
    char login[9];
};

char *logins[] = { "user1", "user2", "user3",
                   "user4", "user5" };

main()
{
    int i, fd;
    struct record rec;

    /*
      Otvorime datovy subor na zapis...
     */
    if ((fd = open("datafile", O_WRONLY | O_CREAT, 0644)) < 0) {
        perror("datafile");
        exit(1);
    }

    /*
      Prechadzame vsetkych uzivatelov z nasho pola odzadu.
     */
    for (i = 4; i >= 0; i--) {
        /*
          Vytvorime polozku pre uzivatela.
         */
        rec.uid = i;
        strcpy(rec.login, logins[i]);

        /*
          Zapiseme tuto polozku na prislusne miesto.
          Vsimnite si, ze funkcii putrec predavame iba adresu
          struktury a nie celu strukturu.
         */
        putrec(fd, i, &rec);
    }

    /*
      Uzavrieme subor.
    */
    close(fd);
    exit(0);
}

/*
   putrec - tato funkcia zapise polozku na i-tu poziciu do
            suboru.
*/
putrec(fd, i, r)
int i, fd;
struct record *r;
{
    /*
      Nastavime sa na i-tu polozku v subore.
     */
    lseek(fd, (long) i * sizeof(struct record), L_SET);

    /*
      Zapiseme zadanu polozku na nastavene miesto. Zapisujeme
      strukturu, ktora ja na adrese 'r' a ma velkost
      sizeof(struct record)
     */
    write(fd, r, sizeof(struct record));
}

