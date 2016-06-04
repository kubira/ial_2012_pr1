
/* P�edm�t: Algoritmy (IAL) - FIT VUT v Brn�
 * Hlavi�kov� soubor pro c201.c (Jednosm�rn� v�zan� line�rn� seznam)
 * Vytvo�il: Martin Tu�ek, z��� 2005
 * Upravil: Bohuslav K�ena, ��jen 2008
 * 
 *
 * Tento soubor, pros�me, neupravujte! 
 */
 
#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

#define TRUE 1
#define FALSE 0

#define RESENO 1
#define NERESENO 0

extern int solved;                         /* Indikace, zda byl p��klad �e�en */
extern int errflg;                                          /* Indikace chyby */

typedef struct tElem {                                       /* Prvek seznamu */
    struct tElem *ptr;
    int data;
} *tElemPtr;	
                                                         
typedef struct {                                            /* Vlastn� seznam */
    tElemPtr Act;
    tElemPtr First;
} tList;
                                                   /* Funkce pro implementaci */
void InitList (tList *);
void DisposeList (tList *);
void InsertFirst (tList *, int);
void First (tList *);
void CopyFirst (tList *, int *);
void DeleteFirst (tList *);
void PostDelete (tList *);
void PostInsert (tList *, int);
void Succ (tList *);
void Copy (tList *, int *);	
void Actualize (tList *, int );
int  Active (tList *);

