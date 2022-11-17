function [min1 min2] = minime(a, T)

% determin coordonatele intregi minime care apar in ura rotirii
% singurele cazuri posibile sunt in calturile imaginii, de aceea pastrez doar cele 4 coordonate

	min1 = 0;
	min2 = 0;

	[linii coloane] = size( a );

% pe fiecare coloana a matricei am cate o pozitie din matricea de pixeli

	v = double( [1 1 linii linii ; 1 coloane 1 coloane] );

	for j = 1 : 4

		v( :, j ) = T * v( :, j );

		if ( min1 > v( 1, j ) )

			min1 = v( 1, j );
		endif

		if ( min2 > v( 2, j ) )
		
			min2 = v( 2, j );
		endif	
	endfor

% am nevoie de vaori intrgi ale minimelor, ele reprezentand valorile pe care le voi scadea pentru a translata imaginea astfel in cat sa incapa in noua matrice

	min1 = round( min1 );
	min2 = round( min2 );

endfunction 
