function [Inv] = Inversa(A)

% aflu numarul de linii si coloane ale amtricii A

	[linii coloane] = size(A);

% aplic algoritmul Gram-Schmidt pe matriea A pentru a gasi descompunerea QR

	[Q R] = gram_schmidt(A);

% transpun matricea ortogonala Q pentru a putea rezolva cele "coloane" sisteme superior triunghiulate

	Q = Q';

% voi rezolva sistemul superior triunghiulat R*Inv = Q'
% pentru fiecare valoare a lui j rezolv un sistem superior superior triunghiulat

	for j = 1 : coloane

		i = Q( :, j );
		Inv( :, j ) = SST( R, i );

	end
end   
