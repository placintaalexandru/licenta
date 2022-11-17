function value = bilerp(img, row, col)
    % Folositi interpolare biliniara pentru a estima intensitatea imaginii
    % in pozitia row, col

    %TODO

	value = 0;

	if ( ( floor( row ) == row ) & ( floor( col ) == col ) )
		
		value = img( row, col );
	else

% aflu dimensiunea matricei data ca parametru

		[linii coloane] = size( img );

% linia, respectiv coloana inferioara intre care se afla punctul reprezinta chiar partea intreaga a lui "row", respectiv "col"

		coloana1 = floor( col );
		linie1 = floor( row );
		coloana2 = coloana1 + 1;
		linie2 = linie1 + 1;
	
		aux = img';

		if ( ( coloana2 <= coloane ) & ( linie2 <= linii ) )
	
			value1 = mylerp( coloana1, aux( coloana1, linie1 ), coloana2, aux( coloana2, linie1 ), col );
			value2 = mylerp( coloana1, aux( coloana1, linie2 ), coloana2, aux( coloana2, linie2 ), col );
			value = mylerp( linie1, value1, linie2, value2, row );
		endif
	endif

endfunction
