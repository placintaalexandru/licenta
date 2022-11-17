function [R] = Power( nume_fisier, d, tol )

% citesc construiesc matricele si citesc numarul de linii din fisier 

	[Mat_ad Mat_vec N val1 val2] = citire( nume_fisier );

% construiesc vectorul plin de 1

	v1( 1 :  length( Mat_ad(:, 1) ), 1 ) = 1;

% construiesc matricea E din formula de la task 3

	E = v1 * v1';

% calculez matricea M din formula, asa cum se calcula si la celelalte 2 task-uri

	M = ( Inversa( Mat_vec ) * Mat_ad )';

% conform substitutiei din enuntul task-ului 3 determin matricea P

	P = ( d * M ) + ( ( 1 - d ) / N ) * E;

	R = v1 / N;

% apelez metoda puterii directe pentru a afla pe R

	R = PutereDirecta( P, R, tol );

end


	
