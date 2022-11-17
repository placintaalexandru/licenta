function [R] = Algebraic( nume_fisier, d )

% citesc cele 2 matrice pentru a calcula matricea M din formula

	[Mat_ad Mat_vec N val1 val2] = citire( nume_fisier );

% construiesc vectorul plin de 1

	v1( 1 :  length( Mat_ad(:, 1) ), 1 ) = 1;
	I = eye( N );

% calculez matricea M din formula
	
	M = ( Inversa( Mat_vec ) * Mat_ad )';
	R = Inversa( I - ( d * M ) )  * double( ( 1 - d ) / N ) * v1;

endfunction	
