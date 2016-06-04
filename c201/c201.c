
/* c201.c *********************************************************************}
{* Téma: Jednosmìrný lineární seznam
**
**                     Návrh a referenèní implementace: Petr Pøikryl, øíjen 1994
**                                          Úpravy: Andrea Nìmcová listopad 1996
**                                                   Petr Pøikryl, listopad 1997
**                                Pøepracované zadání: Petr Pøikryl, bøezen 1998
**                                  Pøepis do jazyka C: Martin Tuèek, øíjen 2004
**	                                          Úpravy: Bohuslav Køena, øíjen 2008
**
** Implementujte abstraktní datový typ jednosmìrný lineární seznam.
** U¾iteèným obsahem prvku seznamu je celé èíslo typu int.
** Seznam bude jako datová abstrakce reprezentován promìnnou typu tList.
** Definici konstant a typù naleznete v hlavièkovém souboru c201.h.
** 
** Va¹ím úkolem je implementovat následující operace, které spolu s vý¹e
** uvedenou datovou èástí abstrakce tvoøí abstraktní datový typ tList:
**
**      InitList ...... inicializace seznamu pøed prvním pou¾itím,
**      DisposeList ... zru¹ení v¹ech prvkù seznamu,
**      InsertFirst ... vlo¾ení prvku na zaèátek seznamu,
**      First ......... nastavení aktivity na první prvek,
**      CopyFirst ..... vrací hodnotu prvního prvku,
**      DeleteFirst ... zru¹í první prvek seznamu,
**      PostDelete .... ru¹í prvek za aktivním prvkem,
**      PostInsert .... vlo¾í nový prvek za aktivní prvek seznamu,
**      Copy .......... vrací hodnotu aktivního prvku,
**      Actualize ..... pøepí¹e obsah aktivního prvku novou hodnotou,
**      Succ .......... posune aktivitu na dal¹í prvek seznamu,
**      Active ........ zji¹»uje aktivitu seznamu.
**
** Pøi implementaci funckí nevolejte ¾ádnou z funkcí implementovaných v rámci
** tohoto pøíkladu, není-li u funkce explicitnì uvedeno nìco jiného.
**
** Nemusíte o¹etøovat situaci, kdy místo legálního ukazatele na seznam 
** pøedá nìkdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodnì komentujte!
**
** Terminologická poznámka: Jazyk C nepou¾ívá pojem procedura.
** Proto zde pou¾íváme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c201.h"

int solved;
int errflg;

void Error()	{
/*
** Vytiskne upozornìní na to, ¾e do¹lo k chybì.
** Tuto funkci budete volat v rámci nìkterých dále implementovaných operací.
**/	
    printf ("*ERROR* Chyba pøi práci se seznamem.\n");
    errflg = TRUE;                      /* globální promìnná -- pøíznak chyby */
}

void InitList (tList *L)	{
/*
** Provede inicializaci seznamu L pøed jeho prvním pou¾itím (tzn. ¾ádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádìt nad ji¾ inicializovaným
** seznamem, a proto tuto mo¾nost neo¹etøujte. V¾dy pøedpokládejte,
** ¾e neinicializované promìnné mají nedefinovanou hodnotu.
**/

 L->Act = NULL; //Aktivní prvek nastavím na NULL
 L->First = NULL; //První prvek nastavím na NULL

}

void DisposeList (tList *L)	{
/*
** Zru¹í v¹echny prvky seznamu L a uvede seznam L do stavu, v jakém se nacházel
** po inicializaci. V¹echny prvky seznamu L budou korektnì uvolnìny voláním
** operace free.
***/

 tElemPtr pomocny; //Pomocný ukazatel na ru¹ený prvek seznamu

   while(L->First) { //Pokud seznam obsahuje platný první prvek,
    pomocny = L->First; //tak pomocný ukazatel na nìj bude ukazovat,
    L->First = L->First->ptr; //pøenastavím první prvek seznamu na následující
    free(pomocny); //a uvolním místo v pamìti po prvku seznamu,
                   //na který ukazoval mùj pomocný ukazatel
   }
   L->First = NULL; //Po konci cyklu u¾ je seznam prázdný, tak uvedu seznam
   L->Act = NULL; //do stavu, v jakém byl po inicializaci

}

void InsertFirst (tList *L, int val)	{
/*
** Vlo¾í prvek s hodnotou val na zaèátek seznamu L.
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci Error().
**/

 tElemPtr novyPrvni; //Prvek novyPrvni bude novým prvkem seznamu na zaèátku

 if(!(novyPrvni = malloc(sizeof(struct tElem)))) //Alokuji mu pamì»
  Error(); //a pokud se nepodaøilo pamì» alokovat, volám funkci Error()
 
 novyPrvni->ptr = L->First; //Následník nového prvku bude aktuální první prvek
 novyPrvni->data = val; //a do nového prvku vlo¾ím hodnotu val

 L->First = novyPrvni; //Nastavím první prvek seznamu na nový prvek
}

void First (tList *L)		{
/*
** Nastaví aktivitu seznamu L na jeho první prvek.
** Funkci implementujte jako jediný pøíkaz, ani¾ byste testovali,
** zda je seznam L prázdný.
**/
	
 L->Act = L->First; //Nastavím první prvek jako aktivní
}

void CopyFirst (tList *L, int *val)	{
/*
** Vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci Error().
**/

 if(!L->First){ //Pokud není první prvek seznamu platný,
  Error(); //tak volám funkci Error()
 }
 else { //Pokud platný je,
   *val = L->First->data; //tak ulo¾ím jeho hodnotu do val
 } 
}

void DeleteFirst (tList *L)	{
/*
** Ru¹í první prvek seznamu L. Pokud byl ru¹ený prvek aktivní, aktivita seznamu
** se ztrácí. Pokud byl seznam L prázdný, nic se nedìje!
**/

 tElemPtr ruseny; //Pomocný ukazatel na ru¹ený prvek

 if(L->First) { //Pokud je první prvek seznamu platný (seznam není prázdný)
  if(L->First == L->Act) //Jestli je první prvek aktivní,
   L->Act = NULL; //tak zru¹ím aktivitu
  ruseny = L->First; //Pomocný ukazatel nastavím na první prvek seznamu,
  L->First = ruseny->ptr; //prvním prvkem se stane prvek následující
  free(ruseny); //a uvolním pamì» pùvodního prvního prvku
 }

}	

void PostDelete (tList *L)			{
/* 
** Ru¹í prvek seznamu L za aktivním prvkem. Pokud není seznam L aktivní
** nebo pokud je aktivní poslední prvek seznamu L, nic se nedìje!
**/
	
 tElemPtr ruseny; //Pomocný ukazatel na ru¹ený prvek
 
 if((L->Act) && (L->Act->ptr)) { //Pokud je seznam aktivní a aktivita není
                                 //na posledním prvku seznamu,
  ruseny = L->Act->ptr; //pomocný ukazatel ukazuje na ru¹ený prvek za aktivním
  L->Act->ptr = L->Act->ptr->ptr; //a nastavím nový následující prvek aktivního
  free(ruseny); //Uvolním pamì» po ru¹eném prvku seznamu
 }

}

void PostInsert (tList *L, int val)	{
/*
** Vlo¾í prvek s hodnotou val za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se nedìje!
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci Error().
**/

 tElemPtr novyZaAktivnim; //Pomocný prvek pro nový prvek za aktivním prvkem

 if(L->Act) { //Pokud je seznam aktivní,

   if(!(novyZaAktivnim = malloc(sizeof(struct tElem)))) //alokuji mu pamì»
    Error(); ////a pokud se nepodaøilo pamì» alokovat, volám funkci Error()
   
   novyZaAktivnim->ptr = L->Act->ptr; //Nastavím následný prvek novému prvku
   novyZaAktivnim->data = val; //a dám novému prvku hodnotu val
  
   L->Act->ptr = novyZaAktivnim; //Nový prvek se stane následníkem aktivního
 }

}

void Copy (tList *L, int *val)		{
/*
** Vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam není aktivní, volá se funkce Error().
**/

 if(!L->Act){ //Pokud není seznam aktivní,
  Error(); //volám funkci Error()
 }
 else { //Pokud aktivní je,
   *val = L->Act->data; //nastavím val na hodnotu aktivního prvku
 }

}

void Actualize (tList *L, int val)	{
/*
** Pøepí¹e data aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedìlá nic!
**/
	
 if(L->Act) //Pokud je seznam aktivní,
  L->Act->data = val; //nastavím aktivnímu prvku novou hodnotu val
}

void Succ (tList *L)	{
/*
** Posune aktivitu na následující prvek seznamu L.
** V¹imnìte si, ¾e touto operací se mù¾e aktivní seznam stát neaktivním.
** Pokud seznam L není aktivní, nedìlá nic!
**/

 if(L->Act) //Pokud je seznam aktivní,
  L->Act = L->Act->ptr; //nastavím aktivitu na následující prvek aktivního

}

int Active (tList *L) 	{		
/*
** Je-li seznam L aktivní, vrací True. V opaèném pøípadì vrací false.
** Tuto funkci implementujte jako jediný pøíkaz return. 
**/
 
 return (L->Act) ? TRUE : FALSE; //Podmínìný výraz, pokud je seznam aktivní,
                                 //vrací TRUE, jinak vrací FALSE
}

/* Konec c201.c */
