	
/* c206.c **********************************************************}
{* Téma: Dvousmìrnì vázaný lineární seznam
**
**                   Návrh a referenèní implementace: Bohuslav Køena, øíjen 2001
**                            Pøepracované do jazyka C: Martin Tuèek, øíjen 2004
**                                            Úpravy: Bohuslav Køena, øíjen 2008
**
** Implementujte abstraktní datový typ dvousmìrnì vázaný lineární seznam.
** U¾iteèným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován promìnnou
** typu tDLList (DL znamená Double-Linked a slou¾í pro odli¹ení
** jmen konstant, typù a funkcí od jmen u jednosmìrnì vázaného lineárního
** seznamu). Definici konstant a typù naleznete v hlavièkovém souboru c206.h.
**
** Va¹ím úkolem je implementovat následující operace, které spolu
** s vý¹e uvedenou datovou èástí abstrakce tvoøí abstraktní datový typ
** obousmìrnì vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu pøed prvním pou¾itím,
**      DLDisposeList ... zru¹ení v¹ech prvkù seznamu,
**      DLInsertFirst ... vlo¾ení prvku na zaèátek seznamu,
**      DLInsertLast .... vlo¾ení prvku na konec seznamu, 
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek, 
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku, 
**      DLDeleteFirst ... zru¹í první prvek seznamu,
**      DLDeleteLast .... zru¹í poslední prvek seznamu, 
**      DLPostDelete .... ru¹í prvek za aktivním prvkem,
**      DLPreDelete ..... ru¹í prvek pøed aktivním prvkem, 
**      DLPostInsert .... vlo¾í nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vlo¾í nový prvek pøed aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... pøepí¹e obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na dal¹í prvek seznamu,
**      DLPred .......... posune aktivitu na pøedchozí prvek seznamu, 
**      DLActive ........ zji¹»uje aktivitu seznamu.
**
** Pøi implementaci jednotlivých funckí nevolejte ¾ádnou z funkcí
** implementovaných v rámci tohoto pøíkladu, není-li u funkce
** explicitnì uvedeno nìco jiného.
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

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozornìní na to, ¾e do¹lo k chybì.
** Tuto funkci budete volat v rámci nìkterých dále implementovaných operací.
**/	
    printf ("*ERROR* Chyba pøi práci se seznamem.\n");
    errflg = TRUE;             /* globální promìnná -- pøíznak o¹etøení chyby */
    return;
}

void DLInitList (tDLList *L)	{
/*
** Provede inicializaci seznamu L pøed jeho prvním pou¾itím (tzn. ¾ádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádìt nad ji¾ inicializovaným
** seznamem, a proto tuto mo¾nost neo¹etøujte. V¾dy pøedpokládejte,
** ¾e neinicializované promìnné mají nedefinovanou hodnotu.
**/
    
 L->First = NULL; //Nastavím první prvek seznamu na NULL
 L->Act = NULL; //Nastavím aktivní prvek seznamu na NULL
 L->Last = NULL; //Nastavím poslední prvek seznamu na NULL

}

void DLDisposeList (tDLList *L)	{
/*
** Zru¹í v¹echny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Ru¹ené prvky seznamu budou korektnì
** uvolnìny voláním operace free. 
**/
	
 tDLElemPtr ruseny; //Pomocný ukazatel na ru¹ený prvek seznamu
 
 while(L->First) { //Pokud není seznam prázdný,
  ruseny = L->First; //nastavím pomocný ukazatel na první prvek seznamu,
  L->First = L->First->rptr; //zaèátek seznamu nastavím na následující prvek
  free(ruseny); //a uvolním pamì» po pùvodním prvním prvku seznamu
 }
 
 L->First = NULL; //Kdy¾ je seznam prázdný,
 L->Act = NULL; //nastavím jeho hodnoty do stavu,
 L->Last = NULL; //ve kterém byly po inicializaci seznamu

}

void DLInsertFirst (tDLList *L, int val)	{
/*
** Vlo¾í nový prvek na zaèátek seznamu L.
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/

 tDLElemPtr novyPrvni; //Pomocný ukazatel na nový první prvek seznamu
 
 if(!(novyPrvni = malloc(sizeof(struct tDLElem)))) //Alokuji mu pamì»
  DLError(); //Pokud se nepodaøilo pøidìlit pamì», volám funkci DLError()
 else { //Pokud má pamì» pøidìlenou,
  novyPrvni->data = val; //nastavím jeho hodnotu na hodnotu val,
  novyPrvni->lptr = NULL; //levého souseda prvku na NULL,
  novyPrvni->rptr = L->First; //pravého souseda prvku na pøedchozí první prvek,
  if(L->First) //Pokud není seznam prázdný,
   L->First->lptr = novyPrvni; //nový prvek je levým sousedem prvku prvního
  else //Pokud seznam je prázdný, 
   L->Last = novyPrvni; //stane se nový prvek posledním prvkem
  L->First = novyPrvni; //a zároveò prvek prvním
 }

}

void DLInsertLast(tDLList *L, int val)	{
/*
** Vlo¾í nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/ 	
	
 tDLElemPtr novyPosledni; //Pomocný ukazatel na nový poslední prvek seznamu
 
 if(!(novyPosledni = malloc(sizeof(struct tDLElem)))) //Pokud se nepodaøí novému
  DLError(); //poslednímu prvku pøidìlit pamì», volám funkci DLError()
 else { //Pokud nový poslední prvek pamì» dostal,
  novyPosledni->data = val; //nastavím jeho hodnotu na hodnotu val,
  novyPosledni->lptr = L->Last; //jeho levý soused bude pùvodní poslední prvek,
  novyPosledni->rptr = NULL; //pravým sousedem není ¾ádný prvek,
  if(L->Last) //Pokud není seznam prázdný,
   L->Last->rptr = novyPosledni; //nový prvek je právý soused prvku posledního
  else //Pokud je seznam prázdný,
   L->First = novyPosledni; //je nový poslední prvek i prvkem prvním
  L->Last = novyPosledni; //a samozøejmì i prvkem posledním
 }

}

void DLFirst (tDLList *L)	{
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný pøíkaz (nepoèítáme-li return),
** ani¾ byste testovali, zda je seznam L prázdný.
**/
	
 L->Act = L->First; //Nastaví aktivitu seznamu na první prvek seznamu

}

void DLLast (tDLList *L)	{
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný pøíkaz (nepoèítáme-li return),
** ani¾ byste testovali, zda je seznam L prázdný.
**/
	
 L->Act = L->Last; //Nastaví aktivitu seznamu na poslední prvek seznamu

}

void DLCopyFirst (tDLList *L, int *val)	{
/*
** Vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

 if(!L->First) //Pokud je seznam prázdný,
  DLError(); //volám funkci DLError()
 else //Pokud seznam prázdný není,
  *val = L->First->data; //ulo¾ím do promìnné val hodnotu prvního prvku

}

void DLCopyLast (tDLList *L, int *val)	{
/*
** Vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
	
 if(!L->Last) //Pokud je seznam prázdný,
  DLError(); //volám funkci DLError()
 else //Pokud prázdný není,
  *val = L->Last->data; //ulo¾ím do promìnné val hodnotu posledního prvku
}

void DLDeleteFirst (tDLList *L)	{
/*
** Zru¹í první prvek seznamu L. Pokud byl první prvek aktivní, aktivita 
** se ztrácí. Pokud byl seznam L prázdný, nic se nedìje.
**/
	
 tDLElemPtr ruseny; //Pomocný ukazatel na ru¹ený prvek
 
 if(L->First) { //Pokud není seznam prázdný,
  ruseny = L->First; //pomocný ukazatel ukazuje na ru¹ený prvek
  if(L->Act == L->First) //Pokud byl první prvek aktivní,
   L->Act = NULL; //zru¹ím aktivitu seznamu
  if(L->First == L->Last) { //Pokud byl ru¹ený prvek jediným prvkem seznamu,
   L->Last = NULL; //vrátím jeho hodnoty do stavu,
   L->First = NULL; //ve kterém byl po inicializaci
  }
  else { //Pokud nebyl ru¹ený prvek jediným prvkem seznamu,
   L->First = L->First->rptr; //nastavím první prvek na prvek následující
   L->First->lptr = NULL; //a tím nemá nový první prvek levého souseda
  }
  free(ruseny); //Uvolním pamì» po ru¹eném prvku
 }

}	

void DLDeleteLast (tDLList *L)	{
/*
** Zru¹í poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se nedìje.
**/ 
	
	
 tDLElemPtr ruseny; //Pomocný ukazatel na ru¹ený prvek
 
 if(L->Last) { //Pokud seznam není prázdný,
  ruseny = L->Last; //pomocný ukazatel ukazuje na ru¹ený prvek
  if(L->Act == L->Last) //Pokud byl ru¹ený prvek prvkem aktivním,
   L->Act = NULL; //aktivita se ztrácí
  if(L->First == L->Last) { //Pokud byl ru¹ený prvek jediným prvkem seznamu,
   L->Last = NULL; //nastavím hodnoty seznamu na hodnoty,
   L->First = NULL; //které mìl po inicializaci
  }
  else { //Kdy¾ ru¹ený prvek nebyl jediným prvkem seznamu,
   L->Last = L->Last->lptr; //nastavím poslední prvek na prvek pøedcházející
   L->Last->rptr = NULL; //a tudí¾ poslední prvek seznamu nemá pravého souseda
  }
  free(ruseny); //Uvolním pamì» po ru¹eném prvku
 }
}

void DLPostDelete (tDLList *L)	{
/*
** Zru¹í prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se nedìje.
**/
	
 tDLElemPtr ruseny; //Pomocný ukazatel na ru¹ený prvek
 
 if(L->Act) { //Pokud je seznam aktivní
  if(L->Act->rptr) { //a pokud má aktivní prvek pravého souseda,
   ruseny = L->Act->rptr; //pomocný ukazatel ukazuje na ru¹ený prvek,
   L->Act->rptr = ruseny->rptr; //nastavím nový pravý prvek aktivního prvku
   if(ruseny == L->Last) { //Pokud byl ru¹ený prvek poslední,
    L->Last = L->Act; //stane se aktivní prvek prvkem posledním
   }
   else { //Pokud nebyl ru¹ený prvek poslední,
    ruseny->rptr->lptr = L->Act; //musím nastavit prvku následujícímu po ru¹eném
                                 //levého souseda na prvek aktivní
   }
   free(ruseny); //Uvolním pamì» po ru¹eném prvku
  }
 }		

}

void DLPreDelete (tDLList *L)	{
/*
** Zru¹í prvek pøed aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se nedìje.
**/
	
 tDLElemPtr ruseny; //Pomocný ukazatel na ru¹ený prvek
 
 if(L->Act) { //Pokud je seznam aktivní
  if(L->Act->lptr) {//a pokud má aktivní prvek levého souseda,
   ruseny = L->Act->lptr; //pomocný ukazatel ukazuje na pøedcházející prvek
                          //prvku aktivního
   L->Act->lptr = ruseny->lptr; //Musíme aktivnímu prvku nastavit nový
                                //pøedcházející prvek na prvek pøedcházející
                                //ru¹enému
   if(ruseny == L->First) { //Pokud byl ru¹ený prvek prvkem prvním,
    L->First = L->Act; //nastavím první prvek na prvek aktivní
   }
   else { //Pokud nebyl ru¹ený prvek prvním,
    ruseny->lptr->rptr = L->Act; //nastavím pøedcházejícímu prvku pøed ru¹eným
                                 //následný prvek na prvek aktivní
   }
   free(ruseny); //Uvolním pamì» po ru¹eném prvku
  }
 }

}

void DLPostInsert (tDLList *L, int val) {
/*
** Vlo¾í prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se nedìje.
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/
	
 tDLElemPtr novyPoAktivnim; //Pomocný ukazatel na nový prvek za aktivním

 if(L->Act) { //Kdy¾ je seznam aktivní
  if(!(novyPoAktivnim = malloc(sizeof(struct tDLElem)))) //Alokuji novému pamì»
   DLError(); //Pokud mu nebyla pamì» pøidìlena, volám funkci DLError()
  else { //Pokud nový prvek pamì» dostal,
   novyPoAktivnim->data = val; //nastavím jeho hodnotu na hodnotu val,
   novyPoAktivnim->rptr = L->Act->rptr; //následující prvek nového je prvek
                                        //následující po aktivním,
   novyPoAktivnim->lptr = L->Act; //pøedchozí prvek nového je prvek aktivní,
   L->Act->rptr = novyPoAktivnim; //následující prvek po aktivním je nový prvek,
   if(L->Act == L->Last) //Pokud byl aktivní prvek poslední,
    L->Last = novyPoAktivnim; //stane se posledním prvkem nový prvek
   else //Pokud nebyl aktivní prvek posledním,
    novyPoAktivnim->rptr->lptr = novyPoAktivnim; //následující prvek po aktivním
                                                 //bude mít jako pøedcházející
                                                 //prvek novì vkládaný prvek
  }
 }
}

void DLPreInsert (tDLList *L, int val)		{
/*
** Vlo¾í prvek pøed aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se nedìje.
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/
	
 tDLElemPtr novyPredAktivnim; //Pomocný ukazatel na nový prvek

 if(L->Act) { //Kdy¾ je seznam aktivní
  if(!(novyPredAktivnim = malloc(sizeof(struct tDLElem)))) //Alokuj novému pamì»
   DLError(); //Pokud pamì» nebyla pøidìlena, volám funkci DLError()
  else { //Pokud nový prvek pamì» dostal,
   novyPredAktivnim->data = val; //nastavím mu hodnotu na hodnotu val,
   novyPredAktivnim->rptr = L->Act; //následující prvek je prvek aktivní,
   novyPredAktivnim->lptr = L->Act->lptr; //pøedcházející prvek je prvek,
                                          //který pøedcházel aktivnímu,
   L->Act->lptr = novyPredAktivnim; //nový prvek je pøedcházející aktivnímu,
   if(L->Act == L->First) //Pokud byl aktivním prvek první,
    L->First = novyPredAktivnim; //bude prvním prvkem nový prvek,
   else //Pokud nebyl aktivní prvek prvním prvkem,
    novyPredAktivnim->lptr->rptr = novyPredAktivnim; //bude následující prvek
                                                     //prvku pøedchozího
                                                     //nový prvek
  }
 }
} 

void DLCopy (tDLList *L, int *val)	{
/*
** Vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/
		
 if(!L->Act) //Pokud není seznam aktivní,
  DLError(); //volám funkci DLError()
 else //Pokud seznam aktivní je,
  *val = L->Act->data; //ulo¾ím do promìnné val hodnotu aktivního prvku

}

void DLActualize (tDLList *L, int val) {
/*
** Pøepí¹e obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedìlá nic.
**/
	
 if(L->Act) //Pokud je seznam aktivní,
  L->Act->data = val;	//nová hodnota aktivního prvku bude hodnota val

}

void DLSucc (tDLList *L)	{
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedìlá nic.
** V¹imnìte si, ¾e pøi aktivitì na posledním prvku se seznam stane neaktivním.
**/
	
 if(L->Act) //Pokud je seznam aktivní,
  L->Act = L->Act->rptr; //posunu aktivitu na prvek následující aktivnímu

}


void DLPred (tDLList *L)	{
/*
** Posune aktivitu na pøedchozí prvek seznamu L.
** Není-li seznam aktivní, nedìlá nic.
** V¹imnìte si, ¾e pøi aktivitì na prvním prvku se seznam stane neaktivním.
**/
	
 if(L->Act) //Pokud je seznam aktivní,
  L->Act = L->Act->lptr; //posunu aktivitu seznamu na prvek pøed aktivním

}

int DLActive (tDLList *L) {		
/*
** Je-li seznam aktivní, vrací true. V opaèném pøípadì vrací false.
** Funkci implementujte jako jediný pøíkaz.
**/
	
 return (L->Act) ? TRUE : FALSE; //Podmínìný výraz, kdy¾ je seznam aktivní,
                                 //vrací TRUE, jinak vrací FALSE

}

/* Konec c206.c*/
