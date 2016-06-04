
/* c201.c *********************************************************************}
{* T�ma: Jednosm�rn� line�rn� seznam
**
**                     N�vrh a referen�n� implementace: Petr P�ikryl, ��jen 1994
**                                          �pravy: Andrea N�mcov� listopad 1996
**                                                   Petr P�ikryl, listopad 1997
**                                P�epracovan� zad�n�: Petr P�ikryl, b�ezen 1998
**                                  P�epis do jazyka C: Martin Tu�ek, ��jen 2004
**	                                          �pravy: Bohuslav K�ena, ��jen 2008
**
** Implementujte abstraktn� datov� typ jednosm�rn� line�rn� seznam.
** U�ite�n�m obsahem prvku seznamu je cel� ��slo typu int.
** Seznam bude jako datov� abstrakce reprezentov�n prom�nnou typu tList.
** Definici konstant a typ� naleznete v hlavi�kov�m souboru c201.h.
** 
** Va��m �kolem je implementovat n�sleduj�c� operace, kter� spolu s v��e
** uvedenou datovou ��st� abstrakce tvo�� abstraktn� datov� typ tList:
**
**      InitList ...... inicializace seznamu p�ed prvn�m pou�it�m,
**      DisposeList ... zru�en� v�ech prvk� seznamu,
**      InsertFirst ... vlo�en� prvku na za��tek seznamu,
**      First ......... nastaven� aktivity na prvn� prvek,
**      CopyFirst ..... vrac� hodnotu prvn�ho prvku,
**      DeleteFirst ... zru�� prvn� prvek seznamu,
**      PostDelete .... ru�� prvek za aktivn�m prvkem,
**      PostInsert .... vlo�� nov� prvek za aktivn� prvek seznamu,
**      Copy .......... vrac� hodnotu aktivn�ho prvku,
**      Actualize ..... p�ep�e obsah aktivn�ho prvku novou hodnotou,
**      Succ .......... posune aktivitu na dal�� prvek seznamu,
**      Active ........ zji��uje aktivitu seznamu.
**
** P�i implementaci funck� nevolejte ��dnou z funkc� implementovan�ch v r�mci
** tohoto p��kladu, nen�-li u funkce explicitn� uvedeno n�co jin�ho.
**
** Nemus�te o�et�ovat situaci, kdy m�sto leg�ln�ho ukazatele na seznam 
** p�ed� n�kdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodn� komentujte!
**
** Terminologick� pozn�mka: Jazyk C nepou��v� pojem procedura.
** Proto zde pou��v�me pojem funkce i pro operace, kter� by byly
** v algoritmick�m jazyce Pascalovsk�ho typu implemenov�ny jako
** procedury (v jazyce C procedur�m odpov�daj� funkce vracej�c� typ void).
**/

#include "c201.h"

int solved;
int errflg;

void Error()	{
/*
** Vytiskne upozorn�n� na to, �e do�lo k chyb�.
** Tuto funkci budete volat v r�mci n�kter�ch d�le implementovan�ch operac�.
**/	
    printf ("*ERROR* Chyba p�i pr�ci se seznamem.\n");
    errflg = TRUE;                      /* glob�ln� prom�nn� -- p��znak chyby */
}

void InitList (tList *L)	{
/*
** Provede inicializaci seznamu L p�ed jeho prvn�m pou�it�m (tzn. ��dn�
** z n�sleduj�c�ch funkc� nebude vol�na nad neinicializovan�m seznamem).
** Tato inicializace se nikdy nebude prov�d�t nad ji� inicializovan�m
** seznamem, a proto tuto mo�nost neo�et�ujte. V�dy p�edpokl�dejte,
** �e neinicializovan� prom�nn� maj� nedefinovanou hodnotu.
**/

 L->Act = NULL; //Aktivn� prvek nastav�m na NULL
 L->First = NULL; //Prvn� prvek nastav�m na NULL

}

void DisposeList (tList *L)	{
/*
** Zru�� v�echny prvky seznamu L a uvede seznam L do stavu, v jak�m se nach�zel
** po inicializaci. V�echny prvky seznamu L budou korektn� uvoln�ny vol�n�m
** operace free.
***/

 tElemPtr pomocny; //Pomocn� ukazatel na ru�en� prvek seznamu

   while(L->First) { //Pokud seznam obsahuje platn� prvn� prvek,
    pomocny = L->First; //tak pomocn� ukazatel na n�j bude ukazovat,
    L->First = L->First->ptr; //p�enastav�m prvn� prvek seznamu na n�sleduj�c�
    free(pomocny); //a uvoln�m m�sto v pam�ti po prvku seznamu,
                   //na kter� ukazoval m�j pomocn� ukazatel
   }
   L->First = NULL; //Po konci cyklu u� je seznam pr�zdn�, tak uvedu seznam
   L->Act = NULL; //do stavu, v jak�m byl po inicializaci

}

void InsertFirst (tList *L, int val)	{
/*
** Vlo�� prvek s hodnotou val na za��tek seznamu L.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci Error().
**/

 tElemPtr novyPrvni; //Prvek novyPrvni bude nov�m prvkem seznamu na za��tku

 if(!(novyPrvni = malloc(sizeof(struct tElem)))) //Alokuji mu pam�
  Error(); //a pokud se nepoda�ilo pam� alokovat, vol�m funkci Error()
 
 novyPrvni->ptr = L->First; //N�sledn�k nov�ho prvku bude aktu�ln� prvn� prvek
 novyPrvni->data = val; //a do nov�ho prvku vlo��m hodnotu val

 L->First = novyPrvni; //Nastav�m prvn� prvek seznamu na nov� prvek
}

void First (tList *L)		{
/*
** Nastav� aktivitu seznamu L na jeho prvn� prvek.
** Funkci implementujte jako jedin� p��kaz, ani� byste testovali,
** zda je seznam L pr�zdn�.
**/
	
 L->Act = L->First; //Nastav�m prvn� prvek jako aktivn�
}

void CopyFirst (tList *L, int *val)	{
/*
** Vr�t� hodnotu prvn�ho prvku seznamu L.
** Pokud je seznam L pr�zdn�, vol� funkci Error().
**/

 if(!L->First){ //Pokud nen� prvn� prvek seznamu platn�,
  Error(); //tak vol�m funkci Error()
 }
 else { //Pokud platn� je,
   *val = L->First->data; //tak ulo��m jeho hodnotu do val
 } 
}

void DeleteFirst (tList *L)	{
/*
** Ru�� prvn� prvek seznamu L. Pokud byl ru�en� prvek aktivn�, aktivita seznamu
** se ztr�c�. Pokud byl seznam L pr�zdn�, nic se ned�je!
**/

 tElemPtr ruseny; //Pomocn� ukazatel na ru�en� prvek

 if(L->First) { //Pokud je prvn� prvek seznamu platn� (seznam nen� pr�zdn�)
  if(L->First == L->Act) //Jestli je prvn� prvek aktivn�,
   L->Act = NULL; //tak zru��m aktivitu
  ruseny = L->First; //Pomocn� ukazatel nastav�m na prvn� prvek seznamu,
  L->First = ruseny->ptr; //prvn�m prvkem se stane prvek n�sleduj�c�
  free(ruseny); //a uvoln�m pam� p�vodn�ho prvn�ho prvku
 }

}	

void PostDelete (tList *L)			{
/* 
** Ru�� prvek seznamu L za aktivn�m prvkem. Pokud nen� seznam L aktivn�
** nebo pokud je aktivn� posledn� prvek seznamu L, nic se ned�je!
**/
	
 tElemPtr ruseny; //Pomocn� ukazatel na ru�en� prvek
 
 if((L->Act) && (L->Act->ptr)) { //Pokud je seznam aktivn� a aktivita nen�
                                 //na posledn�m prvku seznamu,
  ruseny = L->Act->ptr; //pomocn� ukazatel ukazuje na ru�en� prvek za aktivn�m
  L->Act->ptr = L->Act->ptr->ptr; //a nastav�m nov� n�sleduj�c� prvek aktivn�ho
  free(ruseny); //Uvoln�m pam� po ru�en�m prvku seznamu
 }

}

void PostInsert (tList *L, int val)	{
/*
** Vlo�� prvek s hodnotou val za aktivn� prvek seznamu L.
** Pokud nebyl seznam L aktivn�, nic se ned�je!
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci Error().
**/

 tElemPtr novyZaAktivnim; //Pomocn� prvek pro nov� prvek za aktivn�m prvkem

 if(L->Act) { //Pokud je seznam aktivn�,

   if(!(novyZaAktivnim = malloc(sizeof(struct tElem)))) //alokuji mu pam�
    Error(); ////a pokud se nepoda�ilo pam� alokovat, vol�m funkci Error()
   
   novyZaAktivnim->ptr = L->Act->ptr; //Nastav�m n�sledn� prvek nov�mu prvku
   novyZaAktivnim->data = val; //a d�m nov�mu prvku hodnotu val
  
   L->Act->ptr = novyZaAktivnim; //Nov� prvek se stane n�sledn�kem aktivn�ho
 }

}

void Copy (tList *L, int *val)		{
/*
** Vr�t� hodnotu aktivn�ho prvku seznamu L.
** Pokud seznam nen� aktivn�, vol� se funkce Error().
**/

 if(!L->Act){ //Pokud nen� seznam aktivn�,
  Error(); //vol�m funkci Error()
 }
 else { //Pokud aktivn� je,
   *val = L->Act->data; //nastav�m val na hodnotu aktivn�ho prvku
 }

}

void Actualize (tList *L, int val)	{
/*
** P�ep�e data aktivn�ho prvku seznamu L.
** Pokud seznam L nen� aktivn�, ned�l� nic!
**/
	
 if(L->Act) //Pokud je seznam aktivn�,
  L->Act->data = val; //nastav�m aktivn�mu prvku novou hodnotu val
}

void Succ (tList *L)	{
/*
** Posune aktivitu na n�sleduj�c� prvek seznamu L.
** V�imn�te si, �e touto operac� se m��e aktivn� seznam st�t neaktivn�m.
** Pokud seznam L nen� aktivn�, ned�l� nic!
**/

 if(L->Act) //Pokud je seznam aktivn�,
  L->Act = L->Act->ptr; //nastav�m aktivitu na n�sleduj�c� prvek aktivn�ho

}

int Active (tList *L) 	{		
/*
** Je-li seznam L aktivn�, vrac� True. V opa�n�m p��pad� vrac� false.
** Tuto funkci implementujte jako jedin� p��kaz return. 
**/
 
 return (L->Act) ? TRUE : FALSE; //Podm�n�n� v�raz, pokud je seznam aktivn�,
                                 //vrac� TRUE, jinak vrac� FALSE
}

/* Konec c201.c */
