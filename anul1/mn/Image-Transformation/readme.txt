
	Functia "[min1 min2] = minime(a, T)":

		Aceasta funcie primeste ca parametrii a matrice, reprezentand valorile pixelilor unei imagini, si o matrice de transformare si returneaza cele 2 minime, unul pe linii si unul pe coloane, minime pe care le folosesc la 
	translatarea imaginii in fuctiile "inverse_mapping" si "forward_mapping".
		Pentru implementarea acestei functii am luat colturile imagii, acestea fiind dupa rotire cele mai indepartate puncte( punctele de extrem ale imaginii ).
		Am retinut coorodnatele fiecarui pixel intr-un vector, unde fiecare coloana reprezinta un set de coordonate.
		Am parcurs vectorul si pentru fiecare coloana am aplicat tarnsformarea "T" si am analizat daca cele 2 minime trebuie sa ia alte valori in cazul in care obtin valori mai mici decat cele actuale pentru o pereche de 		coordonate dupa ce aplic trasnformarea "T".


	Functia "value = mylerp(x1, y1, x2, y2, x)":

		Functia primeste ca parametrii doua puncte a caror coordonate sunt (x1; y1) si (x2, y2) si calculeaza valoarea functiei de gradul 1 determinata de cele 2 puncte si trece prin punctul x;
		Pentru imeplementarea functiei am caclulat panta dreptei respective, cu ajutorul formulei "panta = double( y2 - y1 ) / ( x2 - x1 )" dupa care am folosit ecuatia matematica a unei drepte ce trece printr-un
	punct si are panta data: "y - y_p = panta * ( x - x_p )" unde (x_p; y_p) reprezinta perechea ce descriu coordonatele carteziene ale punctului prin care trece dreapta.
		Astfel se obtine o functie de gradul 1 ce depinde doar de abscisa x a punctelor, iar eu am calculat acea functie in punctul "x", ultimul din lista de parametrii.

	
	Functia "value = lerp(v, x)":

		Functie primeste ca parametrii un vector de valori si introarce valoarea functiei de gradul 1 in acel punct.
		Pentru implementarea functiei gasesc pozitiile intre care se afla punctul respectiv, iar cele 2 puncte care ma vor ajuta sa determin ecuatia dreptei sunt (i, v( i )), respectiv (i+1, v(i+1)).
		Dupa ce am gasit cele 2 puncte aplic regula descrisa la functia "mylerp" de mai sus si determin valoarea functiei in punctul "x".


	Functia "value = bilerp(img, row, col)":

		Functie primeste ca parametrii o matrice, aceasta reprezentand valorile pixelilor unei imaginii si returneaza valoarea care ar trebui sa se gaseasca la punctul de coordonata (col, row).
		Pentru imeplemntarea acestei functii am folosit functia "floor" pentru a gasi partea intreaga a celor 2 coordonate, "row" si "col", dupa care la aceste 2 parti intregi adaug 1 pentru a gasi cele 2 linii, respectiv
	coloane succesive intre care s e afla punctul de coorodnate (row, col).
		Dupa ce am gasit cele 4 perechi de coorodnate, verific daca cele 2 coorodnate mai mari, "linie2" si "coloana2", sunt mai mici decat numarul de linii, respectiv numarul de coloane ale matrice, pentru a ma asigura ca
	nu ies din dimensiunea matricei.
		Daca nu am iesit din matrice transpun matricea si aplic functia "bilerp" de 2 ori pe cele, de fiecare data pe cate 2 perechi de coordonate si obtin 2 valori, valori ce vor alcatui o coordonatele a 2 puncte, acestea
	determinand o dreapta.
		Dupa ce am gasit aceste 2 valori aplic functia "mylerp" pentru linii, cunoscand cele 2 valori, cele 2 linii si parametrul "row" al punctului.


	Functia "img_out = forward_mapping(img_in, T)":

		Functia primeste ca parametrii o matrice, aceasta reprezentand valorile pixelilor unei imaginii, o matrice de trasnformare si returneaza o matrice ce va reprezenta valorile pixelilor unei noi imagini dupa aplicare
	trasnformarii "T".
		Am verificat daca trebuie sa scalez sau sa rotesc prin verificarea elementelor matricei de transformare:daca elementele de pe diagonala principala sunt pozitile si cele de pe cea secundara sunt 0 atunci scalez, altfel 		rotesc.
		Cand trebuie sa scalez calcuez noile dimensiuni ale imaginii pe baza factorului de scalare care este primul element din matrice.
		Parcurg matricea si pentru fiecare pereche de coordonate "[i j]" aplic matricea de transformare si pentru un punct de la noile coorodnate, valoarea sa va fi aceea de la vechile coordonate din matricea de intrare.
		Cand trebuie sa rotesc procedez fix in acelasi mod, doar ca este posibil ca unele coordonate sa fie negative.
		Pentru a rezolva aceasta problema calculez minimul de pe linie si pe coloana si translatez imaginea atat pe linie cat si pe coloane.
		Dupa calculul celor 2 minime cu functia "minime" descrisa mai sus analizez daca sunt ambele negative, caz in care tanslatez pe ambele axe scanzandu-le, daca unul din ele e pozitiv trasnlatez numai pe o axa, cealalata
	ramanand nemodificata.

		
	Functia "img_out = inverse_mapping(img_in, T)":

		Functia primeste ca parametrii o matrice, aceasta reprezentand valorile pixelilor unei imaginii, o matrice de trasnformare si returneaza o matrice ce va reprezenta valorile pixelilor unei noi imagini dupa aplicare
	trasnformarii "T", dar fara a lasa pixelii morti in imagine.
		Calculez inversa functiei folosind functia "inv".
		Se verifica daca trebuie sa scalez sau sa rotesc exact in acelasi mod ca la functia "forward_mapping".
		Daca trebuie sa scalez, parcurg maticea si pentru fiecare pereche "[i j]" aplic trasnformarea inversa si verifica daca noile coorodnate sunt sunt mai mici deat numarul de linii si coloane ale matricei de intrae si aplic
	functia "bilerp" pentru acea pereche.
		Daca trebuie sa rotesc, parcurg matricea exact ca mai sus, aplic trasnformarea inversa matricei de trasnformare si verific de data aceasta daca cele 2 valori sunt mai mari decat 1 si unt mai mici si decat numarul de linii
	si numarul de coloane.
		

	Functia "stack = image_stack(img, num_levels)":

		Functia primeste ca parametrii o matrice, aceasta reprezentand valorile pixelilor unei imaginii, un numar de nivele si creeaza o stiva de matrice ce contine la baza matricea iniiala.
		Pentru implementarea acestei functii am parcurs nivelele, incepand de la 2, deoarece primul nivel e reprezentat de matricea initiala, iar pentru celelelalte aplic fucntia "conv2".
		

	Functia "value = trilerp(stack, row, col, level)":

		Functia primeste ca parametrii o stiva, coordonatele unui punct si determina valoarea pe care ar trebui sa o aiba functia in acel punct.
		Pentru implemenatrea functiei am gasit nivelele intre care se afla punctul prin aplicarea functiei "floor" pentru a gasi partea intreaga a lui "level" dupa care am verificat daca nivelul superior este mai mic decat 
	nivelul stivei.
		In caz ca conditia de mai sus este indeplinita, aplic functia "bilerp" pe matricele de pe cele 2 nivele, obtinand astfel 2 valori, iar apoi cu aceste 2 valori apelez functia "myerp" ca parametrii cele 2 valori si
	nivelele corespunzatoare celor 2 valori.


	Functia "img_out = transform_image(img_in, k)":

		Functia primeste ca parametrii o matrice, aceasta reprezentand valorile pixelilor unei imaginii, un factor "k" si intoarce imaginea corespunatoare aliasing-ului respectiv.
		Pentru implmenetarea functiei am parcurs fiecare element al matricei si am efectuat functia trilerp pentru a determina valorile pixelilor noii imagini.
		
		
	
