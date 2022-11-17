

Functia "[Matrice_adiacenta Matrice_vecini N val1 val2]= citire( nume_fisier )":

		Aceasta funtie citeste din fisierul primit ca parametru graful si creeaza matricea de adiacenta, matricea ce contine numarul de vecini pentru fiecare nod, toti vecinii fara nodul in sine, 		si, de asemenea, citeste valorile val1 si val2.
		Pentru implementare am folosit functia "fopen" pentru a avea un pointer la fisierul ce contine datele.
		Pentru a citi numarul de noduril am citit un singur element de tip int cu ajutorul functiei "fscanf", dupa care am folosit structura repetitiva "for" de la 1 la numarul de noduri si
	pentru fiecare nod citeam nodul, numarul de vecini, iar apoi intr-un vector citeam vecinii. In matricea de adiacenta de pe pozitia indicata de numarul nodului si valorile vectorului care
	erau diferite de numarul nodului introduceam 1, pentru a gasi vecii diferiti.
		Dupa aceea, pentru a calcula numarul de vecini, am calculat lungimea vectorului de vecini care sunt diferiti de numarul nodului curent.
		Citesc cele 2 valori val1 si val2 cu functia "fscanf", iar la final, cu ajutorul functie "fclose" eliberez pointer-ul catre fisierul deschis pentru citire.


Functia "[solutie] = SST(A, b)":
		
		Aceasta functie rezolva un sistem superior triunghiulat si este implementarea functiei din laboratorul 2.


Functia "[R] = PutereDirecta( A, y, tol )":

		Aceasta functie rerezinta implementarea metodei puterii directe din laboratorul 7.
		Pentru aceasta implementare se stie ca pornind de la un vecotor initial normat, inmultind si normand consecutiv, acest vector converge spre vectorul corespunzator
	valorii proprii dominante.
		Iterez acest proces cat timp norma difernetei dintre vecotrul la pasul "k+1" si vectorul la pasul "k" este mai mare decat o toleranta.


Functia "[Inv] = Inversa(A)":

		Aceasta functie calculeaza inversa unei matrice primite ca parametru.
		Am calculat numarul de linii si de coloane ale matricei primite ca parametru.
		Pentru implementarea acestei functii am folosit descompunerea QR cu ajutorului algoritmului Gram-Schmidt.
		Dupa aceea am avut de rezolvat "n" sisteme superior triunghilate de forma R*x = Q'*i, unde x reprezinta coloana "j" din matricea inversa si "i" reprezinta coloana "j" din 
	din matricea unitate.
		Acest lucru l-am realizat cu ajutorul functiei "SST".


Functia "[R] = Iterative( nume_fisier, d, tol )":

		Aceasta functie contine implementarea algoritmului de la Task-ul 1.
		Pentru implementarea acestuia am folosit functia "citire" pentru a construi matricea de adicenta si matricea cu numarul de vecini.
		Am construi vectorul "v1" care este plin de 1, folosindu-ma de lungimea unei coloane din matricea de adicaenta pentru a sti cati de "1" sa introduc in vector.
		Am construit matricea "M" din formula prin transpunerea produsului dintre inversa matricei de vecini si matricea de adiacenta.
		Conform formulei algoritmului "Iterative" iterez cat timp norma diferenti dintre "R" la pasul "k+1" si "R" la pasul "k" este mai mare decat toleranta, iar cand devine mai mica
	decat tolerant opresc procesul.


Functia "[R] = Algebraic( nume_fisier, d )":

		Aceasta functie contine implementarea algoritmului de la Tasku-ul 2.
		Am folosit functia "citire" pentru a citi cele 2 matrice si cele 2 valori.
		Am construi vectorul "v1" care este plin de 1, folosindu-ma de lungimea unei coloane din matricea de adicaenta pentru a sti cati de "1" sa introduc in vector.
		Am construit matricea "M" din formula prin transpunerea produsului dintre inversa matricei de vecini si matricea de adiacenta.  
		Am aplicat formula din ecuatia matricea de la Task-ul, punand "double" inaintea raportului "( 1 - d ) / N" pentru a se lua elemente reale, nu intregi.


Functia "[R] = Power( nume_fisier, d, tol )":

		Aceasta functie contine implementarea algoritmului de la Tasku-ul 3.
		Pentru implementarea acestuia am folosit functia "citire" pentru a construi matricea de adicenta si matricea cu numarul de vecini.
		Am detreminat matricea "E" din formula de la Task-ul 3 care este "v1 * v1'".
		Am construit matricea "M" din formula prin transpunerea produsului dintre inversa matricei de vecini si matricea de adiacenta.
		Am construit matricea "P" din formula, dar avand grija sa iau elemente reale si nu intregi, iar pentru aflarea vectorului "R" m-am folosit de metoda puterii direct, iterand pana
	cand se indeplinea conditia ca norma diferentei dintre 2 vectori la 2 pasi consecutivi sa fie mai mica decat o tolrenta.


Functia "[y] = Apartenenta( x, val1, val2 )":

		Aceasta functie contine implementarea functiei apartenenta, dar aplicata pentru un vector de valori, returnand tot un vector de valori.
		Pe pozitiile in care vectorul de intrare are valorile in intervalul [0; val1), valorile de iesire sunt 0, iar pentru aceasta am ales varianta vectorizata.
		Pe pozitiile in care vectorul de intrare are valorile in intervalul [val1; val2], valorile de iesire sunt cele ale functiei "a*x+b", cu a si b calculate astfel incat functia sa fie
	continua pe intervalul [0; 1].
		Pe pozitiile in care vectorul de intrare are valorile in intervalul (val2; 1], valorile de iesire sunt 0.
		

Functia "[R1 R2 R3] = PageRank( nume_fisier, d, tol )":

		Aceasta functie contine implementarea algoritmului "PageRank" de la Tasku-ul 4.
		Am folosit functia "citire" pentru a citi cele 2 matrice si cele 2 valori.
		Am calculat cei 3 vectori, pe fiecare cu cate un algoritm de la Task-urile "1", "2" si "3".
		Am creat un nou nume al fisierului de iesire care era numele fiiserului de intrare la care concatenam sufixul ".out", si il deschideam pentru scriere cu ajutorul functiei "fopen".
		Am scris in fisier numarul de noduri si dupa aceea am ordonat valorile din vectorul "R2" si am interschimbat si nodurile de pe pozitiile corespunzatoare.
		La final aplicam functia "Apartenenta" pe vectorul "R2" si scriam in fisierulde iesire acest rezultat.
			
