X=rand(1,8);
avg= mean(X);
disp(['The average using MATLAB functions is: ',num2str(avg)]);
sum=0;
for i=1:length(X)
    sum=sum+X(i);
end
avg2=sum/length(X);
disp(['The average using a for loop is: ', num2str(avg2)]);