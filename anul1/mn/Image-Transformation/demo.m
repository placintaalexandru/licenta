
pkg load image;
a = imread( "flapping_duck.png" );
b = imread( "flapping_bird.png" );

disp( "rotatie cu 180" );

	T = [ -1 0; 0 -1 ];

	out = inverse_mapping( a, T);
	imwrite( mat2gray( out ), "duck_rot_180.png" );

	out = inverse_mapping( b, T) ;
	imwrite( mat2gray( out ), "bird_rot_180.png" );

disp( "scalare cu 0.4" );

	T = 0.4 * eye( 2 );

	out = inverse_mapping( a, T);
	imwrite( mat2gray( out ), "duck_scal_0.4.png" );

	out = inverse_mapping( b, T) ;
	imwrite( mat2gray( out ), "bird_scal_0.4.png" );

disp( "rotire cu 45" );

	T = [ cos( pi / 4) -sin( pi / 4 ); sin( pi / 4 ) cos( pi / 4 ) ];

	out = inverse_mapping( a, T);
	imwrite( mat2gray( out ), "duck_rot_45.png" );

	out = inverse_mapping( b, T) ;
	imwrite( mat2gray( out ), "bird_rot_45.png" );

disp( "scalare cu 2" );

	T = 2 * eye( 2 );
	
	out = inverse_mapping( a, T);
	imwrite( mat2gray( out ), "duck_scal_2.png" );

	out = inverse_mapping( b, T) ;
	imwrite( mat2gray( out ), "bird_scal_2.png" );

disp( "rotire cu 240" );

	T = [ cos( 4 * pi / 3 ) -sin( 4 * pi / 3 ); sin( 4 * pi / 3 ) cos( 4 * pi / 3 ) ];
	
	 out = inverse_mapping( a, T);
	imwrite( mat2gray( out ), "duck_rot_240.png" );

	out = inverse_mapping( b, T) ;
	imwrite( mat2gray( out ), "bird_rot_240.png" );




