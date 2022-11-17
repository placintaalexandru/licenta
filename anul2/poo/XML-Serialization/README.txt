
	Placinta Alexandru, 324CB, Fisier README



Pentru implementarea temei am considerat o clasa abstracta, intitulata MyCollection, care are 3 metode abstracte:
			
- public abstract void add(int element) -> adauga un element in clasa mea, care extinde aceasta clasa abstracta
			
- public abstract void remove(int element) -> sterge un element din clasa mea, care extinde aceasta clasa abstracta
			
- public abstract Collection<Integer> getNeighboursList() -> returneaza o colectie de obiecte de tip Integer ce reprezinta id-urile din clasa

		

Am considerat aceasta clasa abstracta, deoarece toate nodurile, fie ele de tip A, B sau C, 
	au diferit doar modul cum isi retin vecinii: LIST, VECTOR sau SET, restul campurilor fiind identice.
		
Folosind Factory Pattern instantiez un obiect de tipul MyCollection care poate fi SET, LIST sau SET, 
	in functie de maparea care imi specifica acest lucru.
	
		

Pentru a sti cum un nod de un anumit tip isi tine vecinii, am cosniderat in clasa Graph o mapare Map<String, Integer> 
	care specifica pentru ficare tip de nod, A, B sau C, o versiune, 1, 2 sau 3, 
	iar in functie de aceste valori numerice, 1 pt LIST, 2 pt VECTOR si 3 pt SET, 
	creez unu obiect din cele 3 clase implementate de mine, LIST, VECTOR sau SET.
		
		
Cele 3 clase implementate, LIST, VECTOR si SET fac wrap fiecare peste un LinkedList, ArrayList, respectiv HashSet, 
	aceste implementari fiind sufiecient de generale pentru a necesitatea temei si suprascriu metodele din
	clasa abstracta MyCollection.
		
		

Clasa Graph este implementatacitesc din folosind o lista de obiecte de tipul Node, 3 mapari
	( pt nume, pt id si pt versiune) si un camp, maxID, 
	pe care il folosesc pentru a atribui in mod unic id-urile nodurilor la inserare.
		
In aceasta clasa am implementat cele 4 operatii descrise in enuntul temei: 
	adaugare de nod, stergere de nod, adaugare de muchie si stergere de muchie.
		

Pentru implementarea acestei clase am ales sa foloesesc de obiecte de tip Map 
	a caror semnificatie este urmatoarea: mVersionMap(Map<String,Integer>) 
	are rolul de a retine settings-ul curent in umratoarele perechie spre exemplu:
	("NodA", 1), ("NodB", 2), ("NodC", 3), mNameMap(Map<String,Integer>) 
	retine numele relatia dintre nume si id-uri, iar ultimul obiect de tip Map<INteger,String> 
	retine relatia dintre id-uri si numele acestora.
		
Pe langa aceste 3 obiecte de tip Map mai pastrez in aceasta clasa o lista de noduri 
	pe care o actualizez la fiecare operatie de adaugare/stergere nod.
		
Am ales aceasta implementare, cu cele 3 obiecte de tip Map, pentru a avea constant versiunea grafului curent 
	si pentru a mentine relatia dintre id-uri si nume, 
	respectiv nume si id-uri, astfel ca atunci cand scriu in fisier un nod sa am acces la id-ul sau .

		

Clasa Node contine cele 5 camouri: id, clasa( NodA, NodB sau NodC), un obiect de tip MyCollection in care
	 retine id-urile vecinilor, nume si versiune, toate acestea fiind necesare pentru a serializa graful.
		
In aceasta clasa efectuez operatii de adaugare de vecin, stergere de vecin, aflare al modului cum isi retine
	 respectivul nod vecinii si de intoarcere a unei liste ce contine id-urile nodurilor vecine din acel nod.

		
		

Clasa Serializer are scopul de a serializa un graf, graf pe care il primeste ca parametru pe langa fisierul de iesire 
	in care va scrie serializa graful, deoarece pot serializa mai multe grafuri am ales sa creez
cate un obiect pentru 
	fiecare graf ce va trebui serializat.
		
In aceasta clasa efectuez o parcurgere in latime a grafului pentru a scrie vecinii sau referinte la noduri, 
	daca am trcut prin acele noduri inainte.
		
Am ales sa efectuez o parcurgere in latime, deoarece ofera simplitate fisierului de iesire in sensul ca 
	pentru un nod ce trebuie serilizat am imediat dupa aceea nodurile cu care se invecineaza, acest lucru fiind de
foarte mare folos la desrializare.
		
Pe langa parcurgerea in latime in aceasta calsa efectuez si operatiile de scriere a detaliilor in fisier in formatul specificat de enuntul temei.

		

Clasa Deserializer contine elementele necesare deserializarii unui graf pornind 
	de la un nod de inceput si fisierul de intrare.
		
Pentru acest lucru citesc din fisierul de intrare cat timp linia citita este vida, 
	iar daca pe pozitia 1 al liniei am caracterul 'O' atunci inseamna ca urmeaza 
	sa citesc un nod nou si toti vecinii acestuia.
		
Pentru a citi vecinii unui nod citesc linie cu linie pana dau de tabul de inchidere al nodului nou de adaugat. 
Daca atunci cand citesc un vecin dau de o referinta atunci folosesc maparea Map<Integer, 
	String> pentru a vedeace nume contine acea referinta, iar daca dau de un noud prin care nu s-a mai 
	trecut ii extrag id-ul si numele si il adaug la acea mapare.
		
Atunci cand intalnesc un obiect cu o versiune diferita, pastrez Settings-ul curent si scriu in fisier mesajul de OK/FAIL cast.
Daca la deserializarea unui nod versiunea de deserializare coincide ce versiunea cu care nodul a fost serializat atunci nu mai afisez niciun mesaj.
		


Clasa Start are rol de a executa operatiile din fisierul de intrare, citind linie cu linie acel fisier si 
	evaluand fiecare line citita in parte pentru a vedea ce operatie trebuie executata.

		


Alegerea acestei implementari:


	
1. Am incercat sa urmaresc in mare parte ca fiecare clasa sa aiba o anumita functionalitate: 
	SET, LIST, VECTOR retin vecinii unui nod, Graph contine operatiile pe un graf, 
	Serializer serializeaza graful, Deserializer deserializeaza graful, Start prelucreaza 
	graful conform operatiilor din fisierul de intrare.
		

2. De asemenea am folosit Singleton Pattern pentru a limita numarul de instantieri ale obiectelor de tip Serializer, 
	respectiv Deserializer la 1, deoarece acestea fac un singur lucru, serializeaza, 
	respectiv deserializeaza un graf, iar instantierea mai multor obiecte de acest tip ar fi o irosire a memoriei.


3. In clasa Graph am ales sa retin acele 3 mapari: 
	- cea de versiuni, pentru a sti atunci cand adaug un nod pentru care ii stiu tipul, 
		sa stiu sub ce forma isi va retine acesta vecinii
	- cea de de la nume la id-uri pentru a imi fi mai usor sa accesez un id dupa nume
	- cea de la id-uri la nume pentru a imi fi mai usor sa accesez un nume dupa id.


4. Am flosit Pattern-ul Singleton pentru a nu avea mai multe obiecte ce serializeaza/ deserializeaza un graf 	


Dificultati:

		
1. O dificultate in tema a fost aceea de a face ca fiecare clasa sa aiba o singura functionalitate, 
	initial serializarea o efectuam tot in clasa Graph dupa care am incercat sa rup aceasta parte 
	si sa o introduc in alta clasa.
		

2. De asemenea la deserializare a mai fost ptuin dificil pana sa imi dau seama cum sa 
	aflu numele nodurilor care erau reprezentate cu "Reference", iar apoi m-am gandit sa folosesc o 
	mapare pentru a stoce fiecare nume nou in functie de id-ul atribuit.
		

3. Dupa ce am terminat tema mi-am dat seama ca cream in mod inutil obiecte de tip Serialier, respectiv Deserializer, 
	la fiecare serializare sau deserializare si am incercat apoi sa reduc acest lucru 
	la limitarea crearii unui singurobiect din fiecare tip folosind Singleton Pattern.		

!!Observatie: pentru a rula tema din makefile folositi comanda urmatoare: 
	make run ARGS="CALE_CATRE_FISIER_INPUT_COMENZI"
		
