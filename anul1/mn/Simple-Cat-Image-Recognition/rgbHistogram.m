function vector_RGB = rgbHistogram(cale, count_bins)
  
% deschid imaginea ca o matrice de valori cu functia din hint

  imagine = imread(cale);

% pozitia de la care incep valorile nuantelor de culoare corespunzatoare culorii Blue
 
  a = 2 * count_bins;   

% parcurg inervalul [0; count_bins - 1] pentru a afla cate numere respecta formula din pdf-ul temei 1

  for i = 0 : count_bins - 1
  
    [vector_RGB(i + 1) aux] = size(imagine(imagine(:, :, 1)>=(i*256/count_bins) & imagine(:, :, 1)<(i+1)*256/count_bins));
    [vector_RGB(count_bins + i + 1) aux] = size(imagine(imagine(:, :, 2)>=(i*256/count_bins) & imagine(:, :, 2)<(i+1)*256/count_bins));
    [vector_RGB(a + i + 1) aux] = size(imagine(imagine(:, :, 3)>=(i*256/count_bins) & imagine(:, :, 3)<(i+1)*256/count_bins));
  
  endfor
  
endfunction
