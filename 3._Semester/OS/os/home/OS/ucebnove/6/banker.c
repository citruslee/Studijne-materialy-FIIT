/* BANKER.C - bankarov algoritmus
 *            Nacrt riesenia prevencie deadlocku pre Operacne systemy.
 */

#define MAXPROC 20                              /* pocet procesov */
#define MAXRES  8                     /* pocet typov prostriedkov */

typedef enum { FALSE = 0, TRUE } bool;
typedef int  resnum_t;             /* pocet instancii prostriedku */

typedef struct {
          resnum_t Available[MAXRES];  /* prave volne prostriedky */
          resnum_t Allocation[MAXPROC][MAXRES]; /* pridelene      */
          resnum_t Need[MAXPROC][MAXRES];  /* zostavajuca potreba */
                     /* Max[i][j] = Allocation[i][j] + Need[i][j] */
          } status_t;

static status_t CurrentStatus;      /* aktualny stav prostriedkov */


/**********  Prototypy funkcii **********/
/* Vektorove operacie budeme zapisovat iba symbolicky.
 * V skutocnosti by sme ich implementovali napr. takto:
 * Funkcia VectorLE porovna vektory X a Y, oba dlzky n a
 * vrati TRUE ak plati X[i] <= Y[i] pre i=0,1,...,n-1.
 */
static bool VectorLE(resnum_t *X, resnum_t *Y, int n);

/* Funkcia IsSafeStatus pomocou simulacie zisti, ci stav S vedie
 * k uspesnemu koncu. Ak ano, vrati TRUE.
 */
static bool IsSafeStatus(status_t *S);

/* Funkciu RequestResources vola proces P, ktory chce ziskat
 * prostriedky uvedene vo vektore R dlzky MAXRES.
 * Ak system zisti, ze pozicka nevedie k bezpecnemu stavu,
 * proces P musi cakat.
 */
void RequestResources(int P, resnum_t R[MAXRES]);

/* Funkciou ReleaseResources vracia proces P vsetky obsadene
 * prostriedky. Alternativa: proces vrati iba prostriedky
 * uvedene vo vektore ako v predoslom pripade.
 */
void ReleaseResources(int P);

/********** Implementacia funkcii **********/
static bool VectorLE(resnum_t *X, resnum_t *Y, int n)
{
  register int i;
  for (i = 0; i < n; i++)
    if (!(X[i] <= Y[i]))
      return FALSE;
  return TRUE;
}  /***   VectorLE   ***/

static bool IsSafeStatus(status_t *S)
{
  register int i;
  bool wasChange;
  resnum_t work[MAXRES] = S->Available;    /* inicializacia vektora !!! */
  bool finish[MAXPROC] = FALSE;            /* inicializacia vektora !!! */

  do {
     wasChange = FALSE;
     for (i = 0; i < MAXPROC; i++)
        if ((finish[i] == FALSE) &&
            (S->Need[i] <= work)) /* VectorLE(S->Need[i],work,MAXRES) */
           { /* ak procesu i pridelim pozadovane prostriedky,
                tak v konecnom case uvolni vsetky alokovane */
           work += S->Allocation[i];   /* scitanie vektorov */
           finish[i] = TRUE;    /* proces i bol uspokojeny  */
           wasChange = TRUE;
           }
     }
  while (wasChange == TRUE);
  for (i = 0; i < MAXPROC; i++)
    if (finish[i] == FALSE)
      return FALSE;
  return TRUE;
}  /***   IsSafeStatus   ***/

void RequestResources(int P, resnum_t R[MAXRES])
{
  /* POZOR - viacero procesov moze ziadat prostriedky sucasne !!! */

  if (!(R <= CurrentStatus.Need[P])) /* VectorLE(R,...Need[P],MAXRES) */
    ProcessERROR(RESOURCE_LIMIT);
  while (TRUE)
     {
     if (R <= CurrentStatus.Available) /* VectorLE() */
        {
        status_t newStatus;
        /* nasleduju vektorove operacie */
        newStatus.Available = CurrentStatus.Available - R;
        newStatus.Allocation[P] = CurrentStatus.Allocation[P] + R;
        newStatus.Need[P] = CurrentStatus.Need[P] - R;
        if (IsSafeStatus(&newStatus))
           {
           CurrentStatus = newStatus;
           /* PridelProstriedky(R) */
           return;  /* TU JE VYSTUP Z ALGORITMU */
           }
        }
     WAIT(MoreResources); /* pouzite semafory & spol. */
     }
}  /***   RequestResources   ***/

void ReleaseResources(int P)
{
  /* viacero procesov moze aj uvolnovat prostriedky sucasne !!! */

  /* nasleduju vektorove operacie */
  CurrentStatus.Available += CurrentStatus.Allocation[P];
  CurrentStatus.Allocation[P] = 0;
  CurrentStatus.Need[P] = 0;
  /* mozno nejake procesy cakaju na prostriedky */

}  /***   ReleaseResources   ***/
