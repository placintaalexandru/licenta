function [w] = learn(X, t)

  [linii coloane] = size(X);
  
% construiesc matricea X tilda prin adaugarea unei coloane plina de 1, asa cu specifica enuntul problemei

  X(1 : linii, coloane + 1) = 1;

% amplific in membrul stang al ecuatiei matriceale X * w = t cu transpusa lui X pentru a-mi construi o matrice patratica, careia, ulterior,
% ii voi aplica descompunera QR, folosind algoritmul Householder, de la laboratorul 3

  t = X' * t;
  X = X' * X;
  
% extrag transpusa lui Q din descompunerea X=Q*R prin metoda Householder de la laboratorul 3

 [Q R] = Householder(X);
 
% dupa descompunere ecuatia matriceala va deveni Q * R * w = X' * t. Inmultesc ecuatia in partea stanga cu Q', care e inversa lui Q, deoarece Q e matrice ortogonala

 t = Q * t;

% raman cu ecuatia matriceala R * w = Q' * x' * t, unde R este o matrice superior triunghiulata
% rezolv sistemul superior triunghiulat R * w = t, folosind algoritmul de la laboratorul 2

 w = SST(R, t);

endfunction
