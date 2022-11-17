function [R] = PutereDirecta( A, y, tol )

% contine implementarea metodei puterii directe 

	while ( 1 )
		aux = y;
		z = A * y;
		y = z / norm( z, 1 );

% acest proces continua cat timp eroarea este mai mare decat toleranta
	
		if ( norm( A * y - aux ) < tol )
			R = y;
			break;
		end
	end
	
end
