function check12
	path_to_dataset  = 'dataset/';
	path_to_testset  = 'testset/';

	path_to_in_task12 = 'testset/task1-2/';
	path_to_ref_task12 = 'testset/ref/task1-2/';

	eps = 0.01;

	points_task1 = 20;
	points_task2 = 30;
	points_task3 = 30;
	points_task4 = 10;

	x = getImgNames(path_to_in_task12);

	[n d] = size(x);

	total = 0;


	printf('--------------- TASK 1 -----------------\n');
	tic; % start timer
	task1 = 0;
	for i = 1:10
		img = x(i, 1:d);
		in = strcat(path_to_in_task12, img);
		ref = strcat(path_to_ref_task12, strcat(img(1:length(img)-4), '.rgb' ));
		
		if i <= 5
			x_out = rgbHistogram(in, 16);
		else
			x_out = rgbHistogram(in, 20);
		end		
		x_ref = dlmread(ref);



		if (length(x_out) == length(x_ref)) && ( sum ( abs( (x_out - x_ref) ) ) == 0 )
			task1 = task1 + 1;
			printf('Test %d => PASSED\n', i);
		else
			printf('Test %d => FAILED\n', i);
		end	
	
	end
	res = task1 / 10 * points_task1;
	total = total + res;
	printf('Results: %d / %d points\n', res, points_task1);
	toc; % stop timer


	printf('\n');
	printf('--------------- TASK 2 -----------------\n');
	tic; %start timer
	task2 = 0;
	for i = 1:10
		img = x(i, 1:d);
		in = strcat(path_to_in_task12, img);
		ref = strcat(path_to_ref_task12, strcat(img(1:length(img)-4), '.hsv' ));
		x_ref = dlmread(ref);

		if i <= 5
			x_out = hsvHistogram(in, 16);
		else
			x_out = hsvHistogram(in, 20);
		end		
		

        p_out = x_out / sum(x_out);
        p_ref = x_ref / sum(x_ref);

		if (length(x_out) == length(x_ref)) && sum ( abs( (p_out - p_ref) ) < eps ) == length(x_out)
			task2 = task2 + 1;
			printf('Test %d => PASSED\n', i);
		else
			printf('Test %d => FAILED\n', i);
		end	
	
	end
	res = task2 / 10 * points_task2;
	total = total +  res;
	printf('Results: %d / %d points\n', res, points_task2);
	toc; % stop timer

	printf('\n');
	printf('Total score Tasks 1 & 2 ........ %d / 50\n', total);
	printf('\n');

end
