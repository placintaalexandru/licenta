function [Q, R] = gram_schmidt(A)

	[m n] = size(A);
	Q = zeros(m,n);
	R = zeros(n);
	
	for j = 1 : n
		R(1:j-1,j) = Q(:,1:j-1)' * A(:,j);
		
		s = zeros(m,1);
		s = Q(:, 1:j-1) * R(1:j-1, j);
		
		aux = A(:,j) - s;		
		
		R(j,j) = norm(aux,2);
		Q(:,j) = aux/R(j,j);
	endfor
endfunction
