function main()
    % clear workspace variables
    clear variables;
    
    % read in image
    R = imread('road.png');
%     G = myfilter('gaussian', R, 2, 0);
%     figure, imshow(G), title('gaussian'),
    [R_hess, features] = hessian(R, 2, 30, 3);
    figure, imshow(R_hess), title('Hessian'), hold on;
%     disp(features);
    
%     s = 2 (2 points make a line)
%     d = .25 (inlier threshold 25%)
%     m = 7
%     sigma = 2
%     numlines = 4
    ransac(R, features, 2, .25, 7, 2, 4)
    
    
    [rhodetect, thetadetect, accumulator] = houghdetect(R_hess, 4, 25, 3, 4);
    disp(rhodetect);
    disp(thetadetect);
%     disp(accumulator);
    
end

function output = myfilter(filt, pic, sigma, threshold)
    im = double(pic);
    if strcmp(filt, 'gaussian')
        % window size
        sz = 6*sigma-1;
        % compute gaussian filter 
        [x,y] = meshgrid(-sz:sz, -sz:sz);
        M = size(x,1)-1;
        N = size(y,1)-1;
        e_exp = -(x.^2 + y.^2)/(2*sigma^2);
        kern = exp(e_exp)/(2*pi*sigma^2);
        %normalize:
        if round(sum(sum(kern))) ~= 1
            kern = kern/(sz^2);
        end
        % initialize output
        output = zeros(size(im));
        % pad vector with zeros
        im = padarray(im,[sz sz]);

        % apply gaussian filter
        for i = 1:size(im,1)-M
            for j = 1:size(im,2)-N
                tmp = im(i:i+M, j:j+N).*kern;
                output(i,j) = sum(tmp(:));
            end
        end
    output = uint8(output);    
    end
    
    if strcmp(filt, 'sobel-x')
        sobel_x = [-1 0 1; -2 0 2; -1 0 1];
        for i = 1:size(im,1)-2
            for j = 1:size(im,2)-2
                % Apply Sobel Filter in x direction
                Gx = sum(sum(sobel_x.*im(i:i+2,j:j+2)));
                output(i+1, j+1) = Gx;
            end
        end
        
        % apply threshold at every pixel
        output = max(output, threshold);
        for i = 1:size(im,1)-2
            for j = 1:size(im,2)-2
                if output(i,j) == round(threshold)
                    output(i,j) = 0; 
                    % if not edge, set to black
                end
            end
        end
        output = uint8(output);
    end
    
    if strcmp(filt, 'sobel-y')
        sobel_y = [-1 -2 -1; 0 0 0; 1 2 1];
        for i = 1:size(im,1)-2
            for j = 1:size(im,2)-2
                % Apply Sobel Filter in y direction
                Gy = sum(sum(sobel_y.*im(i:i+2,j:j+2)));
                output(i+1, j+1) = Gy;
            end
        end
        
        % apply threshold at every pixel
        output = max(output, threshold);
        for i = 1:size(im,1)-2
            for j = 1:size(im,2)-2
                if output(i,j) == round(threshold)
                    output(i,j) = 0;
                    % if not edge, set to black
                end
            end
        end
        output = uint8(output);
    end
end

function output = convolve(x,y,im,kern)
    [xmax,ymax] = size(im);
    [kxmax,kymax] = size(kern);
    kxmax = floor(kxmax/2);
    kymax = floor(kymax/2);
    output = int64(0);

    for kx = 1:kxmax-1
        for ky = 1:kymax-1
            ax = kx+x;
            ay = ky+y;
            
            if ax < 0
                ax = 0;
            elseif ax > xmax
                ax = xmax;
            end
            
            if ay < 0
                ay = 0;
            elseif ay > ymax
                ay = ymax;
            end
            sum1 = kern(kxmax+kx,kymax+ky) * im(ax,ay);
            sum2 = kern(kxmax-kx,kymax-ky) * im(ax, ay);
            output = output + sum1 + sum2;
        end
    end
        
end

function Gmag = non_max_suppression(im, Gx, Gy)
    im = double(im);
    Gmag = sqrt(double(Gx.^2 + Gy.^2));
    % Use the angle the gradient falls in to determine what to compare to
    angle = atan2(double(Gy),double(Gx))*180/pi;

    % Perform non-maximum suppression 
    [h,w] = size(im);
    output = zeros(h,w);
    for i=2:h-2 % row
        for j=2:w-2 % col         
            if (angle(i,j)>=-22.5 && angle(i,j)<=22.5) || ...
                (angle(i,j)<-157.5 && angle(i,j)>=-180)
                if (Gmag(i,j) >= Gmag(i,j+1)) && ...
                   (Gmag(i,j) >= Gmag(i,j-1))
                    % If pixel i,j has largest magnitude to those
                    % orthogonal to it, keep it. Otherwise, change it to
                    % black.
                    output(i,j)= Gmag(i,j);
                else
                    output(i,j)=0;
                end
            elseif (angle(i,j)>=22.5 && angle(i,j)<=67.5) || ...
                (angle(i,j)<-112.5 && angle(i,j)>=-157.5)
                if (Gmag(i,j) >= Gmag(i+1,j+1)) && ...
                   (Gmag(i,j) >= Gmag(i-1,j-1))
                    % If pixel i,j has largest magnitude to those
                    % orthogonal to it, keep it. Otherwise, change it to
                    % black.
                    output(i,j)= Gmag(i,j);
                else
                    output(i,j)=0;
                end
            elseif (angle(i,j)>=67.5 && angle(i,j)<=112.5) || ...
                (angle(i,j)<-67.5 && angle(i,j)>=-112.5)
                if (Gmag(i,j) >= Gmag(i+1,j)) && ...
                   (Gmag(i,j) >= Gmag(i-1,j))
                    % If pixel i,j has largest magnitude to those
                    % orthogonal to it, keep it. Otherwise, change it to
                    % black.
                    output(i,j)= Gmag(i,j);
                else
                    output(i,j)=0;
                end
            elseif (angle(i,j)>=112.5 && angle(i,j)<=157.5) || ...
                (angle(i,j)<-22.5 && angle(i,j)>=-67.5)
                if (Gmag(i,j) >= Gmag(i+1,j-1)) && ...
                   (Gmag(i,j) >= Gmag(i-1,j+1))
                    % If pixel i,j has largest magnitude to those
                    % orthogonal to it, keep it. Otherwise, change it to
                    % black.
                    output(i,j)= Gmag(i,j);
                else
                    output(i,j)=0;
                end
            end
        end
    end
    Gmag = NormalizeMatrix(output);
end

function [A] = NormalizeMatrix(A)
    % normalize the matrix for output
    A = A/max(A(:));
end

function [output, features] = hessian(im, sigma, threshold, sz)
    % ensure threshold, sigma, and sz are valid numbers
    if isnan(threshold)
        threshold = 125000;
    end
    if isnan(sigma)
        sigma = 1;
    end
    if isnan(sz)
        sz = 3;
    end
    % run gaussian filter and sobel filters to get derivative operators
    G = myfilter('gaussian', im, sigma, threshold);
    Gx = myfilter('sobel-x', G, sigma, threshold);
    Gy = myfilter('sobel-y', G, sigma, threshold);
    Gxx = myfilter('sobel-x', Gx, sigma, threshold);
    Gxy = myfilter('sobel-y', Gx, sigma, threshold);
    Gyy = myfilter('sobel-y', Gy, sigma, threshold);
    % compute determinant matrix
    determinant = Gxx .* Gyy - (Gxy.^2);
    [X,Y] = size(determinant);
    for i = 1:X
        for j = 1:Y
            % compare determinant to threshold, if its lower than
            % threshold, set to 0.
            if determinant(i,j) < threshold
                determinant(i,j) = 0;
            end
        end
    end
    % compute hessian non-max suppression
    output = hess_suppress(im, determinant, sz);
    % save features (important points)
    featuresx = {};
    featuresy = {};
    for i = 1:X
        for j = 1:Y
            if output(i,j) ~= 0
                featuresx = [featuresx; i];
                featuresy = [featuresy; j];
            end
        end
    end
    [x,y] = size(featuresx);
    features = zeros(x, 2);
    for i =1:x
        features(i, 1) = featuresx{i};
        features(i, 2) = featuresy{i};
    end
end

function output = hess_suppress(im, det, sz)
    [x,y,~] = size(im);
    output = zeros(size(im));
    for i = 1:x-2
        for j = 1:y-2
            % for all points in the image, if the determiniant is not 0 and
            % is greater than or equal to the local max, set output to 1
            if det(i,j) >= localmax(i,j,det,sz) && det(i,j) ~= 0
                output(i,j) = 1;
            end
        end
    end
end

function max_val = localmax(x, y, im, sz)
    sz_len = floor(sz/2);
    [im_x, im_y, z] = size(im);
    % set local min and max (if filter is 3x3, min and max are set so local
    % area is 3x3) and keep in parameters of image for both x and y
    % directions.
    min_x = x-sz_len;
    if min_x < 0
        min_x = 0;
    end
    max_x = x + sz_len + 1;
    if max_x > im_x
        max_x = im_x - 1;
    end
    
    min_y = y-sz_len;
    if min_y < 0
        min_y = 0;
    end
    max_y = y + sz_len + 1;
    if max_y > im_y
        max_y = im_y - 1;
    end
    % find max within neighborhood of pixels
    max_val = im(x,y);
    for i = min_x+1:max_x
        for j = min_y+1:max_y
            max_val = max(im(i,j), max_val);
        end
    end
end

function ransac(im, points, s, d, m, sigma, numlines)
    % points: 2xn matrix of points
    % s: initial number of points (min needed for model)
    % d: inlier threshold 
    % m: minimum number of inliers
    % sigma: gaussian sigma
    % numlines: how many lines to fit
    
    if nargin < 7
        numlines = 4;
    end
    if nargin < 6
        sigma = 1;
    end
    
    % n: number of samples (how many times to run)
    % t: distance threshold (minimum distance to be inlier)
    t = sqrt(3.84 * sigma^2);
    n = log(0.01)/(log(1-(d)^s));
    
    % plot points
%     figure;plot(points(1,:),points(2,:),'o');
%     hold on;
    
    figure, title('Plot Lines');
    hold on;
    for l = 1:numlines
        % total points
        num = size(points,2);
        % initialize best line info
        best_inlier_num = 0;
        best1 = 0;
        best2 = 0;
        b_ind = [];
        % run for n number of samples
        for i = 1:n
            % randomly get 2 points
            ind = randperm(num, s);
            samp = points(:, ind);
            % compute dist between all points with line
            ln = samp(:,2) - samp(:, 1);
            nrm = ln/norm(ln);
            vct = [-nrm(2), nrm(1)];
            dist = vct.*(points - repmat(samp(:,1), 1, num));
            % compute number of inliers within distance threshold
            inlier_ind = find(abs(dist) <= t);
            inliernum = length(inlier_ind);
            % if better model, update best line info
            if inliernum  >= round(m*num) & inliernum > best_inlier_num
                inlie_param = inliernum;
                param1 = (samp(2,2) - samp(2,1))/(samp(1,2) - samp(1,1));
                param2 = param1*samp(2,1) - samp(1,1);
                best_inlier_num = inlie_param;
                best1 = param1;
                best2 = param2;
                b_ind = ind;
            end
        end
        samp = points(b_ind, :);
        im = insertShape(im, 'Line', [samp(1,1) samp(1,2) samp(2,1) samp(2, 2)], ...
            'LineWidth',1,'Color','red');
        imshow(im);
        
        xlim = get(gca,'XLim');
        y1 = best1*xlim(1) + best2;
        y2 = best1*xlim(2) + best2;
        line([xlim(1) xlim(2)],[y1 y2])
        % remove points in best line from points
        points(b_ind, :) = [];
    end
    hold off;
end



function [rhodetect, thetadetect, accumulator] = houghdetect(im, rhostep, thetastep, threshold, numlines)
    % im: hessian image
    % pstep: interval for radius of line
    % thetastep: interval for angle of line
    % threshold: minimum number of pixels belonging to a line
    % numlines: number of lines to detect
    
    if nargin < 4
        threshold = 3;
    end
    if nargin < 5 
        numlines = 4;
    end
    [xmax, ymax] = size(im);
    rho = 1:rhostep:sqrt(xmax^2 + ymax^2);
    theta = 0:thetastep:180-thetastep;
    for ln = 1:numlines
        % voting
        % initialize accumulator array
        accumulator = zeros(length(rho), length(theta));
        % find edge pixels
        [yind, xind] = find(im);
        % repeat for each feature point in image 
        for i = 1:numel(xind)
            tind = 0;
            for ti = theta*pi/180
                tind = tind+1;
                rhoi = xind(i)*cos(ti) + yind(i)*sin(ti);
                if rhoi >= 1 && rhoi <= rho(end)
                    temp = abs(rhoi-rho);
                    mintemp = min(temp);
                    rind = find(temp == mintemp);
                    rind = rind(1);
                    accumulator(rind, tind) = accumulator(rind, tind)+1;
                end
            end
        end
        % find values of local maximum
        maxcount = imregionalmax(accumulator);
        [potrho, pottheta] = find(maxcount == 1);
        tmp = accumulator - threshold;
        % detected line: rho = x cos(theta) + y sin(theta)
        rhodetect = [];
        thetadetect = [];
        for i = 1:numel(potrho)
            if tmp(potrho(i), pottheta(i)) >= 0
                rhodetect = [rhodetect, potrho(i)];
                thetadetect = [thetadetect,pottheta(i)];
            end
        end
        % calculation of lines using radius and angle
        rhodetect = rhodetect * rhostep;
        thetadetect = thetadetect * thetastep;
        
    end
end
