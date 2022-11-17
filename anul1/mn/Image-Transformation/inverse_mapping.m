function img_out = inverse_mapping(img_in, T)
    % Creati o noua imagine prin aplicarea transformarii T pe imaginea
    % img_in (grayscale image), folosind inverse mapping si interpolare
    % biliniara
    %
    % Inputs
    % ------
    % img_in: imaginea care trebuie sa fie transformata.
    %      T: transformarea care trebuie aplicata asupra imaginii.
    %         matrice de 2x2.
    %
    % Outputs
    % -------
    % img_out: imaginea transformata (grayscale).

    %TODO

	warning 'off'

	inversa = inv( T );

% determin dimensiunea matricei introduse ca parametru

	[linii coloane] = size( img_in );

% verific daca trebuie sa scalez

	if ( ( T( 1, 1 ) == T( 2, 2 ) ) & ( T ( 1, 2 ) == 0 ) & ( T( 2, 1 ) == 0 ) & ( T( 1, 1 ) > 0 ) )

% calculez dimensiunile noii matrice dupa marire

		m = floor( T( 1, 1 ) * linii ) + 1;
		n = floor( T( 1, 1 ) * coloane ) + 1;
		img_out = zeros( m, n );

		for i = 1 : m
			for j = 1 : n
				
% aplic transformarea inversa a lui T pentru o pereche " [i j] " din matricea rezultat dupa carea aplic functia bilerp

				v = double( [i j]' );
				v = inversa * v;

% completez cu valoarea data de interpolarea din functia "bilerp" pe pozitia " [i j] " in matricea rezultata

				if ( ( linii - v( 1 ) <= linii - 1 ) & ( coloane - v( 2 ) <= coloane - 1 ) )
					
					img_out( i, j ) = bilerp( img_in, v( 1 ), v( 2 ) );
				endif
			endfor
		endfor
				
% altfel verific daca trebuie sa rotesc
	
	else
		
% determin dimensiunile noii imagini dupa rotire

		n = floor( coloane * abs( T( 1, 1 ) ) + linii * abs( T( 1, 2 ) ) + 1 );
		m = floor( coloane * abs( T( 1, 2 ) ) + linii * abs( T( 1, 1 ) ) + 1 );
		img_out = zeros( m, n );

% cum in functia "forward_mapping" translatam in jos imaginea prin scaderea acelui minim, aici trebuie sa il adun si apoi aplic transformarea inversa
% caut mai intai acel minim ca in functia "forward_mapping"

		[min1 min2] = minime( img_in, T );

		for i = 1 : m
			for j = 1 : n

				v = double( [i + min1 j + min2]' );
				v = inversa * v;

				if ( sum( v > 1 & v < linii & v < coloane ) == 2 )
					
					img_out( i, j ) = bilerp( img_in, v( 1 ), v( 2 ) );
				endif
			endfor
		endfor
	endif

endfunction
