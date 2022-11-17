function [solutie] = SST(A, b)

% rezolva un sistem superior triunghiulat

  [linii n] = size(A);

% initializez vectorul coloana de solutii 

  X(1:n) = 0;

% transpun vectorul, deoarece solutia ecuatiei matriceale A * X = b, unde A e o matrice si b este un vector coloana, este un vector coloana

  X = X';

% calculez valoarea ultimului element

  X(n) = b(n)/A(n, n);

% aplic algoritmul de la laboratorul 3 pentru determinarea valorilor de pa pozitiile [1; n - 1]
  
  for i = n - 1 : -1 : 1
    
    s = A(i, i+1 : n) * X( i + 1 : n);
    X(i) = (b(i) - s) / A(i, i);
    
  endfor
 
 solutie = X;
 
endfunction
