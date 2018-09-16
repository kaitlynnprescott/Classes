v=input('Enter the velocity: ','s');
vnum=str2num(v);
if isempty(vnum)
    disp('Velocity must be a number');
    return 
elseif vnum<0
    disp('Velocity must be positive');
    return
    %if the velocity does not meet the requirements, you cannot continue
    %with the code
end
f=input('Enter the friction: ','s');
fnum=str2num(f);
if isempty(fnum)
    disp('Friction must be a number');
    return
elseif fnum<.1 || fnum>.9
    disp('Friction must be in [0.1,0.9]');
    return
    %if the friction does not meet the requirements, you cannot continue
    %with the code
end
g=32.2;
G=input('Enter the roadway grade as a decimal percentage: ','s');
Gnum=str2num(G);
if isempty(Gnum)
    disp('Grade must be a number');
    return
elseif  Gnum<-1 || Gnum>1
    disp('Grade must be in [-1,1]');
    return
    %if the road grade does not meet the requirements, you cannot continue
    %with the code
end
if (fnum+Gnum)<0
    disp('(f+G) cannot be negative');
    return
elseif (fnum+Gnum)==0
    disp('Cannot divide by 0');
    return
    %the final equation for braking distance must make sense, and a
    %negative braking distance does not make sense, and you cannot divide
    %by zero
end
d=(vnum.^2)/(2*g*(fnum+Gnum));
disp(['The braking distance in feet is: ',num2str(d)])