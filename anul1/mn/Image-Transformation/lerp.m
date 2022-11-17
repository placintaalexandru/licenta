function value = lerp(v, x)
    % Interpolare liniara unidimensionala
    %
    % Inputs
    % ------
    % v: un vector cu valorile functie
    % x: o noua pozitie in care sa se calculeze valoarea functiei

    %TODO

	lungime_vector = length( v );

% initializez valoarea dorita cu 0, iar in cazul in care nu se va modifica la cautare, voi returna 0, conform enuntului temei

	value = 0;

% forma unei functii de gradul 1 este f = m*x + n; m = panta dreptei si n = intersectia cu axa oy

	for i = 1 : lungime_vector - 1

% verifica daca se afla in intervalul [ v( i ); v( i + 1 ) ]

		if ( ( i <= x ) & ( x <= i + 1 ) )

% calculez panta dreptei respective cu formula [ f(b) - f(a) ] / ( b - a ); a = i si b = i + 1

			panta = v( i + 1) - v( i);

% stiind panta si alegand unul din punctele ( i, v( i ) ) sau ( i + 1, v( i + 1 ) ) se obtine matematic valoare unei functii intr-un punct

			value = panta * x + ( v( i ) - panta * i );

% daca am gasit valoarea cautata nu mai are niciun rost sa caut mai departe asa ca opresc cautarea

			break;
		endif
	endfor
endfunction
