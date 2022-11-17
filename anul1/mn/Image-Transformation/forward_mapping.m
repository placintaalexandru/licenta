function img_out = forward_mapping(img_in, T)
    % Creati o noua imagine prin aplicarea transformarii T pe imaginea
    % img_in (grayscale image), folosind forward mapping.
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

% calculez dimensiunea matricei initiale

	[linii coloane] = size( img_in );

% verifica daca trebuie sa scalez

	if ( ( T( 1, 1 ) == T( 2, 2 ) ) & ( T ( 1, 2 ) == 0 ) & ( T( 2, 1 ) == 0 ) & ( T( 1, 1 ) > 0 ) )
		
% calculez dimsniunile noii matrice dupa marire

		m = floor( T( 1, 1 ) * linii + 1 );
		n = floor( T( 1, 1 ) * coloane + 1 );

		img_out = zeros( m, n );

		for i = 1 : linii
			for j = 1 : coloane

				v = double( [i j]' );
				v = round( T * v + 1);
				
				img_out( v( 1 ), v( 2 ) ) = img_in( i, j );
			endfor
		endfor

% altfel verific daca trebuie sa rotesc

	else

% calculez dimsniunile noii matrice dupa rotire

		n = floor( coloane * abs( T( 1, 1 ) ) + linii * abs( T( 1, 2 ) ) + 1 );
		m = floor( coloane * abs( T( 1, 2 ) ) + linii * abs( T( 1, 1 ) ) + 1 );
		
		img_out = zeros( m, n );
		
% caut minimul negativ pentru a sti cat sa adaug la coordonatele care sunt negative, deci care ies din imagine, fiind in sus

		[min1 min2] = minime( img_in, T );

% parcurg matricea si efectuez transformarile pe fiecare pixel, fac a fel in toate if-urile, dar depinde de forma celor 2 minime; voi specifica in "readme"

		if  ( ( min1 < 0 ) & ( min2 < 0 ) )

			for i = 1 : linii
				for j = 1 : coloane
				
					v = [i j]';
					v = round( T * v );

% imaginea o voi translata in jos cu modului minimului gasit + 1 pentru a nu iesi din cadru si pentru a evita situatiile in care un indice pentru matrice este 0
				
					img_out( v( 1 ) + 1 - min1, v( 2 ) + 1 - min2 ) = img_in( i, j ); 	
			
				endfor
			endfor

		elseif ( ( min1 < 0 ) & ( min2 >= 0 ) )

			for i = 1 : linii
				for j = 1 : coloane
				
					v = [i j]';
					v = round( T * v );
				
					img_out( v( 1 ) + 1 - min1, v( 2 ) ) = img_in( i, j ); 	
				
				endfor
			endfor

		elseif ( ( min1 >= 0 ) & ( min2 < 0 ) )
		
			for i = 1 : linii
				for j = 1 : coloane
				
					v = [i j]';
					v = round( T * v );
				
					img_out( v( 1 ) , v( 2 ) + 1 - min2 ) = img_in( i, j ); 	
				
				endfor
			endfor	
		endif			
	endif
 
endfunction
