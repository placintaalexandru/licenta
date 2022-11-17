function img_out = transform_image(img_in, k)
    % Scalati imaginea cu un factor k prin aplicarea interpolarii
    % triliniare
    %
    % Inputs
    % ------
    % img_in: imaginea care trebuie transformata.
    %      k: factorul cu care trebuie scalata imaginea.
    %
    % Outputs
    % -------
    % img_out: imaginea transformata 

    % TODO

% calculez dimensiunea matricei

	[linii coloane] = size( img_in );
	img_out = zeros( linii, coloane );

% sunt necesare k+1 imagini pentru stiva

	nr_nivele = floor( k ) + 1;

	stack = image_stack(img_in, nr_nivele);

% aplic functia "trilerp" pentru fiecare pixel din matricea imaginii, pentru a gasii valoarea finala

	for i = 1 : linii
		for j = 1 : coloane

			img_out( i, j ) = trilerp( stack, i, j, k );
		endfor
	endfor
	
end
