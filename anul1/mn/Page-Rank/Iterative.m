function [R] = Iterative( nume_fisier, d, tol )

% citesc matricea de adicanta si matricea de vecini din fisier

	[Mat_ad Mat_vec N val1 val2] = citire( nume_fisier );

% construiesc vectorul plin de 1

	v1( 1 :  length( Mat_ad(:, 1) ), 1 ) = 1;

% aflu matricea M din formula; transousa produsului dintre matricea de adiacenta
% si inversa matricei ce contine numarul de vecini pentru o pagina

	M = ( Inversa( Mat_vec ) * Mat_ad )';
	R = v1 / N;

	while ( 1 )

		aux = R;

% lucrez formula din algoritmul iterative din tema

		R = d * M * R + ( ( 1 - d ) / N ) * v1;

% procesul este activ cate timp eroarea absoluta este mai mare decat o toleranta

		if ( norm( R - aux ) < tol )
			break
		end
	end
end
	
