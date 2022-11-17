  
  In urma analizei efectuate folosind cele 2 tipuri de histograme propuse de aceasta tema, am obtinut urmatoarele rezultate:

  Cea mai mare acuratete pentru histograma RGB a fost obtinuta pentru count_bins = 20, acest lucru dand o acuratete de 85,714% a pozelor.
  Cea mai mare acuratete pentru histograma HSV a fost obtinuta pentru count_bins = 55, acest lucru dand o acuratete de 92.063% a pozelor. 


  Modul de implementare al functiilor:

  Task-ul 1: Functia rgbHistogram("path to an image", count_bins)

  		Aceasta functie realizeaza histograma RGB a unei imagini ce se gaseste la calea path to an image.
		Cu ajutorul functiei "imread" care primeste ca parametru calea catre imaginea respectiva am deschis imaginea sub forma unui tablou numeric cu 3 dimensiuni.
		In loc sa obtin 3 vectori pe care sa ii concatenez la final, am hotarat sa introduc direct in vectorul rezulatat, ce poarta numele vector_RGB, stiinde ca 
	count_bins erau pentru nuantele de rosu, urmatoarele  count_bins pentru verde si ultimele count_bins pentru albastru.
		Pentru realizarea acestei operatii am apelat la o matrice de adevar, care imi da elementele ale caror valoare pentru nuante sunt in intervalul precizat in pdf.
		Pentru a numara elementele am apelat functia "size" si, ca parametru pentru aceasta am dat imagine(matrice de adevara) (intoarce un vector cu elementele de pe pozitiile
	in care matricea de adevar este 1; imagine fiind tabloul tridimensional ce contine nunatele celor 3 culori: rosu, verde si albastru).
		Aplicand functia "size" pe vectorul descris mai sus obtin chiar valorile corespunzatoare pentru primele count_bins elemente din histograma RGB.
		Analog, se poate observa in cod ca am procedat astfel si pentru celelalte 2 culori, verde si albastru.
  
   
   	     Functia RGB2HSV(r, g, b)

		Aceasta functie primeste 3 parametri, acestia reprezentand cate o matrice din tablol tridimensional oferit de functia "imread" atunci cand deschid o imagine in format RGB.
		Cu ajutorul actestei functii fac tranzitia de la reprezentarea unei imagini din format RGB in format HSV, pentru creea, ulterior, histograma HSV ceruta de task-ul 2.
		A fost nevoie sa cunosc dimensiunea unei matrice din cele 3, deoarece ele au dimensiuni egale, acest lucru fiindu-mi necesar pentru a initializa matricele H, S si V.
		Am calculat maximul (C_max), repsectiv minimul (C_min), dintre elementele din cele 3 matrice de pe pozitiile corspondente, respectiv diferenta (delta = C_max - C_min) dintre maximele si 	minimele de pe pozitiile corespondente.
		Dupa aceasta, pe pozitiile in care delta era nenul si maximele erau egale cu valoare elementelor din matricea nuantelor de rosu, acest lucru fiind dat de o matrice de adevar, spre
      exemplu (C_max == R & delta != 0), pentru cazul in care ma raportam la matricea nuantelor de rosu.
		Analog, se poate observa in cod ca am procedat la fel si pentru celelalte 2 culor, verde si albastru. 
		

  Task-ul 2: Functia hsvHistogram("path to an image", count_bins)

		Aceasta functie lucreaza exact in acelasi mod ca si functia rgbHistogram de la Task-ul 1, cu exceptia ca in loc sa numere din cele 3 matrice date de tabloul tridimensional
	obtinut prin deschiderea imaginii folosind functia "imread", aceasta foloseste functia de conversie RGB2HSV ce construieste alte 3 matrice prnind de la cele 3 ce alcatiesc tabloul dat 
	de functia "imread".
		Aceste 3 matrice nou-create sunt folosite de functia hsvHistogram pentru a realiza histograma HSV pe acelasi principiu de lucru ca si functia rgbHistogram de la Task-ul 1.


  Task-ul 3: Functia preporcess("path to a directory", tip_histograma, count_bins)

		Aceasata functie realizeaza acumularea tutoror histogramelor iamginilor din cele 2 subdirectoare(cats si not_cats) din directoru care se gaseste la calea "path to a directory".
		Pentru obtinerea caii fiecarui subdirector am folosit functia "strcat" pentru a concatena numele subdirectorului la sirul de caractere "path to a directory".
		Pentru obtinerea tuturor histogramelor a fost necesara parcurgerea tuturor fisierelor.
		Parcurgerea tuturor fisierelor am inceput-o cu folosirea functiei "dir", al carei parametru a fost calea catre directorul din care voiam sa iau numele fisierelor.
		Acesasta functie mi-a returnat date despre fiecare fisier in parte, aceaste date fiind grupate unele dupa altele pentru fiecare fisier.
		Am aflat numarul fisierelor din directorul repsectiv cu ajutotul functiei size. Deoarece in fiecare director exista 2 fisiere ascunse("." si ".."), dar mai ales pentru ca ni s-a
	garantat ca in directoare nu vor fi si fisiere ascunse, pentru parcurgerea tuturor fisierelor am folosit "for" de la 3(pentru a sari cele 2 fisiere ascunde) pana la nuamrul de fisiere si 
	pentru fiecare fisier in parte calculam histograma ceruta (fiind specificata de variabila tip_histograma primita ca parametru) si o puneam pe linia cu 2 mai putin fata de variabila care era in 	"for".
		Pentru realizarea vectorului de etichete "t" am ales sa introduc mai intai valorile de 1 si apoi pe cele de -1, afland cate imagini cu pisici si fara psici sunt, iar din aceasta scad 4,
	deoarece vor fi 4 fisiere ascunse pentru 2 directoare diferite.
		Am descris mai sus cum am parcurs fisierele dintr-un singur director, neavand importanta daca e "cats" sau  "not_cats", deoarece cum fac pentru unul in acelasi fel fac si pentru celalalt.
		La final, pentru obtinerea matricei "X" ce contine pe fiecare linie o histograma a fiecarei imagini a trebui sa concatenez cele 2 matrice "X_cats" si "X_notcats". 
		Pentru concatenarea celor 2 matrice, dar sa fie una sub cealalta, am concatenat transpusele lor si rezultatul a fost o matrice pe care am concatenat-o din nou.

		
	      Functia learn(X, t)

		Aceasta functie primeste ca parametri matricea de invatare si vectorul de etichete, ambele elemente fiind obtinute la functia prezentata mai sus.
		Dupa ce am concatenat o coloana plina de 1 la matricea X a trebuit sa rezolv sistemul X*w=t.
		Am inmultit ecuatia matriceala la stanga cu transpusa amtricei X, dupa care am ales ca produsul dintre matricea transousa a lui X si matricea X sa il descompun folosind metoda Householder
	de descompunere intr-o matrice ortogonala "Q" si o matrice superior ortogonala "R", acest algoritm fiind prezentat in cadrul cursului si in cadrul laboratorului 3.
		Dupa aceasta descompunere am inmultit la stanga ecuatia matriceala cu transpusa lui "Q" care este si inversa sa, deoarece "Q" este o matrcie superior triangulata superior.
		Totul se rezuma la rezolvarea unui sistem superior triunghiulat, iar pentru rezolvarea acestuia am folosit functia "SST" de la laboratorul 2.

   
   Task-ul 4: Funcctia evaluate("path to a directory", w, tip_histograma, count_bins)

		Aceasta functie realizeaza evaluarea tuturor pozelor din directorul care se afla la calea "path to a directory" ce contine 2 subdirectoare: "cats" si "not"cats".
		Pentru evaluarea fiecarei imagini atrebui sa parcurg fiecare director si apoi toate fisierele din directorul curent.
		Parcurgerea este cea descrisa la functia preprocess de la Task-ul 3, acest lucru fiind evident si in codul functiei "evaluate".
		Daca eram la in diretorul "cats" faceam histograma specificata de tipul histogramei la care mai adaugam 1 si efectuam produsul scalar cu w(vectorul de predictie) si daca produsul scalar
	era pozitiv inseamnca ca predictia era corecta si il incrementam pe corect_cats.
		Analog si pentru "not_cats", dar produsul scalar trebuia sa fie negativ si il incrementam pe "not_cats".
		La final pentru a returna procentul faceam impartirea dintre suma variabilelor "corecte_cats" si "corect_notcats" si nuamrul total al fisierlor minus cele  fisiere ascunse(cate 2 pentru
	fiecare director).
		Inmulteam valoarea obtinuta cu 100, fiind un procent.   


 


		
  		
