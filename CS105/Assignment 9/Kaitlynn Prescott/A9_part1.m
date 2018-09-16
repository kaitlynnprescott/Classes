N=input('Enter vector length: ');
sum=0;
for i=1:N
    x(i)=input('Enter a number: ');
    X(i)=x(i)^2;
    sum=sum+X(i);    
end
rmsavg=sqrt((sum)/N);
disp(['The rms average is: ', num2str(rmsavg)]);
