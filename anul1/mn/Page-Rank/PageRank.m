function [R1 R2 R3] = PageRank( nume_fisier, d, tol )

% citesc din fisier val1, val2 si construiesc matricea de adiacenta si matricea cu numarul vecinilor

	[Mat_ad Mat_vec N val1 val2] = citire( nume_fisier);

% calculez cei 3 vectori prin metodele celor 3 algoritmi

	R1 = Iterative( nume_fisier, d, tol );
	R2 = Algebraic( nume_fisier, d );
	R3 = Power( nume_fisier, d, tol );

% pentru a genera un noufisier de output, concatenez la numele fisierului sirul de caractere .out 
	output = strcat( nume_fisier, ".out" );
	
% deschid fisierul pentru scriere, iar in caz ca el nu exista va fi creat la terminarea programului

	fid = fopen( output, "w" );
	
% afisez ceea ce mi se cere in enuntul temei: numarul de noduri si cei 3 vectori

	fprintf( fid, '%d\n', N );
	fprintf( fid, '\n' );
	
	fprintf( fid, '%f\n', R1( : ) );
	fprintf( fid, '\n' );

	fprintf( fid, '%f\n', R2( : ) );
	fprintf( fid, '\n' );

	fprintf( fid, '%f\n', R3( : ) );
	fprintf( fid, '\n' );

% iau un vector care va contine toate nodurile
	
	v2 = [ 1 : N ];
	
% ordonez elementele din vectorul R2 si la o interschimbare din R2 interschimn elementele si din vectorul de noduri de pe pozitiile corespunzatoare

	for i = 1 : N - 1
		for j = i + 1 : N

			if ( R2( i ) < R2( j ) )
				aux = R2( i );
				R2( i ) = R2( j );
				R2( j ) = aux;

				aux = v2( i );
				v2( i ) = v2( j );
				v2( j ) = aux;
			endif
		endfor
	endfor

% v1 reprezinta functia apartenneta aplicata pe vectorul R2, iar v1 trebuie calculat conform enuntului temei

	v1 = Apartenenta( R2, val1, val2 );

% afisez nodul si valoarea respectiva a lui v1

	for i = 1 : N

		fprintf( fid, '%d %d %f\n', i, v2( i ), v1( i ) );
	endfor

% inchid fisierul deschis pentru scriere

	fclose( fid );

endfunction

	
