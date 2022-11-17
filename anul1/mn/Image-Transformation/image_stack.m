function stack = image_stack(img, num_levels)
    % Creati un image stack pentru o imagine prin manjirea repetata a imaginii
    %
    % Inputs
    % ------
    % num_levels: numarul de imagin care trebuie intors in stack.
    %        img: imaginea de la care se porneste.
    %
    % Outputs
    % -------
    % stack: stack-ul de num_levels imagini

    %TODO

% determin dimensiunea imaginii

	[linii coloane] = size( img );

% initializez stiva de matrice, fiecare matrice avand elementele nule

	stack( linii, coloane, num_levels ) = 0;

% pentru a putrea inmulti matricea K cu una din matricele din stiva, matricea K trebuia sa aiba numarul de coloane egal cu numarul de linii al unei matrice din stiva

	K = ones( 3 ) / 9;

% introduc imaginea initiala in stiva

	stack( :, :, 1 ) = img;

% introduc imagiile urmatoare pe nivelele superioare ale stivei
	
	for i = 2 : num_levels
		
		stack( :, :, i ) = conv2( stack( :, :, i - 1 ), K, 'same' );
	endfor

endfunction
