function [p] = evaluate(cale, w, tip_histograma, count_bins)

% aflu numarul de linii ale vectorului coloana

  [dim aux] = size(w);

% initializez variabilele ce imi vor oferi numarul de identificari corecte

  corect_cats = 0;
  corect_notcats = 0;
  
% construiesc numele celor 2 directoare

  nume_dir_cats = strcat(cale, "/cats/");
  nume_dir_notcats = strcat(cale, "/not_cats/");

% stochez datele fisierelor din cele 2 directoare: cats si not_cats

  fisiere_cats = dir(nume_dir_cats);
  fisiere_notcats = dir(nume_dir_notcats);

% aflu numarul de fisiere din cele 2 directoare

  [number_cats aux] = size(fisiere_cats);
  [number_notcats aux] = size(fisiere_notcats);

  if (strcmp(tip_histograma, "RGB") == 1)

% calculez numarul de identificari corecte pentru directorul cu fisiere cu pisici pentru histograma de tip RGB
  
  	for i = 3 : number_cats

% obtin calea fisierului i din directorul curent prin concatenarea la numele directorului curent a numelui fisierului caruia vreau sa ii obin calea
    
   		nume_fisiere_cats = strcat(nume_dir_cats, fisiere_cats(i).name);

% aplic histograma de tip RGB

   		v = rgbHistogram(nume_fisiere_cats, count_bins);

% aplic histograma de tip RGB

   		v = [v 1];

% conditia pentru a contine pisici
  
    		if (w' * v' > 0)
      			corect_cats++;
    		endif
  	endfor

% calculez numarul de identificari corecte pentru directorul cu fisiere fara pisici

  	for i = 3 : number_notcats

% obtin calea fisierului i din directorul curent prin concatenarea la numele directorului curent a numelui fisierului caruia vreau sa ii obin calea
    
    		nume_fisiere_notcats = strcat(nume_dir_notcats, fisiere_notcats(i).name);

% aplic histograma de tip RGB

    		v = rgbHistogram(nume_fisiere_notcats, count_bins);

% mai adaug 1 la final pentru a putea face produsul scalar cu w

    		v = [v 1];

% conditia pentru a nu contine pisici

    		if (w' * v' < 0)
   		   corect_notcats++;
    		endif
  	endfor
   endif

   if (strcmp(tip_histograma, "HSV") == 1)

% calculez numarul de identificari corecte pentru directorul cu fisiere cu pisici pentru histograma de tip HSV
  
  	for i = 3 : number_cats

% obtin calea fisierului i din directorul curent prin concatenarea la numele directorului curent a numelui fisierului caruia vreau sa ii obin calea

   		nume_fisiere_cats = strcat(nume_dir_cats, fisiere_cats(i).name);

% aplic histograma de tip HSV

   		v = hsvHistogram(nume_fisiere_cats, count_bins);

% mai adaug 1 la final pentru a putea face produsul scalar cu w

   		v = [v 1];

% conditia pentru a contine pisici
  
    		if (w' * v' > 0)
      			corect_cats++;
    		endif
  	endfor

% calculez numarul de identificari corecte pentru directorul cu fisiere fara pisici

  	for i = 3 : number_notcats

% obtin calea fisierului i din directorul curent prin concatenarea la numele directorului curent a numelui fisierului caruia vreau sa ii obin calea

    		nume_fisiere_notcats = strcat(nume_dir_notcats, fisiere_notcats(i).name);

% aplic histograma de tip HSV

    		v = hsvHistogram(nume_fisiere_notcats, count_bins);

% mai adaug 1 la final pentru a putea face produsul scalar cu w

    		v = [v 1];

% conditia pentru a nu contine pisici

    		if (w' * v' < 0)
   		   corect_notcats++;
    		endif
  	endfor
   endif

% calculez porcentul care e dat de catul dintre numarul de imagini recunoscute corect si numarul total de imagini 
  
  p = ((corect_cats + corect_notcats) / (number_cats + number_notcats - 4) );
  p *= 100;
  
endfunction 
  
