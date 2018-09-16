v = input('Enter the velocity: ', 's');
vnum = str2num(v);
while isempty(vnum) || vnum < 0 
    v = input('Enter a positive number for velocity: ', 's');
    vnum = str2num(v);
end
f = input('Enter the friction: ', 's');
fnum = str2num(f);
while isempty(fnum) || fnum < .1 || fnum > .9 
    f = input('Enter a number between 0.1 and 0.9 for friction: ', 's');
    fnum = str2num(f);
end
G = input('Enter the road grade: ', 's');
Gnum = str2num(G);
while isempty(Gnum) || Gnum < -1 || Gnum > 1 
    G = input('Enter the road grade(number between -1 and 1): ', 's');
    Gnum = str2num(G);
end
while (fnum + Gnum) <= 0
    disp('Error: (f + G) < 0 || (f + G) == 0');
    f = input('Enter the friction: ','s');
    fnum = str2num(f);
    while isempty(fnum) || fnum < .1 || fnum > .9 
        f = input('Enter a number between 0.1 and 0.9 for friction: ', 's');
        fnum = str2num(f);
    end
    G = input('Enter the road grade: ', 's');
    Gnum = str2num(G);
    while isempty(Gnum) || Gnum < -1 || Gnum > 1
        G = input('Enter the road grade(number between -1 and 1): ', 's');
        Gnum = str2num(G);
    end
end
d = vnum^2 / (2*32.2*(fnum + Gnum));
disp(['The stopping distance is: ' , num2str(d), 'ft']);
