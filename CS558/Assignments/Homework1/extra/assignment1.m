function assignment1()
    % read in images
    red = imread('red.pgm');
%     plane = imread('plane.pgm');
%     kangaroo = imread('kangaroo.pgm');
    
    % run Gaussing filtering
    % add noise to image
    Gr = imnoise(red, 'Gaussian', 0.04, 0.003);
%     Gp = imnoise(plane, 'Gaussian', 0.04, 0.003);
%     Gk = imnoise(kangaroo, 'Gaussian', 0.04, 0.003);
    R = double(Gr);
%     P = double(Gp);
%     K = double(Gk);

    % Standard deviation and window size
    sigma = 3;
    sz = 5;

    [x,y] = meshgrid(-sz:sz, -sz:sz);
%     M = size(x,1)-1;
%     N = size(y,1)-1;
    e_exp = -(x.^2 + y.^2)/(2*sigma^2);
    kern = exp(e_exp)/(2*pi*sigma^2);
    
    outputR = myfilter(kern, R);
    % red image without noise after gaussian blur
    outputR = uint8(outputR);
    figure,imshow(outputR);
end


function [output] = myfilter(filt, im)
    output = zeros(size(im));
    for i = 1:size(im,1)-2
        for j = 1:size(im,2)-2
            tmp = im(i:i+2, j:j+2).*filt;
            output(i,j) = sum(tmp(:));
        end
    end
    return output;
end

