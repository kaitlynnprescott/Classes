clear variables;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Read in images from file. %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

red = imread('red.pgm');
% imshow(red);
plane = imread('plane.pgm');
% imshow(plane);
kangaroo = imread('kangaroo.pgm');
% imshow(kangaroo);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Gaussian Filtering of images. %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% add noise to image
Gr = imnoise(red, 'Gaussian', 0.04, 0.003);
Gp = imnoise(plane, 'Gaussian', 0.04, 0.003);
Gk = imnoise(kangaroo, 'Gaussian', 0.04, 0.003);
R = double(Gr);
P = double(Gp);
K = double(Gk);

% Standard deviation and window size
sigma = 3;
sz = 5;

[x,y] = meshgrid(-sz:sz, -sz:sz);
M = size(x,1)-1;
N = size(y,1)-1;
e_exp = -(x.^2 + y.^2)/(2*sigma^2);
kern = exp(e_exp)/(2*pi*sigma^2);

% initialize output
outputR = zeros(size(R));
% pad vector with zeros
R = padarray(R,[sz sz]);

% convolution (red)
for i = 1:size(R,1)-M
    for j = 1:size(R,2)-N
        tmp = R(i:i+M, j:j+N).*kern;
        outputR(i,j) = sum(tmp(:));
    end
end

% red image without noise after gaussian blur
outputR = uint8(outputR);
figure,imshow(outputR);

% convolution (plane)
outputP = zeros(size(P));
% pad vector with zeros
P = padarray(P,[sz sz]);

for i = 1:size(P,1)-M
    for j = 1:size(P,2)-N
        tmp = P(i:i+M, j:j+N).*kern;
        outputP(i,j) = sum(tmp(:));
    end
end

% plane image without noise after gaussian blur
outputP = uint8(outputP);
figure,imshow(outputP);

% convolution (kangaroo)
outputK = zeros(size(K));
% pad vector with zeros
K = padarray(K,[sz sz]);

for i = 1:size(K,1)-M
    for j = 1:size(K,2)-N
        tmp = K(i:i+M, j:j+N).*kern;
        outputK(i,j) = sum(tmp(:));
    end
end

% kangaroo image without noise after gaussian blur
outputK = uint8(outputK);
figure,imshow(outputK);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Compute Gradients with Sobel Filter. %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

outputR = red;
outputP = plane;
outputK = kangaroo;
R = double(red);
P = double(plane);
K = double(kangaroo);


sobel_x = [-1 0 1; -2 0 2; -1 0 1];
sobel_y = [-1 -2 -1; 0 0 0; 1 2 1];


for i = 1:size(R,1)-2
    for j = 1:size(R,2)-2
        % Apply Sobel Filter
        R_Gx = sum(sum(sobel_x.*R(i:i+2,j:j+2)));
        R_Gy = sum(sum(sobel_y.*R(i:i+2,j:j+2)));
        % Gradient
        outputR(i+1,j+1) = sqrt(R_Gx.^2+R_Gy.^2);
    end
end

for i = 1:size(P,1)-2
    for j = 1:size(P,2)-2
        % Apply Sobel Filter
        P_Gx = sum(sum(sobel_x.*P(i:i+2,j:j+2)));
        P_Gy = sum(sum(sobel_y.*P(i:i+2,j:j+2)));
        % Gradient
        outputP(i+1,j+1) = sqrt(P_Gx.^2+P_Gy.^2);
    end
end

for i = 1:size(K,1)-2
    for j = 1:size(K,2)-2
        % Apply Sobel Filter
        K_Gx = sum(sum(sobel_x.*K(i:i+2,j:j+2)));
        K_Gy = sum(sum(sobel_y.*K(i:i+2,j:j+2)));
        % Gradient
        outputK(i+1,j+1) = sqrt(K_Gx.^2+K_Gy.^2);
    end
end

% Compute edge detection for each image 

% Red
rthreshold = 250;
figure,imshow(outputR);
title('Red Sobel Gradient');
outputR = max(outputR, rthreshold);
for i = 1:size(R,1)-2
    for j = 1:size(R,2)-2
        if outputR(i,j) == round(rthreshold)
            outputR(i,j) = 0;
        end
    end
end
outputR = uint8(outputR);
figure,imshow(outputR);
title('Red Edge Detected Image');

% Plane
pthreshold = 100;
figure,imshow(outputP);
title('Plane Sobel Gradient');
outputP = max(outputP, pthreshold);
for i = 1:size(P,1)-2
    for j = 1:size(P,2)-2
        if outputP(i,j) == round(pthreshold)
            outputP(i,j) = 0;
        end
    end
end
outputP = uint8(outputP);
figure,imshow(outputP);
title('Plane Edge Detected Image');

% Kangaroo
threshold_k = 175;
figure,imshow(outputK);
title('Kangaroo Sobel Gradient');
outputK = max(outputK, threshold_k);
for i = 1:size(K,1)-2
    for j = 1:size(K,2)-2
        if outputK(i,j) == round(kthreshold)
            outputK(i,j) = 0;
        end
    end
end
outputK = uint8(outputK);
figure,imshow(outputK);
title('Kangaroo Edge Detected Image');

% Image obtained using MATLAB function 'edge'
[E,~]=edge(R,'sobel','nothinning');
figure,imshow(E);title('Image obtained using MATLAB function')

[E,~]=edge(P,'sobel','nothinning');
figure,imshow(E);title('Image obtained using MATLAB function')

[E,~]=edge(K,'sobel','nothinning');
figure,imshow(E);title('Image obtained using MATLAB function')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Perform Non-Maximum Suppression. %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

R = double(red);
P = double(plane);
K = double(kangaroo);




