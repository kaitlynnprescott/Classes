function canny_edges(max_hysteresis_thresh, min_hysteresis_thresh,sigma);

%%INIT VARIABLES:
%%Read in image:
ORIGINAL=imread('kangaroo.pgm');  
%%Convert to double:
ORIGINAL=im2double(ORIGINAL);    
%%Save height and width
[H,W]=size(ORIGINAL);         

max_hysteresis_thresh = 1.5;
min_hysteresis_thresh = 0.05;
sigma = 1;

% Derivatives in x and y
x_deriv=zeros(H,W);              
y_deriv=zeros(H,W);

% Gaussian kernel
kernel_size = 6*sigma+1;         
adjust = ceil(kernel_size/2);

Y_GAUSS=zeros(kernel_size, kernel_size);
X_GAUSS=zeros(kernel_size, kernel_size);
% Create gaussian kernels based on the given sigma.
for i=1:kernel_size
    for iiii=1:kernel_size
        Y_GAUSS(i,iiii) = -((i-((kernel_size-1)/2)-1)/(2*pi*sigma^3)) ...
            * exp(-((i-((kernel_size-1)/2)-1)^2 + ...
            (iiii-((kernel_size-1)/2)-1)^2 )/(2*sigma^2));
    end
end

for i=1:kernel_size
    for iiii=1:kernel_size
        X_GAUSS(i,iiii) = -((iiii-((kernel_size-1)/2)-1)/(2*pi*sigma^3))...
            * exp(-((i-((kernel_size-1)/2)-1)^2 + ...
            (iiii-((kernel_size-1)/2)-1)^2)/(2*sigma^2));
    end
end

GRADIENT = zeros(H,W);       
non_max = zeros(H,W);     
post_hysteresis = zeros(H,W); 

%%Image Derivatives:
for r=1+ceil(kernel_size/2):H-ceil(kernel_size/2)  
    for c=1+ceil(kernel_size/2):W-ceil(kernel_size/2)  
        ref_row = r-ceil(kernel_size/2); 
        ref_col = c-ceil(kernel_size/2); 
        for yyy=1:kernel_size  
            for yyy_col=1:kernel_size  
                x_deriv(r,c) = x_deriv(r,c) + ...
                    ORIGINAL(ref_row+yyy-1, ref_col+yyy_col-1)*X_GAUSS(yyy,yyy_col);
            end
        end
    end
end

for r=1+ceil(kernel_size/2):H-ceil(kernel_size/2)  
    for c=1+ceil(kernel_size/2):W-ceil(kernel_size/2) 
        ref_row = r-ceil(kernel_size/2); 
        ref_col = c-ceil(kernel_size/2); 
        for yyy=1:kernel_size  
            for yyy_col=1:kernel_size 
                y_deriv(r,c) = y_deriv(r,c) + ...
                    ORIGINAL(ref_row+yyy-1, ref_col+yyy_col-1)*Y_GAUSS(yyy,yyy_col);
            end
        end
    end
end

%%Compute the gradient magnitufde based on derivatives in x and y:
for r=1+ceil(kernel_size/2):H-ceil(kernel_size/2)  
    for c=1+ceil(kernel_size/2):W-ceil(kernel_size/2)  
        GRADIENT(r,c) = sqrt (x_deriv(r,c)^2 + y_deriv(r,c)^2 );
    end
end

%%Perform Non maximum suppression:
non_max = GRADIENT;
for r=1+ceil(kernel_size/2):H-ceil(kernel_size/2) 
    for c=1+ceil(kernel_size/2):W-ceil(kernel_size/2)  
        %%quantize:
        if (x_deriv(r,c) == 0) 
            tangent = 5;       
        else
            tangent = (y_deriv(r,c)/x_deriv(r,c));
        end

        if (-0.4142<tangent && tangent<=0.4142)
            if(GRADIENT(r,c)<GRADIENT(r,c+1) || GRADIENT(r,c)<GRADIENT(r,c-1))
                non_max(r,c)=0;
            end
        end

        if (0.4142<tangent && tangent<=2.4142)
            if(GRADIENT(r,c)<GRADIENT(r-1,c+1) || GRADIENT(r,c)<GRADIENT(r+1,c-1))
                non_max(r,c)=0;
            end
        end

        if ( abs(tangent) >2.4142)
            if(GRADIENT(r,c)<GRADIENT(r-1,c) || GRADIENT(r,c)<GRADIENT(r+1,c))
                non_max(r,c)=0;
            end
        end
        
        if (-2.4142<tangent && tangent<= -0.4142)
            if(GRADIENT(r,c)<GRADIENT(r-1,c-1) || GRADIENT(r,c)<GRADIENT(r+1,c+1))
                non_max(r,c)=0;
            end
        end
    end
end

post_hysteresis = non_max;

for r=1+ceil(kernel_size/2):H-ceil(kernel_size/2)  
    for c=1+ceil(kernel_size/2):W-ceil(kernel_size/2)  
        if(post_hysteresis(r,c)>=max_hysteresis_thresh) 
            post_hysteresis(r,c)=1;
        end
        
        if(post_hysteresis(r,c)<max_hysteresis_thresh && post_hysteresis(r,c)>=min_hysteresis_thresh) 
            post_hysteresis(r,c)=2;
        end

        if(post_hysteresis(r,c)<min_hysteresis_thresh) 
            post_hysteresis(r,c)=0;
        end 
    end
end

vvvv = 1; 
while (vvvv == 1)
    vvvv = 0;
    for r=1+ceil(kernel_size/2):H-ceil(kernel_size/2)  
        for c=1+ceil(kernel_size/2):W-ceil(kernel_size/2)  
            if (post_hysteresis(r,c)>0)      
                if(post_hysteresis(r,c)==2) 
                    if( post_hysteresis(r-1,c-1)==1 || post_hysteresis(r-1,c)==1 || post_hysteresis(r-1,c+1)==1 || post_hysteresis(r,c-1)==1 ||  post_hysteresis(r,c+1)==1 || post_hysteresis(r+1,c-1)==1 || post_hysteresis(r+1,c)==1 || post_hysteresis(r+1,c+1)==1 ) 
                        post_hysteresis(r,c)=1;
                        vvvv = 1;
                    end
                end
            end
        end
    end
end

for r=1+ceil(kernel_size/2):H-ceil(kernel_size/2) 
    for c=1+ceil(kernel_size/2):W-ceil(kernel_size/2)  
        if(post_hysteresis(r,c)==2) 
            post_hysteresis(r,c)=0;
        end   
    end
end

imwrite(ORIGINAL,'original_image_kangaroo.jpg');                        
imwrite(x_deriv,'x_deriv_kangaroo.jpg');            
imwrite(y_deriv,'y_deriv_kangaroo.jpg');            
imwrite(GRADIENT,'gradient_kangaroo.jpg');       
imwrite(non_max,'non_max_supr_kangaroo.jpg');      
