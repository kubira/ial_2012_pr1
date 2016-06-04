	
/* c206.c **********************************************************}
{* T�ma: Dvousm�rn� v�zan� line�rn� seznam
**
**                   N�vrh a referen�n� implementace: Bohuslav K�ena, ��jen 2001
**                            P�epracovan� do jazyka C: Martin Tu�ek, ��jen 2004
**                                            �pravy: Bohuslav K�ena, ��jen 2008
**
** Implementujte abstraktn� datov� typ dvousm�rn� v�zan� line�rn� seznam.
** U�ite�n�m obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datov� abstrakce reprezentov�n prom�nnou
** typu tDLList (DL znamen� Double-Linked a slou�� pro odli�en�
** jmen konstant, typ� a funkc� od jmen u jednosm�rn� v�zan�ho line�rn�ho
** seznamu). Definici konstant a typ� naleznete v hlavi�kov�m souboru c206.h.
**
** Va��m �kolem je implementovat n�sleduj�c� operace, kter� spolu
** s v��e uvedenou datovou ��st� abstrakce tvo�� abstraktn� datov� typ
** obousm�rn� v�zan� line�rn� seznam:
**
**      DLInitList ...... inicializace seznamu p�ed prvn�m pou�it�m,
**      DLDisposeList ... zru�en� v�ech prvk� seznamu,
**      DLInsertFirst ... vlo�en� prvku na za��tek seznamu,
**      DLInsertLast .... vlo�en� prvku na konec seznamu, 
**      DLFirst ......... nastaven� aktivity na prvn� prvek,
**      DLLast .......... nastaven� aktivity na posledn� prvek, 
**      DLCopyFirst ..... vrac� hodnotu prvn�ho prvku,
**      DLCopyLast ...... vrac� hodnotu posledn�ho prvku, 
**      DLDeleteFirst ... zru�� prvn� prvek seznamu,
**      DLDeleteLast .... zru�� posledn� prvek seznamu, 
**      DLPostDelete .... ru�� prvek za aktivn�m prvkem,
**      DLPreDelete ..... ru�� prvek p�ed aktivn�m prvkem, 
**      DLPostInsert .... vlo�� nov� prvek za aktivn� prvek seznamu,
**      DLPreInsert ..... vlo�� nov� prvek p�ed aktivn� prvek seznamu,
**      DLCopy .......... vrac� hodnotu aktivn�ho prvku,
**      DLActualize ..... p�ep�e obsah aktivn�ho prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na dal�� prvek seznamu,
**      DLPred .......... posune aktivitu na p�edchoz� prvek seznamu, 
**      DLActive ........ zji��uje aktivitu seznamu.
**
** P�i implementaci jednotliv�ch funck� nevolejte ��dnou z funkc�
** implementovan�ch v r�mci tohoto p��kladu, nen�-li u funkce
** explicitn� uvedeno n�co jin�ho.
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

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozorn�n� na to, �e do�lo k chyb�.
** Tuto funkci budete volat v r�mci n�kter�ch d�le implementovan�ch operac�.
**/	
    printf ("*ERROR* Chyba p�i pr�ci se seznamem.\n");
    errflg = TRUE;             /* glob�ln� prom�nn� -- p��znak o�et�en� chyby */
    return;
}

void DLInitList (tDLList *L)	{
/*
** Provede inicializaci seznamu L p�ed jeho prvn�m pou�it�m (tzn. ��dn�
** z n�sleduj�c�ch funkc� nebude vol�na nad neinicializovan�m seznamem).
** Tato inicializace se nikdy nebude prov�d�t nad ji� inicializovan�m
** seznamem, a proto tuto mo�nost neo�et�ujte. V�dy p�edpokl�dejte,
** �e neinicializovan� prom�nn� maj� nedefinovanou hodnotu.
**/
    
 L->First = NULL; //Nastav�m prvn� prvek seznamu na NULL
 L->Act = NULL; //Nastav�m aktivn� prvek seznamu na NULL
 L->Last = NULL; //Nastav�m posledn� prvek seznamu na NULL

}

void DLDisposeList (tDLList *L)	{
/*
** Zru�� v�echny prvky seznamu L a uvede seznam do stavu, v jak�m
** se nach�zel po inicializaci. Ru�en� prvky seznamu budou korektn�
** uvoln�ny vol�n�m operace free. 
**/
	
 tDLElemPtr ruseny; //Pomocn� ukazatel na ru�en� prvek seznamu
 
 while(L->First) { //Pokud nen� seznam pr�zdn�,
  ruseny = L->First; //nastav�m pomocn� ukazatel na prvn� prvek seznamu,
  L->First = L->First->rptr; //za��tek seznamu nastav�m na n�sleduj�c� prvek
  free(ruseny); //a uvoln�m pam� po p�vodn�m prvn�m prvku seznamu
 }
 
 L->First = NULL; //Kdy� je seznam pr�zdn�,
 L->Act = NULL; //nastav�m jeho hodnoty do stavu,
 L->Last = NULL; //ve kter�m byly po inicializaci seznamu

}

void DLInsertFirst (tDLList *L, int val)	{
/*
** Vlo�� nov� prvek na za��tek seznamu L.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
**/

 tDLElemPtr novyPrvni; //Pomocn� ukazatel na nov� prvn� prvek seznamu
 
 if(!(novyPrvni = malloc(sizeof(struct tDLElem)))) //Alokuji mu pam�
  DLError(); //Pokud se nepoda�ilo p�id�lit pam�, vol�m funkci DLError()
 else { //Pokud m� pam� p�id�lenou,
  novyPrvni->data = val; //nastav�m jeho hodnotu na hodnotu val,
  novyPrvni->lptr = NULL; //lev�ho souseda prvku na NULL,
  novyPrvni->rptr = L->First; //prav�ho souseda prvku na p�edchoz� prvn� prvek,
  if(L->First) //Pokud nen� seznam pr�zdn�,
   L->First->lptr = novyPrvni; //nov� prvek je lev�m sousedem prvku prvn�ho
  else //Pokud seznam je pr�zdn�, 
   L->Last = novyPrvni; //stane se nov� prvek posledn�m prvkem
  L->First = novyPrvni; //a z�rove� prvek prvn�m
 }

}

void DLInsertLast(tDLList *L, int val)	{
/*
** Vlo�� nov� prvek na konec seznamu L (symetrick� operace k DLInsertFirst).
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
**/ 	
	
 tDLElemPtr novyPosledni; //Pomocn� ukazatel na nov� posledn� prvek seznamu
 
 if(!(novyPosledni = malloc(sizeof(struct tDLElem)))) //Pokud se nepoda�� nov�mu
  DLError(); //posledn�mu prvku p�id�lit pam�, vol�m funkci DLError()
 else { //Pokud nov� posledn� prvek pam� dostal,
  novyPosledni->data = val; //nastav�m jeho hodnotu na hodnotu val,
  novyPosledni->lptr = L->Last; //jeho lev� soused bude p�vodn� posledn� prvek,
  novyPosledni->rptr = NULL; //prav�m sousedem nen� ��dn� prvek,
  if(L->Last) //Pokud nen� seznam pr�zdn�,
   L->Last->rptr = novyPosledni; //nov� prvek je pr�v� soused prvku posledn�ho
  else //Pokud je seznam pr�zdn�,
   L->First = novyPosledni; //je nov� posledn� prvek i prvkem prvn�m
  L->Last = novyPosledni; //a samoz�ejm� i prvkem posledn�m
 }

}

void DLFirst (tDLList *L)	{
/*
** Nastav� aktivitu na prvn� prvek seznamu L.
** Funkci implementujte jako jedin� p��kaz (nepo��t�me-li return),
** ani� byste testovali, zda je seznam L pr�zdn�.
**/
	
 L->Act = L->First; //Nastav� aktivitu seznamu na prvn� prvek seznamu

}

void DLLast (tDLList *L)	{
/*
** Nastav� aktivitu na posledn� prvek seznamu L.
** Funkci implementujte jako jedin� p��kaz (nepo��t�me-li return),
** ani� byste testovali, zda je seznam L pr�zdn�.
**/
	
 L->Act = L->Last; //Nastav� aktivitu seznamu na posledn� prvek seznamu

}

void DLCopyFirst (tDLList *L, int *val)	{
/*
** Vr�t� hodnotu prvn�ho prvku seznamu L.
** Pokud je seznam L pr�zdn�, vol� funkci DLError().
**/

 if(!L->First) //Pokud je seznam pr�zdn�,
  DLError(); //vol�m funkci DLError()
 else //Pokud seznam pr�zdn� nen�,
  *val = L->First->data; //ulo��m do prom�nn� val hodnotu prvn�ho prvku

}

void DLCopyLast (tDLList *L, int *val)	{
/*
** Vr�t� hodnotu posledn�ho prvku seznamu L.
** Pokud je seznam L pr�zdn�, vol� funkci DLError().
**/
	
 if(!L->Last) //Pokud je seznam pr�zdn�,
  DLError(); //vol�m funkci DLError()
 else //Pokud pr�zdn� nen�,
  *val = L->Last->data; //ulo��m do prom�nn� val hodnotu posledn�ho prvku
}

void DLDeleteFirst (tDLList *L)	{
/*
** Zru�� prvn� prvek seznamu L. Pokud byl prvn� prvek aktivn�, aktivita 
** se ztr�c�. Pokud byl seznam L pr�zdn�, nic se ned�je.
**/
	
 tDLElemPtr ruseny; //Pomocn� ukazatel na ru�en� prvek
 
 if(L->First) { //Pokud nen� seznam pr�zdn�,
  ruseny = L->First; //pomocn� ukazatel ukazuje na ru�en� prvek
  if(L->Act == L->First) //Pokud byl prvn� prvek aktivn�,
   L->Act = NULL; //zru��m aktivitu seznamu
  if(L->First == L->Last) { //Pokud byl ru�en� prvek jedin�m prvkem seznamu,
   L->Last = NULL; //vr�t�m jeho hodnoty do stavu,
   L->First = NULL; //ve kter�m byl po inicializaci
  }
  else { //Pokud nebyl ru�en� prvek jedin�m prvkem seznamu,
   L->First = L->First->rptr; //nastav�m prvn� prvek na prvek n�sleduj�c�
   L->First->lptr = NULL; //a t�m nem� nov� prvn� prvek lev�ho souseda
  }
  free(ruseny); //Uvoln�m pam� po ru�en�m prvku
 }

}	

void DLDeleteLast (tDLList *L)	{
/*
** Zru�� posledn� prvek seznamu L. Pokud byl posledn� prvek aktivn�,
** aktivita seznamu se ztr�c�. Pokud byl seznam L pr�zdn�, nic se ned�je.
**/ 
	
	
 tDLElemPtr ruseny; //Pomocn� ukazatel na ru�en� prvek
 
 if(L->Last) { //Pokud seznam nen� pr�zdn�,
  ruseny = L->Last; //pomocn� ukazatel ukazuje na ru�en� prvek
  if(L->Act == L->Last) //Pokud byl ru�en� prvek prvkem aktivn�m,
   L->Act = NULL; //aktivita se ztr�c�
  if(L->First == L->Last) { //Pokud byl ru�en� prvek jedin�m prvkem seznamu,
   L->Last = NULL; //nastav�m hodnoty seznamu na hodnoty,
   L->First = NULL; //kter� m�l po inicializaci
  }
  else { //Kdy� ru�en� prvek nebyl jedin�m prvkem seznamu,
   L->Last = L->Last->lptr; //nastav�m posledn� prvek na prvek p�edch�zej�c�
   L->Last->rptr = NULL; //a tud� posledn� prvek seznamu nem� prav�ho souseda
  }
  free(ruseny); //Uvoln�m pam� po ru�en�m prvku
 }
}

void DLPostDelete (tDLList *L)	{
/*
** Zru�� prvek seznamu L za aktivn�m prvkem.
** Pokud je seznam L neaktivn� nebo pokud je aktivn� prvek
** posledn�m prvkem seznamu, nic se ned�je.
**/
	
 tDLElemPtr ruseny; //Pomocn� ukazatel na ru�en� prvek
 
 if(L->Act) { //Pokud je seznam aktivn�
  if(L->Act->rptr) { //a pokud m� aktivn� prvek prav�ho souseda,
   ruseny = L->Act->rptr; //pomocn� ukazatel ukazuje na ru�en� prvek,
   L->Act->rptr = ruseny->rptr; //nastav�m nov� prav� prvek aktivn�ho prvku
   if(ruseny == L->Last) { //Pokud byl ru�en� prvek posledn�,
    L->Last = L->Act; //stane se aktivn� prvek prvkem posledn�m
   }
   else { //Pokud nebyl ru�en� prvek posledn�,
    ruseny->rptr->lptr = L->Act; //mus�m nastavit prvku n�sleduj�c�mu po ru�en�m
                                 //lev�ho souseda na prvek aktivn�
   }
   free(ruseny); //Uvoln�m pam� po ru�en�m prvku
  }
 }		

}

void DLPreDelete (tDLList *L)	{
/*
** Zru�� prvek p�ed aktivn�m prvkem seznamu L .
** Pokud je seznam L neaktivn� nebo pokud je aktivn� prvek
** prvn�m prvkem seznamu, nic se ned�je.
**/
	
 tDLElemPtr ruseny; //Pomocn� ukazatel na ru�en� prvek
 
 if(L->Act) { //Pokud je seznam aktivn�
  if(L->Act->lptr) {//a pokud m� aktivn� prvek lev�ho souseda,
   ruseny = L->Act->lptr; //pomocn� ukazatel ukazuje na p�edch�zej�c� prvek
                          //prvku aktivn�ho
   L->Act->lptr = ruseny->lptr; //Mus�me aktivn�mu prvku nastavit nov�
                                //p�edch�zej�c� prvek na prvek p�edch�zej�c�
                                //ru�en�mu
   if(ruseny == L->First) { //Pokud byl ru�en� prvek prvkem prvn�m,
    L->First = L->Act; //nastav�m prvn� prvek na prvek aktivn�
   }
   else { //Pokud nebyl ru�en� prvek prvn�m,
    ruseny->lptr->rptr = L->Act; //nastav�m p�edch�zej�c�mu prvku p�ed ru�en�m
                                 //n�sledn� prvek na prvek aktivn�
   }
   free(ruseny); //Uvoln�m pam� po ru�en�m prvku
  }
 }

}

void DLPostInsert (tDLList *L, int val) {
/*
** Vlo�� prvek za aktivn� prvek seznamu L.
** Pokud nebyl seznam L aktivn�, nic se ned�je.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
**/
	
 tDLElemPtr novyPoAktivnim; //Pomocn� ukazatel na nov� prvek za aktivn�m

 if(L->Act) { //Kdy� je seznam aktivn�
  if(!(novyPoAktivnim = malloc(sizeof(struct tDLElem)))) //Alokuji nov�mu pam�
   DLError(); //Pokud mu nebyla pam� p�id�lena, vol�m funkci DLError()
  else { //Pokud nov� prvek pam� dostal,
   novyPoAktivnim->data = val; //nastav�m jeho hodnotu na hodnotu val,
   novyPoAktivnim->rptr = L->Act->rptr; //n�sleduj�c� prvek nov�ho je prvek
                                        //n�sleduj�c� po aktivn�m,
   novyPoAktivnim->lptr = L->Act; //p�edchoz� prvek nov�ho je prvek aktivn�,
   L->Act->rptr = novyPoAktivnim; //n�sleduj�c� prvek po aktivn�m je nov� prvek,
   if(L->Act == L->Last) //Pokud byl aktivn� prvek posledn�,
    L->Last = novyPoAktivnim; //stane se posledn�m prvkem nov� prvek
   else //Pokud nebyl aktivn� prvek posledn�m,
    novyPoAktivnim->rptr->lptr = novyPoAktivnim; //n�sleduj�c� prvek po aktivn�m
                                                 //bude m�t jako p�edch�zej�c�
                                                 //prvek nov� vkl�dan� prvek
  }
 }
}

void DLPreInsert (tDLList *L, int val)		{
/*
** Vlo�� prvek p�ed aktivn� prvek seznamu L.
** Pokud nebyl seznam L aktivn�, nic se ned�je.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
**/
	
 tDLElemPtr novyPredAktivnim; //Pomocn� ukazatel na nov� prvek

 if(L->Act) { //Kdy� je seznam aktivn�
  if(!(novyPredAktivnim = malloc(sizeof(struct tDLElem)))) //Alokuj nov�mu pam�
   DLError(); //Pokud pam� nebyla p�id�lena, vol�m funkci DLError()
  else { //Pokud nov� prvek pam� dostal,
   novyPredAktivnim->data = val; //nastav�m mu hodnotu na hodnotu val,
   novyPredAktivnim->rptr = L->Act; //n�sleduj�c� prvek je prvek aktivn�,
   novyPredAktivnim->lptr = L->Act->lptr; //p�edch�zej�c� prvek je prvek,
                                          //kter� p�edch�zel aktivn�mu,
   L->Act->lptr = novyPredAktivnim; //nov� prvek je p�edch�zej�c� aktivn�mu,
   if(L->Act == L->First) //Pokud byl aktivn�m prvek prvn�,
    L->First = novyPredAktivnim; //bude prvn�m prvkem nov� prvek,
   else //Pokud nebyl aktivn� prvek prvn�m prvkem,
    novyPredAktivnim->lptr->rptr = novyPredAktivnim; //bude n�sleduj�c� prvek
                                                     //prvku p�edchoz�ho
                                                     //nov� prvek
  }
 }
} 

void DLCopy (tDLList *L, int *val)	{
/*
** Vr�t� hodnotu aktivn�ho prvku seznamu L.
** Pokud seznam L nen� aktivn�, vol� funkci DLError ().
**/
		
 if(!L->Act) //Pokud nen� seznam aktivn�,
  DLError(); //vol�m funkci DLError()
 else //Pokud seznam aktivn� je,
  *val = L->Act->data; //ulo��m do prom�nn� val hodnotu aktivn�ho prvku

}

void DLActualize (tDLList *L, int val) {
/*
** P�ep�e obsah aktivn�ho prvku seznamu L.
** Pokud seznam L nen� aktivn�, ned�l� nic.
**/
	
 if(L->Act) //Pokud je seznam aktivn�,
  L->Act->data = val;	//nov� hodnota aktivn�ho prvku bude hodnota val

}

void DLSucc (tDLList *L)	{
/*
** Posune aktivitu na n�sleduj�c� prvek seznamu L.
** Nen�-li seznam aktivn�, ned�l� nic.
** V�imn�te si, �e p�i aktivit� na posledn�m prvku se seznam stane neaktivn�m.
**/
	
 if(L->Act) //Pokud je seznam aktivn�,
  L->Act = L->Act->rptr; //posunu aktivitu na prvek n�sleduj�c� aktivn�mu

}


void DLPred (tDLList *L)	{
/*
** Posune aktivitu na p�edchoz� prvek seznamu L.
** Nen�-li seznam aktivn�, ned�l� nic.
** V�imn�te si, �e p�i aktivit� na prvn�m prvku se seznam stane neaktivn�m.
**/
	
 if(L->Act) //Pokud je seznam aktivn�,
  L->Act = L->Act->lptr; //posunu aktivitu seznamu na prvek p�ed aktivn�m

}

int DLActive (tDLList *L) {		
/*
** Je-li seznam aktivn�, vrac� true. V opa�n�m p��pad� vrac� false.
** Funkci implementujte jako jedin� p��kaz.
**/
	
 return (L->Act) ? TRUE : FALSE; //Podm�n�n� v�raz, kdy� je seznam aktivn�,
                                 //vrac� TRUE, jinak vrac� FALSE

}

/* Konec c206.c*/
