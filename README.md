# Strukture-Podataka-Rjeseni-Ispiti
Ovaj repozitorij sadrži riješene ispite s prijašnjih godina iz kolegija strukture podataka na smjeru računarstvo (120) FESB, Split

# DODATAK

# Otkrivanje memory leak-a u Visual Studio-u
*(ova metoda funkcionira samo na MSVC compiler-u dakle generalno samo na Windows-u u bilo kojem Visual Studiu)*  
## Promjene u kodu
Da bi se koristili ovom metodom potrebno je uključiti potrebni header i definirati poseban macro:  
	  **//For debugging memory leaks**  
	  **#define _CRTDBG_MAP_ALLOC**  
	  **#include <crtdbg.h>**
	
Nije loše doadati komentar kako ne bi poslije, kada nam više ne treba, zaboravili izbrisati (iako to nije nužno)  
Nužno je da macro _CRTDBG_MAP_ALLOC bude definiran prije #include <crtdbg.h> (ne prije svake include direktive nego samo ove)  

U main djelu, na početku samog programa, dodati sljedeću funkciju:  
	  **//For debugging memory leaks**  
	  **_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);**  

Ako se koristi VS2010 ili ranije (odnosno starija verzija C-a i pripadajućeg compiler-a) potrebno je da ova linija koda bude nakon deklaracija varijabli (u biti može biti bilo gdje u kodu no obzirom da se memory leak također može dogoditi bilo gdje stoga ju je najbolje staviti na početak)  

## Debuggiranje
Kako bi otkrili memory leak porebno je pokrenuti porgram u debug modu (sa F5 ili Debug->Start Debugging) i otvoriti output prozor (CTRL + ALT + O ili View->Output) ako već nije automatski otvoren.  
Ako postoji memory leak u Output prozoru će nam se ispisati linije tipa:  
*c:\...{put do file-a}...\source.c(162) : {68} normal block at 0x009A5A00, 396 bytes long.*  
 *Data: <Stephen         > 53 74 65 70 68 65 6E 00 00 00 00 00 00 00 00 00*
	  
***c:\...{put do file-a}...\source.c(162)*** -> označava put do file, a broj unutar zagrada označava linija kodu u kojoj je pozvan malloc za kojega nikad nije pozvan free  

***{68} normal block at 0x009A5A00, 396 bytes long.*** -> označava lokaciju u memoriji u koja je ostala ne oslobođena, te pokaziva koliko memorije je ostalo neoslobođeno  

***Data: <Stephen         > 53 74 65 70 68 65 6E 00 00 00 00 00 00 00 00 00*** -> govori što se točno nalazi na toj memoriskoj lokaciji ali prikazano u heksadecimalnom obliku  
