function p = product(n,m)
if mod(n,2)==0
    p = (n/2) * (2*m);
elseif mod(n,2)==1
    p = ((n-1)/2) * (2*m) + m;
elseif n==1
    p=m;
end