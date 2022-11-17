function value = mylerp(x1, y1, x2, y2, x)

% calculeaza valoare in punctul "x" a unei functii de gradul 1 care trece prin 2 puncte date: (x1, y1) si (x2, y2)

	panta = double( y2 - y1 ) / ( x2 - x1 );
	value = panta * ( x - x1 ) + y1;

endfunction
