function setup34	
	path_to_dataset  = 'dataset/';
	path_to_testset  = 'testset/';
	fid_params = fopen('utils/params.out', 'w');
	fid_results = fopen('results', 'w');
	no_of_tests = 2;
	
	
	
	fprintf(fid_params, '%d\n', no_of_tests)
	

	% ---------TEST 1 - RGB----------------
	printf('SETUP - using RGB\n');
	hist_type = 'RGB';
	count_bins = 20;

	tic; % start timer
	[X t] = preprocess(path_to_dataset, hist_type, count_bins);
	w = learn(X, t);
	p = evaluate(path_to_testset, w, hist_type,  count_bins);
    time = toc;

    printf('Elapsed time is %f seconds.\n', time);
    fprintf(fid_results, '%f %f\n', p, time);
	fprintf(fid_params, '%s %d\n', 'rgb', count_bins);
	fprintf(fid_params, '%.12f ', w);
	fprintf(fid_params, '\n%f\n', p);
	
	printf('\n');


	% ---------TEST 2 - HSV ---------------
	printf('SETUP - using HSV\n');
	hist_type = 'HSV';
	count_bins = 20;

	tic; % start timer
	[X t] = preprocess(path_to_dataset, hist_type, count_bins);
	w = learn(X, t);
	p = evaluate(path_to_testset, w, hist_type,  count_bins);
    time = toc;

    printf('Elapsed time is %f seconds.\n', time);
    fprintf(fid_results, '%f %f\n', p, time);
	fprintf(fid_params, '%s %d\n', 'hsv', count_bins);
	fprintf(fid_params, '%.12f ', w);
	fprintf(fid_params, '\n%f\n', p);
	
	printf('\n');


	fclose(fid_params);
	fclose(fid_results);
end
