X=rand(1,8);
maxA=max(X);
minA=min(X);
disp(['The max using MATLAB functions is: ', num2str(maxA)]);
disp(['The min using MATLAB functions is: ', num2str(minA)]);
minB=X(1);
maxB=X(1);
for i=2:length(X)
    if X(i)<minB
        minB=X(i);
    end 
    if X(i)>maxB
        maxB=X(i);
    end
end
disp(['The max using a for loop is: ', num2str(maxB)]);
disp(['The min using a for loop is: ', num2str(minB)]);
maxC=X(1);
minC=X(1);
i=1;
while i<=length(X)
    if X(i)<minC
        minC=X(i);
    end 
    if X(i)>maxC
        maxC=X(i);
    end
    i=i+1;
end 
disp(['The max using a while loop is: ', num2str(maxC)]);
disp(['The min using a while loop is: ', num2str(minC)]);