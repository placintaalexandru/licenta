function [vector_HSV] = hsvHistogram(cale, count_bins)

  imagine = imread(cale); %deschid imaginea in reprezentare RGB
  
% posizita de la care incep valorile corespunatoare matricei V din reprezentarea HSV

  a = 2 * count_bins;

% extrag matricele de nuante pentru fiecare culoare din reprezentarea RGB

  [H S V] = RGB2HSV(imagine(:, :, 1), imagine(:, :, 2), imagine(:, :, 3));

% parcurg intervalul [0; count_bins - 1] pentru a numara cate elemente respecta formula din pdf-ul temei 1
 
  for i = 0 : count_bins - 1
  
    [vector_HSV(i + 1) aux] = size(H(H >= double(i*101)/count_bins & H < double((i+1)*101)/count_bins));
    [vector_HSV(count_bins + i + 1) aux] = size(S(S >= i*101/count_bins & S < (i+1)*101/count_bins));
    [vector_HSV(a + i + 1) aux] = size(V(V >= i*101/count_bins & V < (i+1)*101/count_bins));
    
  endfor

endfunction




