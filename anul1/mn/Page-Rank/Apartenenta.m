function [y] = Apartenenta( x, val1, val2 )

% reprezinta functia apartenenta din task-ul 4 care trebuie sa fie continua pe intervalul [0; 1]

	a = double( 1 ) / ( val2 - val1 );
	b = double( val1 ) / ( val1 - val2 );

% y de pe pozitiile in care valorile vectorului x sunt in intervalul [0; val1) sunt 0

	y( x >= 0 & x < val1 ) = 0;

% y de pe pozitiile in care valorile lui x sunt in intervalul [val1; val2] iau valoarea functiei apartenenta

	y( x >= val1 & x <= val2 ) = a * x( x >= val1 & x <= val2 ) + b;

% y de pe pozitiile in care valorile lui x sunt in intervalul (val2; 1] sunt 1

	y( x > val2 & x <= 1 ) = 1;

endfunction
