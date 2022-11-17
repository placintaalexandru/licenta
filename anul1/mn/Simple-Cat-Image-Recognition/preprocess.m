function [X t] = preprocess(cale, tip_histograma, count_bins)
         
% construiesc numele celor 2 cai care contin setul cu pisici, respectiv fara pisici

  nume_dir_cats = strcat(cale, "/cats/");
  nume_dir_notcats = strcat(cale, "/not_cats/");

% stochez in aceast variabila continutul directorului cu nume "nume_dir_cats, datele despre fiecare fisier
  
  fisiere_cats = dir(nume_dir_cats);
  [number_cats aux] = size(fisiere_cats);

% stochez datele fisierelor din cele 2 directoare: cats si not_cats
  
  fisiere_notcats = dir(nume_dir_notcats);
  [number_notcats aux] = size(fisiere_notcats);

% nu iau in calcul primele 2 fisiere ascunse ale directorului, acestea fiin . si ..

% construiesc vectorul de etichete prin alaturarea celor 2 vectori de etichete de 1 pt cats si -1 pt not_cats

  t_cats(1 : number_cats - 2) = 1;
  t_notcats(1 : number_notcats - 2) = -1;

% concatenez cei 2 vectori de mai sus
  
  t = [t_cats t_notcats]';

% procesul de invatare pentru hitograma de tip RGB
  
  if (strcmp(tip_histograma, "RGB") == 1)

% parcurg directorul cu fisiere cu pisici
  
    for i = 3 : number_cats
    
% aflu calea fisierului respectiv si ii construiesc histograma
    
      nume_fisiere_cats = strcat(nume_dir_cats, fisiere_cats(i).name); 
      X_cats(i - 2, : ) = rgbHistogram(nume_fisiere_cats, count_bins);
    
    endfor

% parcurg directorul cu fisiere fara pisici
  
    for i = 3 : number_notcats

% aflu calea fisierului respectiv si ii construiesc histograma
    
      nume_fisiere_notcats = strcat(nume_dir_notcats, fisiere_notcats(i).name);
      X_notcats(i-2, :) = rgbHistogram(nume_fisiere_notcats, count_bins);

    endfor
  endif

% prcesul de invatare pentru histograma de tip HSV
  
  if (strcmp(tip_histograma, "HSV") == 1)

% parcurg directorul cu fisiere cu pisici
  
    for i = 3 : number_cats

% aflu calea fisierului respectiv si ii construiesc histograma
    
      nume_fisiere_cats = strcat(nume_dir_cats, fisiere_cats(i).name); 
      X_cats(i - 2, : ) = hsvHistogram(nume_fisiere_cats, count_bins);
    
    endfor

% parcurg directorul cu fisiere fara pisici
  
    for i = 3 : number_notcats

% aflu calea fisierului respectiv si ii construiesc histograma
 
      nume_fisiere_notcats = strcat(nume_dir_notcats, fisiere_notcats(i).name);
      X_notcats(i-2, :) = hsvHistogram(nume_fisiere_notcats, count_bins);
      
    endfor    
  endif
  
% concatenez cele 2 matrice obtinute prin punerea fiecarei histograme pe cate o linie prin transpunerea matricei obtinuta
% prin concatenarea celor 2 transpuse ale matricelor obtinute din cele 2 directoare

  X = [X_cats' X_notcats']';
  
endfunction
