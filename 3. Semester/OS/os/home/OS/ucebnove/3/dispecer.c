 /* Planovanie procesov na najnizsej urovni */

 typedef struct process_description *PROCESS;

 struct process_description {
       int pid;  /* identifikacia procesu */
       enum {SRUN, SREADY, SSLEEP} status;
       struct save_context {
             unsigned int SS;
             unsigned int SP;
             } regs;  /* uchovaj kontext  procesu, ak je  zvysok v
                         zasobniku, tak staci Stack Pointer */
       PROCESS next;   /* dalsi opis procesu */
       PROCESS qnext; /* dalsi v rade */
       ...            /* dalsie polozky */
       } ;

 /* definicia radu procesov (zretazeny zoznam pomocou qnext) */
 typedef PROCESS PQUEUE; /* hlavicka radu procesov */
 /* vloz proces na koniec radu q */
 void enter(PQUEUE q, PROCESS p);
 /* vyber prvy proces z radu q; vrat NULL ak prazdny */
 PROCESS remove_first(PQUEUE q);

 /* premenne jadra: */
 PROCESS Prun; /* prave beziaci proces alebo pole procesov
                         v multiprocesorovom systeme */
 PQUEUE  PQready; /* rad pripravenych procesov */



 /* Nasleduje priklad pre procesor 80x86. V tomto priklade sa
    save_context a restore_context musia vykonat
    v tele tej istej funkcie, preto #define                                   */
 #define save_context()                                           \
   /* uloz vsetky registre do zasobnika */                        \
   asm { PUSH AX;  /* ... */ PUSH ES; }                           \
   /* Ukazovatel zasobnika je urceny pomocou SS:SP */             \
   Prun->regs.SS = _SS;                                           \
   Prun->regs.SP = _SP;

 #define restore_context()                                        \
   /* Obnov ukazovatel zasobnika tohoto procesu */                \
   _SS = Prun->regs.SS ;                                          \
   _SP = Prun->regs.SP ;                                          \
   /* obnov vsetky registre zo zasobnika */                       \
   asm { POP ES; /* ... */ POP AX; }

 /* dispecer - prepinanie procesov */
 void context_switch(void)
 {
   save_context();
   /* vyber proces s najvyssou prioritou */
   Prun = schedule_process(PQready);
   Prun->status = SRUN;
   restore_context();
 /* v instrukcii RET (navrat z volania funcie) sa obsah CS:IP naplni
     z noveho zasobnika. Az v tej chvili dojde k prepnutiu kodu zo
      stareho na novy proces!!!                                  */
 }

 /* preempcia - nasilne odobratie procesora beziacemu procesu */
 void preempt(void)
 {
   LOCK(); /* napr. zakazanie prerusenia */
   Prun->status = SREADY;
   enter(PQready, Prun);
   context_switch();
   UNLOCK();
 }

 /* velmi vseobecny algoritmus osetrenia prerusenia -
    implementacia zavisi od konkretnych prostriedkov */
 void interrupt interrupt_handler(void)
 {
 /*  odloz registre; /* nie cely kontext procesu */
   urci zdroj prerusenia; /* 8086: zabezpeLuje hardware */
   volaj osetrenie prerusenia;
   obnov registre; */
 }
 /* napriklad: */
 void interrupt timer_interrupt(void)
 {
   restart_timer();
   end_of_interrupt(); /* pre technicke prostriedky */
   system_clock++;
   time_slice++;   /* pocita cas beziaceho procesu,
                        inicializuje sa v context_switch() */
   if (time_slice > TIME_SLICE_MAX)
     preempt();    /* odober procesor procesu */
 }


/* Implementacia semaforov: */

 typedef struct semaphore *SEM;

 struct semaphore {
   int value;
   PQUEUE queue;
   };

 void init_sem(SEM s, int v)
 {
   s->value = v;
   s->queue = NULL;
 }

 void wait(SEM s)
 {
   LOCK();
   if (s->value > 0)   {
     s->value--;
     UNLOCK();
     return;
     }
   Prun->status = SSLEEP;
   enter(s->queue, Prun);
   context_switch();
   UNLOCK();
 }

 void signal(SEM s)
 {
   PROCESS p;
   LOCK();
   p = remove_first(s->queue);
   if (p != NULL)    {
     p->status = SREADY;
     enter(PQready, Prun);
     }
   else
     s->value++;
   /* treba contex_switch() ??? */
   UNLOCK();
 }

