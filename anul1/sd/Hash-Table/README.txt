/* Placinta Alexandru - 314 CB */

	I. Detalii legate de functii si modul in care am ales implementarea acestora:

		1. Functia "int Suma_elemente(char *sir)":
			
				Aceasta functie primeste ca parametru un sir de caractere si returneaza suma codurilor ASCII acarecterelor ce comoun sirul respectiv.
				Pentru implementarea acestei functii am intializat cu 0 o variabila suma, am parcurs propriu-zis sirul de caractere, folosind
			structura repetiva "for" de la 0 la lungimea sirului minus 1 si am adunat la suma caracterul de pe pozitia "i".
				Am returna valoare variabilei suma calculata mai sus.

		
		2. Functia "int Functie_Hash(void *Key, int Nr_elemente)":

				Aceasta este implementarea funtie hash din tabela hash corespunzatoare enuntului temei.
				Aceasta functie primeste ca parametri un void vointer, care puncteaza catre un sir de caractere, si un numar intreg si returneza pozitia listei din care
			ar trebui sa faca parte celula ce il contine pe "Key".
				Pentru implementarea acestei functii am facut cast la tipul char pointer a void pointerului primit ca parametru si am apelcat functia Suma_elemente descrisa
			mai sus pentru a calcula suma elementelor ce compuneau sirul de carcatere "Key".
				Am returnat restul impartirii sumei la numarul de elemente, aceasta valoare corespunzand pozitie listei din care are trebui sa faca parte celula ce il contine pe "Key".


		3. Functia "TH *IniTH(size_t M, TFHash fh)":
			
				Aceasta functie initializeaza o tabela hash si nu am nicio contributie in implementarea ei, deoarece este cea de la laborator, intrucat ni s-a permis sa
			folosim schelet de cod de la laboratoarele anterioare.


		4. Functia "int Functie_Cmp(void *cel1, void *cel2)":

				Aceasta functie primeste ca parametri 2 void pointeri ce reprezinta 2 celule dintr-o lista si intoarce o valoare pozitiva sau negativa, pozitiva daca cele
			2 celula trebuie interschimbate si negativa altfel.
				Pentru implementarea acestei functii am facut cast la tipul "TLG" celor 2 pointeri la void, iar dupa accea am facut cast la tipul "TSite" pointer a campului
			"info" din cele 2 celule.
				In cazul in care cele 2 celule aveau acelasi Frequency comparam Key-urile celor 2 celule cu functia "strcmp".
				Mereu daca trebuie inserata o celula element intr-o  lista, functia aceasta se apeleaza astfel: "Functie_Cmp( (void *)element, (void *)celula_din_lista )".


		5. Functia "int LungimeLG(ALG a)":

				Aceasta functie primeste ca parametru adresa unui pointer ce puncteaza la inceputul unei liste si intoarce lungimea listei respective.
				In mare parte aceasta este o functie de la laborator, singura mea contributie asupra acestei functii este faptul ca la implementarea ei am modificat-o
			astfel incat daca campul urm din prima celula puncta tot catre prima celula, atunci returnam 1, deoarce lista avea un element si apoi parcurgeam lista cat timp
			celula curenta era diferita de prima celula din lista si incrementam valoarea "lg" initializata cu 0.
				In final returnam valoarea variabilei "lg". 
				Aceasta functia a fost luata de mine din laborator si am adaptat-o pentru listele dublu inlantuite fara santinela.
			

		6. Functia "void AfisareCelulaG(TLG cel)":

				Aceasta functie primeste ca parametru un pointer catre o zona de memorie si afiseaza pe "Key", "Value" si "Frequency" din celula respectiva.
				Pentru implemenarea fucntiei am facut cast la tipul "TSite" pointer a void pointerului "info" din celula si afisat campurile indicate mai sus.
				Aceasta functie am folosit-o mai mult la debuggin, ea neavand un rol semnificativ in tema, decat acela de a-mi arata ca tabela hash se cosntrieste intr-un mod normal.


		7. Functia "void AfisareListaG(ALG l)":

				Aceasta functie primeste ca parametru adresa pointer-ului ce puncteaza catre inceputul unei liste si afiseaza pe: "Key", "Value" si "Frequency" din celula respectiva.
				Pentru implementarea functiei am ales sa fac afisez separat prima celula din lista, folosind functia "AfisareCelulaG", descrisa mai sus, dupa care aprcurgeam  de la
			de la a 2 a celula din lista, folosind structura repetiva "for", cat timp celula curenta era diferita de prima celula din lisat  si foloseam tot funtia "AfisareCelulaG" descrisa
			mai sus.
				Aceasta functie am folosit-o pentru debugging pentru a afisa fiecare lista din tabela hash si pentru a vedea daca inserarea ordonata functioneaza corect, ea neavand un rol 				foarte important in realizarea temei.			
	
	
		8. Functia "void Afisare_tabela(TH *tab_hash)":

				Aceasta functie primeste ca parametru un pointer catre o zona de memorie in care este alocata o tabela hash si afiseaza toate celula din tabela hash.
				Pentru implementarea acesteia am folosit structura repetitiva "for" de la 0 pana la numarul de pointeri din tabela minus 1, si pentru fiecare pozitie am apelat
			functia "AfisareListaG", descrisa mai sus.
				Aceasta functie am folosit-o pentru debugging pentru a afisa toatele elementele din tabela hash, ea neavand un rol foarte important in realizarea temei.
								 
 
		9. Functia "TLG AlocCelulaG(char *Key, char *Value)":

				Functia primeste ca parametri 2 siruri de caractere si aloca spatiu pentru o celula ce contine un void pointer la o zona de memorie in care e o structura 				ce contine pe "Key" si "Value" si  il initializeaza pe "Frequency" cu 0.
				Functia aceasta este in mare parte de la laborator, singura mea contribuite este faptul ca am facut campurile "urm" si "pre" sa puncteze tot la celula in 				sine si am folosit fucntiua "strdup" pentru a aloca exact cat trebuie pentru "Key" si "Value".


		10. Functia "void StergeCelulaG(ALG celula)":

				Functia primeste ca parametru adresa unui pointer la o zona de memorie in care este aloata o celula, elibereaza spatiu pentru celula respectiva si face
			ca pointer-ul respectiv sa puncteze catre "NULL" dupa ce s-a eliberat spatiu.
				Pentru implementarea functiei respective am facut cast la tipul "TSite" pointer a void pinterului din celula si eliberez spatiul alocat pentru 				   				campurile "Key" si "Value".
				Dupa aceea eliberez spatiu alocat pentru zona de memorie spre care puncteaza "info", apoi eliberez spatiu ocupat de celula propiu-zisa si la final fac
			ca pointerul ce puncta catre zona de memorie in care era alocata celula sa puncteze catre NULL.


		11. Functia "void StergeListaG(ALG lista)":
			
				Functia aceasta primeste ca parametru adresa pointer-ului ccare puncteaza catre celula de inceput a unei liste dublu inlantuite fara santinela.
				Pentru implementarea acestei functii am parcurs lisat, folosind structura repetitiva "for" de la a 2 a celula a listei, cat timp celula curenta este diferita 				de prima celula din lista si pentru fiecare celula apelez functia "StergeCelulaG" descrisa mai sus pentru a elibera spatiul pentru fiecare celula din lista.
				La final apelez din nou fucntia "StergeCelulaG" pentru prima celula din lisat, acest lucru facandu-mu lista vida.


		12. Functia "void StergeTabelaG(TH **tab_hash)":

				Functia aceasta primeste ca paramtru adresa pointer-ului care puncteaza la o zona de memorie in care este alocata o celula, elibereaza spatiu si face 
			pointer-ul respectiv sa puncteze catre NULL.
				Pentru implementarea functiei  am parcurs vectorul de pointeri din tabela hash de la 0 la nuamarul de elemente minus 1 folosind structura repetitiva 				"for" si pentru fiecare pointer am apelat functia "StergeListaG" descrisa mai sus pentru a elibera spatiul alocat pentru fiecare lista.


		13. Functia "TLG Verifica_existenta(char *Key, TH *tab_hash)":
			
				Functia primeste ca parametri un pointer la o zona de memeorie unde este un sir de caractere si un pointer la o zona de memeorie unde este alocata o tabela hash
			si returneaza adresa celulei in care se gaseste sirul de caractere "Key" sau "NULL" in caz contrar.
				Pentru implementarea functiei am folosit functia hash din tabela hash pentru a determina pozitia listei din care ar putea face parte celula.
				Daca pointer-ul de la accea pozitie este "NULL", atunci lista e vida, deci intorc "NULL".
				Compar "Key" din celula de inceput a liste si "Key" primit ca parametru si daca sunt identica intorc adresa primei celule, altfel parcurg lista de la a 2 a
			celula din lisat cat timp celula curenta este diferita de prima celula din lista, folosind structura repetitiva "for".
				Daca nu s-a returnat nimic pana la final, inseamna ca "Key" nu exista in lisat si returnez la final "NULL".


		14. Functia "void Inserare_ordonata(TLG element, ALG lista, TFCmp fcmp)":

				Functia primeste ca parametri un pointer la o zona de memorie in care e alocat spatiu pentru o celula de lista, adresa unui pointer la prima celula dintr-o lista
			si un pointer la o functie de tipul "TFCmp" si realizeaza isnerarea ordonata a elementului in lista pe baza functiei "fcmp".
				Pentru implementarea acestei functii am verificat daca lista este vida, ccaz in care inseram celula, aceasta devenind inceputul listei.
				Daca lista era nevida comparam cu prima celula din lisat , folosind fucntia fcmp si daca aceasta returna o valoare pozitiva inseamna ca trebuia sa inserez inaintea
			primei celule din lista, caz in care modififcam adresa pointer-ului care puncta catre prima celula din lista.
				Daca nici acest caz nu era valabil parcurgeam lista de la 2 a celula din lisat cat timp celula curenta este diferita de prima celula din lista.
				Daca ajungeam tot pe prima celula din lisat, inseamna ca trebuia sa inserez la coada listei, iar daca nu ajungeam la inceputul listei, inseamnca ca inserez in interiorul
			listei.
				Refac legaturile celulei de inserat cu celulele intre care trebuie inserata celula.
	

		15. Functia "void Muta(TLG element, TH *tab_hash, TLG *aux, TFCmp fcmp)":

				Functia primeste ca parametru un pointer la o zona de memorie in care este alocata o celula, un pointer la o zona de memorie in care este alocata o tabela hash, un pointer
			de tip "TLG" si un pointer la o functie de tip "TFCmp" si muta fiecare element din tabela hash in noul vector de pointeri, "aux".
				Pentru implementarea functiei am folosit structura repetitiva "for" pentru a parcurga vectorul de pointeri din tabela hash si pentru fiecare pointer am verificat daca 				acesta este "NULL", caz in care lista este vida, iar daca nu este "NULL", parcurgeam lisat de la a 2 a celula folosind structura repetitiva "for", cat timp celula curenta este
			diferita de prima celula.
				Pentru fiecare celula din lista folosesc functia hash din tabela pentru a determina noua pozitie a celulei si apelez functia "Inserare_ordonata" pentru a insera ordonat 				celula.


		16. Functia "void Realoca(TH *tab_hash)":

				Functia primeste ca parametru un pointer la o zona de memorie in care este aclocata tabela hash, dubleaza numarul de pointeri din vectorul de pointeri din tabela si 
			gaseset noua pozitie a fiecarei celule din vechea tabela.
				Pentru implementarea functiei am alocat spatiu de memorie pentru un vector cu 2*M pointeri. Daca alocarea se efectua incepeam mutarea fiecarei celule din vechea tabela
			in noua tabela.
				Pentru mutarea fiecarei celule am parcurs vechea tabela de la 0 pana la jumatae minus 1, deoarece o dublasem mai inainte, folosind structura repetitiva "for", iar in caz
			in care pointerul era diferit de "NULL", lista era nevida, parcurgeam lisat de la a 2 a celula din lista, folosind structura repetitiva "for", cat timp celula curenta este diferita
			de prima celula.
				Pentru fiecare celula aplicam functia "Muta" descrisa mai sus.
				Aplic separat functia "Muta" pentru prima celula din lisat pentru a putea avea o conditie de oprire a "for-ului" de mai sus.
				Eliberez spatiu alocat pentru vechea tabela.
				Fac ca pointer-ul ce puncta catre vechea zona de memeorie sa puncteze catre zona de memorie in care este alocata noua tabela hash.


		17. Functia "void set(char *Key, char *Value, TH *tab_hash)":

				Functia primeste ca parametri 2 pointeri la zone de memorie in care sunt alocate 2 siruri de caractere si un pointer la o zona de memorie in care este alocata tabela hash.
				Functia aloca s[atiu pentru o celula ce contine pe "Key", "Value" si pe "Frequency" il initializeaza cu 0.
				Pentru implementarea functiei am verificat daca exista vreo celula ce il contine pe "Key" in tabela hash cu functia "Verifica_existenta" descrisa mai sus.
				Daca functia intorcea "NULL", inseamna ce celula nu exista in lista si trebuie adaugata.
				Aloc o celula noua ce contine pe "Key" si "Value" si doar daca alocarea a avut succes trec la pasii urmatori.
				Verific daca numarul de celule curente este strict mai mare decat 2*M, caz in care apelez functia "Realoca" descrisa mai sus.
				Ma folosesc de functia hash a tabelei hash pentru a determina pozitia listei din care ar putea face parte celula nou alocata.
				Daca lista este vida, noua celula va fi prima celula din lista.
				Altfel daca numarul de elemente din lista respectiva este mai mare sau egal cu M, apelez functia "StergeCelulaG" descrisa mai sus pentru a sterge ultima celula din lista
			si decrementez numarul de celule curente din tabela hash.
				Daca exista in lisat doar o celula modifica adreasa de icneput a listei inserand noua celula, altfel inseram orodonat in lista.
				Posibil ca dupa stergere lista sa fie vida asa ca mai verifica o data acest lucru dupa care inserez celula noua.
				Daca lista era nevida apelez functia "Inserare_ordonata" descrisa mai sus.
				La final incementez numarul de celule curente din tabela hash.


		18. Functia "char *get(char *Key, TH *tab_hash, FILE *iesire)":

				Functia primeste ca parametru un pointer la o zona de memorie unde este alocat un sir de caractere, un pointer la o zona de memeorie unde este alocata o tabela hash si
			un pointer la un fisier, fisier in care voi scrie ceva si returneaza NULL sau valoarea "Value" din celula ce il  contine pe "Key" sau "NULL" daca nu exista o astfel de celula.
				Pentru implememtarea functiei am folosit functia "Verifica_existenta" descrisa mai sus pentru a verifica daca celula ce il contine pe "Key" exista, iar in caz contrar
			printam in fisier "NULL" si returnam tot "NULL".
				Daca functia "Verifica_existenta" returna o adreasa de memorie diferita de "NULL" inseamnca ca o astfel de celula exista in  lista, il incremnetam pe "Frequency" din
			celula respectiva, facand cast la tipul "TSite" pointer a void pointer-ului info din celula.
				Dupa aceea rupeam celula respectiva din lisat refacand legaturile dintre celula de dinainte si cea de dupa.
				Dupa aceea apelam functia de "Inserare_ordonata" descrisa mai sus pentru a insera ordonat celula in lisatrespectiva, deoarece l-am crescur pe "Frequency" si  trebuia
			modificata si ordinea celulelor, conform enuntului temei.
				La final returnam valoarea "Value" printata in fisier.


		19. Functia "void Remove(char *Key, TH *tab_hash)":

				Functia primeste ca parametri un pointer la o zona de memorie in care este alocat un sir de caractere si un pointer la o zona de memorie in care este alocata o tabela hash
			si sterge celula care il contine pe "Key", daca aceasta exista.
				Pentru implementarea acestei functii am folosit functia "Verifica_existenta" descrisa mai sus, iar in cazul in acre aceasta returna "NULL: nu stergeam nimic, deoarece celula
			nu exista.
				Daca rezultatul era unul diferit de "NULL", folosesc functia hash din tabela hash pentru a afla pozitia listei din care face parte celula.
				Daca celula era singura in lista o sterg si fac lisat vida.
				Altfel daca lista contine cel putin 2 elemente si prima ccelula trebuie stearsa, refac legaturile si sterg prima celula.
				Daca celula de sters este inauntrul listei, fac legaturile dintre cea de dinainte si cea de dupa si sterg celula.
				

		20. Functia "void print(TH *tab_hash, FILE *iesire)":

				Functia primeste ca parametri un pointer la o zona de memorie in care este alocata o tabela hash si un pointer la un fisier si scrie toate valorile "Value" a tuturor 				celulelor din lista.
				Pentru implemenatrea functiei am folosit structura repetitiva "for" pentru a parcurge vectorul de pointeri si pentru fiecare pointer ce puncta la inceputul unei liste
			verificam daca lista e vida, iar in caz de nevida afisam "Value" din prima lista si parcurgeam lista de la a 2 a celula cat timp celula curenta e diferita de prima si afisam "Value"
			facand cast la tipul "TSite" pointer a lui info pentru a putea accesa campul "Value".


		21. Functia "void print_list(int index, TH *tab_hash, FILE *iesire)":

				Functia primeste ca parametri un numar intreg, un pointer la o zona de memorie in care este alocata o tabela hash si un pointer la un fisier si scrie toate valorile "Value" 				a tuturor celulelor din lista de pe pozitia "index".
				Pentru implementarea acestei functiei am procedat la fel ca la functia "print" descrisa mai sus doar ca nu ami parcurg vectrul de pointeri, ci ma duc direct la lista de
			pe pozitia "index".
		
	
		22. Functia "void Start(FILE *intrare, FILE *iesire, TH **h)":

				Functia primeste ca parametri 2 pointeri la fisiere, unul de intrare si unul de iesire si efectueaza comenzile date din fisierul de intrare si printeaza rezultatele in 
			fisierul de iesire.
				Pentru implementarea functiei am luat un "buffer" pe care l-am alocat cu un MAX definit la inceputul programului.
				Cat timp puteam citi  coemnzi din fisier n buffer identificam comanda si parametrii cu ajutorul functiei strtok, iar la final executam comanda respectiva cu parametrii
			identificati.


		23. Fuctia "int main( int argc, char *argv[] )":

				Functia primeste numar variabil de parametri si foloseste funtiile "IniTH", "Start" si "StergeTabelaG" descrise mai sus si returneaza 0.
				


	II. Ce a fost mai greu legat de implemenatare:

			Cred ca cel mai greu luru in timpul temei a fost sa inteleg de ce imi luam "Segmentation fault(core dumped)" cand comentam o singura linie de cod, dupa care am luat functia "set"
		de la 0 si am refacut-o.
			De asemenea, a mai fost greu pana mi-am facut functiile de plecare: cele de alocare a tabelei, definirea structurilor, a tipurilor functiilor, car nu neaparat ca a fost greu, 			deoarece au fost facute la laborato, dar a durat mult, cam 7 ore, pentru a le si verifica buna comportare.

	III. Punctaj pe checker-ul local:

			Checker-ul local imi arata, la fel ca si cel de pe "https://vmchecker.cs.pub.ro/ui/#SDCB" 105 puncte.

				 
				 			

