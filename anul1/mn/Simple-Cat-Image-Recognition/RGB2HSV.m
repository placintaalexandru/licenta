function [H S V] = RGB2HSV(r, g, b)
  
% determin dimensiunea unei matrice de culoare pentru a sti dimensiunea necesara intializarii matricelor H, S si V din reprezentarea HSV

  [linii coloane] = size(r);

% initializez cele 3 matrice

  H(1 : linii, 1 : coloane) = 0;
  S(1 : linii, 1 : coloane) = 0;
  V(1 : linii, 1 : coloane) = 0;

% impart valorile la 255, cum spune algoritmul din pdf-ul ce contine enuntul temei 1

  R = double(r) / 255;
  G = double(g) / 255;
  B = double(b) / 255;

% determin matricea ce contine pe fiecare pozitie maximul dintre R(i), G(i) si B(i), dar si pe cea care contine minimul si calculez delta ca diferenta lor
 
  C_max = max(max(R, G), B);
  C_min = min(min(R, G), B);
  delta = C_max - C_min;

% cum in algoritm trebuie impartit la delta, am considerat ca pe pozitiile unde delta este diferita de 0 sa aplic vectorizarea algoritmul pe baza matricei
% de adevar data de, spre exemplu, de (C_max == R & delta != 0) care intooarce o matrice de adevar ce are 1 pe pozitiile in care elementele de pe acele pozitii
% din matricea R si matricea C_max sunt egale. Analog pentru celelalte variante ale matricelor de adevar de mai jos.
  
  H(C_max == R & delta != 0) = 60 * mod( ( G(C_max == R & delta != 0) - B(C_max == R & delta != 0) ) ./ delta(C_max == R & delta != 0), 6);
  H(C_max == G & delta != 0) = 60 * double( ( ( B(C_max == G & delta != 0) - R(C_max == G & delta != 0) ) ./ delta(C_max == G & delta != 0) ) + 2);
  H(C_max == B & delta != 0) = 60 * double( ( ( R(C_max == B & delta != 0) - G(C_max == B & delta != 0) ) ./ delta(C_max == B & delta != 0) ) + 4);
 
  H = double(100 * H) / 360; 
  S(delta != 0) = delta(delta != 0) ./ C_max(delta != 0);
  S *= 100;
  V = C_max * 100;

endfunction  
  
