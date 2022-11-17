function value = trilerp(stack, row, col, level)
    % Folositi interpolarea triliniara pentru a estima intensitatea unei
    % imagini in pozitia row, col, level.

    %TODO

% calculez dimensiunea imaginii

	[linii coloane nivele] = size( stack );

% gasesc cele 2 nivele intre care se afla punctul respectiv

	nivel1 = floor( level );
	nivel2 = nivel1 + 1;

% verific daca nivelul mai mare este mai mic decat numarul total de nivele

	if ( nivel2 <= nivele )

% aplic functia "bilerp" pe cele 2 matrice de pe cele 2 nivele, dupa care pentru cele 2 valori aplic functia "mylerp" pe cele 2 nivele si cele 2 valori date de functia "bilerp"
 
		value1 = bilerp( stack( :, :, nivel1 ), row, col );
		value2 = bilerp( stack( :, :, nivel2 ), row, col );
		value = mylerp( nivel1, value1, nivel2, value2, level );
	endif

endfunction
