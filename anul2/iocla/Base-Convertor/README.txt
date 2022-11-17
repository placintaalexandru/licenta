
PLACINTA ALEXANDRU, 324CB, Fisier Readme	


	Pentru convertirea unui numar "a" la o baza "b" am folosit algoritmul de impartire succesiva a numarului la baza pana cand catul de impartire ajunge 0.
	Inainte de fiecare impartire verificam daca numarul este mai mare decat zero, caz in care continuam operatia.
	Am retinut in variabila "deimpartit" numarul curent, catul, iar in variabila "impartitor" baza.
	Pentru realizarea instructiunii repetitive am folosit diferite label-uri care mi-ai permis sa simules un "while".
	La inceputul programului imi initializez cele 2 variabile, deimpartit si impartitor, iar apoi incep sa efectuez pasii proriu-zisi ai algoritmului.

	Label-ul "verificare_baza" verifica daca baza este intre 2 si 16, iar in caz negativ folosesc instructiunea "jmp" pentru un jump catre label-ul "exit", de unde afisez mesajul corespunzator si inchei programul.
	Label-ul "conversie" incepe conversia, impartirea propriu-zisa, verificand daca deimpartitul este strict mai mare decat 0, caz in care incep efectuarea impartirii, iar daca este 0 incep afisarea prin extrageri
succesive din stiva.
	Label-ul "impartire" efectueaza impartirea, mutand octetii deimpartitului in cele 2 registrea, EDX( partea superioara) si EAX( partea inferioara), iar instructiunea "div" efectueaza impartirea cu rest, rest pe care il
introduc in stiva, iar deimpartitul va deveni noul cat.
	Labelul "afisare" se decrementeaza valoare din registrul ecx, in care retin numarul de resturi, extrag valoarea cea mai sus de pe stiva in registrul ebx si o compar cu 10, deoarece de la 10 in sus trebui sa afisez caractere
reprezentative pentru baza in care am convertit. Daca valoare din registrul ebx este mai mica decat 10, adun la acea valoare 47 pentru a obtine valoarea caracterul in codul ASCII, iar daca este mai mare adun 87 pentru a obtine valorile
acelor litere reprezentative pentru baza in codul ASCII.
	Label-ul "reluare" verifica daca am scos toate valorile de pe stiva, comparand valoarea din registrul ecx cu 0, iar daca este mai mare reiau label-ul "afisare", altfel opresc executia programului adaugand instructiunea "ret"
dupa ce efectuez compararea.
	Label-urile ""afisare_litera" si "afisare_cifra" au rolul de a afisa litera, respectiv cifra sub forma unui caracter, iar in fiecare din cele 2 label-uri adaug valoarea necesara pentru a obtine valoarea caracterelor respective
in codul ASCII.
	Label-ul "exit" are rol doar de destinatie de salt in caz ca baza e invalida atunci cand verific la inceput acest lucru.	