function [Q R] = Householder(A)

% returneaza trasnspusa matricei Q din descompunerea A=Q*R prin metoda Householder

  [linii coloane] = size(A);
  
  t = min(linii - 1, coloane);
  
  H = eye(linii);
  
  for p = 1 : t
  
    I = eye(linii);
    H1 = zeros(linii);
    
    sigma =  0 - (sign(A(p, p))*(norm(A(p : linii, p), 2)));

    v(1 : p-1) = 0;   
    
    v(p) = A(p, p) + sigma;
    
    v(p+1 : linii) = A(p+1 : linii, p);
    
    norma = v*v';
    
    H1 = (I - (2/norma)*v'*v);
   
    H = H1*H;
    A = H1*A;
    
  endfor
  
  R = A;
  Q = H;
  
endfunction
