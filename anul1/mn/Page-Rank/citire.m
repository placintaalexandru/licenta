function [Matrice_adiacenta Matrice_vecini N val1 val2]= citire( nume_fisier )

% deschid imaginea pentru citire

	fid = fopen( nume_fisier, "r" );

% cum pe prima linie se afla numarul de noduri, voi citi prima data doar un singur element de tip int
	
	N = fscanf( fid, '%d', 1 );

% initializez cele 2 matrice cu elemente nule, fiecare avand N linii si N coloane, deoarece este un reprezentarea de adiacenta a unui graf

	Matrice_adiacenta = zeros( N );
	Matrice_vecini = zeros( N );

% parcurg numarul de noduri

	for i = 1 : N

% citesc numarul nodului

		nod = fscanf( fid, '%d', 1 );

% citresc numarul sau de vecini

		nr_vecini = fscanf( fid, '%d', 1 );

% citesc vectorul de vecini

		vecini = fscanf( fid, '%d', nr_vecini );
		
% in matricea de vecini introduc pe diagonala principala numaul de noduri diferite cu care se invecineaza nodul curent

		Matrice_vecini( nod, nod ) = length( vecini( vecini != nod ) );

% in matricea de adiacenta introduc 1 doar pentru nodurile diferite cu care se invecineaza nodul curent

		Matrice_adiacenta( nod, vecini( vecini != nod ) ) = 1;
	end

	val1 = fscanf( fid, '%f', 1 );
	val2 = fscanf( fid, '%f', 1 );
	
	fclose( fid );
end
		
		
