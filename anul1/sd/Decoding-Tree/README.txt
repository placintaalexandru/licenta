/* Placinta Alexandru - 314CB */


	I. Detalii legate de functii si modul in care am ales implementarea acestora:

	
		1. Functia "TArb ConstrFr( void )":

			Aceasta functie nu trebuie sa primeasca niciun parametru si returneaa un pointer catre o zona de memorie unde este alocat spatiu pentru un nod gol, fara niciun caracter sau litera, deoarece nu am de unde
		sa stiu ce date va avea acesta.
			Am adaugat la parametrii "void" pentru cazul in care in care as fi adaugat din greseala vreun parametru pentru aceasta. Vreau de fiecare data sa imi creez un nod gol fara nicio informatie in el.	

		
		2. Functia "int NrNiv(TArb a)"

			Aceasta functe primeste ca unic parametru un arbore si calculeaza numarul sau de nivele */
			Daca arborele este vid, atunci returnez 0, nu are niciun nivel.
			Daca numarul de fii este egal cu 0, atunci returnez 1, deoarece este doar un nod, nemaiputand sa ma uc in jos in arbore pe acel nod.
			Acestea 2 de mai sus sunt conditiile de oprire ale functiei mele recursive.
			Parcurg vectorul de fii si calculez maximul de nivele ale acestora, iar la final returnez 1 + max, pentru a tine cont si de nodul parinte.

		
		3. Functia "int NrNoduri(TArb a)"

			Aceasta functie primeste ca parametru un arbore si ii calculeaza numarul total de noduri.
			Daca arborele este vid, returnez 0, nu are noduri.
			Daca nu are niciun fii atunci returnez 1, este numai un nod.
			Acestea 2 de mai sus sunt conditiile de oprire pentru functia recursiva.
			Parcurg vectorul de fii al nodului si adun numarul de noduri ale ficecaul fiu, iar la final returnez 1 + numarul de noduri gasit, pentru a tine cont si de nodul parinte.
	
		
		4. Functia "void Afi_aux(TArb a, int nivel_curent, int nivel_dorit, FILE *iesire)":

			Functia primeste ca parametrii un arbore, un numar care tine minte nivelul pe care sunt in arbore, un numar care tine minte nivelul de interes din care vreau sa afisez nodurile si un pointer la un 			fisier.
			Aceasta functie reprezinta o functie auxiliara in afisarea nodurilor arborelui pe nivele.
			Daca arborele este vid, atunci ma opresc.
			Daca cele 2 nivele coincid, afisez informatia din nod, dupa care ma opresc.
			Daca cele 2 conditii de mai sus nu sunt indeplinite, atunci ma duc pe fiecare fiu in parte al nodului curent si apelez recursiv functia, dar crescand nivelul pe care sunt.


		5. Functia "void AfiArb(TArb a, FILE *iesire)":

			Aceasta functie primeste ca parametri un arbore si un pointer la un fisier si afiseaza informatiile tuturor nodurilor pe nivele.
			Pentru implementarea acestei functii am calculat numarul de nivele, dupa care, folosind structura repetitiva "for" parcurg toate nivlele si pentru fiecare "i" din acest interval, apelez functia
 		"Afi_aux", unde nivelul de interes este nivelul "i".
			Dupa fiecare afisare pe nivel trec la linia urmatoare.


		6. Functia "void DistrArb_aux(TArb *a, int nivel_curent, int nivel_dorit)":

			Aceasta functie primeste ca parametrii adresa unui nod, un numar care tine minte nivelul pe care sunt si un numar care tine minte nivelul de interes al nodului pe care vreau sa il sterg.
			Functia reprezinta o functie auxiliar si distruge nodul de pe nivelul de interes.
			Daca arbore este vid, atunci ma opresc, iar daca nivelul curent coincide cu nivelul dorit, eliberez memoria alocata pentru nodul respectiv, dar si memoria alocata pentru vectroul de fii ai acestuia si ma  			opresc.
			Pentru a elibera memoria alocata pentru vectorul de fii, verific daca acesta estediferit de NULL, iar cum in functia principala care va apela aceasta functie auxiliara incep sa elibere nodurile pornind
		de la nivelele superioare spre cele inferioare este clar ca daca vectorul de fii este diferit de NULL, el a fost alocat, dar acum nu mai contine fii, deci pot sa il eliberez, nepierzand referinta catre vreo zona de
		memorie.
			Daca nivelul curent este mai mic decat nivelul de interes, apelez recursiv fucntia pe fiecare din fii nodului curent, avand grija sa incrementez numarul nivelului curent.


		7. Functia "void DistrArb(TArb *a)":

			Functia primeste adresa radacinii unui arbore si elibereaza toata memoria alocata pentru aceasta strcutura.
			Pentru implementarea acestei functii am calculat numarul de nivele din arbore, iar dupa aceea, folosind structura repetitiva "for" am parcurs nivelele in ordine descresacatoare si pentru fiecare nivel de
		interes "i" apelez functia "DistrArb_aux" care elibereaza zona de memoria alocata pentru nodul de pe nivelul "i".


		8. Functia "void Gaseste_aux(TArb a, char litera, TArb *gasit)":

			Aceasta functie primeste ca parametrii un arbore, o litera si adresa unui pointer de tip "TArb", cauta in arbore nodul ce contina "litera" si face ca variabila "gasit" sa puncteze catre acea zona de memorie.
			Pentru implemetarea acestei functii am verificat daca arborele este vid, caz in care me opresc.
			Daca am ajuns intr-un nod, care nu mai are fii, intr-o frunza si litera dorita nu coincide cu litera in nod, ma opresc, altfel modific variabila "gasit" si ma opresc.
			Acestea 2 de mai sus reprezinta conditiile de oprire ale functiei recursive.
			Daca nodul in care ma aflu nu corespunde niciunei conditii, parcurg vectorul de fii ai arborelui curent, iar pentru fiecare fiu apelez recursiv functia.


		9. Functia "TArb Gaseste(TArb a, char litera)":

			Functia primeste ca parametrii un arbore, o litera si returneaza un pointer catre zona de memorie unde este stocat nodul ce contine acea litera.
			Pentru implementarea acestei functii am initializat o variabila "gasit" cu NULL si am apelat functia "GAseste_aux" pentru a modifica aaceasta variabila.
			La final returnez aceasta variabila gasit, fie ca este NULL sau o adresa valida de memorie.


		10. Functia "int add(TArb a, char *linie)":

			Functia primeste ca parametrii un arbore, un sir de caractere care contine atat litera de adaugat cat si codificarea pentru acesta si adauga in arbore litera precum si codificarea aferenta acesteia.
			Pentru implementarea acestei functii am folosit functia strtok pentru a obtine cele 2 parti ale liniei, litera si codificarea acesteia.
			Parcurg codificarea aferenta literei, folosind structura repetitiva "for", iar la inceputul fiecarei iteratii initializez variabila booleana "gasit" cu false si caut prin vectorul d fii ai nodului curent
		fiul ce contine in campul "caracter" caracterul de pe pozitia "i".
			In momentul in care am gasit acest fiu opresc cautarea, variabila boolena "gasit" trece pe true si cobor in arbore pe fiul care satisface aceasta conditie.
			Daca variabila "gasit" a ramas false dupa parcurgearea vectorului de fii, atunci trebuie sa mai adaug un fiu nou ce va contine caracterul, caracterul de pe pozitia "i".
			Realoc vectorul de fii, incrementez numarul curent de fii, iar fiul nou va contine doar caracterul de pe pozitia "i" din codul aferent literei de adaugat in arbore.
			Se reia acest proces pana am ajuns la finalul codificarii pentru litera de adaugat, iar fiul pe care ma voi afla dupa ce au avut loc toate iteratille va fi cel care va contine litera de adaugat.


		11. Functia "void Realoca(TArb a, int pozitie)":

			Functia primeste ca parametru un pointer catre o zona de memorie unde este stocat un nod, un numar ce reprezinta o anumita pozitie din vectro( pozitia fiului ce trebuie eliminat din vector ), 
		elimina fiul de pe pozitia "pozitie" si realoca vectorul de fii cu o dimensiune cu 1 mai mica decat cea anteriaora.
			Pentru implementarea functiei am considerat un vector auxiliar de pointeri pe care l-am alocat cu o dimensiune cu 1 mai mica fata de numarul actual de fii ai nodului primit ca parametru.
			Pentru a elimina fiul de pe pozitia "pozitie" am folosit structura repetitiva "for" de 2 ori: [0; poziztie - 1] prima data si [pozitie + 1; nr_fii) a 2-a oara.
			Pentru fiecare pozitie "i" din acele 2 parcurgeri am luat fii din vectorul vechi si i-am introdus in noul vector.
			La final eliberez vectorul vechi de fii, vectorul auxiliar va deveni noul vector d fii si decrementez numarul curent de fii.


		12. Functia "int delete(TArb a, char litera)":

			Functia primeste ca paremetrii un arbore, o litera si sterge toate nodurile necesare pentru a disparea litera respectiva si pentru a nu lasa codificari invalide in arbore.
			Pentru implementarea acestei functii am folosit functia "Gaseste" si am verificat daca rezultatul intors de aceasta este diferit de NULL.
			In cazul in care este NULL, nodul nu exista deci ma opresc.
			Daca rezultatul este diferit de NULL verifca daca numarul de fii este diferit de 0.
			Daca este diferit de 0, insemna ca mai pot exista codificari mai jos de acest nod si pur si simplu fac ca litera din acel nod sa fie egalu cu '\0'.
			Daca nu mai are fii, adica e frunza, urc in arbore prin campul parinte al fiecarui nod, cat timp nu dau de o litera in parintele nodului curent, pentru a evita stergerea ei, si cat timp bunicul nodului
		respectiv este diferit de NULL, pentru a evita stergerea radacinii, si cta timp nu dau de o bifurcatie.
			In momentul in care acest proces repetitiv se incheie eu mai am de sters un nod.
			Parcurg vectorul de fii ai parintelui acestui nod si gasesc pozotia in vector unde se afla acesta, dupa care folosesc functia "Realoca" pentru a sterge si ultimul nod si a realoca vectroul de fii.


		13. Functia "char ConstrArb(TArb *a, FILE *intrare, FILE *iesire)":
		
			Functia primeste ca parametrii un arbore, 2 pointeri la fisiere, unul de intrare care contine literele de adaugat initial in arbore si codurile operatiilor de efectuat dupa pe acesta si unul de iesire
		in care se va afisa arborele confrom ceintei temei dupa fiecare operatie in parte.
			Pentru implementarea acestei functii am alocat o zona de memorie in care citec codul aferent fiecarei operatii.
			Citesc mai intai numarul de litere de adaugat si folosesc functia "atoi" pentru a-l converti de la tipul "char" la tipul "int".
			Dupa aceea foloesesc structura repetitva "for" pentru a citi atatea litera cate indica variabila convertita de mai sus.
			Citesc separatorul ce va fi folosit la decodificarea textului si il retin in variabila "separator".
			Dupa ce am construit arborele citesc numarul de operartii de efectuat pe acesta si cat timp pot sa citesc din fisier, deoarece operatiile de aplicat pe arbore se continua pana la finalul fisierului, verific ce 
		operatie am de efectuat.
			Daca primele 3 caractere din operatie sunt "add" atunci apelez functia "delete" care efectueaza si o cautarea a literei de introdus, daca deja exista o sterge, iar apoi adaug litera noua.
			Daca conditia de mai sus nu este indeplinta atunci sterg al 7-lea cracter din lina ce contine comanda, fix litera de dupa "delete" si saptiu.
		
			
		14. Functia "char DecodificareLitera(TArb a, char *cod)":

			Functia primeste ca parametrii un arbore, un cod si returneaza litera corespunzatoare codului primit ca parametru.
			Pentru implementarea acestei functii am parcurs sirul de caractere din cod, folosind structura repetitiva for si pentru fiecare caracter de pe pozitia "i" din cod am parcurs in acelasi fel vectorul de fii si 
		am verificat ce fiu continea in campul "caracter" caracetrul de pe pozitia "i".
			Dupa ce am gasit fiul respectiv cobor pe acesta si procesul se reia pana ajung sa identific fiul ce contine si ultimul caracter din codificare.
			La final, nodul in care ma aflu va fi cel in care se va gasi litera aferenta codului primit ca parametru.


		15. Functia "void Decodificare(TArb a, char separator, FILE *intrare, FILE *iesire)":

			Functia primeste ca parametrii un arbore, 2 pointeri la fisiere, unul de intrare ce contine textul codat si unul de iesire ce va contine textul in clar.
			Pentru implementarea aceste functii am alocat o zona de memorie unde citesc randurile textului cat timp pot sa citesc din fisierul de intrare.
			Pentru fiecare rand citit folosesc functia strtok pentru a determina fiecare codificare, din care voi determina literele.
			Verific pentru fiecare codificare daca primul caracter este spatiu, caz in care il scriu in fisier si incrementez pinter-ul cu 1, pentru a sari acel caracter dupa care apelez functia "DecodificareLitera" pentru
		a afla litera corespunzatoare.
		

		16. Functia "void Start(char *intrare_cod, char *intrare_text, char *iesire_arbore, char *iesire_text)":

			Functia primeste ca parametrii 4 siruri de caracter ce reprezinta numele celor 4 fisiere ce vor fi folosite pentru aceasta tema si apeleaza functiile pentru realizarea temei.
			Pentru implementeare folosesc functia "fopen" pentru a initializa cei 4 pointeri la fisiere si verific pentru fiecare daca sunt diferiti de NULL.
			Construiesc arborele si gasesc separatorul de text cu ajutorul functiei "ConstrArb" dupa care cu ajutorul functiei "Decodificare" obtin textul in format clar.
			La final eliberez memeoria alocata pentru structura de arbore si pentru alte variabile auxiliare.


		17. Functia "int main(int argc, char *argv[])":

			Functia primeste ca parametrii cele 4 nume ale fisierelor si apeleaza functia "Start" ce rezolva corect si aceasta tema.


	
	II. Ce a fost mai greu la implementare:

		1. Un lucru foarte dificil la implementare care mi-a luat destul de mult timp, circa 5-6 ore, a fost sa imi dau seama de ce fisierul ce continea textul in format clar era fisier binar, desi el trebuia sa fie in format
	text.
			Am rezolvat acest lucru prin stergerea tuturor cailor care duceau la codificari invalide, observand ca de fiecare data daca litera pe care o scriam in fisier era '\0' rezultatul era un fisier binar.
		
		2. Alt lucru dificil la tema a fost alegerea structurii care sa imi ofere o oarecare flexibilitate prin arbore, nefiind ca celelalate teme unde structura ne era clara. Aici fiecare a fost liber sa isi faca structura sa
	si am vrut sa aleg una care sa im permita sa fac cat de cat rapid operatiile.

		

	III. Punctaj pe checker-ul local:

		Cheker-ul local imi arata, la fel ca si cel de pe "https://vmchecker.cs.pub.ro/ui/#SDCB" 105 puncte.
