
/* ******************************* c203.c *********************************** */
/*  Pøedmìt: Algoritmy (IAL) - FIT VUT v Brnì                                 */
/*  Úkol: c203 - Fronta znakù v poli                                          */
/*  Referenèní implementace: Petr Pøikryl, 1994                               */
/*  Pøepis do jazyka C: Václav Topinka, záøí 2005                             */
/*  Úpravy: Bohuslav Køena, øíjen 2008                                        */
/* ************************************************************************** */
/*
** Implementujte frontu znakù v poli. Pøesnou definici typù naleznete
** v hlavièkovém souboru c203.h (ADT fronta je reprezentována strukturou tQueue,
** která obsahuje pole 'arr' pro ulo¾ení hodnot ve frontì a indexy f_index
** a b_index. V¹echny implementované funkce musí pøedpokládat velikost pole
** QUEUE_SIZE, i kdy¾ ve skuteènosti jsou rozmìry statického pole definovány
** MAX_QUEUE. Hodnota QUEUE_SIZE slou¾í k simulaci fronty v rùznì velkém poli
** a nastavuje se v testovacím skriptu p203-test.c pøed testováním
** implementovaných funkcí. Hodnota QUEUE_SIZE mù¾e nabývat hodnot v rozsahu
** 1 a¾ MAX_QUEUE.
**
** Index f_index ukazuje v¾dy na první prvek ve frontì. Index b_index
** ukazuje na první volný prvek ve frontì. Pokud je fronta prázdná, ukazují
** oba indexy na stejné místo. Po inicializaci ukazují na první prvek pole,
** obsahují tedy hodnotu 0. Z uvedených pravidel vyplývá, ¾e v poli je v¾dy
** minimálnì jeden prvek nevyu¾itý.
**
** Pøi libovolné operaci se ¾ádný z indexù (f_index i b_index) nesni¾uje
** vyjma pøípadu, kdy index pøesáhne hranici QUEUE_SIZE. V tom pøípadì
** se "posunuje" znovu na zaèátek pole. Za tímto úèelem budete deklarovat
** pomocnou funkci NextIndex, která pro kruhový pohyb pøes indexy pole
** vyu¾ívá operaci "modulo".
**
** Implementujte následující funkce:
**
**    nextIndex ..... pomocná funkce - viz popis vý¹e
**    queueInit ..... inicializace fronty
**    queueEmpty .... test na prázdnost fronty
**    queueFull ..... test, zda je fronta zaplnìna (vyèerpána kapacita)
**    queueFront .... pøeète hodnoty prvního prvku z fronty
**    queueRemove ... odstraní první prvek fronty
**    queueGet ...... pøeète a odstraní první prvek fronty
**    queueUp ....... zaøazení prvku na konec fronty
**
** Své øe¹ení úèelnì komentujte!
**
** Terminologická poznámka: Jazyk C nepou¾ívá pojem procedura.
** Proto zde pou¾íváme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**
**/

#include "c203.h"

void queueError ( int error_code ) {
/*
** Vytiskne upozornìní na to, ¾e do¹lo k chybì.
** Tuto funkci budete volat v rámci nìkterých dále implementovaných operací.
**
** TUTO FUNKCI, PROSÍME, NEUPRAVUJTE!
*/
	static const char* QERR_STRINGS[MAX_QERR+1] = {"Unknown error","Queue error: UP","Queue error: FRONT","Queue error: REMOVE","Queue error: GET","Queue error: INIT"};
	if ( error_code <= 0 || error_code > MAX_QERR )
		error_code = 0;
	printf ( "%s\n", QERR_STRINGS[error_code] );
	err_flag = 1;
}

void queueInit ( tQueue* q ) {
/*
** Inicializujte frontu následujícím zpùsobem:
** - v¹echny hodnoty v poli q->arr nastavte na '?',
** - index na zaèátek fronty nastavte na 0,
** - index prvního volného místa nastavte také na 0.
**
** V pøípadì, ¾e funkce dostane jako parametr q == NULL, volejte funkci
** queueError(QERR_INIT).
*/
 int i; //Index v poli znakù fronty

 if(q == NULL) //Pokud q == NULL,
  queueError(QERR_INIT); //volám funkci queueError(QERR_INIT);
 else { //Kdy¾ q není NULL
  for(i = 0; i<MAX_QUEUE; i++) { //Procházím cyklem v¹echny políèka pole znakù
    q->arr[i] = '?'; //a nastavuji poèáteèní znak na '?'
  }
 }

 q->f_index = 0; //Index prvního prvku fronty nastavím na 0
 q->b_index = 0; //Index prvního volného místa nastavím na 0
}

int nextIndex ( int index ) {
/*
** Pomocná funkce, která vrací index následujícího prvku v poli.
** Funkci implementujte jako jediný prikaz vyu¾ívající operace '%'.
** Funkci nextIndex budete vyu¾ívat v dal¹ích implementovaných funkcích.
*/

 return ((index+1)%QUEUE_SIZE); //Pøíkaz vrací index následujícího prvku
                                //oproti indexu v argumentu funkce

}

int queueEmpty ( const tQueue* q ) {
/*
** Vrací nenulovou hodnotu, pokud je frona prázdná, jinak vrací hodnotu 0. 
** Funkci implementujte jako jediný pøíkaz.
*/

 return (q->f_index == q->b_index) ? 1 : 0; //Podmínìný výraz
                                            //Pokud je fronta prázdná, vrací 1,
                                            //jinak vrací 0
}

int queueFull ( const tQueue* q ) {
/*
** Vrací nenulovou hodnotu, je-li fronra plná, jinak vrací hodnotu 0. 
** Funkci implementujte jako jediný pøíkaz s vyu¾itím pomocné funkce nextIndex.
*/

 return (((q->f_index == 0) && (q->b_index == MAX_QUEUE)) || (q->f_index == nextIndex(q->b_index))) ? 1 : 0;
 //Podmínìný výraz, vrací hodnotu 1, pokud je fronta plná, jinak vrací hodnotu 0

}

char queueFront ( const tQueue* q ) {
/*
** Vrátí znak ze zaèátku fronty. Pokud je fronta prázdná, o¹etøete to voláním
** funkce queueError(QERR_FRONT) a jako návratovou hodnotu vra»te hodnotu -1.
** Volání této funkce pøi prázdné frontì je v¾dy nutné pova¾ovat za nekorektní.
** Bývá to toti¾ dùsledek ¹patného návrhu algoritmu, ve kterém je fronta
** pou¾ita. O takové situaci se proto musí programátor-vývojáø dozvìdìt.
** V opaèném pøípadì je ladìní programù obtí¾nìj¹í!
**
** Pøi implementaci vyu¾ijte døíve definované funkce queueEmpty.
*/

 if(!queueEmpty(q)) //Pokud fronta není prázdná,
  return q->arr[q->f_index]; //funkce vrací znak ze zaèátku fronty
 else { //Pokud je fronta prázdná,
  queueError(QERR_FRONT); //volám funkci queueError(QERR_FRONT)
  return -1; //a vracím hodnotu -1
 }
}

void queueRemove ( tQueue* q ) {
/*
** Odstraní znak ze zaèátku fronty. Pokud je fronta prázdná, o¹etøete
** vzniklou chybu voláním funkce queueError(QERR_REMOVE).
** Hodnotu na uvolnìné pozici ve frontì nijak neo¹etøujte (nepøepisujte).
** Pøi implementaci vyu¾ijte døíve definované funkce queueEmpty a nextIndex.
*/

 if(!queueEmpty(q)) //Pokud není fronta prázdná,
  q->f_index = nextIndex(q->f_index); //tak posunu index zaèátku na dal¹í znak
 else queueError(QERR_REMOVE); //Kdy¾ fronta prázdná je,
                               //volám funkci queueError(QERR_REMOVE)

}

char queueGet ( tQueue* q ) {
/*
** Odstraní znak ze zaèátku fronty a vrátí jej jako návratovou hodnotu.
** Pokud je fronta prázdná, o¹etøete to voláním funkce queueError(QERR_GET)
** a jako návratovou hodnotu vra»te hodnotu -1 (stejný pøípad jako
** queueFront).
**
** Pøi implementaci vyu¾ijte døíve definovaných funkcí queueEmpty,
** queueFront a queueRemove.
*/

 char znak; //Pomocná promìnná pro znak zaèátku fronty

	  if(!queueEmpty(q)) { //Pokud fronta není prázdná,
     znak = queueFront(q); //ulo¾ím znak do promìnné 'znak',
     queueRemove(q); //tento znak 'odstraním' z fronty funkcí queueRemove()
     return znak; //a vracím pùvodní znak, který byl na zaèátku fronty
    }
    else { //Pokud je fronta prázdná,
     queueError(QERR_GET); //volám funkci queueError(QERR_GET)
     return -1; //a vracím hodnotu -1
    }
}

void queueUp ( tQueue* q, char c ) {
/*
** Vlo¾í znak c do fronty. Pokud je fronta plná, o¹etøete chybu voláním
** funkce queueError(QERR_UP). Vkládání do plné fronty se pova¾uje za
** nekorektní operaci. Situace by mohla být øe¹ena i tak, ¾e by operace
** neprovádìla nic, ale v pøípadì pou¾ití takto definované abstrakce by se
** obtí¾nì odhalovaly chyby v algoritmech, které by abstrakci vyu¾ívaly.
**
** Pøi implementaci vyu¾ijte døíve definovaných funkcí queueFull a nextIndex.
*/

 if(!queueFull(q)) { //Pokud není fronta je¹tì plná,
  q->arr[q->b_index] = c; //zaøadím do ní znak z promìnné c
  q->b_index = nextIndex(q->b_index); //a posunu index první volné pozice dále
 }
 else queueError(QERR_UP); //Pokud je fronta plná, volám fci queueError(QERR_UP)

}
/* Konec pøíkladu c203.c */
