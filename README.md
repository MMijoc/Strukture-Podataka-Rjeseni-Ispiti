# Strukture-Podataka-Rjeseni-Ispiti

## Napomena:
1. Zadatke raditi isključivo u svom branchub (provjeri branch s naredbom git branch -all i promijeni branch s git checkout)
2. Za svaki zadatak napraviti zaseban VS projekt (preporuka koristiti VS 2010) koji će se nalaziti u lokalnom kloniranom direktoriju (prilikom pravljenja novog projekta "Lokacija:" treba biti ....\Strukture-Podataka-Rjeseni-Ispiti\)
3. Svaki projekt imenovati Zadatak_"broj zadatka", pri čemu je "broj zadatka" redni broj zadatka u datoteci "Ispitni Zadatci.txt" -> broj treba biti u formatu 01, 02, 03 .. (drukčije neće biti poredani kako treba)

	>>> npr. Zadatak_02  
	>>> ili Zadatak_21  
	
4. Svaki put kada se nastavlja raditi na projektu dobro je povući moguće dodatne promjene koje su se dogodile u mani branch-u (pri promjeni teksta zadatka, dodavanja novi zadataka ili tekstualnih datoteka iz koji se čita), to se radi preko naredbe **git pull**, pri čemu je potrebno biti u odgovarajućem branch-u (main)
Da bi se ove promijene prenijele i na vlastiti branch potrebno je napravit: 
>>> git checkout ime-tvog-brancha  
>>> git merege main


## Promjene u main branch-u
Ako je potrebno ispraviti neku pogrešku, dodati novi zadatak ili slično to možemo napraviti unutar main brancha.  
Potrebno je se prebaciti u main branch te nakon napravljenih promjena napraviti smislen commit, i push-at na GitHub;
Promjene se u vlastiti branch (ako nisu napravljene u oba) mogu prebaciti u vlastiti branch pomoću naredbi navedenih iznad pod brojem 4.

## Naredbe koje možda zatrebaju:

1. Napravi lokalnu kopiju repozitorija

git clone https://github.com/MMijoc/Strukture-Podataka-Rjeseni-Ispiti.git

2. Trenutni branch

git branch

3. Svi branch-ovi, bijeli su lokani - na računalu, crveni su na GitHub-u, zeleni je trenutni brnach

git branch --all

4. Promijeni brnach

git checkout ime-brancha
npr. git checkout Marko-Mijoc

5. Commitovi česti, smisleni i uredni

 git commit -m "smislena poruka"

6. Spremanje promjena na remote repozitoriji (na GitHub)

git push

7. Dohvati promjene u main branchu (ako su dodani ili uređeni zadatci)
NAPOMENA: pazit da se nalaziš u svom branchu, ako nisi prvo iskoristit: git checkout ime-tvog-brancha

 git merege main

8. Novi lokalni branch

 git checkout -b ime-brancha
 
9. push-aj novi lokalni branch na GitHub

 git push -u origin ime-brancha


Ko nije ljubitelj git basah-a može koristiti: shift + lijevi klik mišom, zatim odabrati "open PowerShell window here"
