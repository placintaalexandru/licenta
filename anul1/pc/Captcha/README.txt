
Taskul 1:

	Am definita structura "pixel" care contine 3 variabile de tipul "unsigned char" pe care le voi folosi la citirea unui pixel din fisierul ".bmp"
	
	
	Functia void verify_file (FILE *fisier)
	
		Aceasta functie primeste ca parametru un pointer de tipul "FILE" si verifica daca acest pointer puncteaza catre o zona 
	valida de memorie, iar in caz contrar (caz in care fisierul nu a fost deschis cu succes) afisez mesajul de eroare cu
	ajutorul functiei "strerror" din biblioteca "string.h" si a variabilei "errno" din biblioteca "errno.h".

	Functia pixel **matrice(FILE *intrare_captcha, int nr_linii, int nr_coloane)

		Notatii: matrice_pixeli = reprezinta matricea de pixeli aferenta fisierului captcha(este o matrice de structuri)

		Aceasta functie primeste ca parametru un pointer de tipul "FILE" si 2 numere de tip "int" care reprezinta numarul de
	linii,respectiv coloane ale matricei de pixeli.
		Declar variabila "matrice_pixeli" si o aloc cu "nr_linii", fiecare linie avand dimensiunea "sizeof(pixel *)", iar fiecare
	linie este alocata cu "nr_coloane", fiecare element din linie avand dimensiunea "sizeof(pixel)".
		Dupa ce citesc matricea de pixeli, returnez variabila "matrice_pixeli".
	

	Functia void Task1(pixel **matrice, struct bmp_fileheader *fileheader, struct bmp_infoheader *infoheader, unsigned char B, unsigned char G, unsigned char R, FILE *iesire_captcha)

		Aceasta functie primeste ca parametri matricea de pixeli, un pointer de tipul "struct bmp_fileheader" pentru a scrie fileheader-ul fisierului ".bmp", 
	un pointer de tipul "struct bmp_infoheader" pentru a scrie infoheader-ul fisierului ".bmp". Parametrii B, G, R reprezinta componentele culorii citite din fisierul "input.txt"
	in format "BGR".
		Parcurg matricea de pixeli folosind structura repetitiva "for" si verific ce elemente ale acesteia sunt diferite de pixleli albi, iar unde este indeplinita aceasta conditie schimb culoarea pixelului respectiv schimband 
	valorile "B", "G" si "R" corespunzatoare cu cele citite din fisierul "input.txt"	
		
	
	Functia int main(void)

		Notatii: intrare_captcha=pointer de tipul "FILE" aferent fisierului ".bmp" de intrare
			 intrare_text=pointer de tipul "FILE" aferent fisierului "input.txt"
			 iesire_captcha=pointer de tipul "FILE" aferent noului fisier ".bmp" dupa colorare
			 nume_captcha=pointer ce puncteaza catre o zona de memorie ce poate retine 30 de caractere pentru a memora numele fisierlui ".bmp" de intrare
			 nume=un pointer constant ce va fi folosit pentru a genera numele fisierului ".bmp" de iesire
	
	Folosesc functia "fopen()" pentru a deschide fisierele "input.txt" si ".bmp" de intrare si efectuez operatia aferenta Task-ului 1 dupa care eleiberez memoria si inchid fiserele deschise anterior.



Taskul 2:

	Structura "pixel", functia void verify_file (FILE *fisier) si functia pixel **matrice(FILE *intrare_captcha, int nr_linii, int nr_coloane) sunt identice cu cele create la Taskul 1.

	
	Functia void pixeli_nuli(pixel **matrice_pixeli, int inceput_coloana, int inceput_linie)

		Aceasta functie primeste ca parametri matricea de pixeli a fisierului ".bmp" de intrare, si 2 coordonate fata de coltul din stanga sus al matricei curent.
		Am folosit aceasta functie pentru a sterge numarul din fisierul ".bmp" de intrare dupa ce a avut loc recunoasterea lui.
		Stergerea numarului a fost realizata facand toti pixelii din intervalul [inceput_coloana-4; inceput_coloana]x[inceput_linie; inceput_linie+4] pixeli albi, doar in conditiile in care
	in acest interval se afla un numar.
		Pentru realizarea acestei operatii am folsoit structura repetitiva "for" pentru a parcurge o bucata de "5x5" din matricea de pixeli si unde gaseam un pixel colorat il faceam pixel alb.

	
	Functia int nr_pixeli(pixel **matrice_pixeli, int inceput_coloana, int inceput_linie)

		Aceasta functie numara pixelii colorati din aceeasi sumbatrice de "5x5" ca cea descrisa la functia anterioara, pornind tot de la aceleasi coordonate tot fata de coltul din stanga sus.

		

	Functia void Task2(pixel **matrice_pixeli, int nr_linii, int nr_coloane, FILE *iesire_text)

		Notatii: numere=pointer ce va realocat de fiecare data dupa ce gasesc o cifra ce va fi stocata in zona de memorie catre care acesta puncteaza
			 count=reprezinta numarul de cifre gasite, fiind initializat cu 0

		Aceasta functie primeste ca parametri matricea de pixeli a fisierului ".bmp" de intrare, numarul de linii si coloana ale acesteia si un pointer de tipul "FILE" care puncteaza catre zona de memorie
	in care este deschis fisierul.
		Pentru identificarea efectiva a numerelor am folosit structura repetitiva "for" pentru a parcurgea matricea de la dreapta la stanga si de sus in jos si unde gaseam un pixel diferit de pixelul alb,
	deoarece toate numerele reprezentate pe o mtrice de "5x5" au in coltul din dreapta sus un pixel colorat. Unde gasesc pixel colorat apelez functia "nr_pixeli" sipe baza numarului de pixeli gasiti in acea
	submatrice, iar in unele cazuri si pe baza analizei a inca maxim 2 pixeli semnificativi pentru unele cifre, identific numarul, deorace majoritatea cifrelor au un numar de pixeli bine definit.
		Dupa ce am identificat o cifra o memorez pe pizitia count in zona de memorie spre care pucteaza pointer-ul "numere" pe pozitia "count", dupa care incrementez pe count si realoc dimensiunea zonei de memorie
	respective, dar am grija sa fac toti pixelii din acea submatrice pixeli nulti, pentru a nu interveni in alte analize.
		La final scriu in fisier numere din zona de memorie catre puncteaza pointer-ul "numere" de la coada la cap din cauza modului in care parcurg matricea de pixeli.


	Functia int main(void)
		Aceasta functie contine in mare parte acelasi variabile ca si functia int main(void) de la "Taskul 1", modul de gandire fiind acelasi, cu exceptia faptului ca in loculu pointer-ului de tip "iesire_captcha" "FILE"	 		
	apare pointer-ul "iesire_text" tot de tip "FILE" in care se vor scrie cifrele din fisierul ".bmp" de intrare.
	
	
	
Taskul 3:

	Structura "pixel", functia void verify_file (FILE *fisier), functia pixel **matrice(FILE *intrare_captcha, int nr_linii, int nr_coloane), functia void pixeli_nuli(pixel **matrice_pixeli, int inceput_coloana, int inceput_linie) 
si functia int nr_pixeli(pixel **matrice_pixeli, int inceput_coloana, int inceput_linie) sunt identice cu cele create la Taskul 2.
	Am creat structura "pozitie" ce contine cele 2 campuri pentru a retine pozitia coltului din dreapta sus a fiecarei cifre fata din coltul stanga sus din matricea de pixeli a fisierului ".bmp" de intrare.

	
	Functia int numere_pozitii(pixel **matrice_pixeli, int nr_linii, int nr_coloane, int **numere_captcha, pozitie **vector_poz) 
	
	Este aproape identica cu functia Task2 de la "Taskul 2", doar ca de data aceasta pastrez vectorul de cifre din fisierul ".bmp" de intrare si pozitia fiecaruia in vectorul de tip "pozitie" "vect_poz"
	

	Functia void schimbare(pixel **matrice_pixeli, int linie_origine, int coloana_origine, int linie_destinatie, int coloana_destinatie)

		Aceasta functie muta o cifra din matricea de pixeli de pe pozitia ce are ca si coordonatele coltului din dreapta( coloana_origine, linie_oirigine) sus fata de coltul din stanga sus al matricei de pixeli 
	in pozitia (linie_destinatie, coloana_destinatie).


	Functia void translatare(pixel **matrice_pixeli, pozitie *vector_poz, int *numere_captcha, int *numere_text, int count, int nr_elemente)

		Aceasta functie, dupa ce am generat vectorul ce contine cifrele din fisierul ".bmp" de intrare( numere_captcha), verifica ce elemente din acest vector se afla in vectorul "numere_text", vector ce contine
	cifrele care nu trebuie sa apara in fisierul ".bmp" de iesire
		Pentru realizarea acestei operatii am folosit strucutra repetitiva "for" pentru a parcurge vectorul de cifra ale fisierului ".bmp" de intrare si tot pentru a verifica ce cifra trebuie eliminata.
		In cazul in care ccifra respectiva trebuia eliminata, amapelat functia "schimbare()" si, de asemenea, am avut grija de a schimba pozitiile cifrelor dupa ce a avut loc mutarea
		La final am verificat daca ultima cifra din fisierul ".bmp"de intrare trebuie eliminata, iar daca trebuie transform pixelii aferenti acelei cifre in pixeli nuli.
			

	Functia void Task3(pixel **matrice_pixeli, struct bmp_fileheader *fileheader, struct bmp_infoheader *infoheader, FILE *iesire_captcha, int *numere_captcha, int *numere_text, int count, int nr_elemente, pozitie *vector_poz)

		Aceasta functie nu face decat sa apeleze functia "translatare" care are rolul de a modifica matricea de pixeli, iar dupa ce aceasta functie se excuta creez noua imagine ".bmp".


	Functia int main(void)

		Generez vectorul de pozitii si vectorul de numere prin apelul la functia "numere_pozitii" dupa care apelez functia "Task3" care creeaza noua imagine ".bmp"
		


Bonus:
	
	Functia pixel ***vector_mat_pixeli()
		Aeasta functie genereal un vector de matrice care contine reprezentarea matriceala "5x5" a ficarei cifre.
	


	Functia int cmp(pixel ***vect_mat_pixeli, pixel **matrice_pixeli, int linie, int coloana)

		Verifica intr-o submatrice de "5x5" a submatricei de pixeli numarul minim de pixeli care pe care ii are submatricea cu fiecare element din vectorul de matrice de pixeli (vect_mat_pixeli);
		Dupca ce am stocat in vectorul "v" nuamrul de pixeli prin care o cifra din intervalul [0;9] difera de submatricea curenta de "5x5" este timpul sa gasesc numarul minim de pixeli care difera.
		Daca numarul minim este "0" sau "1" atunci returnez pozitia "i" care rerezinta defapt si cifra in cazul de fata.
		


	Functia void bonus(pixel ***vect_mat_pixeli, pixel **matrice_pixeli, struct bmp_infoheader *infoheader, FILE *iesire_text)

		Am parcurs matricea de la dreapta la stanga si de sus si unde am gasit pixel diferit de pixelul alb, am apelat fucntia "cmp" pentru a gasi numarul de pixeli diferiti dintre submatrciea de "5x5" si reprezentarea
	fiecarei cifre si returnez cifra.
		In cazul in care pixelul de coltul din drapta sus al cifrei este 0, am verificat daca pe linia curenta sub pixelul curent sa afla cel putin 3 pixeli nenuli, iar daca pe a 5 linie se afla un pixel nenul. Daca
	aceasta conditie este indeplinita inseamna ca conditia de linie este indeplinita ("sw_linie=1").
		Am verificat ca si pe coloana cu 5 pozitii mai inainte, daca aceasta exista, sa fie pixel alb, iar daca aceast conditie este indeplinita inseamna ca si conditia de coloana este indeplinita ("sw_coloana=1").
		Daca ambele conditii inseamna ca sumbatricea are mari sanse sa reprezinta un numar din care sa extras sau in care s-a adaugat un pixel si apelez functia "cmp" pentru a vedea ce numar, dupa care submtaricea aferenta
	acelui numar va contine numai pixeli albi prin apelul la functia "pixeli_nuli".
		La final am grija sa scriu in fisierul ".txt" de iesire cifrele care sunt prezente in fisierul ".bmp" de intrare.

	 	
	


			